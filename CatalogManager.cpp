//
//  CatalogManager.cpp
//  
//
//  Created by 杨凯 on 15/10/11.
//
//

#include "CatalogManager.h"
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
using std::string;
using std::stringstream;
CatalogManager::CatalogManager(){
    flevel = 0;
}
bool CatalogManager::FindTable(string name,off_t &position){
    map(meta.tablepos,tablehash);
    unsigned int addr = hashFunc(name);
    bool found = false;
    int i = 0;
    while(tablehash[addr].pos!=-1){
        if(tablehash[addr].name == name){
            found = true;
            position = tablehash[addr].pos;
        }
        if(i>HASH_SIZE)
            break;
        i++;
        addr = (addr+1)%HASH_SIZE;
    }
    return found;
}
table_t CatalogManager::FindTable(off_t tablepos){
    table_t table;
    map(tablepos, &table);
    return table;
}

index_t CatalogManager::FindIndex(off_t indexpos){
    index_t index;
    map(indexpos, &index);
    return index;
}
bool CatalogManager::FindIndex(string name, off_t &position){
    map(meta.indexpos,indexhash);
    unsigned int addr = hashFunc(name);
    bool found = false;
    int i = 0;
    while(indexhash[addr].pos!=-1){
        if(indexhash[addr].name == name){
            found = true;
            position = indexhash[addr].pos;
        }
        if(i>HASH_SIZE)
            break;
        i++;
        addr = (addr+1)%HASH_SIZE;
    }
    return found;

}

bool CatalogManager::addIndex(sqlstruct::createindex index,off_t tablepos,off_t indexpos){
    index_t indexnode;
    indexnode.name = index.indexname;
    indexnode.table = index.tablename;
    indexnode.numofcol = index.col.size();
    indexnode.pos = indexpos;
    for(int i = 0;i<indexnode.numofcol;i++){
        indexnode.col[i] = index.col[i];
    }
    map(meta.indexpos,indexhash);
    int addr = hashFunc(indexnode.name);
    int i = 0;
    while(indexhash[addr].pos!=-1){
        if(i>HASH_SIZE)
            break;
        i++;
        addr = (addr+1)%HASH_SIZE;
    }
    if(i>HASH_SIZE){
            return false;
    }
    else {
        size_t size = 2*NAME_LENGTH + MAXNUM_COL*NAME_LENGTH + sizeof(off_t) + sizeof(size_t);
        //size_t isize = sizeof(indexnode);
        off_t pos = Alloc(size);
        indexhash[addr].pos = pos;
        indexhash[addr].name = indexnode.name;
        addIndextoTable(tablepos, indexnode.name);
        unmap(pos, &indexnode);
        unmap(meta.indexpos, indexhash);
        return true;
    }
}

void CatalogManager::addIndextoTable(off_t pos, string name){
    table_t table;
    map(pos,&table);
    table.index[table.numofIndex++] = name;
    unmap(pos, &table);
}

bool CatalogManager::addTable(string name,string createstr){
    table_t tablenode;
    //tablenode.table = table;
    tablenode.createstr = createstr;
    tablenode.numofIndex = 0;
    unsigned int addr = hashFunc(name);
    map(meta.tablepos,tablehash);
    int i = 0;
    while(tablehash[addr].pos!=-1){
        if(i>HASH_SIZE)
            return false;
        i++;
        addr = (addr + 1)%HASH_SIZE;
    }
    size_t size = createstr.length()+ 1 + sizeof(size_t)*2 + MAXNUM_INDEX*NAME_LENGTH + sizeof(off_t);
    off_t pos = Alloc(size);
    tablehash[addr].pos = pos;
    tablehash[addr].name = name;
    unmap(meta.tablepos, tablehash);
    unmap(pos, &tablenode);
    return true;
}
bool CatalogManager::dropTable(string name){
    map(meta.tablepos,tablehash);
    unsigned int addr = hashFunc(name);
    int i = 0;
    while(tablehash[addr].name!=name){
        if(i>HASH_SIZE)
            return false;
        i++;
        addr = (addr + 1) % HASH_SIZE;
    }
    off_t pos = tablehash[addr].pos;
    tablehash[addr].pos = -1;
    tablehash[addr].name = "";
    unmap(meta.tablepos, tablehash);
    table_t table;
    map(pos,&table);
    off_t indexpos;
    for(int i = 0;i<table.numofIndex;i++)
        if(FindIndex(table.index[i], indexpos))
            dropIndex(table.index[i]);
    Unalloc(pos,sizeof(table));
    return true;
}

bool CatalogManager::dropIndex(string name){
    map(meta.indexpos,indexhash);
    unsigned int addr = hashFunc(name);
    int i = 0;
    while(indexhash[addr].name != name){
        if(i>HASH_SIZE)
            return false;
        i++;
        addr = (addr+1)% HASH_SIZE;
    }
    off_t pos = indexhash[addr].pos;
    indexhash[addr].pos = -1;
    indexhash[addr].name = "";
    unmap(meta.indexpos, indexhash);
    index_t index;
    map(pos,&index);
    off_t tablepos;
    if(FindTable(index.table, tablepos)){
        dropIndextoTable(tablepos, index.name);
        Unalloc(pos,sizeof(index));
        return true;
    }
    else return false;
}

void CatalogManager::dropIndextoTable(off_t pos, std::string indexname){
    table_t table;
    map(pos,&table);
    int i;
    for(i = 0;i<table.numofIndex;i++)
        if(table.index[i] == indexname)
            break;
    if(i == table.numofIndex)
        return ;
    for(int j = i;j<table.numofIndex-1;j++)
        table.index[j] = table.index[j+1];
    table.numofIndex--;
    unmap(pos, &table);
}

unsigned int CatalogManager::hashFunc(string value){
    unsigned int seed = 131;
    unsigned int hash = 0;
    for(int i = 0;i<value.length();i++){
        hash = hash*seed + value[i];
    }
    return (hash&0x7fffffff)%HASH_SIZE;
}
/*
void CatalogManager::Openfile(){
    if(flevel == 0){
        fp = fopen(filename.c_str(), "rb+");
    }
    flevel++;
}
void CatalogManager::Closefile(){
    if(flevel == 1){
        fclose(fp);
    }
    flevel--;
}*/

void CatalogManager::map(off_t pos,hash_t *table){
    //size_t indexofblock = pos / BLOCKREMAINDER;
    //size_t index = pos % BLOCKREMAINDER;
    //Openfile();
    char name[NAME_LENGTH];
    off_t position;
    int offset = 0;
    //fseek(fp, pos*BLOCKSIZE, SEEK_SET);
    for(int i = 0;i<HASH_SIZE;i++){
        //fread(name, NAME_LENGTH, 1, fp);
        //fread(&position, sizeof(off_t),1, fp);
        bm->constReadBuffer(filename, pos, name, offset, sizeof(char)*NAME_LENGTH);
        offset += sizeof(char)*NAME_LENGTH;
        bm->constReadBuffer(filename, pos, &position, offset, sizeof(off_t));
        offset += sizeof(off_t);
        stringstream ss;
        ss << name;
        table[i].name = ss.str();
        table[i].pos = position;
    }
}

void CatalogManager::unmap(off_t pos, hash_t *table){
    //size_t indexofblock = pos / BLOCKREMAINDER;
    //size_t index = pos - indexofblock * BLOCKREMAINDER;
    //Openfile();
    char name[NAME_LENGTH];
    //fseek(fp, pos*BLOCKSIZE, SEEK_SET);
    int offset = 0;
    for(int i = 0;i<HASH_SIZE;i++){
        memset(name, 0, NAME_LENGTH);
        strcpy(name,table[i].name.c_str());
        //fwrite(name, sizeof(char)*NAME_LENGTH, 1, fp);
        //fwrite(&(table[i].pos), sizeof(off_t), 1, fp);
        bm->writeBuffer(filename, pos, name, offset, sizeof(char)*NAME_LENGTH);
        offset += sizeof(char)*NAME_LENGTH;
        bm->writeBuffer(filename, pos, &table[i].pos, offset, sizeof(off_t));
        offset += sizeof(off_t);
    }
    bm->save();
}
void CatalogManager::map(off_t pos,table_t *table){
    size_t blockindex = pos / BLOCKREMAINDER;
    size_t blockoffset = pos % BLOCKREMAINDER;
    //Openfile();
    //fseek(fp, indexofblock*BLOCKSIZE+index, SEEK_SET);
    size_t lengthofstr = 0;
    //fread(&(table->pos), sizeof(off_t), 1, fp);
    //fread(&lengthofstr, sizeof(size_t), 1, fp);
    bm->constReadBuffer(filename, blockindex, &(table->pos), blockoffset, sizeof(off_t));
    blockoffset += sizeof(off_t);
    bm->constReadBuffer(filename, blockindex, &lengthofstr, blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    char *createstr = new char[lengthofstr];
    //fread(createstr,sizeof(char)*lengthofstr,1,fp);
    bm->constReadBuffer(filename, blockindex, createstr, blockoffset, sizeof(char)*lengthofstr);
    blockoffset += sizeof(char)*lengthofstr;
    stringstream ss;
    ss.str("");
    ss << createstr;
    table->createstr = ss.str();
    ss.str("");
    int numofindex = 0;
    //fread(&numofindex,sizeof(size_t),1,fp);
    bm->constReadBuffer(filename, blockindex, &numofindex, blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    char name[NAME_LENGTH];
    table->numofIndex = numofindex;
    for(int i = 0;i<numofindex;i++)
    {
        //fread(name,sizeof(char)*NAME_LENGTH,1,fp);
        bm->constReadBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
        ss << name;
        table->index[i] = ss.str();
        ss.str("");
    }
    delete [] createstr;
}

void CatalogManager::unmap(off_t pos, table_t *table){
    size_t blockindex = pos / BLOCKREMAINDER;
    size_t blockoffset = pos % BLOCKREMAINDER;
    //Openfile();
    //fseek(fp, indexofblock*BLOCKSIZE+index, SEEK_SET);
    size_t lengthofstr = table->createstr.size();
    lengthofstr++;
    //fwrite(&(table->pos), sizeof(off_t), 1, fp);
    //fwrite(&lengthofstr, sizeof(size_t), 1, fp);
    bm->writeBuffer(filename, blockindex, &(table->pos), blockoffset, sizeof(off_t));
    blockoffset += sizeof(off_t);
    bm->writeBuffer(filename, blockindex, &lengthofstr, blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    char *createstr = new char [lengthofstr];
    strcpy(createstr,table->createstr.c_str());
    //fwrite(createstr, sizeof(char)*lengthofstr, 1, fp);
    bm->writeBuffer(filename, blockindex, createstr, blockoffset, sizeof(char)*lengthofstr);
    blockoffset += sizeof(char)*lengthofstr;
    delete [] createstr;
    //fwrite(&(table->numofIndex), sizeof(size_t), 1, fp);
    bm->writeBuffer(filename, blockindex, &(table->numofIndex), blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    char name[NAME_LENGTH];
    for(int i = 0;i<table->numofIndex;i++){
        memset(name, 0, NAME_LENGTH);
        strcpy(name, table->index[i].c_str());
        //fwrite(name, sizeof(char)*NAME_LENGTH, 1, fp);
        bm->writeBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
    }
    bm->save();
}

void CatalogManager::map(off_t pos,index_t *indextable){
    size_t blockindex = pos / BLOCKREMAINDER;
    size_t blockoffset = pos % BLOCKREMAINDER;
    //Openfile();
    //fseek(fp, indexofblock*BLOCKSIZE+index, SEEK_SET);
    //fread(&(indextable->pos),sizeof(off_t),1,fp);
    bm->constReadBuffer(filename, blockindex, &(indextable->pos), blockoffset, sizeof(off_t));
    blockoffset += sizeof(off_t);
    char name[NAME_LENGTH];
    stringstream ss;
    ss.str("");
    //fread(name, sizeof(char)*NAME_LENGTH, 1, fp);
    bm->constReadBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
    blockoffset += sizeof(char)*NAME_LENGTH;
    ss << name;
    indextable->name = ss.str();
    ss.str("");
    //fread(name, sizeof(char)*NAME_LENGTH, 1, fp);
    bm->constReadBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
    blockoffset += sizeof(char)*NAME_LENGTH;
    ss << name;
    indextable->table = ss.str();
    ss.str("");
    //fread(&(indextable->numofcol), sizeof(size_t), 1, fp);
    bm->constReadBuffer(filename, blockindex, &(indextable->numofcol), blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    for(int i = 0;i<indextable->numofcol;i++){
        //fread(name, sizeof(char)*NAME_LENGTH, 1, fp);
        bm->constReadBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
        ss << name;
        indextable->col[i] = ss.str();
        ss.str("");
    }
}

void CatalogManager::map(){
    //Openfile();
    //fseek(fp, 0, SEEK_SET);
    //fread(&(meta.tablepos), sizeof(off_t), 1, fp);
    //fread(&(meta.indexpos), sizeof(off_t), 1, fp);
    //fread(&(meta.freeblock), sizeof(off_t), 1, fp);
    //fread(&(meta.head), sizeof(off_t), 1, fp);
    //fread(&(meta.end), sizeof(off_t), 1, fp);
    bm->constReadBuffer(filename, 0, &meta, 0, sizeof(meta));
}

void CatalogManager::unmap(){
    //Openfile();
    //fseek(fp, 0, SEEK_SET);
    //fwrite(&(meta.tablepos), sizeof(off_t), 1, fp);
    //fwrite(&(meta.indexpos), sizeof(off_t), 1, fp);
    //fwrite(&(meta.freeblock), sizeof(off_t), 1, fp);
    //fwrite(&(meta.head), sizeof(off_t), 1, fp);
    //fwrite(&(meta.end), sizeof(off_t), 1, fp);
    bm->writeBuffer(filename, 0, &meta, 0, sizeof(meta));
    bm->save();
}

void CatalogManager::unmap(off_t pos,index_t *indextable){
    size_t blockindex = pos / BLOCKREMAINDER;
    size_t blockoffset = pos % BLOCKREMAINDER;
    //Openfile();
    //fseek(fp, indexofblock*BLOCKSIZE+index, SEEK_SET);
    char name[NAME_LENGTH];
    //fwrite(&(indextable->pos), sizeof(off_t), 1, fp);
    bm->writeBuffer(filename, blockindex, &(indextable->pos), blockoffset, sizeof(off_t));
    blockoffset += sizeof(off_t);
    memset(name, 0, NAME_LENGTH);
    strcpy(name,indextable->name.c_str());
    //fwrite(name, sizeof(char)*NAME_LENGTH, 1, fp);
    bm->writeBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
    blockoffset += sizeof(char)*NAME_LENGTH;
    memset(name, 0, NAME_LENGTH);
    strcpy(name,indextable->table.c_str());
    //fwrite(name, sizeof(char)*NAME_LENGTH, 1, fp);
    //fwrite(&(indextable->numofcol), sizeof(size_t), 1, fp);
    bm->writeBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
    blockoffset += sizeof(char)*NAME_LENGTH;
    bm->writeBuffer(filename, blockindex, &(indextable->numofcol), blockoffset, sizeof(size_t));
    blockoffset += sizeof(size_t);
    for(int i = 0;i<indextable->numofcol;i++){
        memset(name, 0, NAME_LENGTH);
        strcpy(name, indextable->col[i].c_str());
        //fwrite(name, sizeof(char)*NAME_LENGTH, 1, fp);
        bm->writeBuffer(filename, blockindex, name, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
    }
    bm->save();
}

off_t CatalogManager::Alloc(size_t size){
    //Openfile();
    //size_t tsize = sizeof(table);
    size_t blockused = 0;
    bool flag = false;
    off_t indexblock = meta.end;
    if(meta.end == -1)
        flag = true;
    else {
        //fseek(fp, meta.end*BLOCKSIZE, SEEK_SET);
        //fread(&blockused, sizeof(size_t), 1, fp);
        bm->constReadBuffer(filename, meta.end, &blockused, 0, sizeof(size_t));
    }
    if(flag||BLOCKSIZE - blockused <= size){
        if(meta.freeblock == -1){
            if(flag)
                meta.end = STORAGE_START_BLOCK;
            else {
                //ftruncate(fp, BLOCKSIZE*(STORAGE_START_BLOCK + meta.end + 1));
                meta.end++;
            }
            indexblock = meta.end;
        }
        else indexblock = meta.freeblock;
        blockused = BLOCK_HEAD_SIZE + size;
        //fseek(fp, indexblock*BLOCKSIZE, SEEK_SET);
        //fwrite(&blockused, sizeof(size_t), 1, fp);
        bm->writeBuffer(filename, indexblock, &blockused, 0, sizeof(size_t));
        //bm->save();
        unmap();
        return BLOCK_HEAD_SIZE + indexblock*BLOCKREMAINDER;
    }
    else{
        size_t tmp = blockused;
        blockused += size;
        //fseek(fp, meta.end*BLOCKSIZE, SEEK_SET);
        //fwrite(&blockused, sizeof(size_t), 1, fp);
        bm->writeBuffer(filename, meta.end, &blockused, 0, sizeof(size_t));
        unmap();
        return tmp + indexblock*BLOCKREMAINDER;
    }
}

void CatalogManager::Unalloc(off_t pos,size_t size){

}
void CatalogManager::InitFromEmpty(){
    fp = fopen(filename.c_str(),"wb+");
    fclose(fp);
    meta.tablepos = 1;
    meta.indexpos = 2;
    meta.end = -1;
    meta.freeblock = -1;
    //ftruncate(fp, BLOCKSIZE*4);
    off_t sign = -1;
    char str[NAME_LENGTH];
    memset(str, 0, sizeof(char)*NAME_LENGTH);
    //fseek(fp, meta.tablepos*BLOCKSIZE, SEEK_SET);
    int blockindex = meta.tablepos;
    int blockoffset = 0;
    for(int i = 0;i<HASH_SIZE;i++){
        //fseek(fp, sizeof(char)*NAME_LENGTH, SEEK_CUR);
        //fwrite(str, sizeof(char)*NAME_LENGTH, 1, fp);
        //fwrite(&sign, sizeof(off_t), 1, fp);
        bm->writeBuffer(filename, blockindex, str, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
        bm->writeBuffer(filename, blockindex, &sign, blockoffset, sizeof(off_t));
        blockoffset += sizeof(off_t);
        if(BLOCKSIZE - blockoffset < sizeof(char)*NAME_LENGTH + sizeof(off_t)){
            blockindex++;
            blockoffset = 0;
        }
    }
    //fseek(fp, meta.indexpos*BLOCKSIZE, SEEK_SET);
    blockindex = meta.indexpos;
    blockoffset = 0;
    for(int i = 0;i<HASH_SIZE;i++){
        //fseek(fp, sizeof(char)*NAME_LENGTH, SEEK_CUR);
        //fwrite(str, sizeof(char)*NAME_LENGTH, 1, fp);
        //fwrite(&sign, sizeof(off_t), 1, fp);
        bm->writeBuffer(filename, blockindex, str, blockoffset, sizeof(char)*NAME_LENGTH);
        blockoffset += sizeof(char)*NAME_LENGTH;
        bm->writeBuffer(filename, blockindex, &sign, blockoffset, sizeof(off_t));
        blockoffset += sizeof(off_t);
        if(BLOCKSIZE - blockoffset < sizeof(char)*NAME_LENGTH + sizeof(off_t)){
            blockindex++;
            blockoffset = 0;
        }
    }
    bm->save();
    //fclose(fp);
    unmap();
}
sqlstruct::createtable CatalogManager::GetTableSchema(off_t pos){
    table_t table;
    //size_t indexofblock = pos % BLOCKREMAINDER;
   // Openfile();
    map(pos,&table);
    FILE* stream;
    stream = fmemopen((void*)table.createstr.c_str(), table.createstr.length(), "r");
    scanPushBuffer(stream);
    yy::sqlparser parser(*this);
    parser.set_debug_level(false);
    parser.parse();
    //parse(stream);
    fclose(stream);
    scanPopBuffer();
    return ctable;
}

void CatalogManager::Createtable(sqlstruct::createtable &table){
    ctable = table;
}

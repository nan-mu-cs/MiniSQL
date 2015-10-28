//
//  RManager.cpp
//  
//
//  Created by 杨凯 on 15/10/28.
//
//

#include "RManager.h"
#include <vector>
#include <sstream>
using std::string;
using std::vector;
using std::stringstream;
off_t RecordManager::AllocMeta(){
    bool flag = false;
    size_t used = 0;
    size_t size = sizeof(meta_t);
    if(mem.meta_now == -1){
        mem.meta_now = META_START_BLOCK;
        flag = true;
    }
    else {
        bm->constReadBuffer(filepath, mem.meta_now, &used, 0, sizeof(size_t));
    }
    if(flag||used + size > BLOCKSIZE){
        if(!flag){
            if(mem.freelist !=-1)
            {
                mem.meta_now = mem.freelist;
                NextFreeBlock();
            }
            else {
                mem.meta_now = mem.endblock;
                mem.endblock++;
            }
        }
        used = BLOCK_HEADER + size;
        bm->writeBuffer(filepath, mem.meta_now, &used, 0, sizeof(size_t));
        return mem.meta_now*BLOCKREMAINDER + BLOCK_HEADER;
    }
    else {
        size_t tmp = used;
        used += size;
        bm->writeBuffer(filepath, mem.meta_now, &used, 0, sizeof(size_t));
        return mem.meta_now*BLOCKREMAINDER + tmp;
    }
}

off_t RecordManager::AllocRecord(size_t size){
    bool flag = false;
    size_t used = 0;
    off_t sign = -1;
    if(meta.firstblock == -1){
        meta.endblock = meta.firstblock = RECORD_START_BLOCK;
        flag = true;
    }
    if(flag||used + size > BLOCKSIZE){
        if(!flag){
            off_t tmp = meta.endblock;
            if(mem.freelist !=-1){
                meta.endblock = mem.freelist;
                NextFreeBlock();
            }
            else {
                meta.endblock = mem.endblock;
                mem.endblock++;
            }
            bm->writeBuffer(filepath, tmp, &meta.endblock, NEXT_BLOCK_POS, sizeof(off_t));
        }
        bm->writeBuffer(filepath, meta.endblock, &sign, NEXT_BLOCK_POS, sizeof(off_t));
        used = size + BLOCK_HEADER;
        bm->writeBuffer(filepath, meta.endblock, &used, 0, sizeof(size_t));
        return meta.endblock * BLOCKREMAINDER + BLOCK_HEADER;
    }
    else {
        size_t tmp = used;
        used += size;
        bm->writeBuffer(filepath, meta.endblock, &used, 0, sizeof(size_t));
        return meta.endblock * BLOCKREMAINDER + BLOCK_HEADER;
    }
}
void RecordManager::InitFromEmpty(){
    FILE *fp = fopen(filepath.c_str(), "wb+");
    fclose(fp);
    mem.meta_now = -1;
    mem.meta_head = META_START_BLOCK;
    mem.freelist = -1;
    mem.endblock = 1;
    unmap();
}

void RecordManager::InitFromFile(){
    map();
}

void RecordManager::map(){
    bm->constReadBuffer(filepath, 0, &mem, 0, sizeof(mem));
}

void RecordManager::unmap(){
    bm->writeBuffer(filepath, 0, &mem, 0, sizeof(mem));
    bm->save();
}

void RecordManager::map(off_t pos){
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    bm->constReadBuffer(filepath, index, &meta, offset, sizeof(meta_t));
}

void RecordManager::unmap(off_t pos){
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    bm->writeBuffer(filepath, index, &meta, offset, sizeof(meta_t));
}

off_t RecordManager::CreateTable(std::vector<sqlstruct::record_t> table){
    meta.firstblock = meta.endblock = -1;
    off_t pos = AllocMeta();
    meta.head = -1;
    meta.recordsize = 0;
    for(int i = 0;i<table.size();i++){
        if(table[i].data_type == sqlstruct::INTNUM){
            meta.recordsize += sizeof(int);
        }
        else if(table[i].data_type == sqlstruct::FLOATNUM){
            meta.recordsize += sizeof(float);
        }
        else {
            meta.recordsize += sizeof(char)*(table[i].data_type - sqlstruct::CHAR + 1);
        }
    }
    meta.recordsize += sizeof(short) + sizeof(off_t);
    unmap(pos);
    return pos;
}

off_t RecordManager::InsertRecord(off_t tablepos, std::vector<sqlstruct::insertitem> item){
    map(tablepos);
    off_t pos = AllocRecord(meta.recordsize);
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    short del = 0;
    bm->writeBuffer(filepath, index, &del, offset, sizeof(short));
    offset += sizeof(short);
    off_t next = meta.head;
    meta.head = pos;
    bm->writeBuffer(filepath, index, &next, offset, sizeof(off_t));
    offset += sizeof(off_t);
    unmap(tablepos);
    unmap(pos, item);
    /*
    for(int i = 0;i<item.size();i++){
        if(item[i].data_type == sqlstruct::INTNUM){
            int value = atoi(item[i].value.c_str());
            bm->writeBuffer(filepath, index, &value, offset, sizeof(int));
            offset += sizeof(int);
        }
        else if(item[i].data_type == sqlstruct::FLOATNUM){
            float value = atof(item[i].value.c_str());
            bm->writeBuffer(filepath, index, &value, offset, sizeof(float));
            offset += sizeof(float);
        }
        else {
            size_t size = item[i].data_type - sqlstruct::CHAR +1;
            char *str = new char [size];
            strcpy(str, item[i].value.c_str());
            bm->writeBuffer(filepath, index, &str,
                            offset, sizeof(char)*size);
            offset += sizeof(char)*size;
        }
    }*/
    return pos;
}
void RecordManager::unmap(off_t pos,std::vector<sqlstruct::insertitem> &record){
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    offset += sizeof(short) + sizeof(off_t);
    for(int i = 0;i<record.size();i++){
        if(record[i].data_type == sqlstruct::INTNUM){
            int value = atoi(record[i].value.c_str());
            bm->writeBuffer(filepath, index, &value, offset, sizeof(int));
            offset += sizeof(int);
        }
        else if(record[i].data_type == sqlstruct::FLOATNUM){
            float value = atof(record[i].value.c_str());
            bm->writeBuffer(filepath, index, &value, offset, sizeof(float));
            offset += sizeof(float);
        }
        else {
            size_t size = record[i].data_type - sqlstruct::CHAR +1;
            char *str = new char [size];
            strcpy(str, record[i].value.c_str());
            bm->writeBuffer(filepath, index, str,
                            offset, sizeof(char)*size);
            offset += sizeof(char)*size;
            delete str;
        }
    }
    bm->save();
}
void RecordManager::map(off_t pos,std::vector<sqlstruct::record_t> table,std::vector<std::string> &record){
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    stringstream ss;
    offset += sizeof(short) + sizeof(off_t);
    for(int i = 0;i<table.size();i++){
        if(table[i].data_type == sqlstruct::INTNUM){
            int value = 0;
            bm->constReadBuffer(filepath, index, &value, offset, sizeof(int));
            offset += sizeof(int);
            ss.str("");
            ss << value;
            record.push_back(ss.str());
        }
        else if(table[i].data_type == sqlstruct::FLOATNUM){
            float value = 0;
            bm->constReadBuffer(filepath, index, &value, offset, sizeof(float));
            offset += sizeof(float);
            ss.str("");
            ss << value;
            record.push_back(ss.str());
        }
        else {
            size_t size = table[i].data_type - sqlstruct::CHAR + 1;
            char *str = new char [size];
            bm->constReadBuffer(filepath, index, str, offset, sizeof(char)*size);
            offset += sizeof(char)*size;
            ss.str("");
            ss << str;
            record.push_back(ss.str());
            delete str;
        }
    }
}
bool RecordManager::evalExpr(sqlstruct::ele_t *v1,int oper,sqlstruct::ele_t *v2){
    if(v1 == NULL||v2 == NULL)
        return true;
    if(v1->type >= sqlstruct::CHAR&&(v2->type == sqlstruct::INTNUM||v2->type == sqlstruct::FLOATNUM))
        return false;
    if(v2->type >= sqlstruct::CHAR &&(v1->type == sqlstruct::INTNUM||v1->type == sqlstruct::FLOATNUM))
        return false;
    float nv1,nv2;
    nv1 = nv2 = 0;
    if(v1->type == sqlstruct::INTNUM||v1->type == sqlstruct::FLOATNUM)
        nv1 = atof(v1->value.c_str());
    if(v2->type == sqlstruct::INTNUM||v2->type == sqlstruct::FLOATNUM)
        nv2 = atof(v2->value.c_str());
    switch (oper) {
        case sqlstruct::LESS:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value < v2->value;
            else return nv1 < nv2;
            break;
        case sqlstruct::LESSOREQUAL:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value <= v2->value;
            else return nv1 <= nv2;
            break;
        case sqlstruct::EQUAL:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value == v2->value;
            else return nv1 == nv2;
            break;
        case sqlstruct::GREAT:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value > v2->value;
            else return nv1 > nv2;
            break;
        case sqlstruct::GREATOREQUAL:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value >= v2->value;
            else return nv1 >= nv2;
            break;
        case sqlstruct::NOTEQUAL:
            if(v1->type >= sqlstruct::CHAR)
                return v1->value != v2->value;
            else return nv1 != nv2;
            break;
        default:
            break;
    }
    return true;
}
bool RecordManager::evalAST(vector<string> record,sqlstruct::astree *root,std::vector<sqlstruct::record_t> table){
    if(root == NULL)
        return true;
    else if(!root->isleaf){
        if(root->operate == sqlstruct::NOT){
            if(root->left == NULL)
                return true;
            if(root->left->isleaf){
                sqlstruct::ele_t ele;
                if(root->left->value.type == sqlstruct::VARIABLE)
                {
                    int index = atoi(root->left->value.value.c_str());
                    ele.value = record[index];
                    ele.type = table[index].data_type;
                    return evalExpr(&ele, sqlstruct::NOT);
                }
            }
            else return !evalAST(record, root->left, table);
        }
        else {
            switch (root->operate) {
                case sqlstruct::AND:
                    return evalAST(record, root->left, table)&&evalAST(record, root->right, table);
                    break;
                case sqlstruct::OR:
                    return evalAST(record, root->left, table)||evalAST(record, root->right, table);
                case sqlstruct::LESS:
                case sqlstruct::LESSOREQUAL:
                case sqlstruct::EQUAL:
                case sqlstruct::GREAT:
                case sqlstruct::GREATOREQUAL:
                case sqlstruct::NOTEQUAL:
                    {
                        sqlstruct::ele_t v1,v2;
                        if(root->left->value.type == sqlstruct::VARIABLE)
                        {
                            int i = atoi(root->left->value.value.c_str());
                            v1.value = record[i];
                            v1.type = table[i].data_type;
                        }
                        else v1 = root->left->value;
                        if(root->right->value.type == sqlstruct::VARIABLE){
                            int i = atoi(root->right->value.value.c_str());
                            v2.value = record[i];
                            v2.type = table[i].data_type;
                        }
                        else v2 = root->right->value;
                        return evalExpr(&(v1), root->operate,&(v2));
                    }
                default:
                    return true;
            }
        }
    }
    return true;
}
vector<vector<string>> RecordManager::Search(off_t tablepos,vector<sqlstruct::record_t> table,sqlstruct::astree *root)
{
    map(tablepos);
    vector<vector<string>> result;
    off_t next = meta.head;
    short del = 0;
    while(next!=-1){
        int index = next / BLOCKREMAINDER;
        int offset = next % BLOCKREMAINDER;
        off_t tmp = next;
        bm->constReadBuffer(filepath, index, &del, offset, sizeof(short));
        offset += sizeof(short);
        bm->constReadBuffer(filepath, index, &next, offset, sizeof(off_t));
        offset += sizeof(off_t);
        if(del == 1)
            continue;
        vector<string> record;
        map(tmp, table, record);
        if(evalAST(record, root, table))
            result.push_back(record);
    }
    return result;
}

size_t RecordManager::DeleteRecord(off_t tablepos,vector<sqlstruct::record_t> table,sqlstruct::astree *root){
    size_t result = 0;
    map(tablepos);
    off_t next = meta.head;
    short del = 0;
    while(next!=-1){
        int index = next / BLOCKREMAINDER;
        int offset = next % BLOCKREMAINDER;
        off_t tmp = next;
        bm->constReadBuffer(filepath, index, &del, offset, sizeof(short));
        offset += sizeof(short);
        bm->constReadBuffer(filepath, index, &next, offset, sizeof(off_t));
        offset += sizeof(off_t);
        if(del == 1)
            continue;
        vector<string> record;
        map(tmp, table, record);
        if(evalAST(record, root, table))
        {
            result++;
            DeleteRecordNode(tmp);
        }
    }
    return result;
}

void RecordManager::DeleteRecordNode(off_t pos){
    int index = pos / BLOCKREMAINDER;
    int offset = pos % BLOCKREMAINDER;
    short del = 1;
    bm->writeBuffer(filepath, index, &del, offset, sizeof(short));
    bm->save();
}

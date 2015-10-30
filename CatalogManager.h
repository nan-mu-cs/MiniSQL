//
//  CatalogManager.h
//  
//
//  Created by 杨凯 on 15/10/11.
//
//

#ifndef ____CatalogManager__
#define ____CatalogManager__

#include <stdio.h>//
#include "sqlstruct.h"
#include "sqlparser_driver.hh"
#include "BufferManager.hpp"
using namespace catalog;
class CatalogManager:public sqlparser_driver{
private:
    meta_t meta;
    hash_t tablehash[HASH_SIZE],indexhash[HASH_SIZE];
    FILE *fp;
    int flevel;
    std::string filename = "/Users/andyyang/Documents/MiniSQL/MiniSQL/test.txt";
    void addIndextoTable(off_t tablepos,std::string name);
    void dropIndextoTable(off_t tablepos,std::string name);
    void map(off_t position,hash_t *hashtable);
    void map(off_t position,table_t *table);
    void map(off_t postion,index_t *index);
    void map();
    void unmap(off_t position,table_t *table);
    void unmap(off_t position,hash_t *hashtable);
    void unmap(off_t position,index_t *index);
    void unmap();
    //BKDR hash
    unsigned int hashFunc(std::string);
    off_t Alloc(size_t size);
    //off_t Alloc(table_t table);
    void Unalloc(off_t pos,size_t size);
    BufferManager *bm;
    //void Unalloc(table_t table);

    /*
    struct tablelist_t{
        char name[NAME_LENGTH];
        off_t positon;
        off_t next;
    };
    struct indexlist_t{
        char name[NAME_LENGTH];
        char table[NAME_LENGTH];
        char attr[NAME_LENGTH];
        off_t next;
    };
    struct meta_t{
        size_t size;
        off_t firstTable;
        off_t firstIndex;
    } meta;
    struct index_t{
        char indexkey[NAME_LENGTH];
        off_t position;
    };
    struct col_t{
        char name[NAME_LENGTH];
        int datatype;
        int attr;
    };
    struct table_t{
        size_t numofcol;
        size_t sizeofPrimarykey;
        size_t sizeofIndex;
        char (*primaykey)[NAME_LENGTH];
        index_t *index;
        col_t *col;
    };
    bool FindTable(std::string name,off_t &position);
    bool FindIndex(std::string name,off_t &position);
    void map(off_t position,struct tablelist_t &table);
    void map(off_t position,struct indexlist_t &index);
    */
public:
    CatalogManager();
    /*open catalog file*/
    //void Openfile();
    /*close catalog file*/
    //void Closefile();
    /*add index into catalog, type createindex is define in sqlstruct.h, pos is the addr of head of bpt*/
    bool addIndex(sqlstruct::createindex index,off_t tablepos,off_t indexpos);
    /*add table into catalog,name is table name,createstr is the sql cmd that create the table*/
    bool addTable(std::string name,std::string createstr);
    /*find table named name, return exist or not and the addr in catalog file*/
    bool FindTable(std::string name,off_t &position);
    //void UpdateTable(off_t tablepos,table_t &table){unmap(tablepos, table);}
    table_t FindTable(off_t tablepos);
    /*find index named name, return exist or not and the addr in catalog file*/
    bool FindIndex(std::string name,off_t &position);
    index_t FindIndex(off_t indexpos);
    /*get table info , createtable is define in sqlstruct.h, pos is the addr of catalog that store the table*/
    sqlstruct::createtable GetTableSchema(off_t pos);
    /*drop table named name*/
    bool dropTable(std::string name);
    /*drop table named name*/
    bool dropIndex(std::string name);
    /*do some basic setting, using it when the first time construct db**/
    void InitFromEmpty();
    /*after first time construct db, then every time initialize CatalogManager, call this func*/
    void InitFromFile(){map();};
    sqlstruct::createtable ctable;
    //size_t hashFindName(std::string name);
    //size_t hashFindPos(std::string name);
    void Createtable(sqlstruct::createtable &table);
    void SetBuffer(BufferManager &bm){this->bm = &bm;}
    ~CatalogManager(){unmap();}
};
#endif /* defined(____CatalogManager__) */

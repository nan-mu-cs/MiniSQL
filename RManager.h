//
//  RManager.h
//  
//
//  Created by 杨凯 on 15/10/28.
//
//

#ifndef ____RManager__
#define ____RManager__

#include <stdio.h>
#include "BufferManager.hpp"
#include "sqlstruct.h"
#include "RManager.h"
class RecordManager{
#define BLOCKSIZE 4096
#define BLOCKREMAINDER 10000
#define META_START_BLOCK 1
#define RECORD_START_BLOCK 2
#define BLOCK_HEADER 16
#define NEXT_BLOCK_POS 8
public:
    struct mem_t{
        off_t meta_head,meta_now;
        //off_t record_head,record_now;
        off_t freelist,endblock;
    }mem;
    struct meta_t{
        size_t size;
        off_t firstblock;
        off_t endblock;
        off_t head;
        size_t recordsize;
    }meta;
    BufferManager *bm;
    std::string filepath = "/Users/andyyang/Documents/MiniSQL/MiniSQL/table.txt";
    off_t CreateTable(std::vector<sqlstruct::record_t> table);
    off_t InsertRecord(off_t tablepos,std::vector<sqlstruct::insertitem> item);
    std::vector<std::vector<std::string>> Search(off_t tablepos,
                                            std::vector<sqlstruct::record_t> table,sqlstruct::astree *root);
    size_t DeleteRecord(off_t tablepos,std::vector<sqlstruct::record_t> table,sqlstruct::astree *root);
    void DeleteRecordNode(off_t pos);
    void unmap(off_t pos,std::vector<sqlstruct::insertitem> &record);
    void map(off_t pos,std::vector<sqlstruct::record_t> table,std::vector<std::string> &record);
    bool evalAST(vector<string> record,sqlstruct::astree *root,std::vector<sqlstruct::record_t> table);
    bool evalExpr(sqlstruct::ele_t *v1,int oper,sqlstruct::ele_t *v2 = NULL);
    off_t DeleteTable();
    off_t AllocMeta();
    off_t AllocRecord(size_t size);
    void map();
    void unmap();
    void map(off_t pos);
    void unmap(off_t pos);
    void InitFromFile();
    void InitFromEmpty();
    void NextFreeBlock(){mem.freelist = -1;}
    void SetBuffer(BufferManager &buffer){bm = &buffer;}
    RecordManager(off_t pos){map();map(pos);}
    RecordManager(){ bm = NULL;}
};
#endif /* defined(____RManager__) */

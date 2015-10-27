//
//  RecordManager.hpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/20/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#ifndef RecordManager_hpp
#define RecordManager_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "BufferManager.hpp"
#include "SelectValue.hpp"

using namespace std;
extern BufferManager bm;

class recordPointer{
public:
    int blockNum; // blockNum == -1 : NULL pointer
    unsigned short offset;
    recordPointer(){}
    recordPointer(int blockNumInput, unsigned short offsetInput){
        blockNum = blockNumInput;
        offset = offsetInput;
    }
};


class condition{
public:
    int attr_startPos;
    valueType type;
    SelectOp op;
    selectValue value;
    condition(int aPos, valueType typeInput, SelectOp o, selectValue v){
        attr_startPos = aPos;
        type = typeInput;
        op = o;
        value = v;
    }
};


//each record structure: (双向链表）
//file head: Record Size + Empty List Head
//nextRecordPointer/nextEmptyRecordPointer + lastRecordPointer + deleteBit +  recordContent


class RecordManager{
public: //this public modifier is for debug only, change back to private later!
    const int RCPos = 0;
    const int ELHeadPos = sizeof(unsigned int);

    const int recordStartPos = ELHeadPos + sizeof(recordPointer);

    
    const int recordPrefixLen = (sizeof(recordPointer) << 1) + sizeof(short);
    const int nextOffset = 0;
    const int lastOffset = sizeof(recordPointer);
    const int deleteBitOffset = sizeof(recordPointer) << 1;
    
public:
    void createTableFile(string tableName);
    
    void deleteTableFile(string tableName);
    
    int insertRecords(string tableName, void* recordContent, int size);
    
    vector<recordPointer> select(string tableName, int tableTotalSize, int recordSizeInFile, vector<condition> conditions);
    
    int deleteRecords(string tableName, vector<recordPointer> deleteList);
};




#endif /* RecordManager_hpp */

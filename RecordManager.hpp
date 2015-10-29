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
#include "sqlstruct.h"
//#include "SelectValue.hpp"

using namespace std;
using namespace sqlstruct;

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
    operate op;
    insertitem value;
    condition(int aPos, operate o, insertitem v){
        attr_startPos = aPos;
        op = o;
        value = v;
    }
};

typedef pair<string, recordPointer> indexPair;


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
    
    vector<indexPair> returnIndexInfo(string tableName, int attr_pos, int attrType, int recordContentSize);
    
    recordPointer insertRecords(string tableName, vector<insertitem>& recordContent, int recordSize);
    
    vector<vector<string> > selectRecords(string tablename, int recordSize, vector<condition>& conditions, vector<int>& attrTypes);
    
    vector<string> deleteRecords(string tableName, int recordSize, vector<condition>& conditions, int attrPos, int attrType);
    
    // after passing tests, set to private
    vector<recordPointer> select(string tableName, int recordSize, vector<condition>& conditions, bool returnDeleteKey, int attrPos, int attrType, vector<string>& deleteKeys);
};




#endif /* RecordManager_hpp */

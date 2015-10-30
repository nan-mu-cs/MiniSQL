//
//  RecordManager.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/20/15.
//  Copyright © 2015 laoreja. All rights reserved.
//
#include <fcntl.h>
#include <sys/stat.h>

#include "BufferManager.hpp"
#include "RecordManager.hpp"
#include "sqlstruct.h"

using namespace sqlstruct;

void RecordManager::createTableFile(string tableName){
    int fd;
    if((fd = open(tableName.c_str(), O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH)) == -1){
        fprintf(stderr, "create file error: %s", tableName.c_str());
        throw createFileError;
    }
    
    if (close(fd)) {
        fprintf(stderr, "close file error: %s", tableName.c_str());
        throw closeFileError;
    }
    
    // file head write
    unsigned int recordCount = 0;
    recordPointer emptyListHead(0, recordStartPos);
    
    bm.writeBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    bm.writeBuffer(tableName, 0, &emptyListHead, ELHeadPos, sizeof(recordPointer));

}

void RecordManager::deleteTableFile(string tableName){
    bm.deleteFileFromBuffer(tableName);
    if (remove(tableName.c_str())) {
        fprintf(stderr, "remove file error: %s", tableName.c_str());
        throw removeFileError;
    }
}

vector<indexPair> RecordManager::returnIndexInfo(string tableName, int attr_pos, int attrType, int recordContentSize){
    int recordSizeInFile = recordContentSize + recordPrefixLen;
    vector<indexPair> res;
    unsigned int recordCount;
    bm.constReadBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    
    recordPointer currentPointer(0, recordStartPos);
    short deleteBit;
    
    bm.constReadBuffer(tableName, currentPointer.blockNum, &deleteBit, currentPointer.offset+deleteBitOffset, sizeof(deleteBit));
    while (deleteBit) {
        currentPointer.offset += recordSizeInFile;
        if (currentPointer.offset >= BUFFERSIZE) {
            currentPointer.blockNum++;
            currentPointer.offset = 0;
        }
        bm.constReadBuffer(tableName, currentPointer.blockNum, &deleteBit, currentPointer.offset+deleteBitOffset, sizeof(deleteBit));
    }
    
    switch (attrType) {
        case INTNUM:
        {
            int tmpValue;
            for (int i = 0; i < recordCount; i++) {
                bm.constReadBuffer(tableName, currentPointer.blockNum, &tmpValue, currentPointer.offset+recordPrefixLen+attr_pos, sizeof(int));
                res.push_back(indexPair(to_string(tmpValue), currentPointer));
                
                bm.constReadBuffer(tableName, currentPointer.blockNum, &currentPointer, currentPointer.offset+nextOffset, sizeof(recordPointer));
            }
            break;
        }
        case FLOATNUM:
        {
            float tmpValue;
            for (int i = 0; i < recordCount; i++) {
                bm.constReadBuffer(tableName, currentPointer.blockNum, &tmpValue, currentPointer.offset+recordPrefixLen+attr_pos, sizeof(float));
                res.push_back(indexPair(to_string(tmpValue), currentPointer));
                
                bm.constReadBuffer(tableName, currentPointer.blockNum, &currentPointer, currentPointer.offset+nextOffset, sizeof(recordPointer));
            }
            break;
        }
        default:
        {
            char* tmpValue = new char[attrType - CHAR];
            for (int i = 0; i < recordCount; i++) {
                bm.constReadBuffer(tableName, currentPointer.blockNum, tmpValue, currentPointer.offset+recordPrefixLen+attr_pos, attrType-CHAR);
                res.push_back(indexPair(string(tmpValue), currentPointer));
                
                bm.constReadBuffer(tableName, currentPointer.blockNum, &currentPointer, currentPointer.offset+nextOffset, sizeof(recordPointer));
            }
            delete[] tmpValue;
            break;
        }
    }

    
    return res;
}

recordPointer RecordManager::insertRecords(string tableName, vector<insertitem>& recordContent, int recordSize){
    recordPointer next;
    recordPointer last;
    recordPointer current;
    short tempDeleteBit; // 1: deleted
    
    recordSize += recordPrefixLen;
    
    //read file head
    unsigned int recordCount;
    recordPointer emptyListHead;
    bm.constReadBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    bm.constReadBuffer(tableName, 0, &emptyListHead, ELHeadPos, sizeof(recordPointer));
    
    current.blockNum = emptyListHead.blockNum;
    current.offset = emptyListHead.offset;
    
    //set the new empty list head
    bm.constReadBuffer(tableName, current.blockNum, &tempDeleteBit, current.offset+deleteBitOffset, sizeof(short));
    
    if (tempDeleteBit){
        bm.constReadBuffer(tableName, current.blockNum, &emptyListHead, current.offset+nextOffset, sizeof(recordPointer));
    }else {
        //current node is the first node of the empty list.
        // and is the last node in record list
        emptyListHead.blockNum = current.blockNum;
        emptyListHead.offset = current.offset + recordSize;
        if (emptyListHead.offset + recordSize >= BUFFERSIZE) {
            emptyListHead.blockNum += 1;
            emptyListHead.offset = 0;
        }
    }
    bm.writeBuffer(tableName, 0, &emptyListHead, ELHeadPos, sizeof(recordPointer)); //store the new empty list head
    
    if (recordCount == 0) {
        last = current;
        next = current;
    } else {
        if (tempDeleteBit) {
            next = current;
            do{
                next.offset += recordSize;
                if (next.offset >= BUFFERSIZE) {
                    next.blockNum += 1;
                    next.offset = 0;
                }
                bm.constReadBuffer(tableName, next.blockNum, &tempDeleteBit, next.offset+deleteBitOffset, sizeof(short));
            }while(tempDeleteBit);
        } else{
            next.blockNum = current.blockNum;
            next.offset = current.offset + recordSize;
            if (next.offset >= BUFFERSIZE) {
                next.blockNum++;
                next.offset = 0;
            }
        }
        
        bm.constReadBuffer(tableName, next.blockNum, &last, next.offset+lastOffset, sizeof(recordPointer));
        if (last.blockNum == 0 && last.offset == 0) {
            //the next node is wrong, need to search from the start.
            next.blockNum = 0; next.offset = recordStartPos;
            bm.constReadBuffer(tableName, next.blockNum, &tempDeleteBit, next.offset+deleteBitOffset, sizeof(short));
            while (tempDeleteBit) {
                next.offset += recordSize;
                if (next.offset >= BUFFERSIZE) {
                    next.blockNum ++;
                    next.offset = 0;
                }
                bm.constReadBuffer(tableName, next.blockNum, &tempDeleteBit, next.offset+deleteBitOffset, sizeof(short));
            }
            bm.constReadBuffer(tableName, next.blockNum, &last, next.offset+lastOffset, sizeof(recordPointer));
        }
    }
    
    
    short deleteBit = 0;
    bm.writeBuffer(tableName, current.blockNum, &deleteBit, current.offset+deleteBitOffset, sizeof(short));
    int tempPos = recordPrefixLen;
    for (int i = 0; i < recordContent.size(); i++) {
        int valueSize = recordContent[i].size();
        switch (recordContent[i].data_type) {
            case INTNUM:
            {
                int iValue = recordContent[i].getInt();
                bm.writeBuffer(tableName, current.blockNum, &iValue, current.offset+tempPos, sizeof(int));
                break;
            }
            case FLOATNUM:
            {
                float fValue = recordContent[i].getFloat();
                bm.writeBuffer(tableName, current.blockNum, &fValue, current.offset+tempPos, sizeof(float));
                break;
            }
            default:
            {
                char* cNValue = new char[valueSize];
                strcpy(cNValue, recordContent[i].getCharN());
                bm.writeBuffer(tableName, current.blockNum, cNValue, current.offset+tempPos, valueSize);
                delete[] cNValue;
                break;
            }
        }
        tempPos += valueSize;
    }
    
    bm.writeBuffer(tableName, current.blockNum, &next, current.offset+nextOffset, sizeof(recordPointer));
    bm.writeBuffer(tableName, current.blockNum, &last, current.offset+lastOffset, sizeof(recordPointer));
    
    bm.writeBuffer(tableName, last.blockNum, &current, last.offset+nextOffset, sizeof(recordPointer));
    bm.writeBuffer(tableName, next.blockNum, &current, next.offset+lastOffset, sizeof(recordPointer));
    
    recordCount++;
    bm.writeBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    return current;
}


vector<string> RecordManager::deleteRecords(string tableName, int recordSize, vector<condition>& conditions, int attrPos, int attrType){
    recordPointer next;
    recordPointer last;
    recordPointer ELHead;
    unsigned int recordCount;
    short deleteBit = 1;
    vector<string> res;
    
    vector<recordPointer> deleteList = select(tableName, recordSize, conditions, true, attrPos, attrType, res);
    
    bm.constReadBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    
    for (int i = 0; i < deleteList.size(); i++) {
        recordCount--;
        bm.writeBuffer(tableName, deleteList[i].blockNum, &deleteBit, deleteList[i].offset+deleteBitOffset, sizeof(short));
        
        if (recordCount){
            bm.constReadBuffer(tableName, deleteList[i].blockNum, &next, deleteList[i].offset+nextOffset, sizeof(recordPointer));
            bm.constReadBuffer(tableName, deleteList[i].blockNum, &last, deleteList[i].offset+lastOffset, sizeof(recordPointer));
            
            bm.writeBuffer(tableName, last.blockNum, &next, last.offset+nextOffset, sizeof(recordPointer));
            bm.writeBuffer(tableName, next.blockNum, &last, next.offset+lastOffset, sizeof(recordPointer));
        }
        
        bm.constReadBuffer(tableName, 0, &ELHead, ELHeadPos, sizeof(recordPointer));
        bm.writeBuffer(tableName, deleteList[i].blockNum, &ELHead, deleteList[i].offset+nextOffset, sizeof(recordPointer));
        bm.writeBuffer(tableName, 0, &(deleteList[i]), ELHeadPos, sizeof(recordPointer));
    }
    
    bm.writeBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    return res;
}


vector<recordPointer> RecordManager::select(string tableName, int recordSize, vector<condition>& conditions, bool returnDeleteKey, int attrPos, int attrType, vector<string>& deleteKeys){
    vector<recordPointer> res;
    recordSize += recordPrefixLen;
    
    recordPointer tmp(0, recordStartPos);
    insertitem tmpValue;
    unsigned int tableTotalSize;
    bm.constReadBuffer(tableName, 0, &tableTotalSize, RCPos, sizeof(unsigned int));
    
    short deleteBit;
    bm.constReadBuffer(tableName, tmp.blockNum, &deleteBit, tmp.offset+deleteBitOffset, sizeof(short));
    while (deleteBit) {
        tmp.offset+=recordSize;
        if (tmp.offset >= BUFFERSIZE) {
            tmp.blockNum += 1;
            tmp.offset = 0;
        }
        bm.constReadBuffer(tableName, tmp.blockNum, &deleteBit, tmp.offset+deleteBitOffset, sizeof(short));
    }

    int i = 0;
    for (int j = 0; j < tableTotalSize; j++) {
        switch (conditions[i].value.data_type) {
            case INTNUM:
            {
                int iValue;
                bm.constReadBuffer(tableName, tmp.blockNum, &iValue, tmp.offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(int));
                tmpValue.data_type = INTNUM;
                tmpValue.value = to_string(iValue);
                break;
            }
            case FLOATNUM:
            {
                float fValue;
                bm.constReadBuffer(tableName, tmp.blockNum, &fValue, tmp.offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(float));
                tmpValue.data_type = FLOATNUM;
                tmpValue.value = to_string(fValue);
                break;
            }
            default:
            {
                char* cValue = new char[conditions[i].value.size()];
                bm.constReadBuffer(tableName, tmp.blockNum, cValue, tmp.offset+recordPrefixLen+conditions[i].attr_startPos, conditions[i].value.size());
                tmpValue.data_type = CHAR + conditions[i].value.size();
                tmpValue.value = string(cValue);
                delete[] cValue;
                break;
            }
        }

        if (tmpValue.operation(conditions[i].op, conditions[i].value)) {
            res.push_back(tmp);
            if (returnDeleteKey) {
                switch (attrType) {
                    case INTNUM:
                    {
                        int tmpIntForDeleteKey;
                        bm.constReadBuffer(tableName, tmp.blockNum, &tmpIntForDeleteKey, tmp.offset+recordPrefixLen+attrPos, sizeof(int));
                        deleteKeys.push_back(to_string(tmpIntForDeleteKey));
                        break;
                    }
                    case FLOATNUM:{
                        float tmpFloatForDeleteKey;
                        bm.constReadBuffer(tableName, tmp.blockNum, &tmpFloatForDeleteKey, tmp.offset+recordPrefixLen+attrPos, sizeof(float));
                        deleteKeys.push_back(to_string(tmpFloatForDeleteKey));
                        break;
                    }
                    default:
                    {
                        char* tmpCharNForDeleteKey = new char[attrType - CHAR];
                        bm.constReadBuffer(tableName, tmp.blockNum, tmpCharNForDeleteKey, tmp.offset+recordPrefixLen+attrPos, attrType-CHAR);
                        deleteKeys.push_back(string(tmpCharNForDeleteKey));
                        break;
                    }
                }
            }
        }
        bm.constReadBuffer(tableName, tmp.blockNum, &tmp, tmp.offset+nextOffset, sizeof(recordPointer));
    }
    
    for (i = 1; i < conditions.size(); i++) {
        vector<recordPointer>::iterator it = res.begin();
        vector<string>::iterator deleteKeysIt = deleteKeys.begin();
        int originalSize = (int)res.size();
        
        for (int k = 0; k < originalSize; k++) {
            switch (conditions[i].value.data_type) {
                case INTNUM:
                {
                    int iValue;
                    bm.constReadBuffer(tableName, it->blockNum, &iValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(int));
                    tmpValue.data_type = INTNUM;
                    tmpValue.value = to_string(iValue);
                    break;
                }
                case FLOATNUM:
                {
                    float fValue;
                    bm.constReadBuffer(tableName, it->blockNum, &fValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(float));
                    tmpValue.data_type = FLOATNUM;
                    tmpValue.value = to_string(fValue);
                    break;
                }
                default:
                {
                    char* cValue = new char[conditions[i].value.size()];
                    bm.constReadBuffer(tableName, it->blockNum, cValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, conditions[i].value.size());
                    tmpValue.data_type = CHAR + conditions[i].value.size();
                    tmpValue.value = string(cValue);
                    delete[] cValue;
                    break;
                }
            }
            if (!tmpValue.operation(conditions[i].op, conditions[i].value)) {
                it = res.erase(it);
                if (returnDeleteKey) {
                    deleteKeysIt = deleteKeys.erase(deleteKeysIt);
                }
                
            }else{
                it++;
                if (returnDeleteKey) {
                    deleteKeysIt++;
                }
            }
        }
    }
    return res;
}

vector<vector<string> > RecordManager::selectRecords(string tablename, int recordSize, vector<condition>& conditions, vector<int>& attrTypes){
    vector<vector<string> > res;
    vector<string> nouse;
    vector<recordPointer> resPointers = select(tablename, recordSize, conditions, false, 0, 0, nouse);
    for (int i = 0; i < resPointers.size(); i++) {
        vector<string> lineRes;
        int tempPos = recordPrefixLen;
        for (int j = 0; j < attrTypes.size(); j++) {
            switch (attrTypes[j]) {
                case INTNUM:
                {
                    int iValue;
                    bm.constReadBuffer(tablename, resPointers[i].blockNum, &iValue, resPointers[i].offset+tempPos, sizeof(int));
                    lineRes.push_back(to_string(iValue));
                    tempPos += sizeof(int);
                    break;
                }
                case FLOATNUM:
                {
                    float fValue;
                    bm.constReadBuffer(tablename, resPointers[i].blockNum, &fValue, resPointers[i].offset+tempPos, sizeof(float));
                    lineRes.push_back(to_string(fValue));
                    tempPos += sizeof(float);
                    break;
                }
                default:
                {
                    char* cValue = new char[attrTypes[j] - CHAR];
                    bm.constReadBuffer(tablename, resPointers[i].blockNum, cValue, resPointers[i].offset+tempPos, attrTypes[j] - CHAR);
                    lineRes.push_back(string(cValue));
                    tempPos += attrTypes[j] - CHAR;
                    delete[] cValue;
                    break;
                }
            }
        }
        res.push_back(lineRes);
    }
    return res;
}
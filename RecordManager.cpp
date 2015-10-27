//
//  RecordManager.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/20/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#include "RecordManager.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include "BufferManager.hpp"

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

//把一个一插调对以后可以改成 vector<void*>
int RecordManager::insertRecords(string tableName, void* recordContent, int size){
    int recordSizeInFile = recordPrefixLen + size;
    printf("recordPointer size: %ld, recordPrefix size: %d, record size: %d\n",sizeof(recordPointer), recordPrefixLen, size);

    recordPointer next;
    recordPointer last;
    recordPointer current;
    short tempDeleteBit; // 1: deleted
    
    //read file head
    unsigned int recordCount;
    recordPointer emptyListHead;
    bm.constReadBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    bm.constReadBuffer(tableName, 0, &emptyListHead, ELHeadPos, sizeof(recordPointer));

    current.blockNum = emptyListHead.blockNum;
    current.offset = emptyListHead.offset;
    
    //set the new empty list head
    bm.constReadBuffer(tableName, current.blockNum, &tempDeleteBit, current.offset+deleteBitOffset, sizeof(short));
    
    if (tempDeleteBit) {
        bm.constReadBuffer(tableName, current.blockNum, &emptyListHead, current.offset+nextOffset, sizeof(recordPointer));
    }else {
        //current node is the first node of the empty list.
        // and is the last node in record list
        emptyListHead.blockNum = current.blockNum;
        emptyListHead.offset = current.offset + recordSizeInFile;
        if (emptyListHead.offset + recordSizeInFile >= BUFFERSIZE) {
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
                next.offset += recordSizeInFile;
                if (next.offset >= BUFFERSIZE) {
                    next.blockNum += 1;
                    next.offset = 0;
                }
                bm.constReadBuffer(tableName, next.blockNum, &tempDeleteBit, next.offset+deleteBitOffset, sizeof(short));
            }while(tempDeleteBit);
        } else{
            next.blockNum = current.blockNum;
            next.offset = current.offset + recordSizeInFile;
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
                next.offset += recordSizeInFile;
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
    bm.writeBuffer(tableName, current.blockNum, recordContent, current.offset+recordPrefixLen, size);
    
    bm.writeBuffer(tableName, current.blockNum, &next, current.offset+nextOffset, sizeof(recordPointer));
    bm.writeBuffer(tableName, current.blockNum, &last, current.offset+lastOffset, sizeof(recordPointer));
    
    bm.writeBuffer(tableName, last.blockNum, &current, last.offset+nextOffset, sizeof(recordPointer));
    bm.writeBuffer(tableName, next.blockNum, &current, next.offset+lastOffset, sizeof(recordPointer));
    
    recordCount++;
    bm.writeBuffer(tableName, 0, &recordCount, RCPos, sizeof(unsigned int));
    return 0;
}

int RecordManager::deleteRecords(string tableName, vector<recordPointer> deleteList){
    recordPointer next;
    recordPointer last;
    recordPointer ELHead;
    unsigned int recordCount;
    short deleteBit = 1;
    
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
    return 0;
}


vector<recordPointer> RecordManager::select(string tableName, int tableTotalSize, int recordSizeInfile, vector<condition> conditions){
    
    vector<recordPointer> res;
    recordPointer tmp(0, recordStartPos);
    selectValue tmpValue;
    
//    if (conditions.size() == 0) {
//        return res;
//    }
    
    short deleteBit;
    bm.constReadBuffer(tableName, tmp.blockNum, &deleteBit, tmp.offset+deleteBitOffset, sizeof(short));
    while (deleteBit) {
        tmp.offset+=recordSizeInfile;
        if (tmp.offset >= BUFFERSIZE) {
            tmp.blockNum += 1;
            tmp.offset = 0;
        }
        bm.constReadBuffer(tableName, tmp.blockNum, &deleteBit, tmp.offset+deleteBitOffset, sizeof(short));
    }
    

    int i = 0;
    for (int j = 0; j < tableTotalSize; j++) {
        switch (conditions[0].type) {
            case INT:
                tmpValue.setValue(INT, sizeof(int));
                bm.constReadBuffer(tableName, tmp.blockNum, tmpValue.iValue, tmp.offset+recordPrefixLen+conditions[0].attr_startPos, sizeof(int));
                break;
                    
            case FLOAT:
                tmpValue.setValue(FLOAT, sizeof(float));
                bm.constReadBuffer(tableName, tmp.blockNum, tmpValue.fValue, tmp.offset+recordPrefixLen+conditions[0].attr_startPos, sizeof(float));
                break;
                    
            case CHARN:
                tmpValue.setValue(CHARN, conditions[i].value.size);
                bm.constReadBuffer(tableName, tmp.blockNum, tmpValue.cValue, tmp.offset+recordPrefixLen+conditions[0].attr_startPos, (int)conditions[0].value.size);
                break;
            default:
                break;
        }
        if (tmpValue.operation(conditions[0].op, conditions[0].value)) {
            res.push_back(tmp);
        }
        bm.constReadBuffer(tableName, tmp.blockNum, &tmp, tmp.offset+nextOffset, sizeof(recordPointer));
    }
    
    for (i = 1; i < conditions.size(); i++) {
        vector<recordPointer>::iterator it = res.begin();
        vector<recordPointer>::iterator tempIt;
        int originalSize = (int)res.size();
        
        for (int k = 0; k < originalSize; k++) {
            switch (conditions[i].type) {
                case INT:
                    tmpValue.setValue(INT, sizeof(int));
                    bm.constReadBuffer(tableName, it->blockNum, tmpValue.iValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(int));
                    break;
                    
                case FLOAT:
                    tmpValue.setValue(FLOAT, sizeof(float));
                    bm.constReadBuffer(tableName, it->blockNum, tmpValue.fValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, sizeof(float));
                    break;
                    
                case CHARN:
                    tmpValue.setValue(CHARN, conditions[i].value.size);
                    bm.constReadBuffer(tableName, it->blockNum, tmpValue.cValue, it->offset+recordPrefixLen+conditions[i].attr_startPos, (int)conditions[i].value.size);
                    break;
                default:
                    break;
            }
            
            if (!tmpValue.operation(conditions[i].op, conditions[i].value)) {
                it = res.erase(it);
            }else{
                it++;
            }
        }
    }
    
    return res;
}

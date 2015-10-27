//
//  BufferManager.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#include "BufferManager.hpp"
#include "BlockForBuffer.hpp"

//private
int BufferManager::ReplaceBlockIndex(){
    static int tempIndex = 0;
    while (1) {
        if(tempIndex == NUMOFBUFFER){
            tempIndex -= NUMOFBUFFER;
        }
        if (!blocks[tempIndex].getPinBit()) {
            if (blocks[tempIndex].getReferenceBit()) {
                blocks[tempIndex].setReferenceBit(0);
            }
            else{
                if (blocks[tempIndex].getDirtyBit()) {
                    if(bufferToFile(tempIndex)){
                        goto CONTINUELOOP;
                    }
                }
                //erase the hash key
                if (blocks[tempIndex].getInTableBit()) {
                    IndexTable.erase(hashKey(blocks[tempIndex].getFileName(), blocks[tempIndex].getPartOfFile()));
                    blocks[tempIndex].setInTableBit(0);
                }
                return tempIndex++;
            }
        }
    CONTINUELOOP:
        tempIndex++;
    
    }
}


int BufferManager::lookUpIndex(string fileName, int part){
    if (IndexTable.find(hashKey(fileName, part)) != IndexTable.end()) {
        return IndexTable[hashKey(fileName, part)];
    }else{
        return fileToBuffer(fileName, part);
    }
}

//public
BufferManager::BufferManager(){
    memset(blocks, 0, sizeof(blocks));
}

void BufferManager::save(){
    for (int i = 0; i < NUMOFBUFFER; i++) {
        if (blocks[i].getInTableBit() && blocks[i].getDirtyBit()) {
            bufferToFile(i);
        }
    }
}


void BufferManager::writeBuffer(string fileName, int part, void* content, int startPos, int size){
    int index = lookUpIndex(fileName, part);
    
    memcpy(blocks[index].buffer + startPos, content, size);
//    if (startPos + size > blocks[index].currentSize) {
//        blocks[index].currentSize = startPos + size;
//    }
    
    blocks[index].setReferenceBit(1);
    blocks[index].setDirtyBit(1);
}

void BufferManager::constReadBuffer(string fileName, int part, void* des, int startPos, int size){
    int index = lookUpIndex(fileName, part);
    memcpy(des, blocks[index].buffer + startPos, size);
    blocks[index].setReferenceBit(1);
}

void BufferManager::deleteFileFromBuffer(string fileName){
    int fd = open(fileName.c_str(), O_RDONLY);
    struct stat sb;
    
    if(fd == -1){
        fprintf(stderr, "Cannot open file: %s, in BufferManager::deleteFileFromBuffer.\n", fileName.c_str());
        throw openFileError;
    }
    if (fstat(fd, &sb)) {
        fprintf(stderr, "File: %s, fstat error, in BufferManager::deleteFileFromBuffer.\n", fileName.c_str());
        throw fstatError;
    }
    
    int blockCount = (int)(sb.st_size >> BUFFERSIZESHIFT);
    
    for (int part = 0; part < blockCount; part++) {
        if (IndexTable.find(hashKey(fileName, part)) != IndexTable.end()) {
            int index = IndexTable[hashKey(fileName, part)];
            blocks[index].sign = 0;
            IndexTable.erase(hashKey(fileName, part));
        }
    }
    
    if (close(fd) == -1) {
        fprintf(stderr, "Cannot close file: %s, in BufferManager::deleteFileFromBuffer.\n", fileName.c_str());
        throw closeFileError;
    }
}

// return the index of the block.
// If errors occurred, return -1.
int BufferManager::fileToBuffer(string fileName, int part){
    int index = ReplaceBlockIndex();
    
    int fd = open(fileName.c_str(), O_RDWR);
    if(fd == -1){
        throw openFileError;
    }
    
    struct stat sb;
    if (fstat(fd, &sb)) {
        fprintf(stderr, "File: %s, fstat error, in fileToBuffer, BufferManager.\n", fileName.c_str());
        return -1;
    }
    
    if (((part + 1) << BUFFERSIZESHIFT) >= sb.st_size) {
        ftruncate(fd, (part+1) << BUFFERSIZESHIFT);
        fsync(fd);
    }
    
    char* mbuf = (char *) mmap(NULL, BUFFERSIZE ,PROT_READ, MAP_PRIVATE, fd, part << BUFFERSIZESHIFT);
    
    memcpy(blocks[index].buffer, mbuf, BUFFERSIZE);
//    blocks[index].setSize(BUFFERSIZE);
    
    munmap(mbuf, BUFFERSIZE);
    close(fd);
    
    blocks[index].setFileInfo(fileName, part);
    
    // may be not needed
    blocks[index].setDirtyBit(0);
    blocks[index].setPinBit(0);
    // may be not needed
    
    blocks[index].setReferenceBit(1);
    IndexTable[hashKey(fileName, part)] = index;
    blocks[index].setInTableBit(1);
    return index;
}

int BufferManager::bufferToFile(string fileName, int part){
    if (IndexTable.find(hashKey(fileName, part)) == IndexTable.end()) {
        fprintf(stderr, "buffer not exists, in BufferManager::bufferToFile.\n");
        return -1;
    }
    int index = IndexTable[hashKey(fileName, part)];
    
    return bufferToFile(index);
}

int BufferManager::bufferToFile(int index){
    FILE* fp = fopen(blocks[index].getFileName().c_str(), "r+");
    // we can later modify this function to use mmap, now I do not if it is safe enough.
    if (fseek(fp, blocks[index].getPartOfFile() << BUFFERSIZESHIFT, SEEK_SET)) {
        fprintf(stderr, "fseek error, part num may exceed the file size, in BufferManager::bufferToFile.\n");
        return -1;
    }
    ;
    fwrite(blocks[index].buffer, sizeof(char), BUFFERSIZE, fp);
    fclose(fp);
    
    blocks[index].setReferenceBit(0);
    blocks[index].setDirtyBit(0);
    return 0;
}

int BufferManager::wholeFileToBuffer(string fileName){
    
    int fd = open(fileName.c_str(), O_RDONLY);
    struct stat sb;

    if(fd == -1){
        fprintf(stderr, "Cannot open file: %s, in BufferManager::wholeFileToBuffer.\n", fileName.c_str());
        throw openFileError;
    }
    if (fstat(fd, &sb)) {
        fprintf(stderr, "File: %s, fstat error, in BufferManager::wholeFileToBuffer.\n", fileName.c_str());
        throw fstatError;
    }

    int blockCount = (int)(sb.st_size >> BUFFERSIZESHIFT);
    char* mbuf;
    int index;
    for (int i = 0; i < blockCount; i++) {
        if (IndexTable.find(hashKey(fileName, i)) == IndexTable.end()) {
            mbuf = (char *) mmap(NULL, BUFFERSIZE ,PROT_READ, MAP_PRIVATE, fd, i << BUFFERSIZESHIFT);
            index = ReplaceBlockIndex();
            
            memcpy(blocks[index].buffer, mbuf, BUFFERSIZE);
            munmap(mbuf, BUFFERSIZE);
//            blocks[index].setSize(BUFFERSIZE);
            
            blocks[index].setReferenceBit(1);
            // may be not needed
            blocks[index].setDirtyBit(0);
            blocks[index].setPinBit(0);
            // may be not needed
            blocks[index].setFileInfo(fileName, i);
            IndexTable[hashKey(fileName, i)] = index;
            blocks[index].setInTableBit(1);
        }
    }
    if(close(fd)){
        fprintf(stderr, "Cannot close file: %s, in BufferManager::wholeFileToBuffer.\n", fileName.c_str());
        throw closeFileError;
    }
    
    return 0;
}

//void BufferManager::read(void* des, string fileName, off_t pos, size_t size){
//    int index;
//
//    if ((pos % BUFFERSIZE + size) < BUFFERSIZE) {
//        index = lookUpIndex(fileName, pos / BUFFERSIZE);
//        memcpy(des, blocks[index].buffer + (pos % BUFFERSIZE), size);
//    }else{
//        int blockNum = pos / (long)BUFFERSIZE;
//        index = lookUpIndex(fileName, blockNum);
//        memcpy(des, blocks[index].buffer + (pos % BUFFERSIZE), BUFFERSIZE - (pos % BUFFERSIZE));
//        blockNum++;
//        char* charDes = (char*)des;
//        charDes += BUFFERSIZE - (pos % BUFFERSIZE);
//
//        int blockCount = (int)((size - (pos % (long)BUFFERSIZE)) >> (long)BUFFERSIZESHIFT);
//
//        for (int i = 0; i < blockCount; i++) {
//            index = lookUpIndex(fileName, blockNum);
//            memcpy(charDes, blocks[index].buffer, BUFFERSIZE);
//            blockNum++;
//            charDes += BUFFERSIZE;
//        }
//
//        index = lookUpIndex(fileName, blockNum);
//        memcpy(charDes, blocks[index].buffer, (size - (pos % (long)BUFFERSIZE)) % BUFFERSIZE);
//
//    }
//}
//
//void BufferManager::write(void* source, string fileName, off_t pos, size_t size){
//    int index;
//
//    if ((pos % BUFFERSIZE + size) < BUFFERSIZE) {
//        index = lookUpIndex(fileName, pos / BUFFERSIZE);
//        memcpy(blocks[index].buffer + (pos % BUFFERSIZE), source, size);
//    }else{
//        int blockNum = pos / (long)BUFFERSIZE;
//        index = lookUpIndex(fileName, blockNum);
//        memcpy(blocks[index].buffer + (pos % BUFFERSIZE), source, BUFFERSIZE - (pos % BUFFERSIZE));
//        blockNum++;
//        char* charSource = (char*)source;
//        charSource += BUFFERSIZE - (pos % BUFFERSIZE);
//
//        int blockCount = (int)((size - (pos % (long)BUFFERSIZE)) >> (long)BUFFERSIZESHIFT);
//
//        for (int i = 0; i < blockCount; i++) {
//            index = lookUpIndex(fileName, blockNum);
//            memcpy(blocks[index].buffer, charSource, BUFFERSIZE);
//            blockNum++;
//            charSource += BUFFERSIZE;
//        }
//
//        index = lookUpIndex(fileName, blockNum);
//        memcpy(blocks[index].buffer, charSource, (size - (pos % (long)BUFFERSIZE)) % BUFFERSIZE);
//
//    }
//}


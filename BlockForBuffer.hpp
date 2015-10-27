//
//  BlockForBuffer.hpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#ifndef BlockForBuffer_hpp
#define BlockForBuffer_hpp

#include <cstdio>
#include <string>

#define BUFFERSIZE 4096
#define BUFFERSIZESHIFT 12

using namespace std;

const unsigned int PIN = 1;
const unsigned int REFERENCE = 2;
const unsigned int DIRTY = 4;
const unsigned int INTABLE = 8;


class BlockForBuffer {
private:
    unsigned int sign; // ....dirty|reference|pin

    int currentSize;
    string fileName;
    int partOfFile;
    char buffer[BUFFERSIZE];
    
public:
    friend class BufferManager;
    
    BlockForBuffer(){
        currentSize = 0;
        sign = 0; //reference->0
    }    
    
    int getSize(){
        return currentSize;
    }
    void setSize(int size){
        currentSize = size;
    }

    int getPinBit() const{
        return sign & PIN;
    }
    void setPinBit(int pinBit){
        if (pinBit) {
            sign = sign | PIN;
        }
        else {
            sign &= ~PIN;
        }
    }
    
    int getReferenceBit() const{
        return (sign & REFERENCE) >> 1;
    }
    void setReferenceBit(int referenceBit){
        if(referenceBit) {
            sign = sign | REFERENCE;
        }
        else {
            sign &= ~REFERENCE;
        }
    }
    
    int getDirtyBit() const{
        return (sign & DIRTY) >> 2;
    }
    void setDirtyBit(int dirtyBit){
        if(dirtyBit){
            sign = sign | DIRTY;
        }
        else{
            sign &= ~DIRTY;
        }
    }
    
    int getInTableBit() const{
        return (sign & INTABLE) >> 3;
    }
    void setInTableBit(int inTableBit){
        if(inTableBit){
            sign = sign | INTABLE;
        }
        else{
            sign &= ~INTABLE;
        }
    }
    
//    int getUseBit() const{
//        return (sign & USE) >> 3;
//    }
//    
//    void setInUse(int inUseBit){
//        if(inUseBit) {
//            sign = sign | USE;
//        }
//        else {
//            sign &= ~USE;
//        }
//    }
    
    void writeBuffer(void* bufferInfo, int size){
        memcpy(buffer, bufferInfo, size);
        currentSize = size;
    }
    
    string getFileName() const{
        return fileName;
    }
    int getPartOfFile() const{
        return partOfFile;
    }
    void setFileInfo(string fileNameIn, int partNum){
        fileName = fileNameIn;
        partOfFile = partNum;
    }
    
};

#endif /* BlockForBuffer_hpp */

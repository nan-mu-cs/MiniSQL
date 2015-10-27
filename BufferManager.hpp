//
//  BufferManager.hpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#ifndef BufferManager_hpp
#define BufferManager_hpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <string>
#include <map>

#include "BlockForBuffer.hpp"

enum MiniSqlError{createFileError = 1, closeFileError, removeFileError, openFileError, fstatError, emptyListEndNotEmptyError, typeNotMatchError};

#define NUMOFBUFFER 16 * 1024 / 4
typedef pair<string, int> hashKey;


class BufferManager{
private:
    BlockForBuffer blocks[NUMOFBUFFER];
    map<pair<string, int>, int> IndexTable;//(fileName, partNum) -> index
    
    int ReplaceBlockIndex();
    int lookUpIndex(string fileName, int part);
    
public:
    friend class RecordManager;
    
    BufferManager();
    
    void save();
    
    void constReadBuffer(string fileName, int part, void* des, int startPos, int size);
    void writeBuffer(string fileName, int part, void* content, int startPos, int size);
    
    int wholeFileToBuffer(string fileName); //0 success, otherwise, failed.
    void deleteFileFromBuffer(string fileName);
    int fileToBuffer(string fileName, int part);
    
    int bufferToFile(string fileName, int part); //call by outside, not needed?
    int bufferToFile(int index); //call by the replace function
    
//    void read(void* des, string fileName, off_t pos, size_t size);
//    void write(void* source, string fileName, off_t pos, size_t size);
    
    void pinBuffer(string fileName, int part){
        blocks[lookUpIndex(fileName, part)].setPinBit(1);
    }
    void pinBuffer(int index){
        blocks[index].setPinBit(1);
    }
    void unPinBuffer(string fileName, int part){
        blocks[lookUpIndex(fileName, part)].setPinBit(0);
    }
    void unPinBuffer(int index){
        blocks[index].setPinBit(0);
    }
};

#endif /* BufferManager_hpp */

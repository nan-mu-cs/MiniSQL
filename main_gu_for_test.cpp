//
//  main.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#include "BufferManager.hpp"
#include "BlockForBuffer.hpp"
#include "RecordManager.hpp"

//for test
BufferManager bm = BufferManager();

struct record{
    int i;
//    char c[10];
    float f;
};

int main(int argc, const char * argv[]) {
    
    RecordManager rm;
    string fname = "/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile";
    rm.createTableFile("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile");
    
    struct record r;
    r.i = 111;
//    strcpy(r.c, "hello");
    r.f = 3.14159;
    rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", &r, sizeof(r));
    r.i = 112;
    rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", &r, sizeof(r));

//    charNValue c(sizeof("hello"), "hello");
    floatValue f(98.7);
    intValue i(112);
    condition con1(sizeof(int), FLOAT, EQUAL, f);
    condition con2(0, INT, LESSOREQUAL, i);
    vector<condition> conditions{con1, con2};
    //conditions为空时，part num （read/write buffer) 出问题了

    r.f = 98.7;
    int k;
    for (k = 0; k < 300; k++) {
        r.i = 113;
        rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", &r, sizeof(r));
    }
    
    vector<recordPointer> vr = rm.select("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", k + 2, 26, conditions);
    rm.deleteRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", vr);
    
    
    unsigned int recordCount;
    bm.constReadBuffer(fname, 0, &recordCount, rm.RCPos, sizeof(unsigned int));
    printf("record size: %u\n", recordCount);
    
    recordPointer rpStart(0, rm.recordStartPos);
    int tempDeleteBit;
    int rs = rm.recordPrefixLen+sizeof(struct record);
    struct record res;
    
    if (recordCount > 0) {
        bm.constReadBuffer(fname, rpStart.blockNum, &tempDeleteBit, rpStart.offset+rm.deleteBitOffset, sizeof(short));
        while (tempDeleteBit) {
            rpStart.offset+=rs;
            if (rpStart.offset >= BUFFERSIZE) {
                rpStart.offset = 0;
                rpStart.blockNum += 1;
            }
            bm.constReadBuffer(fname, rpStart.blockNum, &tempDeleteBit, rpStart.offset+rm.deleteBitOffset, sizeof(short));
        }

        
        for (int i = 0; i < recordCount; i++) {
            bm.constReadBuffer(fname, rpStart.blockNum, &res, rpStart.offset+rm.recordPrefixLen, sizeof(struct record));
            printf("%d %f\n", res.i, res.f);
            
            bm.constReadBuffer(fname, rpStart.blockNum, &rpStart, rpStart.offset+rm.nextOffset, sizeof(recordPointer));
        }
    }

    
    
//    char messContent[100] = {'a', 'b', 'c', 'd', '\n'};
//    
//    printf("whole buffer to file, 1 block, %d\n", bm.wholeFileToBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block.txt"));
//    printf("whole buffer to file, 1+ block, %d\n", bm.wholeFileToBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block_and_more.txt"));
//    
//
//    
//    char readBuffer[BUFFERSIZE+1];
//    memcpy(readBuffer, bm.constReadBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block.txt", 0), BUFFERSIZE);
//    readBuffer[BUFFERSIZE] = '\0';
//    puts(readBuffer);
//    
//    bm.writeBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block.txt", 0, messContent);
//    bm.bufferToFile("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block.txt", 0);
//    
//    bm.pinBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block.txt", 0);
//    
//    bm.wholeFileToBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block_and_more.txt");
//    
//    bm.unPinBuffer(0);
//    
//    printf("file to block, return index %d\n", bm.fileToBuffer("/Users/laoreja/study/DB/MiniSQL/MiniSQL/one_block_and_more.txt", 1));
  
    bm.save();
    return 0;
}

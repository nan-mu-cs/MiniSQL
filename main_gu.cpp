//
//  main.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#include <iostream>
#include "BufferManager.hpp"
#include "BlockForBuffer.hpp"
#include "RecordManager.hpp"
#include "IndexManager.h"
#include "API.h"
#include "CatalogManager.h"
#include "Interpreter.h"
//for test
BufferManager bm = BufferManager();



int main(int argc, const char * argv[]) {
    RecordManager rm;
    IndexManager im;
    API api;
    CatalogManager cm;
    Interpreter it(std::cin,std::cout,&cm);
    api.rm = &rm;
    api.im = &im;
    api.cm = &cm;
    im.SetBuffer(bm);
    im.InitFromEmpty();
    cm.SetBuffer(bm);
    cm.InitFromEmpty();
    it.api = &api;
    it.run();
    /*
    RecordManager rm;
    string fname = "/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile";
    rm.createTableFile("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile");
    int recordContentSize = sizeof(int)+sizeof(float)+10;
    
    vector<insertitem> r;
    
    r.push_back(insertitem("111", INTNUM));
    r.push_back(insertitem("nihao", CHAR+10));
    r.push_back(insertitem("3.14159", FLOATNUM));
    recordPointer rp1 = rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", r, sizeof(int)+sizeof(float)+10);
    printf("rp1, %d : %u\n", rp1.blockNum, rp1.offset);
    
    r.clear();
    r.push_back(insertitem("112", INTNUM));
    r.push_back(insertitem("nihao", CHAR+10));
    r.push_back(insertitem("3.14159", FLOATNUM));
    recordPointer rp2 = rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", r, sizeof(int)+sizeof(float)+10);
    printf("rp2, %d : %u\n", rp2.blockNum, rp2.offset);
    
    condition con1(14, EQUAL, insertitem("98.7", FLOATNUM));
    condition con2(0, LESSOREQUAL, insertitem("111", INTNUM));
    condition con3(4, EQUAL, insertitem("hello", CHAR + 10));
    vector<condition> conditions{con2};

    int k;
    for (k = 0; k < 300; k++) {
        r.clear();
        r.push_back(insertitem(to_string(k), INTNUM));
        r.push_back(insertitem("hello", CHAR+10));
        r.push_back(insertitem("98.7", FLOATNUM));
        rm.insertRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", r, sizeof(int)+sizeof(float)+10);
    }
    
    vector<int> attrType = {INTNUM, CHAR+10, FLOATNUM};
    vector<vector<string> > selectRes = rm.selectRecords(fname, sizeof(int)+sizeof(float)+10, conditions, attrType);
    vector<vector<string> >::iterator it;
    for (it = selectRes.begin(); it != selectRes.end(); it++) {
        vector<string>::iterator insideIt;
        for (insideIt = it->begin(); insideIt != it->end(); insideIt++) {
            cout << *insideIt << " ";
        }
        cout << endl;
    }
    rm.deleteRecords("/Users/laoreja/study/DB/MiniSQL/MiniSQL/createTableFile", sizeof(int)+sizeof(float)+10, conditions);
    
    
    
    unsigned int recordCount;
    bm.constReadBuffer(fname, 0, &recordCount, rm.RCPos, sizeof(unsigned int));
    printf("record size: %u\n", recordCount);
    
    recordPointer rpStart(0, rm.recordStartPos);
    int tempDeleteBit;
    int recordSizeInFile = rm.recordPrefixLen+recordContentSize;
    
    if (recordCount > 0) {
        bm.constReadBuffer(fname, rpStart.blockNum, &tempDeleteBit, rpStart.offset+rm.deleteBitOffset, sizeof(short));
        while (tempDeleteBit) {
            rpStart.offset+=recordSizeInFile;
            if (rpStart.offset >= BUFFERSIZE) {
                rpStart.offset = 0;
                rpStart.blockNum += 1;
            }
            bm.constReadBuffer(fname, rpStart.blockNum, &tempDeleteBit, rpStart.offset+rm.deleteBitOffset, sizeof(short));
        }

        
        for (int i = 0; i < recordCount; i++) {
            int iv;
            float fv;
            char cv[10];
            
            bm.constReadBuffer(fname, rpStart.blockNum, &iv, rpStart.offset+rm.recordPrefixLen, sizeof(int));
            bm.constReadBuffer(fname, rpStart.blockNum, cv, rpStart.offset+rm.recordPrefixLen+sizeof(int), 10);
            bm.constReadBuffer(fname, rpStart.blockNum, &fv, rpStart.offset+rm.recordPrefixLen+sizeof(int)+10, sizeof(float));
            printf("%d %s %f\n", iv, cv, fv);
            
            bm.constReadBuffer(fname, rpStart.blockNum, &rpStart, rpStart.offset+rm.nextOffset, sizeof(recordPointer));
        }
    }
    vector<indexPair> ipv = rm.returnIndexInfo(fname, 4, CHAR+10, 18);
    printf("return index info:\n");
    for (int i = 0; i < ipv.size(); i++) {
        printf("%s: %d - %u\n", ipv[i].first.c_str(), ipv[i].second.blockNum, ipv[i].second.offset);
    }
    
    bm.save();*/
    
    return 0;
}

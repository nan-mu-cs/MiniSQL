//
//  main.cpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/12/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#include <iostream>
#include <string.h>
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
    cm.SetBuffer(bm);
    if(argc>1&&strcmp(argv[1], "init") == 0){
        cm.InitFromEmpty();
        im.InitFromEmpty();
    }
    else {
        //cm.InitFromEmpty();
        //im.InitFromEmpty();
        im.InitFromFile();
        cm.InitFromFile();
    }
    it.api = &api;
    it.run();

    return 0;
}

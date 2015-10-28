//
//  main.cpp
//  BplusTree
//
//  Created by 杨凯 on 15/9/24.
//  Copyright (c) 2015年 杨凯. All rights reserved.
//
#include <iostream>
#include "CatalogManager.h"
#include "Interpreter.h"
#include "IndexManager.h"
#include "BufferManager.hpp"
#include "sqlstruct.h"
#include "RManager.h"
using namespace std;
BufferManager bm = BufferManager();
char str[10] = "aaaaaaaaa";
void nextstr(){
    for(int i = 0;i<8;i++)
    if(str[i]<'z')
    {
        str[i]++;
        return ;
    }
}
//string RecordManager::filepath = "/Users/andyyang/Documents/MiniSQL/MiniSQL/table.txt";
int main(){
    CatalogManager cm;
    cm.SetBuffer(bm);
    cm.InitFromEmpty();
    //cm.InitFromFile();
    RecordManager rm;
    rm.SetBuffer(bm);
    rm.InitFromEmpty();
    Interpreter it(std::cin,std::cout,&cm);
    it.rm = &rm;
    it.run();
    //cm.InitFromEmpty();
    //cm.Select();
    //IndexManager im;
    //im.SetBuffer(bm);
    //im.InitFromEmpty();
    //im.InitFromFile();
    /*
    off_t pos = im.newIndex(sqlstruct::INTNUM);
    for(int i = 0;i<300;i++){
        im.InsertKey(pos, i, i);
    }
    for(int i = 20;i<30;i++)
    im.DeleteKey(pos, i);
    for(int i = 0;i<300;i++){
        if(im.SearchKey(pos, i) == -1)
            cout << i << endl;
    }*/
    //off_t pos = im.newIndex(sqlstruct::CHAR + 10);
    /*
    for(int i = 0;i<300;i++){
        im.InsertKey(pos, str, i);
        nextstr();
    }*/
    /*
    off_t pos = 10008;
    strcpy(str, "aaaaaaaaa");
    for(int i = 0;i<300;i++){
        if(im.SearchKey(pos, str) == -1)
            cout << i << endl;
    }*/
    //cout << im.SearchKey(pos, "aasdfasdf") << endl;
}

/*
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "BplusTree.h"
struct key{
    off_t k;
    bool cmp(const struct key &a,const struct key &b) const {
        return a.k<b.k;
    }
    friend bool operator==(const struct key &a,const struct key &b){
        return a.k == b.k;
    }
    friend bool operator>=(const struct key &a,const struct key &b){
        return a.k>=b.k;
    }
    friend bool operator<=(const struct key &a,const struct key &b){
        return a.k<=b.k;
    }
    friend bool operator>(const struct key &a,const struct key &b){
        return a.k>b.k;
    }
    friend bool operator<(const struct key &a,const struct key &b){
        return a.k<b.k;
    }
    void operator=(const int &a){
        k = a;
    }
    key(const int &a){
        k = a;
    }
    key(){
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    bpt::BplusTree<struct key> a(true);
    //a.GetKeyAndValueSize(4, 8);
    a.setOrder(2);
    a.BuildNewTree();
    struct key node;
    long long value = 2;
    //a.printAllLeaf();
    for(int i = 0;i<500;i++)
    {
        node.k = 500 - i;
        //node.k = 30 - i;
        value = 500 - i;
        a.insert(node, value);
        //a.printAllLeaf();
    }
    a.levelorder();
    for(int i = 0;i<500;i++){
        node.k = 500 - i;
        a.search(node, value);
        assert(value == 500 - i);
    }
    std::vector<long long> result;
    key minkey,maxkey;
    minkey.k = 10;
    maxkey.k = 20;
    a.searchrange(minkey, maxkey, result);
    std::cout << result.size() << std::endl;
    //a.printAllLeaf();
    for(int i = 0;i<500;i++){
        node.k = i;
        a.remove(node);
        a.levelorder();
        a.search(node, value);
        //assert(value != i);
    }
    //node.k = 5;
    //a.remove(node);
    //a.search(node, value);
    //assert(value == 5);
    return 0;
}*/

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
#include "sqlstruct.h"
using namespace std;
void nextChar(char *str){
    for(int i = 0;i<31;i++)
        if(str[i]<'z'){
            str[i]++;
            break;
        }
}
//int String::times = 0;
//int String::create = 0;
int main(){
    IndexManager im;
    im.InitFromEmpty();
    off_t pos;
    pos = im.newIndex(sqlstruct::CHAR + 32);
    //pos = im.newIndex(sqlstruct::FLOATNUM);
    char str[32];
    for(int i = 0;i<31;i++)
        str[i] = 'a';
    str[31] = '\0';
    for(int i = 0;i<300;i++){
        nextChar(str);
        im.InsertKey(pos, str, i);
    }
    //im.DeleteKey(pos, );
    //im.DeleteKey(pos, 21);
    //cout << im.SearchKey(pos, 103)<< endl;
    //for(int i = 30;i<50;i++)
      //  im.DeleteKey(pos, i*1.0f);
    for(int i = 0;i<31;i++)
        str[i] = 'a';
    str[31] = '\0';
    for(int i = 0;i<300;i++){
        nextChar(str);
        if(im.SearchKey(pos, str) == -1)
            cout << i << endl;
    }
    //CatalogManager cm;
    //cm.InitFromFile();
    //cm.Test();
    //cm.GetTableSchema(50000);
    //cm.InitFromEmpty();
    //cm.Select();
    //Interpreter it(std::cin,std::cout,&cm);
    //it.Test();
    //Interpreter it;
    //it.run();
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

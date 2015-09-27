//
//  main.cpp
//  BplusTree
//
//  Created by 杨凯 on 15/9/24.
//  Copyright (c) 2015年 杨凯. All rights reserved.
//

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
    /*
    for(int i = 0;i<500;i++){
        node.k = 500 - i;
        a.search(node, value);
        assert(value == 500 - i);
    }*/
    std::vector<long long> result;
    key minkey,maxkey;
    minkey.k = 10;
    maxkey.k = 20;
    a.searchrange(minkey, maxkey, result);
    std::cout << result.size() << std::endl;
    //a.printAllLeaf();
    return 0;
}

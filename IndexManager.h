//
//  IndexManager.h
//  
//
//  Created by 杨凯 on 15/10/23.
//
//

#ifndef ____IndexManager__
#define ____IndexManager__
#include "sqlstruct.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
struct Integer{
    int value;
    bool cmp(const struct Integer &a,const struct Integer &b) const {
        return a.value<b.value;
    }
    friend bool operator==(const struct Integer &a,const struct Integer &b){
        return a.value == b.value;
    }
    friend bool operator>=(const struct Integer &a,const struct Integer &b){
        return a.value>=b.value;
    }
    friend bool operator<=(const struct Integer &a,const struct Integer &b){
        return a.value<=b.value;
    }
    friend bool operator>(const struct Integer &a,const struct Integer &b){
        return a.value>b.value;
    }
    friend bool operator<(const struct Integer &a,const struct Integer &b){
        return a.value<b.value;
    }
    void operator=(const int &a){
        value = a;
    }
    Integer(const int &a){
        value = a;
    }
    Integer(){
    }
};
struct Float{
    float value;
    bool cmp(const struct Float &a,const struct Float &b) const {
        return a.value<b.value;
    }
    friend bool operator==(const struct Float &a,const struct Float &b){
        return a.value == b.value;
    }
    friend bool operator>=(const struct Float &a,const struct Float &b){
        return a.value>=b.value;
    }
    friend bool operator<=(const struct Float &a,const struct Float &b){
        return a.value<=b.value;
    }
    friend bool operator>(const struct Float &a,const struct Float &b){
        return a.value>b.value;
    }
    friend bool operator<(const struct Float &a,const struct Float &b){
        return a.value<b.value;
    }
    Float& operator=(const float &a){
        std::cout << "enter" << a << std::endl;
        value = a;
        return *this;
    }
    Float(const float &a){
        value = a;
    }
    Float(){
    }
};
struct String{
    char *value;
    //static int times;
    //static int create;
    size_t size;
    bool cmp(const struct String &a,const struct String &b) const {
        return strcmp(a.value,b.value)<=0;
    }
    friend bool operator==(const struct String &a,const struct String &b){
        return strcmp(a.value, b.value) == 0;
    }
    friend bool operator>=(const struct String &a,const struct String &b){
        return strcmp(a.value, b.value)>=0;
    }
    friend bool operator<=(const struct String &a,const struct String &b){
        return strcmp(a.value,b.value)<=0;
    }
    friend bool operator>(const struct String &a,const struct String &b){
        return strcmp(a.value, b.value)>0;
    }
    friend bool operator<(const struct String &a,const struct String &b){
        return strcmp(a.value, b.value)<0;
    }
    String& operator=(const String &a){
        //std::cout << "enter operator=" << std::endl;
        size = a.size;
        if(this!=&a){
            if(value)
                delete value;
            value = new char [a.size];
            strcpy(value,a.value);
        }
        return *this;
    }
    String(const char *a,size_t size){
        this->size = size;
        value = new char [size];
        //std::cout << "create " << create  << "  ";
        //printf("%x\n",value);
        //create++;
        strcpy(value,a);
    }
    String(){
        //value = NULL;
        //std::cout << "create " << create << "  ";
        //printf("%x\n",value);
        //create++;
        value = NULL;
        size = 0;
    }
    ~String(){
        //std::cout << "in string destory func " << times << "  ";
        //printf("%x\n",value);
        //times++;
        if(value){
            delete value;
        }
    }
    String(const String &a){
        size = a.size;
        value = new char[size];
        strcpy(value,a.value);
    }
};

class IndexManager {
public:
    /*do some basic setting, using it when the first time construct db*/
    void InitFromEmpty();
    /*after first time construct db, then every time initialize IndexManager, call this func*/
    void InitFromFile();
    /*create new index(new bplustree) dataType are define in sqlstruct.h (note number of char is dataType - CHAR)
     *return head addr of bpt(be store in catalog file) 
     */
    off_t newIndex(int dataType);
    /*delete index*/
    void DeleteIndex(off_t pos);
    /*Insert int into bpt, pos is bpt's head addr(store in catalog file),value is the addr of this record*/
    void InsertKey(off_t pos,int key,off_t value);
    /*Insert float into bpt*/
    void InsertKey(off_t pos,float key,off_t value);
    /*insert char into bpt*/
    void InsertKey(off_t pos,char *key,off_t value);
    //void InsertKey(off_t pos,sqlstruct::insertitem item,off_t value);
    /*delete char key*/
    void DeleteKey(off_t pos,char *key);
    /*delete int key*/
    void DeleteKey(off_t pos,int key);
    /*delete float key*/
    void DeleteKey(off_t pos,float key);
    /*search int key*/
    off_t SearchKey(off_t pos,int key);
    /*search float key*/
    off_t SearchKey(off_t pos,float key);
    /*search char key*/
    off_t SearchKey(off_t pos,char *key);
};
#endif /* defined(____IndexManager__) */

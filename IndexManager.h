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
    void operator=(const float &a){
        value = a;
    }
    Float(const float &a){
        value = a;
    }
    Float(){
    }
};
struct String{
    char *value;
    size_t size;
    bool cmp(const struct String &a,const struct String &b) const {
        return strcmp(a.value,b.value);
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
    void operator=(const char *a){
        memset(value, 0, size*sizeof(char));
        strcpy(value, a);
    }
    String(const char *a){
        size = strlen(a);
        value = new char [size];
        strcpy(value,a);
    }
    String(){}
    ~String(){
        delete [] value;
    }
};


class IndexManager {
public:
    void InitFromEmpty();
    void InitFromFile();
    off_t newIndex(int dataType);
    void DeleteIndex(off_t pos);
    void InsertKey(off_t pos,int key,off_t value);
    void InsertKey(off_t pos,float key,off_t value);
    void InsertKey(off_t pos,char *key,off_t value);
    void InsertKey(off_t pos,sqlstruct::insertitem item,off_t value);
    void DeleteKey(off_t pos,char *key);
    void DeleteKey(off_t pos,int key);
    void DeleteKey(off_t pos,float key);
    off_t SearchKey(off_t pos,int key);
    off_t SearchKey(off_t pos,float key);
    off_t SearchKey(off_t pos,char *key);
};
#endif /* defined(____IndexManager__) */

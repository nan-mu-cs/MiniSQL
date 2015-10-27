//
//  SelectValue.hpp
//  MiniSQL
//
//  Created by 顾秀烨 on 10/24/15.
//  Copyright © 2015 laoreja. All rights reserved.
//

#ifndef SelectValue_hpp
#define SelectValue_hpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "BufferManager.hpp"

enum SelectOp{EQUAL = 1, NOTEQUAL, LESSTHAN, GREATERTHAN, LESSOREQUAL, GREATEROREQUAL};

enum valueType{INT = 1, CHARN, FLOAT};


class selectValue{
private:
    const float ZERO = 0.00001;
public:
    valueType type;
    int* iValue = NULL;
    float* fValue = NULL;
    char* cValue = NULL;
    size_t size;
    
    selectValue(){}
    selectValue(const selectValue& v){
        type = v.type;
        size = v.size;
        switch (type) {
            case INT:
                iValue = (int*)malloc(size);
                *iValue = *(v.iValue);
                break;
            case FLOAT:
                fValue = (float*)malloc(size);
                *fValue = *(v.fValue);
                break;
            case CHARN:
                cValue = (char*)malloc(size);
                strcpy(cValue, v.cValue);
                break;
                
            default:
                break;
        }
    }
    
    selectValue& operator=(const selectValue& v){
        if (this != &v) {
            type = v.type;
            size = v.size;
            switch (type) {
                case INT:
                    iValue = (int*)malloc(size);
                    *iValue = *(v.iValue);
                    break;
                case FLOAT:
                    fValue = (float*)malloc(size);
                    *fValue = *(v.fValue);
                    break;
                case CHARN:
                    cValue = (char*)malloc(size);
                    strcpy(cValue, v.cValue);
                    break;
                    
                default:
                    break;
            }
        }
        return *this;
    }
    
    
    void setValue(valueType typeInput, size_t sizeInput){
        type = typeInput;
        size = sizeInput;
        switch (typeInput) {
            case INT:
                iValue = (int *)malloc(sizeof(int));
                break;
            case FLOAT:
                fValue = (float *)malloc(sizeof(float));
                break;
            case CHARN:
                cValue = (char *)malloc(sizeInput);
                
            default:
                break;
        }
    }


    
    // return [this op v2]
    bool operation(SelectOp op, selectValue v2){
        switch (op) {
            case EQUAL:
                return this->equals(v2);
                break;
            case NOTEQUAL:
                return !this->equals(v2);
                break;
            case LESSTHAN:
                return this->lessThan(v2);
                break;
            case GREATERTHAN:
                return v2.lessThan(*this);
                break;
            case LESSOREQUAL:
                return !v2.lessThan(*this);
                break;
            case GREATEROREQUAL:
                return !(this->lessThan(v2));
                break;
            default:
                break;
        }
    }
    
    bool equals(selectValue v2){
        if (v2.type != type) {
            throw typeNotMatchError;
        }
        switch (type) {
            case INT:
                return *iValue == *(v2.iValue);
                break;
            case CHARN:
                if (this->size != v2.size) {
                    throw typeNotMatchError;
                }
                if (strcmp(cValue, v2.cValue) == 0) {
                    return true;
                }else{
                    return false;
                }
            case FLOAT:
                return abs(*fValue - *(v2.fValue)) < ZERO;
        }
    }
    
    bool lessThan(selectValue v2){
        if (v2.type != type) {
            throw typeNotMatchError;
        }
        switch (type) {
            case INT:
                return *iValue < *(v2.iValue);
                break;
            case CHARN:
                if (this->size != v2.size) {
                    throw typeNotMatchError;
                }
                if (strcmp(cValue, v2.cValue) < 0) {
                    return true;
                }else{
                    return false;
                }
                break;
            case FLOAT:
                return *fValue < *(v2.fValue);
                break;
        }

    }
};

class intValue: public selectValue{
public:
    intValue(int v){
        type = INT;
        size = sizeof(int);
        iValue = (int *)malloc(size);
        *iValue = v;
    }
//    intValue(const intValue& v){
//        type = INT;
//        size = sizeof(int);
//        iValue = (int *)malloc(size);
//        *iValue = *(v.iValue);
//    }
    
    ~intValue(){
        free(iValue);
    }
};

class floatValue: public selectValue{
public:
    floatValue(float v){
        type = FLOAT;
        size = sizeof(float);
        fValue = (float *)malloc(size);
        *fValue = v;
    }
//    floatValue(const floatValue& v){
//        type = FLOAT;
//        size = sizeof(float);
//        fValue = (float *)malloc(size);
//        *fValue = *(v.fValue);
//    }
    ~floatValue(){
        free(fValue);
    }
};

class charNValue: public selectValue{
public:
    charNValue(int n, char* v){
        type = CHARN;
        size = sizeof(char) * n;
        cValue = (char *)malloc(size);
        strcpy(cValue, v);
    }
//    charNValue(const charNValue& v){
//        type = CHARN;
//        size = v.size;
//        cValue = (char *)malloc(size);
//        strcpy(cValue, v.cValue);
//    }
    ~charNValue(){
        free(cValue);
    }
};

#endif /* SelectValue_hpp */

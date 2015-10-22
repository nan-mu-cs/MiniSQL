//
//  Interpreter.h
//  
//
//  Created by 杨凯 on 15/10/16.
//
//

#ifndef ____Interpreter__
#define ____Interpreter__

#include <iostream>
#include "sqlparser_driver.hh"
#include "CatalogManager.h"
using std::istream;
using std::ostream;
class Interpreter:public sqlparser_driver{
#define SIZE 50000
public:
    void run();
    istream &in;
    ostream &out;
    std::string tmp,used,left;
    bool checktable;
    sqlstruct::createtable ctable;
    CatalogManager *cm;
    std::string strexec;
    Interpreter(istream &is,ostream &os,CatalogManager* cm):in(is),out(os){
        this->cm = cm;
    }
    void Createtable(sqlstruct::createtable &node);
    void DropTable(std::string table);//done
    void DropIndex(std::string node);//done
    void CreateIndex(sqlstruct::createindex &node);//done
    void ExecFile(std::string filename);//done
    void InsertValues(sqlstruct::insertvalues node);//done
    void Select(sqlstruct::selecttable node) ;//not check where clause
    void Delete(sqlstruct::deletetable node);//not check where clause
    void Exit(){exit(0);};
    //void Parser(istream &in,bool file = false);
    void ParserFile(std::string filepath);
    //void ParserStr(std::string);
    void Test(){
        std::cout << "Hello world" << std::endl;}
    //void Test(){ out << "Hello world" << std::endl;}
   // ~Interpreter(){}
    //FILE *fmemopen(void *buf, size_t size, const char *opentype);
};
#endif /* defined(____Interpreter__) */

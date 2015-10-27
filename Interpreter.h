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
private:
    std::string tmp,used,left;
    bool checktable;
    sqlstruct::createtable ctable;
    CatalogManager *cm;
    std::string strexec;
public:
    //input stream
    istream &in;
    //output stream
    ostream &out;
    /*run interpreter*/
    void run();
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
    void ParserFile(std::string filepath);
};
#endif /* defined(____Interpreter__) */

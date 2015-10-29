//
//  API.h
//  
//
//  Created by 杨凯 on 15/10/28.
//
//

#ifndef ____API__
#define ____API__

#include <stdio.h>
#include "IndexManager.h"
#include "RecordManager.hpp"
#include "CatalogManager.h"
#include "sqlstruct.h"
class API{
public:
    IndexManager *im;
    RecordManager *rm;
    CatalogManager *cm;
    std::string currentpath = "/Users/andyyang/Documents/MiniSQL/MiniSQL/";
    void CreateTable(sqlstruct::createtable &table,std::string createstr,std::string &msg);
    void DropTable(std::string name,off_t tablepos,std::string &msg);
    void CreateIndex(sqlstruct::createindex &index,sqlstruct::createtable &table,off_t tablepos,std::string &msg);//not add msg
    void DropIndex(std::string name,off_t indexpos,std::string &msg);
    void InsertValues(sqlstruct::createtable &table,sqlstruct::insertvalues &item,off_t tablepos,std::string &msg);
    vector<vector<string>> Select(sqlstruct::createtable &table,sqlstruct::astree *root,std::string &msg);
    void Delete(sqlstruct::createtable &table,sqlstruct::astree *root,std::string &msg);
private:
    vector<condition> GenCondition(sqlstruct::astree *root,sqlstruct::createtable &table);
    int CalStarPos(sqlstruct::createtable &table,int i);
};

#endif /* defined(____API__) */

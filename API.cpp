//
//  API.cpp
//  
//
//  Created by 杨凯 on 15/10/28.
//
//

#include "API.h"
#include <sstream>
#include <map>
#include <algorithm>
using std::stringstream;
using std::string;
using std::map;
void API::CreateTable(sqlstruct::createtable &table,string createstr,string &msg){
    rm->createTableFile(currentpath + table.name);
    int ntable = 0;
    if(!cm->addTable(table.name, createstr)){
        msg = "Error:fail to add table " + table.name;
        return ;
    }
    off_t tablepos;
    if(!cm->FindTable(table.name, tablepos)){
        msg = "Error: fail to create table "+ table.name;
        return ;
    }
    ntable = 1;
    if(table.col.primarykey.size()>0){
        string colname = table.col.primarykey;
        int i = 0;
        for(i = 0;i<table.col.record.size();i++)
            if(table.col.record[i].name == colname)
                break;
        if(i<table.col.record.size()){
            //off_t indexpos = im->newIndex(table.col.record[i].data_type);
            //cm->addIndex(<#sqlstruct::createindex index#>, indexpos);
            sqlstruct::col_attr attr;
            attr.type = sqlstruct::UNIQUE;
            table.col.record[i].attr.push_back(attr);
        }
        //im->newIndex(<#int dataType#>)
    }
    int nindex = 0;
    for(int i = 0;i<table.col.record.size();i++){
        int j = 0;
        for(j = 0;j<table.col.record[i].attr.size();i++)
            if(table.col.record[i].attr[j].type == sqlstruct::UNIQUE)
                break;
        if(j<table.col.record[i].attr.size()){
            sqlstruct::createindex cindex;
            cindex.indexname = table.col.record[i].name;
            cindex.tablename = table.name;
            cindex.col.push_back(cindex.indexname);
            off_t indexpos = im->newIndex(table.col.record[i].data_type);
            if(!cm->addIndex(cindex, tablepos,indexpos)){
                msg = "Error:fail to add index " + cindex.indexname;
                return ;
            }
            nindex++;
        }
    }
    stringstream ss;
    ss << "Sucessfully create " << ntable << " table and "<< nindex << " index";
    msg = ss.str();
}

void API::DropTable(string name,off_t tablepos,string &msg){
    catalog::table_t table = cm->FindTable(tablepos);
    for(int i = 0;i<table.numofIndex;i++){
        off_t indexpos;
        if(!cm->FindIndex(table.index[i], indexpos))
        {
            msg = "Error:fail to drop table " +  name + "'s index " + table.index[i];
            return ;
        }
        catalog::index_t index = cm->FindIndex(indexpos);
        im->DeleteIndex(indexpos);
    }
    rm->deleteTableFile(currentpath + name);
    if(!cm->dropTable(name)){
        msg = "Error: fail to drop table " + name;
        return ;
    }
    stringstream ss;
    ss << "Successfully drop table "+ name + "and its " << table.numofIndex << " index";
}

void API::CreateIndex(sqlstruct::createindex &index, sqlstruct::createtable &table, off_t tablepos, string &msg){
    int i = 0;
    bool flag = false;
    int attr_pos = 0;
    int recordsize = 0;
    int colindex = 0;
    map<string,int> indexmap;
    catalog::table_t ctable = cm->FindTable(tablepos);
    for(int i = 0;i<ctable.numofIndex;i++){
        off_t tmpos = 0;
        if(cm->FindIndex(ctable.index[i], tmpos)){
            catalog::index_t tmpindex = cm->FindIndex(tmpos);
            indexmap[tmpindex.col[0]] = 1;
        }
    }
    if(indexmap.find(index.col[0])!=indexmap.end()){
        msg = "Error: table " + table.name + " already has index on " + index.col[0];
        return ;

    }
    for(i = 0;i<table.col.record.size();i++){
        if(table.col.record[i].name == index.col[0]){
            flag = true;
            attr_pos = recordsize;
            colindex = i;
        }
        recordsize += table.col.record[i].size();
    }
    if(!flag){
        return ;
    }
    int data_type = table.col.record[colindex].data_type;
    off_t indexpos = im->newIndex(data_type);
    cm->addIndex(index, tablepos,indexpos);
    off_t posofindex = 0;
    if(!cm->FindIndex(index.indexname, posofindex)){
        msg = "Error:fail to create index " + index.indexname;
        return ;
    }
    //catalog::index_t cindex = cm->FindIndex(posofindex);
    //catalog::table_t itable = cm->FindTable(tablepos);
    vector<indexPair> result = rm->returnIndexInfo(currentpath + table.name, attr_pos, data_type, recordsize);
    for(int i = 0;i<result.size();i++){
        off_t recordpos = result[i].second.blockNum*BLOCKREMAINDER + result[i].second.offset;
        if(data_type == sqlstruct::INTNUM)
            im->InsertKey(indexpos, atoi(result[i].first.c_str()), recordpos);
        else if(data_type == sqlstruct::FLOATNUM)
            im->InsertKey(indexpos, (float)atof(result[i].first.c_str()), recordpos);
        else if(data_type >= sqlstruct::CHAR){
            char *str = new char[result[i].first.length()+1];
            strcpy(str, result[i].first.c_str());
            im->InsertKey(indexpos,str, recordpos);
            if(str)
                delete str;
        }
    }
    msg = "Sucessfully create index " + index.indexname;
}

void API::DropIndex(std::string name,off_t indexpos,std::string &msg){
    catalog::index_t index = cm->FindIndex(indexpos);
    im->DeleteIndex(index.pos);
    cm->dropIndex(name);
    msg = "Successfully drop index " + name;
}

void API::InsertValues(sqlstruct::createtable &table,sqlstruct::insertvalues &item,off_t tablepos,string &msg){
    int recordSize = 0;
    for(int i = 0;i<table.col.record.size();i++)
        recordSize += table.col.record[i].size();
    catalog::table_t cataTable = cm->FindTable(tablepos);
    for(int i = 0;i<cataTable.numofIndex;i++){
        off_t indexpos = 0;
        if(!cm->FindIndex(cataTable.index[i], indexpos)){
            msg = "Error: fail to insert into table " + table.name + "'s index " + cataTable.index[i];
            return ;
        }
        catalog::index_t index = cm->FindIndex(indexpos);
        int j = 0;
        int data_type = 0;
        for(j = 0;j<table.col.record.size();j++)
            if(table.col.record[j].name == index.col[0])
            {
                data_type = table.col.record[j].data_type;
                break;
            }
        if(j == table.col.record.size())
        {
            return ;
        }
        switch (data_type) {
            case sqlstruct::INTNUM:{
                int ivalue = atoi(item.item[j].value.c_str());
                if(im->SearchKey(index.pos, ivalue)!=-1){
                    msg = "Error: There already exists a record col " + index.col[0] + " has value " + item.item[j].value;
                    return ;
                }
                //im->InsertKey(indexpos, ivalue, itempos);
                break;
            }
            case sqlstruct::FLOATNUM:{
                float fvalue = atof(item.item[j].value.c_str());
                if(im->SearchKey(index.pos, fvalue)!=-1){
                    msg = "Error: There already exists a record col " + index.col[0] + " has value " + item.item[j].value;
                    return ;
                }
                //im->InsertKey(indexpos, fvalue, itempos);
                break;
            }
            default:
                char *str = new char [item.item[j].value.length()+1];
                strcpy(str, item.item[j].value.c_str());
                if(im->SearchKey(index.pos, str)!=-1){
                    msg = "Error: There already exists a record col " + index.col[0] + " has value " + item.item[j].value;
                    return ;
                }
                //im->InsertKey(indexpos, str, itempos);
                delete str;
                break;
        }
    }
    recordPointer itempointer = rm->insertRecords(currentpath + table.name, item.item, recordSize);
    off_t itempos = itempointer.blockNum*BLOCKREMAINDER + itempointer.offset;
    for(int i = 0;i<cataTable.numofIndex;i++){
        off_t indexpos = 0;
        if(!cm->FindIndex(cataTable.index[i], indexpos)){
            msg = "Error: fail to insert into table " + table.name + "'s index " + cataTable.index[i];
            return ;
        }
        catalog::index_t index = cm->FindIndex(indexpos);
        int j = 0;
        int data_type = 0;
        for(j = 0;j<table.col.record.size();j++)
            if(table.col.record[j].name == index.col[0])
            {
                data_type = table.col.record[j].data_type;
                break;
            }
        if(j == table.col.record.size())
        {
            return ;
        }
        switch (data_type) {
            case sqlstruct::INTNUM:{
                int ivalue = atoi(item.item[j].value.c_str());
                im->InsertKey(index.pos, ivalue, itempos);
                break;
            }
            case sqlstruct::FLOATNUM:{
                float fvalue = atof(item.item[j].value.c_str());
                im->InsertKey(index.pos, fvalue, itempos);
                break;
            }
            default:
                char *str = new char [item.item[j].value.length()+1];
                strcpy(str, item.item[j].value.c_str());
                im->InsertKey(index.pos, str, itempos);
                delete str;
                break;
        }
    }
    msg = "Sucessfully insert 1 record";
}
int API::CalStarPos(sqlstruct::createtable &table,int index){
    int startpos = 0;
    if(index >= table.col.record.size())
        return -1;
    for(int i = 0;i<index;i++)
        startpos += table.col.record[i].size();
    return startpos;
}
vector<condition> API::GenCondition(sqlstruct::astree *root,sqlstruct::createtable &table){
    vector<condition> result;
    if(root == NULL)
        return result;
    if(root->isleaf)
        return result;
    if(root->operate == AND)
    {
        vector<condition> left = GenCondition(root->left, table);
        vector<condition> right = GenCondition(root->right, table);
        result.insert(result.end(), left.begin(),left.end());
        result.insert(result.end(), right.begin(),right.end());
    }
    else {
        int index = atoi(root->left->value.value.c_str());
        int startpos = CalStarPos(table, index);
        insertitem item;
        item.value = root->right->value.value;
        if(root->right->value.type>=sqlstruct::CHAR&&table.col.record[index].data_type>=sqlstruct::CHAR)
            item.data_type = table.col.record[index].data_type;
        else item.data_type = root->right->value.type;
        result.push_back(condition(startpos, (operate)root->operate, item));
    }
    return result;
}
vector<vector<string>> API::Select(sqlstruct::createtable &table,sqlstruct::astree *root,std::string &msg){
    vector<int> attrTypes;
    int recordSize;
    for(int i = 0;i<table.col.record.size();i++){
        recordSize += table.col.record[i].size();
        attrTypes.push_back(table.col.record[i].data_type);
    }
    vector<condition> result = GenCondition(root,table);
    return rm->selectRecords(currentpath + table.name, recordSize, result, attrTypes);
}
bool API::cmp(const del_t &a,const del_t &b){
    return a.startpos < b.startpos;
}
void API::Delete(sqlstruct::createtable &table,sqlstruct::astree *root,off_t tablepos,std::string &msg){
    int recordSize;
    vector<int> attrTypes;
    for(int i = 0;i<table.col.record.size();i++){
        recordSize += table.col.record[i].size();
        attrTypes.push_back(table.col.record[i].data_type);
    }
    vector<condition> result = GenCondition(root,table);
    vector<int> attrPos;
    vector<del_t> delset;
    catalog::table_t ctable = cm->FindTable(tablepos);
    for(int i = 0;i<ctable.numofIndex;i++){
        off_t indexpos = 0;
        if(cm->FindIndex(ctable.index[i], indexpos)){
            catalog::index_t cindex = cm->FindIndex(indexpos);
            int startpos = 0;
            int j;
            for(j = 0;j<table.col.record.size();j++){
                if(table.col.record[j].name == cindex.col[0]){
                    break;
                }
                startpos += table.col.record[j].size();
            }
            if(j<table.col.record.size()){
                attrPos.push_back(startpos);
                del_t tmp;
                tmp.startpos = startpos;
                tmp.data_type = table.col.record[j].data_type;
                tmp.pos = cindex.pos;
                delset.push_back(tmp);
            }
        }
    }
    sort(attrPos.begin(), attrPos.end());
    sort(delset.begin(), delset.end(), cmp);
    vector<vector<string>> delrecord = rm->deleteRecords(currentpath + table.name, recordSize, result, attrPos, attrTypes);
    for(int i = 0;i<delrecord.size();i++){
        for(int j = 0;j<delrecord[i].size();j++){
            if(delset[j].data_type == sqlstruct::INTNUM){
                im->DeleteKey(delset[j].pos, atoi(delrecord[i][j].c_str()));
            }
            else if(delset[j].data_type == sqlstruct::FLOATNUM){
                im->DeleteKey(delset[j].pos, (float)atof(delrecord[i][j].c_str()));
            }
            else {
                size_t size = delrecord[i][j].length() + 1;
                char *str = new char [size];
                strcpy(str, delrecord[i][j].c_str());
                im->DeleteKey(delset[j].pos, str);
                delete str;
            }
        }
    }
    stringstream ss;
    ss << "Successfully delete "  << delrecord.size() << " records" ;
    msg = ss.str();
}

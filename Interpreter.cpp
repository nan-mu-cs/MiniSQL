//
//  Interpreter.cpp
//  
//
//  Created by 杨凯 on 15/10/16.
//
//

#include "Interpreter.h"
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#define CHARBASE 120000
using std::istream;
using std::string;
using std::endl;
using std::ifstream;
using std::stringstream;
void Interpreter::run(){
    FILE *stream;
    string tmp,used,left;
    while(1){
        getline(in,tmp);
        tmp += "\n";
        int i;
        for(i = 0;i<tmp.length();i++)
            if(tmp[i] == ';'){
                used += ';';
                break;
            }
            else {
                used += tmp[i];
            }
        if(i<tmp.length()){
            i++;
            used = left + used;
            tmp.clear();
            left.clear();
            strexec = used;
            checktable = false;
            stream = fmemopen((void *)used.c_str(),used.length(),"r");
            used.clear();
            for(;i<tmp.length();i++)
                left += tmp[i];
            parse(stream);
            fclose(stream);
        }
    }
}
void Interpreter::ParserFile(string filepath){
    ifstream fin;
    fin.open(filepath.c_str(),std::ifstream::in);
    FILE *stream;
    while(getline(fin, tmp)){
        tmp += "\n";
        int i;
        for(i = 0;i<tmp.length();i++)
            if(tmp[i] == ';'){
                used += ';';
                break;
            }
            else {
                used += tmp[i];
            }
        if(i<tmp.length()){
            i++;
            used = left + used;
            tmp.clear();
            left.clear();
            strexec = used;
            stream = fmemopen((void *)used.c_str(),used.length(),"r");
            scanPushBuffer(stream);
            used.clear();
            for(;i<tmp.length();i++)
                left += tmp[i];
            parse(stream);
            scanPopBuffer();
            fclose(stream);
        }
    }
}
/*
void Interpreter::ParserStr(string str){
    FILE *stream;
    stream = fmemopen((void *)str.c_str(),str.length(),"r");
    parse(stream);
    fclose(stream);
}
 */
void Interpreter::Createtable(sqlstruct::createtable &node){
    /*
    if(checktable){
        ctable = node;
        return ;
    }*/
    off_t pos;
    if(cm->FindTable(node.name, pos)){
        out << "Error: Table " + node.name + " Already Exist" << endl;
        return ;
    }
    cm->addTable(node.name, strexec);
    this->pos = rm->CreateTable(node.col.record);
}

void Interpreter::DropTable(std::string table){
    off_t pos;
    if(!cm->FindTable(table, pos)){
        out << "Error: Table " + table + " does not exist" << endl;
        return ;
    }
    cm->dropTable(table);
}

void Interpreter::DropIndex(string node){
    off_t pos;
    if(!cm->FindIndex(node, pos)){
        out << "Error: Index " + node << " does not exist" << endl;
        return ;
    }
    cm->dropIndex(node);
}

void Interpreter::CreateIndex(sqlstruct::createindex &node){
    off_t ipos;
    if(cm->FindIndex(node.indexname, ipos)){
        out << "Error: Index " + node.indexname << " Already exist" << endl;
        return ;
    }
    off_t tpos;
    if(!cm->FindTable(node.tablename, tpos)){
        out << "Error: Table " << node.tablename << " does not exist" << endl;
        return ;
    }
    sqlstruct::createtable table = cm->GetTableSchema(tpos);
    for(int i = 0;i<node.col.size();i++){
        int j;
        for(j = 0;j<table.col.record.size();j++)
            if(node.col[i] == table.col.record[j].name)
                break;
        if(j == table.col.record.size()){
            out << "Error: Table " << node.tablename << " does not have cols " << node.col[i] << endl;
            return ;
        }
    }
    cm->addIndex(node, tpos);
}

void Interpreter::ExecFile(std::string filename){
    struct stat buffer;
    if(stat(filename.c_str(),&buffer) == -1){
        out << "Error: File " + filename << " does not exist" << endl;
        return ;
    }
    //FILE *stream = fopen(filename.c_str(), "r");
    //scanPushBuffer(stream);
    //yy::sqlparser parser(*this);
    //parser.set_debug_level(false);
    //parser.parse();
    //fclose(stream);
    //scanPopBuffer();
    ParserFile(filename);
}

void Interpreter::InsertValues(sqlstruct::insertvalues node){
    off_t pos;
    if(!cm->FindTable(node.tablename,pos)){
        out << "Error: Table " + node.tablename + " does not exist" << endl;
        return ;
    }
    sqlstruct::createtable table = cm->GetTableSchema(pos);
    //sqlstruct::createtable table = ctable;
    if(node.item.size()!=table.col.record.size()){
        out << "Error: Table " << node.tablename << " has " << table.col.record.size() << " cols "
        << "input " << node.item.size() << " cols" << endl;
    }
    for(int i = 0;i<node.item.size();i++){
        if(node.item[i].data_type == sqlstruct::STRING&&table.col.record[i].data_type>CHARBASE){
            if(node.item[i].value.length()>table.col.record[i].data_type - sqlstruct::CHAR + 1){
                out << "Error : string out of length" << '(' << node.item[i].value <<')' << endl;
                return ;
            }
            node.item[i].data_type = table.col.record[i].data_type;
        }
        else if(node.item[i].data_type!=table.col.record[i].data_type){
            out << "Error: Data type does not match" << '(' << node.item[i].value <<')'<<endl;
            return ;
        }
    }
    rm->InsertRecord(this->pos, node.item);
}

void Interpreter::Select(sqlstruct::selecttable node){
    off_t pos;
    if(!cm->FindTable(node.fromtable,pos)){
        out << "Error: Table " + node.fromtable + " does not exist" << endl;
        return ;
    }
    //string createstr = ;
    //FILE *stream = fmemopen((void *)createstr.c_str(),createstr.length(),"r");
    //scanPushBuffer(stream);
    sqlstruct::createtable table = cm->GetTableSchema(pos);
    if(node.col.size()){
        for(int i = 0;i<node.col.size();i++)
        {
            int j;
            for(j = 0;j<table.col.record.size();j++)
                if(table.col.record[i].name == node.col[i])
                    break;
            if(j == table.col.record.size()){
                out << "Error: " + node.col[i] << " cols does not exist in table " << node.fromtable << endl;
                return ;
            }
        }
    }
    //evalASTree(node.where);
    if(!CheckWhere(table, node.where)){
        out << "Error: Where Clause is invalid" << endl;
        return ;
    }
    rm->Search(this->pos, table.col.record, node.where);
}

void Interpreter::Delete(sqlstruct::deletetable node){
    off_t pos;
    if(!cm->FindTable(node.fromtable, pos)){
        out << "Error: Table " + node.fromtable + " does not exist" << endl;
        return ;
    }
    sqlstruct::createtable table = cm->GetTableSchema(pos);
    if(!CheckWhere(table, node.where)){
        out << "Error: Where Clause is invalid" << endl;
        return ;
    }
    rm->DeleteRecord(this->pos, table.col.record, node.where);
}

void Exit(){
    
}
bool Interpreter::CheckWhere(sqlstruct::createtable table,sqlstruct::astree *root){
    if(root == NULL)
        return true;
    else if(!root->isleaf){
        if(root->operate == sqlstruct::NOT)
            return CheckWhere(table, root->left);
        else return CheckWhere(table, root->left)&&CheckWhere(table, root->right);
    }
    else {
        if(root->value.type == sqlstruct::VARIABLE){
            int i = 0;
            for(i = 0;i<table.col.record.size();i++)
                if(table.col.record[i].name == root->value.value)
                    break;
            if(i == table.col.record.size())
                return false;
            stringstream ss;
            ss << i;
            root->value.value = ss.str();
        }
    }
    return true;
}


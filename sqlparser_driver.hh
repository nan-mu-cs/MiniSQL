#ifndef SQLPARSER_DRIVER_HH
#define SQLPARSER_DRIVER_HH
#include <iostream>
#include <string>
#include <map>
#include "sqlparser.hh"
#include "sqlstruct.h"
//typedef yy::sqlparser::symbol symbol;

#define YY_DECL yy::sqlparser::symbol_type \
	yylex (sqlparser_driver &driver)

YY_DECL;
class sqlparser_driver{
	public:
    int test;
        sqlparser_driver();
		bool berror;
		//virtual ~sqlparser_driver();
    
		void scan_begin();
    void scan_begin(FILE *fp);
    virtual void Test(){}
		void scan_end();
		bool trace_scanning;
		int parse(const std::string &f);
		int parse(FILE *fp);
		std::string file;
		bool trace_parsing;
        FILE *fmemopen(void *buf, size_t size, const char *opentype);
		void error(const yy::location& l,const std::string &m);
		void error(const std::string &m);
		virtual void  Createtable(sqlstruct::createtable &node){
		/*
            std::cout << "Name: " << node.name << std::endl;
			if(node.col.primarykey.size())
				std::cout << "Primary Key " << node.col.primarykey[0] << std::endl;
			//if(node.col.indexkey.size())
			//	std::cout << "Index Key" << node.col.indexkey[0] << std::endl;
			std::cout << "Record:" << std::endl;
			std::cout << "recordSize: " << node.col.record.size() << std::endl;
			for(int i = 0;i<node.col.record.size();i++){
				std::cout << "recordname: " << node.col.record[i].name << "datatype: " <<node.col.record[i].data_type;
				for(int j = 0;j<node.col.record[i].attr.size();i++)
					std::cout << "attr: " << node.col.record[i].attr[j].type <<' '<< std::endl;
			}
         */
            std::cout << "hello world" << std::endl;
		}

		virtual void DropTable(std::string table){
			std::cout << "Drop table: " << table << std::endl;
		}

    virtual void DropIndex(std::string node){
		}
		virtual void CreateIndex(sqlstruct::createindex &node){
			std::cout << "Table Name: " << node.tablename << std::endl;
			std::cout << "Index Name: " << node.indexname << std::endl;
			for(int i = 0;i<node.col.size();i++)
				std::cout << node.col[i]<< ' ';
			std::cout << std::endl;
		}
		virtual void ExecFile(std::string filename){
			std::cout << filename << std::endl;
		}
		virtual void InsertValues(sqlstruct::insertvalues node){
			std::cout << "Table name: " << node.tablename << std::endl;
			for(int i = 0;i<node.item.size();i++){
				std::cout << "Datatype: " << node.item[i].data_type <<' ';
				if(node.item[i].data_type!=sqlstruct::DEFAULT)
					std::cout << "VALUES " << node.item[i].value;
				std::cout << std::endl;
			}
		}
		sqlstruct::astree * newLeafNode(sqlstruct::ele_t value){
			sqlstruct::astree *node = new sqlstruct::astree;
			node->value = value;
			node->left = node->right = NULL;
			node->isleaf = true;
			return node;
		}
		virtual sqlstruct::astree * newInternalNode(sqlstruct::astree*left,int operate,sqlstruct::astree *right){
			sqlstruct::astree *node = new sqlstruct::astree;
			node->left = left;
			node->right = right;
			node->operate = operate;
			node->isleaf = false;
			return node;
		}
		void freeASTree(sqlstruct::astree *root){
			if(root->isleaf)
			{
				delete root;
				return ;
			}
			if(root->left)
				freeASTree(root->left);
			if(root->right)
				freeASTree(root->right);
			delete root;
		}
		void evalASTree(sqlstruct::astree *root){
			if(root == NULL)
				return ;
			if(root->isleaf){
                //std::cout << root->value.value << std::endl;
				return ;
			}
            /*
			if(root->operate == sqlstruct::NOT||root->operate == sqlstruct::ISNULL){
				std::cout << root->operate << std::endl;
				evalASTree(root->left);
			}*/
			else {
				evalASTree(root->left);
                //std::cout << root->operate << std::endl;
				evalASTree(root->right);
			}
		}
        virtual void Select(sqlstruct::selecttable node);
		virtual void Delete(sqlstruct::deletetable node){
			std::cout << "From table: " << node.fromtable << std::endl;
			if(node.deleteall)
				std::cout << "Delete ALL" <<std::endl;
			else evalASTree(node.where);
		}
		virtual void Exit(){
			exit(0);
		}
    void scanPushBuffer(FILE *fp);
    void scanPopBuffer();
};
#endif

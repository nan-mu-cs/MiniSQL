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
		sqlparser_driver();
		virtual ~sqlparser_driver();

		std::map<std::string,int> variables;
		void scan_begin();
		void scan_end();
		bool trace_scanning;
		
		int parse(const std::string &f);
		int parse(FILE *fp);
		std::string file;
		bool trace_parsing;

		void error(const yy::location& l,const std::string &m);
		void error(const std::string &m);
		void 	Createtable(sqlstruct::createtable &node){
			std::cout << "Name: " << node.name << std::endl;
			if(node.col.primarykey.size())
				std::cout << "Primary Key " << node.col.primarykey[0] << std::endl;
			if(node.col.indexkey.size())
				std::cout << "Index Key" << node.col.indexkey[0] << std::endl;
			std::cout << "Record:" << std::endl;
			std::cout << "recordSize: " << node.col.record.size() << std::endl;
			for(int i = 0;i<node.col.record.size();i++){
				std::cout << "recordname: " << node.col.record[i].name << "datatype: " <<node.col.record[i].data_type;
				for(int j = 0;j<node.col.record[i].attr.size();i++)
					std::cout << "attr: " << node.col.record[i].attr[j].type <<' '<< std::endl;
			}
		}
		void DropTable(std::string table){
			std::cout << "Drop table: " << table << std::endl;
		}
		void DropIndex(sqlstruct::dropindex &node){
			std::cout << "Table Name: " << node.tablename << std::endl;
			std::cout << "Index Name: " << node.indexname << std::endl;
			for(int i = 0;i<node.col.size();i++)
				std::cout << node.col[i]<< ' ';
			std::cout << std::endl;
		}
		void CreateIndex(sqlstruct::createindex &node){
			std::cout << "Table Name: " << node.tablename << std::endl;
			std::cout << "Index Name: " << node.indexname << std::endl;
			for(int i = 0;i<node.col.size();i++)
				std::cout << node.col[i]<< ' ';
			std::cout << std::endl;
		}
		void ExecFile(std::string filename){
			std::cout << filename << std::endl;
		}
		void InsertValues(sqlstruct::insertvalues node){
			std::cout << "Table name: " << node.tablename << std::endl;
			for(int i = 0;i<node.item.size();i++){
				std::cout << "Datatype: " << node.item[i].data_type <<' ';
				if(node.item[i].data_type!=sqlstruct::DEFAULT)
					std::cout << "VALUES " << node.item[i].value;
				std::cout << std::endl;
			}
		}
		sqlstruct::astree * newLeafNode(std::string value){
			sqlstruct::astree *node = new sqlstruct::astree;
			node->value = value;
			node->left = node->right = NULL;
			node->isleaf = true;
			return node;
		}
		sqlstruct::astree * newInternalNode(sqlstruct::astree*left,int operate,sqlstruct::astree *right){
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
				std::cout << root->value << ' ';
				return ;
			}
			if(root->operate == sqlstruct::NOT||root->operate == sqlstruct::ISNULL){
				std::cout << root->operate << ' ';
				evalASTree(root->left);
			}
			else {
				evalASTree(root->left);
				std::cout << root->operate << ' ';
				evalASTree(root->right);
			}
		}
		void Select(sqlstruct::selecttable node){
			if(node.selectall)
				std::cout << "SelectALL" <<std::endl;
			else {
				for(int i = 0;i<node.col.size();i++)
					std::cout << node.col[i] << ' ';
				std::cout << std::endl;
			}
			std::cout << "Fromtable: " << node.fromtable << std::endl;
			evalASTree(node.where);
		}
		void Delete(sqlstruct::deletetable node){
			std::cout << "From table: " << node.fromtable << std::endl;
			if(node.deleteall)
				std::cout << "Delete ALL" <<std::endl;
			else evalASTree(node.where);
		}
		void Exit(){
			exit(0);
		}
};
#endif

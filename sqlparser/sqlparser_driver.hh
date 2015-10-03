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
};
#endif

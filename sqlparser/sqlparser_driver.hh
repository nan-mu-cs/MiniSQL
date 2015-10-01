#ifndef SQLPARSER_DRIVER_HH
#define SQLPARSER_DRIVER_HH
#include <iostream>
#include <string>
#include <map>
#include "sqlparser.hh"
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
};
#endif

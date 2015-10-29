%skeleton "lalr1.cc" /* -*- C++ -*- */  
%language "C++"
%require "3.0.4"
%defines
%define parser_class_name {sqlparser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires {
	#include <iostream>
	#include <string>
	#include <vector>
	#include <sstream>
	#include "sqlstruct.h"
	class sqlparser_driver;
	void emit(char *s,...);
	std::string itostr(int value);
	std::string ftostr(float value);
}
%param {sqlparser_driver &driver}
%locations
%initial-action{
	@$.begin.filename = @$.end.filename = &driver.file;
}
%define parse.trace
%define parse.error verbose
%code{
	#include "sqlparser_driver.hh"
}
%token <std::string> NAME
%token <std::string> STRING
%token <int> INTNUM
%token <float> FLOATNUM
%token ADD 
%token ALL
%token ALTER
%token AND
%token AS
%token KEY
%token DELETE
%token DROP
%token QUIT
%token EXECFILE
%token ON
%token CREATE
%token INDEX
%token FROM
%token UPDATE
%token<int> DEFAULT
%token<int> AUTO_INCREMENT
%token EXISTS
%token TABLE
%token CHAR
%token SELECT
%token SET
%token<int> NULLX
%token INT
%token FLOAT
%token VALUES
%token DISTINCT
%token  WHERE
%token<int> UNIQUE
%token INSERT
%token<int> PRIMARY
%token INTO
%token END 0

%token  MINUS "-"
	PLUS "+"
	STAR "*"
	SLASH "/"
	LPAREN "("
	RPAREN ")"
	COMMA ","
	SINGLEAND "&"
	SYMBOLNOT "!"
	SEMICOL	";"
	POINT "."
%right ASSIGN
%left OR
%left XOR
%left ANDOP
%nonassoc IN IS LIKE
%left NOT '!'
%left BETWEEN
%left <int> COMPARISON
%left "|"
%left "&"
%left "+" "-"
%left "*" "/"
%nonassoc UMINUS
/*%type <int> table_references*/
%type <std::vector<std::string>> column_list 
%type <sqlstruct::record_t> create_definition
/*%type <intval> delete_opts*/

/*%type <int>  update_asgn_list*/
%type <int> data_type 
%type <int> opt_length
/*%type <int> update_stmt*/
%type <sqlstruct::create_col_list> create_col_list
%type <sqlstruct::createtable> create_table_stmt
%type <std::vector<sqlstruct::col_attr>> column_atts
%type <std::string> drop_table_stmt
%type <std::string> drop_index_stmt
%type <std::string> execfile_stmt
%type <int> intexp
%type <float> floatexp
%type <std::vector<sqlstruct::insertitem>> insert_vals 
%type <sqlstruct::insertvalues> insert_stmt;
%type <sqlstruct::astree*> expr
%type <std::vector<std::string>> select_expr_list
%type <sqlstruct::astree*> opt_where
%type <sqlstruct::selecttable> select_stmt
%type <sqlstruct::deletetable> delete_stmt
%type <sqlstruct::createindex> create_index_stmt
%type <std::string> filename
%start stmt_list
%%

stmt_list: stmt ";"
	| stmt_list stmt ";"
	| error ";"
	| stmt_list error ";"

expr: NAME { sqlstruct::ele_t ele; ele.value = $1;ele.type = sqlstruct::VARIABLE;$$ = driver.newLeafNode(ele); }
	| intexp {sqlstruct::ele_t ele;ele.value = itostr($1); ele.type = sqlstruct::INTNUM;$$ = driver.newLeafNode(ele);}
	| floatexp {sqlstruct::ele_t ele;ele.value = ftostr($1);ele.type = sqlstruct::FLOATNUM;$$ = driver.newLeafNode(ele);}
	| "(" expr ")" {$$ = $2;}
	| expr ANDOP expr {$$ = driver.newInternalNode($1,sqlstruct::AND,$3);}
/*	| expr OR expr {$$ = driver.newInternalNode($1,sqlstruct::OR,$3);}
	| NOT expr {$$ = driver.newInternalNode($2,sqlstruct::NOT,NULL);}
	| "!" expr {$$ = driver.newInternalNode($2,sqlstruct::NOT,NULL);}*/
/*	| expr COMPARISON expr {$$ = driver.newInternalNode($1,$2,$3);}
	| expr IS NULLX {$$ = driver.newInternalNode($1,sqlstruct::ISNULL,NULL);}
	| expr IS NOT NULLX {$$ = driver.newInternalNode($1,sqlstruct::ISNULL,NULL); $$ = driver.newInternalNode($$,sqlstruct::NOT,NULL);}*/
	| expr BETWEEN expr AND expr %prec BETWEEN { 
						    sqlstruct::astree *left,*right;
						    left = driver.newInternalNode($1,sqlstruct::GREATOREQUAL,$3);
						    right = driver.newInternalNode($1,sqlstruct::LESSOREQUAL,$5);
						    $$ = driver.newInternalNode(left,sqlstruct::AND,right);}
	;
/*stmt: numexp {std::cout << $1 << std::endl;} */

intexp: INTNUM {$$ = $1;}
	| intexp "+" intexp {$$ = $1 + $3;}
	| intexp "-" intexp {$$ = $1 + $3;}
	| intexp "*" intexp {$$ = $1 * $3;}
	| intexp "/" intexp {$$ = $1 / $3;}
	| "-" intexp %prec UMINUS {$$ = -$2;}
	| intexp "|" intexp {$$ = $1 | $3;}
	| intexp "&" intexp {$$ = $1 & $3;}
	| "!" intexp {$$ = !$2;}	
	| "(" intexp ")" {$$ = $2;}	
	;

floatexp: FLOATNUM {$$ = $1;}
	| floatexp "+" floatexp {$$ = $1 + $3;}
	| floatexp "+" intexp {$$ = $1 + $3;}
	| intexp "+" floatexp {$$ = $1 + $3;}
	| floatexp "-" floatexp {$$ = $1 - $3;}
	| floatexp "-" intexp {$$ = $1 - $3;}
	| intexp "-" floatexp {$$ = $1 - $3;}
	| floatexp "*" floatexp {$$ = $1 * $3;}
	| floatexp "*" intexp {$$ = $1 * $3;}
	| intexp "*" floatexp {$$ = $1 * $3;}
	| floatexp "/" floatexp {$$ = $1 / $3;}
	| floatexp "/" intexp {$$ = $1 / $3;}
	| intexp "/" floatexp {$$ = $1 / $3;}
	| "-" floatexp %prec UMINUS {$$ = -$2;}
	| "(" floatexp ")" {$$ = $2;}
	;
/*
expr : expr IN "(" val_list ")" {emit("ISIN %d",$4);}
	| expr NOT IN "(" val_list ")" {emit("ISIN %d",$5); emit("NOT");}
	| expr IN "(" select_stmt ")" {emit("CMPANYSELECT 4");}
	| expr NOT IN "(" select_stmt ")" {emit("COMPANYSELECT 3");}
	;

expr: expr LIKE expr {emit("LIKE");}
    | expr NOT LIKE expr {emit("LIKE"); emit("NOT");}

*/
stmt: select_stmt {driver.berror = false;driver.Select($1);}
    ;

select_stmt:  SELECT select_expr_list FROM NAME opt_where {($$).col = $2;($$).fromtable = $4;
	   							($$).where = $5;
								if(($2).size() == 0) ($$).selectall = true;
								else ($$).selectall = false;}
	;

opt_where: %empty {$$ = NULL;}
	 | WHERE expr {$$ = $2;}
	 ;
/*
opt_groupby:
	 | GROUP BY groupby_list opt_with_rollup {emit("GROUPBYLIST %d %d",$3,$4);}
groupby_list: expr opt_asc_desc {emit("GROUPBY %d",$2); $$ = 1;}
	 | groupby_list ',' expr opt_asc_desc {emit("GROUPBY %d",$4); $$ = $1 + 1;}

opt_asc_desc: {$$ = 0;}
	 | ASC {$$ = 0;}
	 | DESC {$$ = 1;}
	 

opt_with_rollup:   {$$ = 0;}
	| WITH ROLLUP {$$ = 1;}

opt_having:
	| HAVING expr {emit("HAVING");}

opt_orderby:
	   | ORDER BY groupby_list {emit("ORDERBY %d",$3);}

opt_limit:
	 | LIMIT expr {emit("LIMIT 1");}
	 | LIMIT expr ',' expr {emit("LIMIT 2");}

opt_into_list:
	     | INTO column_list {emit("INTO %d",$2);}
             ;
*/
column_list: NAME {($$).clear(); ($$).push_back($1);}
	| STRING {($$).clear(); ($$).push_back($1);}   
	| column_list "," NAME {$$ = $1;($1).push_back($3);}
	| column_list "," STRING {$$ = $1;($1).push_back($3);}


select_expr_list: NAME {($$).clear();($$).push_back($1);}
		| select_expr_list "," NAME {$$ = $1;($$).push_back($3);}
		| "*" {($$).clear(); }
		;

/*
opt_as_alias: AS NAME {emit("ALIAS %s",($2).c_str());} 
	| NAME {emit("ALIAS %s",($1).c_str());} 
	|
	;
*/
/*
table_references: table_reference {$$ = 1;}
	| table_references "," table_reference {$$ = $1 + 1;}
	;

table_reference: table_factor
	;

table_factor:
	NAME   {emit("TALBLE %s",($1).c_str());} 
	| NAME "." NAME   {emit("TABLE %s.%s",($1).c_str(),($3).c_str());} 
	| "(" table_references ")" {emit("TABLEREFERENCES %d",$2);}
	;
*/
/*
opt_as: 
      |AS
      ;
*/
stmt: delete_stmt {driver.berror = false;driver.Delete($1);}
    ;

delete_stmt: DELETE  FROM NAME opt_where {($$).fromtable = $3;($$).where = $4; if($4 == NULL) ($$).deleteall = true;else ($$).deleteall = false; }
	   ;

stmt: insert_stmt {driver.berror = false;driver.InsertValues($1);}
    ;

insert_stmt: INSERT opt_into NAME VALUES 
	   "(" insert_vals ")" {($$).tablename = $3;($$).item = $6;}
	   ;

opt_into: INTO 
	;
/*
insert_val_list: "(" insert_vals ")" {emit("VALUES %d",$2); $$ = 1;}
	       |insert_val_list "," "(" insert_vals  ")" {emit("VALUES %d",$4); $$ = $1 + 1;}
*/
insert_vals: STRING {($$).clear(); sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = $1;($$).push_back(item); }
	| intexp {($$).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr($1);($$).push_back(item);}
	| floatexp {($$).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr($1);($$).push_back(item);}   
	|DEFAULT {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;($$).push_back(item);}
	|insert_vals "," STRING {sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = $3;$$ = $1;($$).push_back(item);}
	|insert_vals "," intexp {sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr($3);$$ = $1;($$).push_back(item);}
	|insert_vals "," floatexp {sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr($3);$$ = $1;($$).push_back(item);}
	|insert_vals "," DEFAULT {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;}

/*
stmt: update_stmt {emit("STMT");}
    ;
update_stmt: UPDATE table_references SET update_asgn_list opt_where {emit("UPDATE %d %d",$2,$4);}
	   ;
update_asgn_list:
		NAME COMPARISON expr {if($2 != 4) {error(@2,"Bad update assignment"); YYERROR;}
				      emit("ASSIGN %s",($1).c_str());  $$ = 1;}
		|NAME "." NAME COMPARISON expr {if($4 != 4) {error(@4,"Bad update assignment"); 
			YYERROR;} emit("ASSIGN %s.%s",($1).c_str(),($3).c_str());  $$ = 1;}
		;

*/
stmt: create_table_stmt {
		driver.berror = false;
		driver.Createtable($1);
	}
	;
create_table_stmt: CREATE TABLE NAME "(" create_col_list ")" {($$).name = $3;($$).col = $5; }
		 ;

create_col_list: create_definition {($$).record.clear();($$).record.push_back($1);}
	       | create_col_list "," create_definition {$$ = $1;($$).record.push_back($3);}
	       | create_col_list "," PRIMARY KEY "(" column_list ")" {$$ = $1;($$).primarykey = $6;}

create_definition:  NAME data_type column_atts {($$).name = $1;($$).data_type = $2;($$).attr = $3; }

column_atts: %empty {($$).clear();}
	| column_atts NOT NULLX {sqlstruct::col_attr attr; attr.type = $3 + 1000;$$ = $1;($$).push_back(attr);}
	| column_atts NULLX 	{sqlstruct::col_attr attr; attr.type = $2;$$ = $1;($$).push_back(attr);}
	| column_atts DEFAULT STRING {sqlstruct::col_attr attr;attr.type = $2; attr.value = $3; $$ = $1;($$).push_back(attr);}
	| column_atts DEFAULT INTNUM {sqlstruct::col_attr attr;attr.type = $2;attr.value = itostr($3);$$ = $1;($$).push_back(attr);}
	| column_atts DEFAULT FLOATNUM {sqlstruct::col_attr attr;attr.type = $2; attr.value = ftostr($3);$$ = $1;($$).push_back(attr);}
	| column_atts AUTO_INCREMENT {sqlstruct::col_attr attr; attr.type = $2;$$ = $1;($$).push_back(attr);}
	| column_atts UNIQUE 	{sqlstruct::col_attr attr;attr.type = $2;$$ = $1;($$).push_back(attr);}
	| column_atts PRIMARY KEY {sqlstruct::col_attr attr;attr.type = $2;$$ = $1; ($$).push_back(attr);}
	;

opt_length: %empty {$$ = 0;}
	  | "(" INTNUM ")" {$$ = $2;}

data_type: INT {$$ = 40000;}
	 |CHAR opt_length {$$ = 120000 + $2;}
	 |FLOAT {$$ = 90000;}
stmt: create_index_stmt {driver.berror = false;driver.CreateIndex($1);}
create_index_stmt: CREATE INDEX NAME ON NAME "(" column_list ")" {($$).indexname = $3;($$).tablename = $5;($$).col = $7; }

stmt: drop_table_stmt {driver.berror = false;driver.DropTable($1);}

drop_table_stmt: DROP TABLE NAME {$$ = $3; }

stmt: drop_index_stmt {driver.berror = false;driver.DropIndex($1);}

drop_index_stmt: DROP INDEX NAME  {$$ = $3; }

stmt: quit_stmt {driver.berror = false;driver.Exit();}

quit_stmt:QUIT

stmt: execfile_stmt {driver.berror = false;driver.ExecFile($1);}

filename: NAME {$$ = $1;}
	| filename "." NAME {$$ = $1 + "." + $3;}
	| filename "/" NAME {$$ = $1 + "/" + $3;}
	| "/" filename {$$ = "/" + $2;}
	; 
execfile_stmt: EXECFILE filename {$$ = $2; }
%%
void emit(char *s,...){
	extern int yylineno;
	va_list ap;
	va_start(ap,s);
	printf("rpn: ");
	vfprintf(stdout,s,ap);
	printf("\n");
}
/*
void error(char *s,...){
	extern int  yylineno;
	va_list ap;
	va_start(ap,s);
	fprintf(stderr,"%d:error: ",yylineno);
	vfprintf(stderr,s,ap);
	fprintf(stderr,"\n");
}
int main(int argc,char **argv){
	extern FILE *yyin;
	if(argc>1&&!strcmp(argv[1],"-d")){
		yydebug = 1;
		argc--;
		argv++;
	}
	if(argc>1&&((yyin = fopen(argv[1],"r")) == NULL)){
		perror(argv[1]);
		exit(1);
	}
	if(!yyparse()){
		printf("SQL parse worked\n");
	}
	else printf("SQL parse failed\n");
	return 0;
}*/
void yy::sqlparser::error(const location_type& l,const std::string &m){
	driver.error(l,m);
}
std::string itostr(int value){
	std::stringstream sstr;
	sstr << value;
	return sstr.str();   
}

std::string ftostr(float value){
	std::stringstream sstr;
	sstr << value;
	return sstr.str();   
}

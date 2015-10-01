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
	class sqlparser_driver;
	void emit(char *s,...);
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
%token DEFAULT
%token AUTO_INCREMENT
%token EXISTS
%token TABLE
%token CHAR
%token SELECT
%token SET
%token NULLX
%token INT
%token FLOAT
%token VALUES
%token DISTINCT
%token  WHERE
%token UNIQUE
%token INSERT
%token PRIMARY
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
%type <int> select_opts select_expr_list
%type <int> val_list opt_val_list 
%type <int> table_references
%type <int> column_list 
/*%type <intval> delete_opts*/

%type <int> insert_vals insert_val_list
%type <int>  update_asgn_list
%type <int> column_atts data_type create_col_list
%type <int> opt_length
%type <int> insert_stmt
%type <int> expr
%type <int> update_stmt
%start stmt_list
%%

stmt_list: stmt ";"
	| stmt_list stmt ";"
	| error ";"
	| stmt_list error ";"

expr: NAME {emit("NAME %s",($1).c_str()); }
	| NAME "." NAME {emit("FILEDNAME %s.%s",($1).c_str(),($3).c_str()); }
  	| STRING {emit("STRING %s",($1).c_str()); }
	| INTNUM {emit("NUMBER %d",$1);}
	| FLOATNUM {emit("FLOAT %g",$1);}
	| expr "+" expr {emit("ADD");}
	| expr "-" expr {emit("SUB");}
	| expr "*" expr {emit("MUL");}
	| expr "/" expr {emit("DIV");}
	| "-" expr %prec UMINUS {emit("NEG");}
	| expr ANDOP expr {emit("AND");}
	| expr OR expr {emit("OR");}
	| expr XOR expr {emit("XOR");}
	| expr "&" expr {emit("BITAND");}
	| NOT expr {emit("NOT");}
	| "!" expr {emit("NOT");}
	| expr COMPARISON expr {emit("CMP %d",$2);}
	| expr IS NULLX {emit("ISNULL");}
	| expr IS NOT NULLX {emit("ISNULL"); emit("NOT");}
	| expr BETWEEN expr AND expr %prec BETWEEN {emit("BETWEEN");}
	;
val_list: expr {$$ = 1;}
	| expr "," val_list {$$ = $3 + 1;}
	;

opt_val_list: {$$ = 0;}
	    | val_list
	    ;

expr : expr IN "(" val_list ")" {emit("ISIN %d",$4);}
	| expr NOT IN "(" val_list ")" {emit("ISIN %d",$5); emit("NOT");}
	| expr IN "(" select_stmt ")" {emit("CMPANYSELECT 4");}
	| expr NOT IN "(" select_stmt ")" {emit("COMPANYSELECT 3");}
	;

expr: expr LIKE expr {emit("LIKE");}
    | expr NOT LIKE expr {emit("LIKE"); emit("NOT");}


stmt: select_stmt {emit("STMT");}
    ;

select_stmt: SELECT select_opts select_expr_list {emit("SELECTNODATA %d %d",$2,$3);}
	| SELECT select_opts select_expr_list FROM table_references
	 opt_where 
	{emit("SELECT %d %d %d",$2,$3,$5);}
	;

opt_where:
	 | WHERE expr {emit("WHERE");}
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
column_list: NAME {emit("COLUMN %s",($1).c_str()); $$ = 1;}
	| STRING {emit("COLUMN %s",($1).c_str()); $$ = 1;}   
	| column_list "," NAME {emit("COLUMN %s",($3).c_str()); $$ = $1 + 1;}
	| column_list "," STRING {emit("COLUMN %s",($3).c_str()); $$ = $1 + 1;}

select_opts: {$$ = 0;}
	| select_opts ALL {if($1 & 01) error(@1,"duplicate ALL option"); $$ = $1 | 01;}
	| select_opts DISTINCT  {if($1 & 02) error(@1,"duplicate DISTINCT option"); $$ = $1 | 02;}
	;

select_expr_list: select_expr {$$ = 1;}
		| select_expr_list ',' select_expr {$$ = $1 + 1;}
		| "*" {emit("SELECTALL"); $$ = 1;}
		;

select_expr: expr opt_as_alias;

opt_as_alias: AS NAME {emit("ALIAS %s",($2).c_str());} 
	| NAME {emit("ALIAS %s",($1).c_str());} 
	|
	;

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
/*
opt_as: 
      |AS
      ;
*/
stmt: delete_stmt {emit("STMT");}
    ;

delete_stmt: DELETE  FROM NAME opt_where {emit("DELETEONE %s",($3).c_str()); }
	   ;

stmt: insert_stmt {emit("STMT");}
    ;

insert_stmt: INSERT opt_into NAME VALUES 
	   insert_val_list {emit("INSERTVALS  %d %s",$5,($3).c_str()); }
	   ;

opt_into: INTO 
	|
	;

insert_val_list: "(" insert_vals ")" {emit("VALUES %d",$2); $$ = 1;}
	       |insert_val_list "," "(" insert_vals  ")" {emit("VALUES %d",$4); $$ = $1 + 1;}
insert_vals: expr {$$ = 1;}
	   |DEFAULT {emit("DEFAULT"); $$ = 1;}
	   |insert_vals "," expr {$$ = $1 + 1;}
	   |insert_vals "," DEFAULT {emit("DEFAULT"); $$ = $1 + 1;}

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

stmt: create_table_stmt {
    		emit("STMT");
	}
	;
create_table_stmt: CREATE TABLE NAME "(" create_col_list ")" {emit("CREATE %d %s",$5,($3).c_str()); }
		 ;

create_col_list: create_definition {$$ = 1;}
	       | create_col_list "," create_definition {$$ = $1+1;}

create_definition: PRIMARY KEY "(" column_list ")" {emit("PRIKEY %d",$4);}
		 | INDEX "(" column_list ")" {emit("INDEX %d",$3);}

create_definition: {emit("STARTCOL");} NAME data_type column_atts {emit("COLUMNDEF %d %s",$3,($2).c_str()); }

column_atts: {$$ = 0;}
	| column_atts NOT NULLX {emit("ATTR NOTNULL"); $$ = $1 + 1;}
	| column_atts NULLX 
	| column_atts DEFAULT STRING {emit("ATTR DEFAULT STRING %s",($3).c_str());  $$ = $1+1;}
	| column_atts DEFAULT INTNUM {emit("ATTR DEFAULT NUMBER %d",$3); $$ = $1 + 1;}
	| column_atts DEFAULT FLOATNUM {emit("ATTR DEFAULT FLOAT %g",$3); $$ = $1+1;}
	| column_atts AUTO_INCREMENT {emit("ATTR AUTOINC"); $$ = $1 +1;}
	| column_atts UNIQUE "(" column_list ")" {emit("ATTR UNIQUEKEY %d",$4); $$ = $1 + 1;}
	| column_atts UNIQUE KEY {emit("ATTR UNIQUEKEY"); $$ = $1+1;}
	| column_atts PRIMARY KEY {emit("ATTR PRIKEY"); $$ = $1 + 1;}
	;

opt_length: {$$ = 0;}
	  | "(" INTNUM ")" {$$ = $2;}

data_type: INT {$$ = 40000;}
	 |CHAR opt_length {$$ = 120000 + $2;}
	 |FLOAT {$$ = 90000;}
stmt: create_index_stmt {emit("STMT");}
create_index_stmt: CREATE INDEX NAME ON NAME "(" column_list ")" {emit("INDEX %s %s",($3).c_str(),($5).c_str()); }

stmt: drop_table_stmt {emit("STMT");}

drop_table_stmt: DROP TABLE NAME {emit("DROPTABLE %s",($3).c_str()); }

stmt: drop_index_stmt {emit("STMT");}

drop_index_stmt: DROP INDEX NAME {emit("DROPINDEX %s",($3).c_str()); }

stmt: quit_stmt {emit("STMT");}

quit_stmt:QUIT {exit(0);}

stmt: execfile_stmt {emit("STMT");}

execfile_stmt: EXECFILE NAME {emit("EXECFILE %s",($2).c_str()); }
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

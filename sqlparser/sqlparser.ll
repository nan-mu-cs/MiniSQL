%{
	/* -*- C++ -*- */ 
	#include <iostream>
	#include <cerrno>
	#include <climits>
	#include <cstdlib>
	#include <string>
	#include "sqlparser_driver.hh"
	#include "sqlparser.hh"

	#undef yywrap
	#define yywrap() 1
	#define yyterminate() return yy::sqlparser::make_END(loc);
	static yy::sqlparser::location_type loc;
%}
%option batch debug noinput noyywrap nodefault  yylineno case-insensitive

%x COMMENT
%s BTWMODE

%%
%{
	loc.step();
%}
ADD	{return yy::sqlparser::make_ADD(loc);}
ALL 	{return yy::sqlparser::make_ALL(loc);}


<BTWMODE>AND	{BEGIN(0); return yy::sqlparser::make_AND(loc);}
AND	{return yy::sqlparser::make_AND(loc);}
AS	{return yy::sqlparser::make_AS(loc);}
AUTO_INCREMENT	{return yy::sqlparser::make_AUTO_INCREMENT(loc);}
BETWEEN	{BEGIN(BTWMODE); return yy::sqlparser::make_BETWEEN(loc);}
CHAR	{return yy::sqlparser::make_CHAR(loc);}
CREATE	{return yy::sqlparser::make_CREATE(loc);}
DEFAULT	{return yy::sqlparser::make_DEFAULT(loc);}
DELETE	{return yy::sqlparser::make_DELETE(loc);}
DISTINCT	{return yy::sqlparser::make_DISTINCT(loc);}
DROP 	{return yy::sqlparser::make_DROP(loc);}
FLOAT	{return yy::sqlparser::make_FLOAT(loc);}
FROM	{return yy::sqlparser::make_FROM(loc);}
EXISTS	{ return yy::sqlparser::make_EXISTS(loc);}
EXECFILE 	{return yy::sqlparser::make_EXECFILE(loc);}
IN 	{return yy::sqlparser::make_IN(loc);}
INT 	{return yy::sqlparser::make_INT(loc);}
INTO	{return yy::sqlparser::make_INTO(loc);}
INDEX	{return yy::sqlparser::make_INDEX(loc);}
INSERT	{return yy::sqlparser::make_INSERT(loc);}
IS	{return yy::sqlparser::make_IS(loc);}
KEY 	{return yy::sqlparser::make_KEY(loc);}
LIKE	{return yy::sqlparser::make_LIKE(loc);}
NOT	{return yy::sqlparser::make_NOT(loc);}
NULL	{return yy::sqlparser::make_NULLX(loc);}
ON 	{return yy::sqlparser::make_ON(loc);}
OR	{return yy::sqlparser::make_OR(loc);}
PRIMARY	{return yy::sqlparser::make_PRIMARY(loc);}
QUIT 	{return yy::sqlparser::make_QUIT(loc);}
SELECT	{return yy::sqlparser::make_SELECT(loc);}
TABLE	{return yy::sqlparser::make_TABLE(loc);}
UPDATE	{return yy::sqlparser::make_UPDATE(loc);}
VALUES 	{return yy::sqlparser::make_VALUES(loc);}
WHERE	{return yy::sqlparser::make_WHERE(loc);}


[-+]?[0-9]+	{return yy::sqlparser::make_INTNUM(atoi(yytext),loc);}

[-+]?[0-9]+"."[0-9]+|[+-]?"."[0-9]+	{ return yy::sqlparser::make_FLOATNUM(atof(yytext),loc);}

'[^\n]*'|\"[^\n]'|\"[^\n]*'|\"[^\n]\"	{ return yy::sqlparser::make_STRING(yytext,loc);}


"+"	{return yy::sqlparser::make_PLUS(loc);}
"-"	{return yy::sqlparser::make_MINUS(loc);}
"*"	{return yy::sqlparser::make_STAR(loc);}
"/"	{return yy::sqlparser::make_SLASH(loc);}
"("	{return yy::sqlparser::make_LPAREN(loc);}
")"	{return yy::sqlparser::make_RPAREN(loc);}
"&"	{return yy::sqlparser::make_SINGLEAND(loc);}
","	{return yy::sqlparser::make_COMMA(loc);}
"."	{return yy::sqlparser::make_POINT(loc);}
";"	{return yy::sqlparser::make_SEMICOL(loc);}
"!"	{return yy::sqlparser::make_SYMBOLNOT(loc);}

"&&"	{return yy::sqlparser::make_ANDOP(loc);}
"||"	{return yy::sqlparser::make_OR(loc);}
"=="	{return yy::sqlparser::make_COMPARISON(4,loc);}
"<=>"	{return yy::sqlparser::make_COMPARISON(12,loc);}
">="	{return yy::sqlparser::make_COMPARISON(6,loc);}
">"	{return yy::sqlparser::make_COMPARISON(2,loc);}
"<="	{return yy::sqlparser::make_COMPARISON(5,loc);}
"<"	{return yy::sqlparser::make_COMPARISON(1,loc);}
"!="|"<>"	{return yy::sqlparser::make_COMPARISON(3,loc);}


[A-Za-z][A-Za-z0-9_]*	{return yy::sqlparser::make_NAME(yytext,loc);}

[ \t]+	loc.step();
[\n]+ 	loc.lines(yyleng); loc.step();
.	{driver.error(loc,"Invalid Character ");}
%%
void sqlparser_driver::scan_begin(){
	yy_flex_debug = trace_scanning;
	if(file.empty()||file == "-")
		yyin = stdin;
	else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}
void sqlparser_driver::scan_end ()
{
  fclose (yyin);
}
int sqlparser_driver::parse(FILE *fp){
	yy_flex_debug = trace_scanning;
	yyin = fp;
	yy::sqlparser parser(*this);
	parser.set_debug_level(false);
	return parser.parse();
}

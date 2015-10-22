#include "sqlparser_driver.hh"
#include "sqlparser.hh"

sqlparser_driver::sqlparser_driver():trace_scanning(false),trace_parsing(false)
{
}
/*
sqlparser_driver::~sqlparser_driver(){

}
*/
int sqlparser_driver::parse(const std::string &f){
	file = f;
	scan_begin();
	yy::sqlparser parser(*this);
    test += 1;
	parser.set_debug_level(trace_parsing);
	int res = parser.parse();
	scan_end();
	return res;
}
int sqlparser_driver::parse(FILE *fp){
    //std::cout << yy::sqlparser::token::END <<std::endl;
    //yy_flex_debug = trace_scanning;
    //yyin = fp;
    scan_begin(fp);
    yy::sqlparser parser(*this);
    parser.set_debug_level(false);
    return parser.parse();
}
void sqlparser_driver::error(const yy::location &l,const std::string &m){
	std::cerr << l << ":" << m << std::endl;
}

void sqlparser_driver::error(const std::string &m){
	berror = true;
	std::cerr << m << std::endl;
}

FILE *sqlparser_driver::fmemopen(void *buf, size_t size, const char *opentype)
{
    FILE *f;
    assert(strcmp(opentype, "r") == 0);
#ifdef WIN32
    char* tmp_fname = _tempnam("%TMP%", "fmemopen");
    f = fopen(tmp_fname, "wt");
    fwrite(buf, 1, size, f);
    fclose(f);
    f = fopen(tmp_fname, "rt");
#else
    f = tmpfile();
    fwrite(buf, 1, size, f);
    rewind(f);
#endif
    return f;
}

void sqlparser_driver::Select(sqlstruct::selecttable node){
    /*
    if(node.selectall)
        std::cout << "SelectALL" <<std::endl;
    else {
        for(int i = 0;i<node.col.size();i++)
            std::cout << node.col[i] << ' ';
        std::cout << std::endl;
    }
    std::cout << "Fromtable: " << node.fromtable << std::endl;
    evalASTree(node.where);

     */}


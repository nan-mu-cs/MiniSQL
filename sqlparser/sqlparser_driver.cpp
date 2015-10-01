#include "sqlparser_driver.hh"
#include "sqlparser.hh"

sqlparser_driver::sqlparser_driver():trace_scanning(false),trace_parsing(false)
{
	variables["one"] = 1;
	variables["two"] = 2;
}

sqlparser_driver::~sqlparser_driver(){

}

int sqlparser_driver::parse(const std::string &f){
	file = f;
	scan_begin();
	yy::sqlparser parser(*this);
	parser.set_debug_level(trace_parsing);
	int res = parser.parse();
	scan_end();
	return res;
}
void sqlparser_driver::error(const yy::location &l,const std::string &m){
	std::cerr << l << ":" << m << std::endl;
}

void sqlparser_driver::error(const std::string &m){
	std::cerr << m << std::endl;
}


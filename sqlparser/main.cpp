#include <iostream>
//#include "fmemopen.h"
#include "sqlparser_driver.hh"
#define SIZE 50000
using namespace std;

FILE *fmemopen (void *buf, size_t size, const char *opentype)
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

int main (int argc, char *argv[])
{
  int res = 0;
  sqlparser_driver driver;
  FILE *stream;
  char buffer[SIZE];
  string tmp,used,left;
  while(1){
  	getline(cin,tmp);
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
		cout << used.c_str() << endl;
		stream = fmemopen((void *)used.c_str(),used.length(),"r");
		used.clear();
		for(;i<tmp.length();i++)
			left += tmp[i];
		driver.parse(stream);
		fclose(stream);
	}
  }
  /*
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      driver.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
      driver.trace_scanning = true;
    else driver.parse(argv[i]);
  if(argc < 1)
	  driver.parse("");
  */
  return 0;
}

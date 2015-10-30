#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H
//#include "sqlparser.hh"
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
//typedef yy::sqlparser::token::tokentype TOKEN;
using namespace std;

namespace sqlstruct{
    const int INTNUM  = 40000;
    const int CHAR = 120000;
    const int FLOATNUM = 90000;
    const int VARIABLE = 50000;
    enum operate {
        AND,
        //OR,
        //NOT,
        //ISNULL,
        LESS,
        LESSOREQUAL,
        EQUAL,
        GREATOREQUAL,
        GREAT,
        NOTEQUAL
    };
	struct col_attr{
		int type;
		std::string value;
	};
	struct record_t{
		std::string name;
		std::vector<col_attr>  attr;
		int  data_type;
        int size(){
            switch (data_type) {
                case INTNUM:
                    return sizeof(int);
                    break;
                case FLOATNUM:
                    return sizeof(float);
                    break;
                default:
                    return data_type - CHAR;
                    break;
            }
        }
	};
	
	struct create_col_list{
		std::vector<std::string> primarykey;
		//std::vector<std::string> indexkey;
		std::vector<record_t> record;
	};
	struct createtable{
		std::string name;
		struct create_col_list col;
		//std::vector<struct record_t> record;
		//vector<std::string> primarykey;
		//vector<std::string> indexkey;
	};
	struct dropindex{
		std::string tablename;
		std::string indexname;
		std::vector<std::string> col;
	};
class insertitem{
    public:
		std::string value;
		int data_type;
        insertitem(){};
        insertitem(std::string valueInput, int type):value(valueInput), data_type(type) {};
        int size(){
            switch (data_type) {
                case INTNUM:
                    return sizeof(int);
                    break;
                case FLOATNUM:
                    return sizeof(float);
                    break;
                default:
                    return data_type - CHAR;
                    break;
            }
        }
        int getInt(){
            return stoi(value);
        }
        float getFloat(){
            return stof(value);
        }
        const char* getCharN(){
            return value.c_str();
        }
        /* another correct version:
         *  void getCharN(char* des){
         *      strcpy(des, value.c_str();
         *  }
         *
         */
        /* wrong version:
         * char* getCharN(){
         *      return value.c_str();
         * }
         *
         * when called by rm.insertRecords(..), signal SIGABRT
         *      malloc: *** error for object: pointer being freed was not allocated *** set a breakpoint in malloc_error_break to debug
         * and the value in cNValue is correct...
         * error, because the cNValue receive's xxx.c_str()'s address, the two pointers equal. And I assume that the space allocated by c_str() call would be cleared by the system??
            so the delet[] cNValue made a second time delete. and caused error.
            one more time, delete would not make the pointer equal NULL.
         */
        
        bool operation(operate op, insertitem item2){
            switch (op) {
                case EQUAL:
                    return this->equal(item2);
                    break;
                case NOTEQUAL:
                    return !this->equal(item2);
                    break;
                case LESS:
                    return this->lessThan(item2);
                    break;
                case GREATOREQUAL:
                    return !this->lessThan(item2);
                    break;
                case GREAT:
                    return item2.lessThan(*this);
                    break;
                case LESSOREQUAL:
                    return !item2.lessThan(*this);
                default:
                    fprintf(stderr, "unknown operator!\n");
                    return false;
                    break;
            }
        }
        bool equal(insertitem item2){
            if (data_type != item2.data_type) {
                return false;
            }
            if (data_type != FLOATNUM) {
                return value == item2.value;
            }else{
                return abs(getFloat() - item2.getFloat()) < 0.00001;
            }
            
        }
        bool lessThan(insertitem item2){
            if (data_type != item2.data_type) {
                return false;
            }
            switch (data_type) {
                case INTNUM:
                    return getInt() < item2.getInt();
                    break;
                case FLOATNUM:
                    return getFloat() < item2.getFloat();
                    break;
                default:
                    return value < item2.value;
                    break;
            }
        }
	};
	struct insertvalues{
		std::string tablename;
		std::vector<insertitem> item;
	};
    struct ele_t{
        int type;
        std::string value;
    };
	struct astree{
		//std::string value;
        ele_t value;
        bool isleaf;
		int operate;
		struct astree *left,*right;
	};
	struct selecttable{
		std::string fromtable;
		std::vector<std::string> col;
		bool selectall;
		struct astree *where;
	};
	struct deletetable{
		std::string fromtable;
		struct astree *where;
		bool deleteall;
	};
	struct createindex{
		std::string indexname;
		std::string tablename;
		std::vector<std::string> col;
	};

	enum attr_type{
		AUTO_INCREMENT,
		DEFAULT,
		NULLX,
		PRIMARY,
		UNIQUE,
		STRING,
	};

}
namespace catalog {
#define NAME_LENGTH 32
#define HASH_SIZE 102
#define MAX_PRIMARY_COL 10
#define MAXNUM_INDEX 10
#define MAXNUM_COL 10
#define MAXNUM_ATTR 3
#define BLOCKSIZE 4096
#define BLOCKREMAINDER 10000
#define BLOCK_HEAD_SIZE 8
#define STORAGE_START_BLOCK 3
    struct meta_t{
        off_t tablepos;
        off_t indexpos;
        off_t freeblock;
        off_t head,end;
    };
    struct record_t {
        std::string name;
        int datatype;
        std::string attr[MAXNUM_ATTR];
    };
    struct hash_t{
        std::string name;
        off_t pos;
    };
    struct table_t{
        //sqlstruct::createtable table;
        std::string createstr;
        size_t numofIndex;
        std::string index[MAXNUM_INDEX];
        off_t pos;
    };
    struct index_t{
        std::string name;
        std::string table;
        size_t numofcol;
        std::string col[MAXNUM_COL];
        off_t pos;
    };

}
#endif

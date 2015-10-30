CC=g++
FLEX=/usr/local/bin/flex
BISON=/usr/local/bin/bison

All: minisql

sqlparser.cpp sqlparser.hh: sqlparser.yy
	BISON --defines=sqlparser.hh -o sqlparser.cpp sqlparser.yy

sqlparser_scanner.cpp: sqlparser.ll
	FLEX -o sqlparser_scanner.cpp sqlparser.ll

OBJ=BufferManager.o RecordManager.o IndexManager.o API.o CatalogManager.o Interpreter.o main.o sqlparser_driver.o sqlparser_scanner.o sqlparser.o
minisql:$(OBJ)
	g++ -o minisql $(OBJ)
main.o: BufferManager.hpp  RecordManager.hpp IndexManager.h API.h CatalogManager.h Interpreter.h main.cpp
BufferManager.o: BlockForBuffer.hpp

RecordManager.o: BufferManager.hpp sqlstruct.h

IndexManager.o: sqlstruct.h BufferManager.hpp BplusTree.h

API.o: IndexManager.h RecordManager.hpp CatalogManager.h sqlstruct.h

CatalogManager.o: sqlstruct.h sqlparser_driver.hh BufferManager.hpp 

Interpreter.o: sqlparser_driver.hh CatalogManager.h API.h

sqlparser_driver.o:  sqlparser_driver.hh sqlparser.hh

sqlparser_scanner.o: sqlparser_scanner.cpp sqlparser.hh sqlparser_driver.hh

sqlparser.o: sqlparser.cpp sqlparser.hh sqlparser_driver.hh

.PHONY: clean
clean:
	rm minisql $(OBJ)

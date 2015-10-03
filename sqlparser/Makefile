ALL: sqlparser
CC=g++
FLEX = /usr/local/bin/flex
BISON = /usr/local/bin/bison
sqlparser: sqlparser_driver.o sqlparser.o sqlparser_scanner.o main.o
	g++ -o sqlparser sqlparser_driver.o sqlparser.o sqlparser_scanner.o main.o

sqlparser_driver.o: sqlparser_driver.cpp sqlparser_driver.hh sqlparser.hh
	g++ -c sqlparser_driver.cpp

sqlparser.o: sqlparser.cpp sqlparser.hh sqlparser_driver.hh
	g++ -c sqlparser.cpp

sqlparser.cpp sqlparser.hh: sqlparser.yy
	BISON --defines=sqlparser.hh -o sqlparser.cpp sqlparser.yy

sqlparser_scanner.o: sqlparser_scanner.cpp  sqlparser.hh sqlparser_driver.hh
	g++ -c sqlparser_scanner.cpp

sqlparser_scanner.cpp: sqlparser.ll
	FLEX -o sqlparser_scanner.cpp sqlparser.ll

main.o:  sqlparser_driver.hh main.cpp
	g++ -w -c main.cpp 

.PHONY: clean

clean:
	-rm *.o sqlparser.hh sqlparser.cpp sqlparser_scanner.cpp location.hh position.hh stack.hh 

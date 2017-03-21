make: dbms

dbms: dbms.o Engine.o  Parser.o Table.o
	g++ -std=c++11 -o dbms dbms.o Engine.o Catalog.o Parser.o Table.o

dbms.o: dbms.cpp Engine.h Catalog.h Parser.h Table.h 
	g++ -std=c++11 -c dbms.cpp

Engine.o: Engine.h Catalog.h
	g++ -std=c++11 -c Engine.cpp

Parser.o: Parser.h
	g++ -std=c++11 -c Parser.cpp

Table.o: Table.h
	g++ -std=c++11 -c Table.cpp

clean:
	rm -rf *.o main


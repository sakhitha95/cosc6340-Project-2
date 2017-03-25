make: clean dbms

dbms: dbms.o Engine.o Parser.o Table.o
	g++ -std=c++11 -o dbms dbms.o Engine.o Parser.o Table.o

dbms.o: dbms.cpp Engine.h Catalogtable.h Parser.h Table.h
	g++ -Wall -std=c++11 -c dbms.cpp

Engine.o: Engine.h Catalogtable.h
	g++ -Wall -std=c++11 -c Engine.cpp

Parser.o: Parser.h
	g++ -Wall -std=c++11 -c Parser.cpp

Table.o: Table.h
	g++ -Wall -std=c++11 -c Table.cpp

clean:
	rm -rf *.o main


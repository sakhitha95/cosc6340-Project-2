make: dbms

dbms: dbms.o Parser.o
	g++ -o dbms dbms.o Parser.o

dbms.o: dbms.cpp Parser.h
	g++ -c dbms.cpp

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp

clean:
	rm -rf *.o dbms
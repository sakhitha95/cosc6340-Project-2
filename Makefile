make: dbms

dbms:
	g++ -o dbms dbms.cpp

clean:
	rm -rf *.o dbms
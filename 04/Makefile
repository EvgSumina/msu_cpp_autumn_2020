all: my_prog

test:
	./my_prog

my_prog: tests.o BigInt.o 
		g++ -o my_prog tests.o BigInt.o

BigInt.o: BigInt.cpp BigInt.h
		g++ -c BigInt.cpp

tests.o: tests.cpp BigInt.h
		g++ -c tests.cpp
		
run:	my_prog
		./my_prog

clean:
		rm -rf *.o my_prog
		rm -rf *.stackdump my_prog
		rm -rf *.exe my_prog

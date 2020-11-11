all: my_prog

test:
	./my_prog

my_prog: tests.o serializer.o 
		g++ -o my_prog tests.o serializer.o

BigInt.o: serializer.cpp serializer.h
		g++ -c serializer.cpp

tests.o: tests.cpp serializer.h
		g++ -c tests.cpp
		
run:	my_prog
		./my_prog

clean:
		rm -rf *.o my_prog
		rm -rf *.stackdump my_prog
		rm -rf *.exe my_prog

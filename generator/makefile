all : result

result: main.o generator.o 
	g++ main.o generator.o -o result
	 
main.o:  main.cc generator.o
	g++ -c main.cc -o main.o


generator.o: generator.cc generator.h 
	g++ -c generator.cc -o generator.o
	

clean:
	rm -rf *.o 


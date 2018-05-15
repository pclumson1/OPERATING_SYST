
prodCons:	Buffer.o main.o
	g++ -g -std=c++11 -lpthread Buffer.o main.o -o prodCons
main.o: Buffer.hpp main.cpp
	g++ -g -std=c++11 -c -lpthread main.cpp
Buffer.o: Buffer.cpp Buffer.hpp
	g++ -g -std=c++11 -c -lpthread Buffer.cpp  

clean:
	rm  -f core prodCons.o prodCons



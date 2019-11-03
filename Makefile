# fonte: https://stackoverflow.com/questions/41205042/c-makefile-headers-and-cpp


CXX = g++
CXXFLAGS = -std=c++11 -Wall


OBJECTS = btree_tools.o btree_util.o btree.o Comandos.o main.o

main: $(OBJECTS)
	gcc -o btree_tools.o -c btree_tools.c
	gcc -o btree_util.o -c btree_util.c
	gcc -o btree.o -c btree.c
	$(CXX) $(CXXFLAGS) -o main.exe $(OBJECTS)

Comandos.o: Comandos.h

clean:
	rm *.o *.exe tabelas/*.txt

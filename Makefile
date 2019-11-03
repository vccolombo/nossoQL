# fonte: https://stackoverflow.com/questions/41205042/c-makefile-headers-and-cpp


CXX = g++
CXXFLAGS = -std=c++11 -Wall


OBJECTS = main.o Comandos.o btree_tools.o btree_util.o btree.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main.exe $(OBJECTS)

Comandos.o: Comandos.h
btree_tools.o: btree_tools.h
btree_util.o: btree_util.h
btree.o: btree.h

clean:
	rm *.o *.exe tabelas/*.txt

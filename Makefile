# fonte: https://stackoverflow.com/questions/41205042/c-makefile-headers-and-cpp


CXX = g++
CXXFLAGS = -std=c++11 -Wall


OBJECTS = main.o Comandos.o hash.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main.exe $(OBJECTS)

Comandos.o: Comandos.h
hash.o: hash.h

clean:
	rm *.o *.exe tabelas/*.txt

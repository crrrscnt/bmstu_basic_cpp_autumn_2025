CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw6

hw6: vector.o test.o
	$(CXX) $(CXXFLAGS) -o hw6 vector.o test.o $(LDFLAGS) $(LDLIBS)

vector.o: $(SRC)/vector.cpp $(SRC)/vector.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/vector.cpp -o vector.o

test.o: $(TESTS)/test.cpp $(SRC)/vector.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp -o test.o

.PHONY: test clean

clean:
	del /Q /F hw6 hw6.exe *.o

test: hw6
	.\hw6.exe
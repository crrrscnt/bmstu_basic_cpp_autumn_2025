CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw7

hw7: format.o test.o
	$(CXX) $(CXXFLAGS) -o hw7 format.o test.o $(LDFLAGS) $(LDLIBS)

format.o: $(SRC)/format.cpp $(SRC)/format.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/format.cpp -o format.o

test.o: $(TESTS)/test.cpp $(SRC)/format.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp -o test.o

.PHONY: test clean

clean:
	del /Q /F hw7 hw7.exe *.o

test: hw7
	.\hw7.exe
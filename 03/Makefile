CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw3 $(TESTS)

hw3: parser.o test.o
	$(CXX) $(CXXFLAGS) -o hw3 parser.o test.o $(LDFLAGS) $(LDLIBS)

parser.o: $(SRC)/parser.cpp $(SRC)/parser.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/parser.cpp  -o parser.o

test.o: $(TESTS)/test.cpp $(SRC)/parser.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp  -o test.o
.PHONY: test
clean:
	del /Q *.o hw3.exe 2>nul

test: hw3
	.\hw3.exe
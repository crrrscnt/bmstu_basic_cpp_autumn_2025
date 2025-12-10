CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw8 $(TESTS)

hw8: test.o
	$(CXX) $(CXXFLAGS) -o hw8 test.o $(LDFLAGS) $(LDLIBS)

test.o: $(TESTS)/test.cpp $(SRC)/bin_tree.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp

.PHONY: clean test

clean:
	del /Q /S *.o *.exe

test: hw8
	.\hw8.exe
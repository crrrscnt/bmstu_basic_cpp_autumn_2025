CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: bigint_test

bigint_test: bigint.o test.o
	$(CXX) $(CXXFLAGS) -o bigint_test bigint.o test.o $(LDFLAGS) $(LDLIBS)

bigint.o: $(SRC)/bigint.cpp $(SRC)/bigint.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/bigint.cpp -o bigint.o

test.o: $(TESTS)/test.cpp $(SRC)/bigint.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp -o test.o

.PHONY: test clean

clean:
	del /Q /F bigint_test bigint_test.exe *.o

test: bigint_test
	.\bigint_test.exe
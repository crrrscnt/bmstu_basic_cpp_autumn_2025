CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw4 $(TESTS)

hw4: matrix.o test.o
	$(CXX) $(CXXFLAGS) -o hw4 matrix.o test.o $(LDFLAGS) $(LDLIBS)

matrix.o: $(SRC)/matrix.cpp $(SRC)/matrix.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/matrix.cpp

test.o: $(TESTS)/test.cpp $(SRC)/matrix.hpp
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp

clean:
	del /Q /S *.o *.exe
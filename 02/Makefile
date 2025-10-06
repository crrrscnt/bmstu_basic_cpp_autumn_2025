CXX = g++
VCPKG_ROOT = C:/Users/User/vcpkg/installed/x64-mingw-static
CXXFLAGS = -std=c++20 -g -Wall -pedantic -Wextra -I$(VCPKG_ROOT)/include
LDFLAGS = -L$(VCPKG_ROOT)/lib
LDLIBS = -lgtest -lgtest_main -lpthread

SRC = src
TESTS = tests

all: hw2

hw2: allocator.o test.o
	$(CXX) $(CXXFLAGS) -o hw2 allocator.o test.o $(LDFLAGS) $(LDLIBS)

allocator.o: $(SRC)/allocator.cpp $(SRC)/allocator.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/allocator.cpp

test.o: $(TESTS)/test.cpp $(SRC)/allocator.h
	$(CXX) $(CXXFLAGS) -c $(TESTS)/test.cpp

clean:
	del /Q *.o hw2.exe 2>nul
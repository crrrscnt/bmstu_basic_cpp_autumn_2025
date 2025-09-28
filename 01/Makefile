CXX = g++
FLAGS =-std=c++20 -g -Wall

SRC = src

all: hw1

hw1: hw1.o
	$(CXX) $(FLAGS) -o hw1 hw1.o

hw1.o: $(SRC)/hw1.cpp
	$(CXX) $(FLAGS) -c $(SRC)/hw1.cpp

clean:
	rm -rf *.o hw1

CXX=g++
CXXFLAGS=--std=c++20 -g -O0 -Wall

start: receiver.o  start.o
	g++ receiver.o  start.o -o start --std=c++20 


.PHONY:
clean:
	rm -f *.o start

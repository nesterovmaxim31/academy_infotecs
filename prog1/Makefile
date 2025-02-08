CXX=g++
CXXFLAGS=--std=c++20 -g -O0 -Wall

start: sockethandler.o sender.o start.o
	g++ sockethandler.o sender.o start.o -o start --std=c++20 


.PHONY:
clean:
	rm -f *.o start

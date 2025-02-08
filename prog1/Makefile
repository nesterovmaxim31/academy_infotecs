CXX=g++
CXXFLAGS=--std=c++20

start: sockethandler.o sender.o start.o
	g++ sockethandler.o sender.o start.o -o start --std=c++20 


.PHONY:
clean:
	rm -f *.o start

#ifndef SOCKETHANDLER_HH
#define SOCKETHANDLER_HH

#include "main.hh"

class SocketHandler {
  Main &parent;
  
  
public:
  SocketHandler(Main &parent_) : parent(parent_) {};
  void send();
  void start();
};


#endif

#ifndef SOCKETHANDLER_HH
#define SOCKETHANDLER_HH

#include "main.hh"

class SocketHandler {
  Main &parent;
  
  void buffer_unload();
  void send();
  
public:
  SocketHandler(Main &parent_) : parent(parent_) {};
  void start();   
};


#endif

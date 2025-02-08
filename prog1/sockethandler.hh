#ifndef SOCKETHANDLER_HH
#define SOCKETHANDLER_HH

#include "main.hh"

class SocketHandler {
  Main &parent;
  const int PORT = 8080;
  std::string packet;
   
  void buffer_unload();
  void send_packet();
  
public:
  SocketHandler(Main &parent_) : parent(parent_) {};
  void start();   
};


#endif

#ifndef SOCKETHANDLER_HH
#define SOCKETHANDLER_HH

#include "main.hh"

#include <vector>
#include <utility>

class SocketHandler {
  Main &parent;
  const int PORT = 8080;
  std::string packet;
  std::vector<std::pair<int, char>> pairs;

  void print_queue();
  void buffer_unload();
  void send_packet();
  
public:
  SocketHandler(Main &parent_) : parent(parent_), pairs(0) {};
  void start();   
};


#endif

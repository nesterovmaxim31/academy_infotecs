#ifndef RECEIVER_HH
#define RECEIVER_HH

#include <vector>
#include <utility>

class Receiver {
  const int PORT = 8080;
  char buffer[1024];
  bool newly_created;
  std::vector<std::pair<int, char>> pairs;

  void get_packet();
  void print_buffer();

public:
  Receiver() : newly_created(true), pairs(0) {};
  void start();
};



#endif

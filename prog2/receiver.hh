#ifndef RECEIVER_HH
#define RECEIVER_HH


class Receiver {
  const int PORT = 8080;
  char buffer[1024];
  bool newly_created;

  void get_packet();
  void print_buffer();

public:
  Receiver() : newly_created(true) {};
  void start();
};



#endif

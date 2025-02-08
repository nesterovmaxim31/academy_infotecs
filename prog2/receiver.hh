#ifndef RECEIVER_HH
#define RECEIVER_HH


class Receiver {
  const int PORT = 8080;
  

  void get_packet();
  void output_data();

public:
  void start();
};



#endif

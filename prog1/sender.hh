#ifndef SENDER_HH
#define SENDER_HH

#include <string>

#include "main.hh"

class Sender{
  Main &parent;
  std::string str;

  void get_string();
  bool is_valid();
  void parse_string();

public:
  Sender(Main &parent_) : parent(parent_) {};
  void start();
};

#endif

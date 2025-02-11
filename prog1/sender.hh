#ifndef SENDER_HH
#define SENDER_HH

#include <string>
#include <vector>
#include <utility>

#include "main.hh"

class Sender{
  Main &parent;
  std::string str;
  std::vector<std::pair<int, char>> pairs;

  void get_string();
  bool is_valid();
  void buffer_load();
  void parse_string();

public:
  Sender(Main &parent_) : parent(parent_), pairs(0) {};
  void start();
};


#endif

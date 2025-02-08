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
  void parse_string();
  void buffer_load();

public:
  Sender(Main &parent_) : parent(parent_) {};
  void start();
};

#endif

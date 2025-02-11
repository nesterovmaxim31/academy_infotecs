#ifndef MAIN_HH
#define MAIN_HH

#include <barrier>
#include <queue>
#include <utility>


class Main {
public:
  std::barrier<> sync_point;
  std::queue<std::pair<int, char>> buffer;

  Main() : sync_point(2) {}
};


#endif

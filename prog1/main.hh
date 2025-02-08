#ifndef MAIN_HH
#define MAIN_HH

#include <barrier>
#include <queue>
#include <utility>
#include <thread> 

class Main {
protected:
  std::barrier<> sync_point;
  std::queue<std::pair<int, char>> buffer;

public:
  Main() : sync_point(2) {}
};


#endif

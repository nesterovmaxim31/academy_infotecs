#ifndef MAIN_HH
#define MAIN_HH

#include <barrier>
#include <queue>

class Main {
  std::barrier sync_point;
  std::queue<pair<int, char>> buffer;

public:
  Main() {
    sync_point = std::barrier{2};
  }
};


#endif MAIN_HH

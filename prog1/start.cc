#include <iostream>

#include "sender.hh"
#include "sockethandler.hh"

#include <thread>


using namespace std;

int main() {
  Main parent;
  Sender sender(parent);
  SocketHandler sockethandler(parent);
  
  thread thread1(&Sender::start, &sender);
  thread thread2(&SocketHandler::start, \
		 &sockethandler);

  thread1.join();
  thread2.join();

  return 0;
}

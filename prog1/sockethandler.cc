#include "sockethandler.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>


using namespace std;

void SocketHandler::buffer_unload() {
  
}

void SocketHandler::send() {
  
}


void SocketHandler::start() {
  while(true) {
    // wait for first thread to finish input
    this->buffer_unload();
    this->send();
  }
}

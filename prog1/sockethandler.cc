#include "sockethandler.hh"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>


using namespace std;



void SocketHandler::buffer_unload() {
  pair<int, char> el;
  el = parent.buffer.front();
  
  while(el.first != -1 && !parent.buffer.empty()) {
    parent.buffer.pop();
    packet += " " + to_string(el.first) + " " + el.second;
    el = parent.buffer.front();

  }

  packet += "\n\0";
}

void SocketHandler::send_packet() {  
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  while (connect(clientSocket, (struct sockaddr*)&serverAddress,
	  sizeof(serverAddress)) != 0) {
    cout << "Error during connection. Try again in 3 seconds" << endl; 
    sleep(3);
  }


  send(clientSocket, packet.c_str(), packet.length(), 0);

  close(clientSocket);


}


void SocketHandler::start() {
 reconnect:
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;


  while (connect(clientSocket, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress)) != 0) {
    cout << "Error during connection. Try again in 2 seconds" << endl; 
    sleep(3);
  }
  int q;
  while(true) {    
    parent.sync_point.arrive_and_wait();
    
    this->buffer_unload();

    q = send(clientSocket, packet.c_str(), packet.length() + 1, MSG_NOSIGNAL);
    if (q == -1) {
      cout << "connection is lost" << endl;
      goto reconnect;
    } 
  }

  close(clientSocket);
}

#include "sockethandler.hh"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

void SocketHandler::print_queue() {
  cout << "The entered string consists of these characters:" << endl;
  
  for(vector<pair<int, char>>::iterator it = pairs.begin();\
      it != pairs.end(); it++) {
    cout << "Character: " << (*it).second << " количество повторений: "	\
	 << (*it).first << endl;
  }
}


void SocketHandler::buffer_unload() {
  pairs.clear();
  pair<int, char> el;
  el = parent.buffer.front();
  
  while(el.first != -1 && !parent.buffer.empty()) {
    pairs.push_back({el.first, el.second});
    parent.buffer.pop();
    el = parent.buffer.front();
  }

  this->print_queue();
  
  sort(pairs.begin(), pairs.end());  
  pairs.erase(unique(pairs.begin(), pairs.end()), pairs.end());

  for(vector<pair<int, char>>::iterator it = pairs.begin();	\
      it != pairs.end(); it++) {
    packet += to_string((*it).first) + " " + (*it).second + " ";    
  }

  pairs.clear();
  packet += "-1 -1\n";
}


void SocketHandler::send_packet() {  
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  while (connect(clientSocket, (struct sockaddr*)&serverAddress,
	  sizeof(serverAddress)) != 0) {
    fprintf(stderr,"Error during connection. Try again in 3 seconds\n"); 
    sleep(3);
  }

  send(clientSocket, packet.c_str(), packet.length(), 0);

  close(clientSocket);
}


void SocketHandler::start() {
  int q, clientSocket;
  sockaddr_in serverAddress;
  
 reconnect:
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;


  while (connect(clientSocket, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress)) != 0) {
    cout << "Error during connection. Try again in 2 seconds" << endl; 
    sleep(3);
  }

  while(true) {    
    parent.sync_point.arrive_and_wait();
    
    this->buffer_unload();

    q = send(clientSocket, packet.c_str(), packet.length() + 1, MSG_NOSIGNAL);
    if (q == -1) {
      fprintf(stderr, "connection is lost");
      goto reconnect;
    } 
  }

  close(clientSocket);
}

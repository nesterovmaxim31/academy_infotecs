#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "receiver.hh"


using namespace std;

void Receiver::output_data() {
  
}


void Receiver::get_packet() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  bind(serverSocket, (struct sockaddr*)&serverAddress,
       sizeof(serverAddress));

 reconnect:
  cout << "Wait for connection" << endl;
  listen(serverSocket, 5);

 
  int clientSocket = accept(serverSocket, nullptr, nullptr);

  if (clientSocket == -1) {
    cout << "Error during connection. Try adain in 3 seconds" << endl;
    sleep(3);
    // goto connection;
  }

  cout << "connection  succesfull" << endl;
  char buffer[1024] = { 0 };

  int q;
  
  while (true) {
    q = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(q != 0) {
      cout << "Message from client: " << buffer << endl;
      bzero(buffer, sizeof(buffer));
    }
    else
      goto reconnect;
  }

  close(serverSocket);
}


void Receiver::start() {
  while(true) {
    this->get_packet();
    this->output_data();
  }
}

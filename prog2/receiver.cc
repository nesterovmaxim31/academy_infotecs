#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "receiver.hh"


using namespace std;

inline bool is_return(const char& input)
{
    return input == '\n' || input == '\r';
}

string last_line (const string& input)
{
    if(input.length() == 1) return input;
    size_t position = input.length()-2; // last character might be a return character, we can jump over it anyway
    while((not is_return(input[position])) and position > 0) position--;
    // now we are at the \n just before the last line, or at the first character of the string
    if(is_return(input[position])) position += 1;
    // now we are at the beginning of the last line

    return input.substr(position);
}

void Receiver::print_buffer() {
  if(newly_created) {
    cout << buffer;
    newly_created = false;
  }
  else {
    cout << last_line(buffer);
  }
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
  }

  cout << "connection  succesfull" << endl;


  int q;
  
  while (true) {
    q = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(q != 0) {
      this->print_buffer();
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
  }
}

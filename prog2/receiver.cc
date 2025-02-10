#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "receiver.hh"


using namespace std;

bool is_return(const char& input) {
  return input == '\n' || input == '\r';
}


string last_line (const string& input) {
  if(input.length() == 1)
    return input;

  size_t position = input.length()-2;
    
  while((not is_return(input[position])) and position > 0)
    position--;

  if(is_return(input[position]))
    position += 1;

  return input.substr(position);
}


void Receiver::print_buffer() {
  string str;
  int value;
  char c;
  
  if(newly_created) {
    str = buffer;
    newly_created = false;
  }
  else {
    str = last_line(buffer);
  }

  stringstream s(str);  
  s >> value;
  s >> c;
  
  do {
    pairs.push_back({value, c});
    s >> value;
    s >> c;
  } while(value != -1);

  sort(pairs.begin(), pairs.end());  

  cout << endl << "The entered string consists of these characters: " << endl;
  for(vector<pair<int, char>>::iterator it = pairs.begin(); \
      it != pairs.end(); it++) {    
    cout << "Character: " << (*it).second << ", amount: " << (*it).first << endl;
  }

  pairs.clear();
}


void Receiver::get_packet() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  int clientSocket, q;

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  bind(serverSocket, (struct sockaddr*)&serverAddress,
       sizeof(serverAddress));

 reconnect:
  cout << "Wait for connection" << endl;
  listen(serverSocket, 5);
 
  clientSocket = accept(serverSocket, nullptr, nullptr);

  if (clientSocket == -1) {
    cout << endl <<"Error during connection. Try again in 3 seconds" << endl;
    sleep(3);
  }

  cout << "Connection  succesfull" << endl;
  
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

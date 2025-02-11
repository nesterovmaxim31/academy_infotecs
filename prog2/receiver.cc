#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "receiver.hh"


using namespace std;

/* Парсинг полученного сообщения, сортировка символов и вывод в консоль */
void Receiver::print_buffer() {
  string str, str_;
  int value;
  char c;

  str = buffer;

  stringstream s(str);
  for(size_t i = 0; i < count(str.begin(), str.end(), '\n'); i++) {
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
  
}

/* Получение информации от первой программы через сокет */
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
      /* Потеря соединения */
      goto reconnect;
  }

  close(serverSocket);
}

/* Запуск второй программы */ 
void Receiver::start() {
  while(true) {
    this->get_packet();
  }
}

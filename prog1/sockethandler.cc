#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <algorithm>

#include "sockethandler.hh"


using namespace std;

/* Вывод полученных данных от первого потока */
void SocketHandler::print_queue() {
  cout << endl <<"The entered string consists of these characters:" << endl;
  
  for(vector<pair<int, char>>::iterator it = pairs.begin();\
      it != pairs.end(); it++) {
    cout << "Character: " << (*it).second << ", amount: "\
	 << (*it).first << endl;
  }
}

/* Выгрузка из общего буфера первой программы в вектор для вывода
   в консоль полученных символов и формирования строки для отправки по сокету */
void SocketHandler::buffer_unload() {
  pairs.clear();
  
  pair<int, char> el = parent.buffer.front();
  
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
  packet += "-1 0\n";
}

// Запуск второго потока первой программы
void SocketHandler::start() {
  int q, clientSocket;
  sockaddr_in serverAddress;
  
 reconnect:
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  /* Ожидание подключения второй программы (ввод пользователь
     может продолжать, когда сокет подключиться, из буфера будет
     считана вся накопившеейся информация и обработана) */ 
  while (connect(clientSocket, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress)) != 0) {}

  while(true) {    
    parent.sync_point.arrive_and_wait();
    
    this->buffer_unload();

    q = send(clientSocket, packet.c_str(), packet.length() + 1, MSG_NOSIGNAL);
    if (q == -1) {
      /* Попытка переподключения при потери соединения со второй программой */
      goto reconnect;
    }

    packet.clear();
  }

  close(clientSocket);
}

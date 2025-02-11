#include <cctype>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "sender.hh"


using namespace std;

/* Получение строки от пользователя из терминала */
void Sender::get_string() {
  getline(cin, str);
}

/* Проверка строки на соотвествие правилам */
bool Sender::is_valid() {
  if (str.length() > 64)
    return false;
  
  for(string::const_iterator it = str.begin(); it != str.end();\
      it++) {
    if(!isalpha(*it))
      return false;
  }
    
  return true;
}

/* Загрузка в буффер множества всех символов и количества
   их повторений в введённой строке */
void Sender::buffer_load() {
  for(vector<pair<int, char>>::iterator it = pairs.begin(); \
      it != pairs.end(); it++) {
    parent.buffer.push(*it);
  }

  pairs.clear();
}

/* Разбитие строки на символы и подсчёт количества их вхождения */
void Sender::parse_string() {
  int value;
  bool flag; 
  
  for(string::iterator it = str.begin(); it != str.end(); it++) {
    value = ranges::count(str, *it);

    flag = true;

    for(vector<pair<int, char>>::iterator itv = pairs.begin();\
	itv != pairs.end(); itv++) {
      if((*itv).second  == *it) {
	flag = false;
	break;
      }
    }

    if (flag)      
      pairs.push_back({value, *it});
  }
}

/* Запуск первого потока первой программы */
void Sender::start() {
  while(true) {
    this->get_string();

    if (this->is_valid()) {
      this->parse_string();
      this->buffer_load();
    }
    else {
      cout << "String doesn't math rules" << endl;
      continue;
    }

    parent.sync_point.arrive_and_wait();
  }
}

#include <cctype>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>

#include "sender.hh"


using namespace std;

void Sender::get_string() {
  cout << "Enter a string: ";
  getline(cin, str);
}


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


void Sender::buffer_load() {
  for(vector<pair<int, char>>::iterator it = pairs.begin(); \
      it != pairs.end(); it++) {
    parent.buffer.push(*it);
  }
}


void Sender::parse_string() {
  int value;
  
  for(string::iterator it = str.begin(); it != str.end(); it++) {
    value = ranges::count(str, *it);
    pairs.push_back({value, *it});
  }

  pairs.erase(unique(pairs.begin(), pairs.end()), pairs.end());
  sort(pairs.begin(), pairs.end());  
}


void Sender::start() {
  while(true) {
    this->get_string();

    if (this->is_valid()) {
      this->parse_string();
      this->buffer_load();
    }
    else {
      fprintf(stderr, "String doesn't math rules\n");
    }

    cout << "String is handled and sent to buffer" << endl;
    parent.sync_point.arrive_and_wait();
  }
}

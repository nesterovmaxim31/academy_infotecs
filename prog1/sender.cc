#include <cctype>
#include <iostream>
#include <stdio.h>

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


void Sender::parse_string() {
  parent.buffer.push({30, '7'}); 
}


void Sender::start() {
  while(true) {
    this->get_string();

    if (this->is_valid()) {
      cout << 
      this->parse_string();
      
    }
    else {
      fprintf(stderr, "String doesn't math rules\n");
    }
  }
}

#include <iostream>
#include <map>
#include <string>
using namespace std;

int next_state(int state, string next_word, map<int, map<string, int>> table){
     map<string, int> event = table[state];
     if(event.count(next_word)){
          return event[next_word];
     }
     else{
          return -1;
     }
}

int main(){
     int state = 0;
     string next_word = "Hello";
     map<int, map<string, int>> table = {
          {0, {{"the", 1}}},
          {1, {{"lazy", 2}}},
          {1, {{"smelly", 2}}}
          //{"lazy", 2},
     };

     next_state(state, next_word, table);   

     
};


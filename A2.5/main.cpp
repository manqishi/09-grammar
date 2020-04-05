#include <iostream>
#include <map>
#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
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

int test_sentence(char str[]){
    vector <string> words;
    int state = 0;
    
    char* token;
    char* rest = str;
    while((token = strtok_r(rest, " ", &rest))){
        words.push_back(token);
    }
    
    map<int, map<string, int>> table = {
      {0, {{"the", 1}}},
      {1, {{"lazy", 2}, {"smelly", 2}, {"cat", 3}, {"dog", 3}}},
      {2, {{"lazy", 2}, {"smelly", 2}, {"cat", 3}, {"dog", 3}}},
      {3, {{"ate", 4}, {"ran", 4}}},
      {4, {{"slowly", 5}, {"noisily", 5}, {"EOI", 10}}},
      {5, {{"EOI", 10}}}
    };
    
    for(int i = 0; i < words.size(); i++){
        state = next_state(state, words[i], table);
    }
    return state;
}

TEST_CASE("Basic sentence structure"){
    char test1[] = "the dog ate EOI";
    REQUIRE(test_sentence(test1) == 10);
    
    char test2[]= "the cat ran EOI";
    REQUIRE(test_sentence(test2) == 10);
}

TEST_CASE("Adjectives test"){
    char test1[] = "the lazy dog ate EOI";
    REQUIRE(test_sentence(test1) == 10);
    
    char test2[] = "the smelly dog ate EOI";
    REQUIRE(test_sentence(test2) == 10);
    
    char test3[] = "the lazy smelly dog ate EOI";
    REQUIRE(test_sentence(test3) == 10);
    
    char test4[] = "the smelly lazy dog ate EOI";
    REQUIRE(test_sentence(test4) == 10);
}

TEST_CASE("Adverbs test"){
    char test1[] = "the dog ate slowly EOI";
    REQUIRE(test_sentence(test1) == 10);
    
    char test2[] = "the lazy dog ate noisily EOI";
    REQUIRE(test_sentence(test2) == 10);
    
    char test3[] = "the lazy dog ate slowly noisily EOI";
    REQUIRE(test_sentence(test3) == -1);
}

TEST_CASE("Full sentence"){
    char test1[] = "the lazy smelly cat ran slowly EOI";
    REQUIRE(test_sentence(test1) == 10);

    char test2[] = "the smelly lazy cat ate noisily EOI";
    REQUIRE(test_sentence(test2) == 10);
}

TEST_CASE("Not starting with the"){
    char test1[] = "dog ate EOI";
    REQUIRE(test_sentence(test1) == -1);
}

TEST_CASE("Missing EOI"){
    char test1[] = "the dog ate";
    REQUIRE(test_sentence(test1) != 10);
}

TEST_CASE("None existent word or symbol test"){
    char test1[] = "the cow ate EOI";
    REQUIRE(test_sentence(test1) == -1);
    
    char test2[] = "the lazy, smelly cow ate EOI";
    REQUIRE(test_sentence(test2) == -1);
}
    


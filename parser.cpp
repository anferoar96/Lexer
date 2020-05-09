#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>


using namespace std;

typedef multimap<string, vector<string>> Map;



string parser_func(vector<Token> analisis){

    Map map;
    map.insert(Map::value_type("TEST", {"HOLA","2","3"}));
    map.insert(Map::value_type("TEST", {"HOLA2","4","5"}));

    for (auto itr = map.begin(); itr != map.end(); itr++) {
       for (int i=0;i<itr->second.size();i++){
           cout<<itr->second[i]<<" ";
       }
       cout<<endl;
    }
    return to_string(analisis.size());
}
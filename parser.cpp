#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>


using namespace std;

typedef multimap<string, vector<vector<string>>> Map;

string parser_func(vector<Token> analisis){

    Map map;
    map.insert(Map::value_type("inicial", {{"var_def"},{"func_def"},{"class_def"},{"stmt"},{"multi_init"}}));
    map.insert(Map::value_type("var_def",{{"typed_var","TK_ASIG","literal","NEWLINE"}}));
    map.insert(Map::value_type("literal",{{"NONE"},{"TRUE"},{"FALSE"},{"TK_ENTERO"}}));
    map.insert(Map::value_type("typed_var", {{"id_n","TK_DOS_PUNTOS","type"},{"multi_var"},{"tipo_dato","TK_DOS_PUNTOS","type"}}));
    map.insert(Map::value_type("id_n", {{"ID"}}));

    for (auto itr = map.begin(); itr != map.end(); itr++) {
       for (int i=0;i<itr->second.size();i++){
           cout<<itr->second[i][0]<<" ";
       }
       cout<<endl;
    }
    return to_string(analisis.size());
}
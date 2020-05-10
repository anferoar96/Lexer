#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef multimap<string, vector<vector<string>>> Map;


Map gramatica={
    {Map::value_type("inicial", {{"var_def"},{"func_def"},{"class_def"},{"stmt"},{"multi_init"}})},
    {Map::value_type("var_def",{{"typed_var","TK_ASIG","literal","NEWLINE"}})},
    {Map::value_type("literal",{{"NONE"},{"TRUE"},{"FALSE"},{"TK_ENTERO"}})},
    {Map::value_type("typed_var", {{"id_n","TK_DOS_PUNTOS","type"},{"multi_var"}})},
    {Map::value_type("type", {{"id_n"},{"tipo_dato"}})},
    {Map::value_type("tipo_dato", {{"INT"},{"STRING"}})},
    {Map::value_type("id_n", {{"ID"}})}
};

string parser_func(vector<Token> analisis){

    stack<int> posicion;
    stack<vector<string>> estado;


    string inicial="inicial";
    auto word =gramatica.find(inicial);
    auto vec = word->second[0];
    cout<<vec[0]<<endl;
    
   /* while(true){
        int contvec=0;
        auto word=gramatica.find(inicial);
        auto vec=word->second[0];
        for(int j=0;j<vec.size();j++){
            if(isupper(vec[0][0])){
                string res=analisis[contvec].id;
                transform(vec[0].begin(), vec[0].end(), vec[0].begin(), ::tolower);
                if(res.compare(vec[0])!=0){
                    cout<<"Error semantico"<<endl;
                }
                contvec++;
            }else{
                posicion.push(contvec);
                estado.push(word->second[0]);
                inicial=j;
                break;
            }
        }

    } */
    

    return to_string(analisis.size());
}
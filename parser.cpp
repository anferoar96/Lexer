#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


int cont =0;
string tok;

extern vector<Token> analisis;

void emparejar(string esperado,string token){
    if(esperado==token){
        if(cont>=analisis.size()){
        }else{
            tok=analisis[cont++].id;
        }  
    }else{
        cout<<"Error sintactico, se esperaba "<<esperado<<endl;
        exit (EXIT_FAILURE);
    }
}

void typed_v(string& tok){
    if(tok=="id"){

    }
}

void literal(string& tok){
    if(tok=="None" || tok=="True" || tok=="False" || tok=="tk_entero" || tok=="tk_cadena"){
        emparejar(tok,tok);
    }else{
        cout<<"Error sintactico"<<endl;
    }
}

void var_def(string& tok){
    if(tok=="id"){
        typed_v(tok);
        emparejar("tk_asig",tok);
        literal(tok);
    }else{
        cout<<"Error sintactico"<<endl;
    }
}

void inicial(string& tok){
    if(tok=="id"){
        var_def(tok);
    }else{
        cout<<"Error sintactico"<<endl;
    }
}

string parser_func(){

    string tok=analisis[cont].id;

    while(cont<analisis.size()){
        inicial(tok);
    }

    return "No hay error sintactico";
}
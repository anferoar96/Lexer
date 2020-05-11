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
string error="Error sintantico se esperaba";

extern vector<Token> analisis;

void emparejar(string esperado,string token){
    cont++;
    if(esperado==token){
        if(cont>=analisis.size()){
        }else{
            tok=analisis[cont].id;
        }  
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

void id_n(string& tok){
    if(tok=="id"){
        emparejar("id",tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

void tipo_dato(string& tok){
    if(tok=="int" || tok=="str" || tok=="bool"){
        emparejar(tok,tok);
    }else{
        exit (EXIT_FAILURE);
    }
}

void type_d(string& tok){
    if(tok=="id"){
        id_n(tok);
    }else if(tok=="tk_corch_izq"){
        emparejar("tk_corch_izq",tok);
        type_d(tok);
        emparejar("tk_corch_der",tok);
    }else{
        tipo_dato(tok);
    }
}

void typed_v(string& tok){
    if(tok=="id"){
        id_n(tok);
        emparejar("tk_dos_puntos",tok);
        type_d(tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

void literal(string& tok){
    if(tok=="None" || tok=="True" || tok=="False" || tok=="tk_entero" || tok=="tk_cadena"){
        emparejar(tok,tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

void var_def(string& tok){
    if(tok=="id"){
        typed_v(tok);
        emparejar("tk_asig",tok);
        literal(tok);
        emparejar("newline",tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

void inicial(string& tok){
    if(tok=="id"){
        var_def(tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
}

string parser_func(){

    tok=analisis[cont].id;

    while(cont<analisis.size()){
        inicial(tok);
    }

    return "No hay error sintactico";
}
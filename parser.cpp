#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include<set>

using namespace std;


int cont =0;
string tok;
string error="Error sintantico se esperaba";

extern vector<Token> analisis;

set<string>p1={"id","tk_corch_izq","tk_par_izq","tk_neg","None","True","False","tk_entero","tk_cadena"};
set<string>p2={"none","true","false","tk_entero","tk_cadena"};
set<string>p3={"tk_suma","tk_multi","tk_neg","tk_division","tk_modulo","tk_distinto","tk_igual_igual","tk_mayor_igual","tk_menor_igual","tk_mayor","tk_menor","is"};

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

void id_o(string& tok){
    if(tok=="object"){
        emparejar("object",tok);
    }else{
        cout<<error<<endl;
        exit(EXIT_FAILURE);
    }
}

void type_d(string& tok){
    if(tok=="id"){
        id_n(tok);
    }else if(tok=="tk_corch_izq"){
        emparejar("tk_corch_izq",tok);
        type_d(tok);
        emparejar("tk_corch_der",tok);
    }else if(tok=="object"){
        id_o(tok);
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
    if(tok=="None" || tok=="True" || tok=="False" || tok=="tk_entero" || tok=="tk_cadena" || tok=="id"){
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

void expr(string& tok){
    int sig=cont+1;
    if(tok=="not"){
        emparejar(tok,"not");
        expr(tok);
    }else{
        cout<<error<<endl;
    }
}

void multi_expr(string& tok){
    expr(tok);
    emparejar("tk_coma",tok);
    multi_expr(tok);
}

void cexpr(string& tok){
    if(tok=="id"){
        id_n(tok);
    }else if(p2.find(tok)!=p2.end()){
        literal(tok);
    }else if(tok=="tk_par_izq"){
        emparejar("tk_par_izq",tok);
        expr(tok);
        emparejar("tk_par_der",tok);
    }else if(tok=="tk_corch_izq"){
        emparejar("tk_corch_izq",tok);
        multi_expr(tok);
        emparejar("tk_corch_der",tok);
    }else{
        cout<<error<<endl;
    }

}

void member_expr(string& tok){
    if(p1.find(tok)!=p1.end()){
        cexpr(tok);
        emparejar("tk_corch_izq",tok);
        expr(tok);
        emparejar("tk_corch_der",tok);
    }else{
        cout<<error<<endl;
    }
}

void target(string& tok){
    if(p1.find(tok)!=p1.end()){
        member_expr(tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);  
    }
    
    
}


void multitar(string& tok){
    if(p1.find(tok)!=p1.end()){
        target(tok);
        emparejar("tk_asign",tok);
        multitar(tok);
    }else{
        cout<<error<<endl;
    }

}

void stmt_simple(string& tok){
    if(p1.find(tok)!=p1.end()){
        multitar(tok);
        expr(tok);
    }else{
      cout<<error<<endl;
      exit (EXIT_FAILURE);  
    }
}


void stmt(string& tok){
    if(p1.find(tok)!=p1.end()){
        stmt_simple(tok);
        emparejar("newline",tok);
    }else{
        cout<<error<<endl;
        exit (EXIT_FAILURE);
    }
    
}

void inicial(string& tok){
    if(tok=="id"){
        int view=cont+1;
        if(analisis[view].id=="tk_dos_puntos"){
            var_def(tok);
        }else{
             stmt(tok);
        }   
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
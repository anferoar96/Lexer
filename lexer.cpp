#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std; 

#define ll long long
#define pb push_back
#define rep(i,n) for (int i = 0; i < n; i++)

set<string> keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", 
"class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", 
"if", "import", "in","is","lambda","nonlocal","not","or","pass","raise","return","try","while",
"with","yield","int","str","object","bool","self","print","len"}; 

map<char,string> solo={
	{'(',"tk_par_izq"},
	{')',"tk_par_der"},
	{':',"tk_dos_puntos"},
	{'%',"tk_modulo"},
	{'[',"tk_corch_izq"},
	{']',"tk_corch_der"},
	{'*',"tk_multi"},
	{'+',"tk_suma"},
	{',',"tk_coma"},
	{'.',"tk_punto"},
};

struct token
{
	string id;
	string info;
	int fila;
	int col;
}ob;


vector<token> analisis;

//Compatibilidad con windows
string& rtrim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

int solve(string s,int fila,int columna){
	
	int state=0;
	string s2="";
	string res;
	int cont=-1;
	regex letra("[a-zA-Z]");
	regex numero("[0-9]");
	regex numletra("[0-9a-zA-z]");
	while(true){
		switch(state)
    	{
        case 0: 
        	{
	        	cont++;
	        	string aux=s.substr(cont,1);
				 if(int(s[cont])<32 || int(s[cont])>126 ){
					if(s[cont]== '\0'){
					}else{
						ob={"error","error",fila,cont+1};
						analisis.pb(ob);
						return -1;
					}
				}

				auto itr =solo.find(s[cont]);
				if(itr!=solo.end()){
					ob={itr->second,"",fila,cont+1};
	        		analisis.pb(ob);
				}else if(s[cont]=='_' || regex_match(aux, letra)){
	        		state=1;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(regex_match(aux,numero)){
	        		state=3;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='"'){
	        		state=4;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='='){
	        		state=5;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='-'){
	        		state=6;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='/'){
	        		state=7;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='!'){
	        		state=8;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='>'){
	        		state=9;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='<'){
	        		state=10;
	        		columna=cont;
	        		s2=s2+s[cont];
	        	}else if(s[cont]=='#'){
					cont = s.length();
	        	}else if(s[cont]==' '){
	        	}
	        	break;
        	}
        case 1: 
        	{
	        	cont++;
				while(s[cont]=='_' || regex_match(s.substr(cont,1), numletra) ){
	        		s2=s2+s[cont];
	        		cont++;
	        	}
	        	cont--;
	        	auto key=keywords.find(s2); //Retornar la string
	        	if(key == keywords.end()){
					ob={"id",s2,fila,columna+1};
	        		analisis.pb(ob);
	        	}else{
					ob={s2,"",fila,columna+1};
	        		analisis.pb(ob);
	        	}
	        	state=0;
	        	s2="";
	        	break;
        	}
        case 3:
        	{
        		cont++;
				while(regex_match(s.substr(cont,1), numero)){
        			s2=s2+s[cont];
        			if(stol(s2)>2147483647){
						ob={"error","error",fila,cont+1};
	        			analisis.pb(ob);
        				return -1;
        			}
        			cont++;
        		}
        		cont--;
				ob={"tk_entero",s2,fila,columna+1};
	        	analisis.pb(ob);
        		state=0;
        		s2="";

        		break;
    		}
    	case 4:
    		{
				cont++;
				while((int(s[cont])>=32 && int(s[cont])<=126) ){ 
					s2=s2+s[cont];
    				cont++;
					if(s[cont]=='"'){
						s2=s2+s[cont];
						break;
					}
    			}
				ob={"tk_cadena",s2,fila,columna+1};
	        	analisis.pb(ob);
				if(int(s[cont])<32 || int(s[cont])>126){
					ob={"error","error",fila,cont+1};
	        		analisis.pb(ob);
					return -1;
				}
    			state=0;
    			s2="";
    			break;
    		}
    	 case 5:
    		{
				cont++;
    			if(s[cont]=='='){
					ob={"tk_igual_igual","",fila,columna+1};
	        		analisis.pb(ob);
    			}else{
					ob={"tk_asig","",fila,columna+1};
	        		analisis.pb(ob);
					cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 6:
    		{
				cont++;
    			if(s[cont]=='>'){
					ob={"tk_ejecuta","",fila,columna};
	        		analisis.pb(ob);
    			}else{
					ob={"tk_neg","",fila,columna+1};
	        		analisis.pb(ob);
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 7:
    		{
    			cont++;
				if(s[cont]=='/'){
    				ob={"tk_division","",fila,columna+1};
	        		analisis.pb(ob);
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 8:
    		{
    			cont++;
				if(s[cont]=='='){
					ob={"tk_distinto","",fila,columna+1};
	        		analisis.pb(ob);
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	 case 9:
    		{
    			cont++;
				if(s[cont]=='='){
    				ob={"tk_mayor_igual","",fila,columna+1};
	        		analisis.pb(ob);
    			}else{
					ob={"tk_mayor","",fila,columna+1};
	        		analisis.pb(ob);
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 10:
    		{
    			cont++;
				if(s[cont]=='='){
    				ob={"tk_menor_igual","",fila,columna+1};
	        		analisis.pb(ob);
    			}else{
    				ob={"tk_menor","",fila,columna+1};
	        		analisis.pb(ob);
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
        default: 
        	cout << "Usted ha ingresado una opción incorrecta";
        	cont=s.length(); 
    	}
    	if(s.length()<=cont){
    		return state;
    	}
	}
}


 int main(int argc, char *argv[])
{
     string line;
	 string texto=argv[1];
	 string res="Casos/"+texto;
	 ifstream myfile (res);

     int fila=1,col;
	if (myfile.is_open()){
		while ( getline (myfile,line) ){
			line=rtrim(line);
			if(line.length()==0){
			}else{
				col=1;
     			int t=solve(line,fila,col);	
				if(t==-1){
					break;
				}
			}	
			fila++;
		}
    	myfile.close();
  	}else{
		  cout<<"Unable to open file"<<endl;
	}
	ofstream resultado;
	resultado.open("Resultados/"+texto);
	for(auto i:analisis){
		if(i.id=="error" && i.info=="error"){
			resultado<<">>> Error lexico (linea: "<<i.fila<<",posicion:"<<i.col<<")"<<'\n';
		}else if(i.info==""){
			resultado<<"<"<<i.id<<","<<i.fila<<","<<i.col<<">"<<'\n';
		}else{
			resultado<<"<"<<i.id<<","<<i.info<<","<<i.fila<<","<<i.col<<">"<<'\n';
		}
		
	}
	resultado.close();
     return 0;
}
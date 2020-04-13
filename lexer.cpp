#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>

using namespace std; 

#define ll long long
#define pb push_back
#define rep(i,n) for (int i = 0; i < n; i++)

vector<string> keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", 
"class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", 
"if", "import", "in","is","lambda","nonlocal","not","or","pass","raise","return","try","while",
"with","yield","int","str","object","bool","self","print","len"}; 

vector<string> analisis;


string search(string word){
	for(auto i:keywords){
		if(i==word){
			return i;
		}
	}
	return "";
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
						res=">>>Error léxico(linea:"+to_string(fila)+",posicion:"+to_string(cont+1)+")";
						analisis.pb(res);
						return -1;
					}
				}
	        	if(s[cont]=='_' || regex_match(aux, letra)){
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
	        	}else if(s[cont]=='('){ 
					res = "<tk_par_izq,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
	        	}else if(s[cont]==')'){
					res= "<tk_par_der,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
	        	}else if(s[cont]==':'){
					res= "<tk_dos_puntos,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
	        	}else if(s[cont]=='%'){
					res= "<tk_modulo,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
	        	}else if(s[cont]=='['){
					res= "<tk_corch_izq,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
				}else if(s[cont]==']'){
					res= "<tk_corch_der,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
				}else if(s[cont]=='*'){
					res= "<tk_multi,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
	        	}else if(s[cont]=='+'){
					res= "<tk_suma,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
				}else if(s[cont]==','){
					res= "<tk_coma,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
				}else if(s[cont]=='#'){
					cont = s.length();
				}else if(s[cont]=='.'){
					res= "<tk_punto,"+to_string(fila)+","+to_string(cont+1)+">";
	        		analisis.pb(res);
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
	        	string key=search(s2); //Retornar la string
	        	if(key.empty()){
					res= "<id,"+s2+","+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
	        	}else{
					res= "<"+key+","+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
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
						res= ">>>Error léxico(linea:"+to_string(fila)+",posicion:"+to_string(cont+1)+")";
	        			analisis.pb(res);
        				return -1;
        			}
        			cont++;
        		}
        		cont--;
				res= "<tk_entero,"+s2+","+to_string(fila)+","+to_string(columna+1)+">";
	        	analisis.pb(res);
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
				res= "<tk_cadena,"+s2+","+to_string(fila)+","+to_string(columna+1)+">";
	        	analisis.pb(res);
				if(int(s[cont])<32 || int(s[cont])>126){
					res= ">>>Error léxico(linea:"+to_string(fila)+",posicion:"+to_string(cont+1)+")";
	        		analisis.pb(res);
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
					s2=s2+s[cont];
					res= "<tk_igual_igual,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}else{
					res= "<tk_asig,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
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
    				s2=s2+s[cont];
					res= "<tk_ejecuta,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}else{
					res= "<tk_neg,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
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
    				s2=s2+s[cont];
					res= "<tk_division,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 8:
    		{
    			cont++;
				if(s[cont]=='='){
    				s2=s2+s[cont];
					res= "<tk_distinto,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	 case 9:
    		{
    			cont++;
				if(s[cont]=='='){
    				s2=s2+s[cont];
					res= "<tk_mayor_igual,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}else{
    				s2=s2+s[cont];
					res= "<tk_mayor,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
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
    				s2=s2+s[cont];
					res= "<tk_menor_igual,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
    			}else{
    				s2=s2+s[cont];
					res= "<tk_menor,"+to_string(fila)+","+to_string(columna+1)+">";
	        		analisis.pb(res);
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
	resultado.open("Resultado/"+texto);
	for(auto i:analisis){
		resultado<<i<<'\n';
	}
	resultado.close();
     return 0;
}
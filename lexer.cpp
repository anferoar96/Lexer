#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>

using namespace std; 

#define ll long long
#define rep(i,n) for (int i = 0; i < n; i++)

vector<string> keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", 
"class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", 
"if", "import", "in","is","lambda","nonlocal","not","or","pass","raise","return","try","while",
"with","yield","int","str","object","bool","self","print","len"}; //Object,bool,self,print no son reservadas pera segun eso se manejan asi



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
					cont=s.length();
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
	        		cont++;
	        	}else if(s[cont]=='='){
	        		state=5;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='-'){
	        		state=6;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='/'){
	        		state=7;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='!'){
	        		state=8;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='>'){
	        		state=9;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='<'){
	        		state=10;
	        		columna=cont;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='('){ //Suponiendo que (( seguidos son dos tk_par_izq
	        		cout<<"<tk_par_izq,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]==')'){
	        		cout<<"<tk_par_der,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]==':'){
	        		cout<<"<tk_dos_puntos,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]=='%'){
	        		cout<<"<tk_modulo,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]=='*'){
	        		cout<<"<tk_multi,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]=='+'){
	        		cout<<"<tk_suma,"<<fila<<","<<cont+1<<">"<<endl;
				}else if(s[cont]==','){
					cout<<"<tk_coma,"<<fila<<","<<cont+1<<">"<<endl;
				}else if(s[cont]=='#'){
					cont = s.length();
				}else if(s[cont]=='.'){
	        		cout<<"<tk_punto,"<<fila<<","<<cont+1<<">"<<endl;
	        	}else if(s[cont]==' '){
	        		continue;
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
	        	//cout<<s2<<endl;
	        	string key=search(s2); //Retornar la string
	        	if(key.empty()){
	        		cout<<"<id,"<<s2<<","<<fila<<","<<columna+1<<">"<<endl;
	        	}else{
	        		cout<<"<"<<key<<","<<fila<<","<<columna+1<<">"<<endl;
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
        				cout<<"Error1"<<endl;
        				cont=s.length(); //Para que se salga del loop, tiene que ser mejorado
        				break;
        			}
        			cont++;
        		}
        		cont--;
        		if(s[cont]=='?'){ //Final de linea hay que solucionarlo
        			cout<<"Error2"<<endl;
        			cont=s.length();
        		}else{
        			cout<<"<tk_entero,"<<s2<<","<<fila<<","<<columna+1<<">"<<endl;
        			state=0;
        			s2="";
        		}
        		break;
    		}
    	case 4:
    		{
				while((int(s[cont])>=32 && int(s[cont])<=126) ){ //Mejorarlo para que solo admita ASCII del 32 al 126
					s2=s2+s[cont];
    				cont++;
					if(s[cont]=='"'){
						s2=s2+s[cont];
						break;
					}
    			}
    			//cont--;
    			cout<<"<tk_cadena,"<<s2<<","<<fila<<","<<columna+1<<">"<<endl;
    			state=0;
    			s2="";
    			break;
    		}
    	 case 5:
    		{
    			if(s[cont]=='='){
    				cout<<"<tk_igual_igual,"<<fila<<","<<columna+1<<">"<<endl;
    				cont--;
    			}else{
    				cout<<"<tk_asig,"<<fila<<","<<columna+1<<">"<<endl;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 6:
    		{
    			if(s[cont]=='>'){
    				s2=s2+s[cont];
    				cout<<"<tk_ejecuta,"<<fila<<","<<columna+1<<">"<<endl;
    			}else{
    				cout<<"<tk_neg,"<<fila<<","<<columna+1<<">"<<endl;
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 7:
    		{
    			if(s[cont]=='/'){
    				s2=s2+s[cont];
    				cout<<"<tk_division,"<<fila<<","<<columna+1<<">"<<endl;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 8:
    		{
    			if(s[cont]=='='){
    				s2=s2+s[cont];
    				cout<<"<tk_distinto,"<<fila<<","<<columna+1<<">"<<endl;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	 case 9:
    		{
    			if(s[cont]=='='){
    				s2=s2+s[cont];
    				cout<<"<tk_mayor_igual,"<<fila<<","<<columna+1<<">"<<endl;
    			}else{
    				s2=s2+s[cont];
    				cout<<"<tk_mayor,"<<fila<<","<<columna+1<<">"<<endl;
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
    	case 10:
    		{
    			if(s[cont]=='='){
    				s2=s2+s[cont];
    				cout<<"<tk_menor_igual,"<<fila<<","<<columna+1<<">"<<endl;
    			}else{
    				s2=s2+s[cont];
    				cout<<"<tk_menor,"<<fila<<","<<columna+1<<">"<<endl;
    				cont--;
    			}
    			state=0;
    			s2="";
    			break;
    		}
        default: 
        	cout << "Usted ha ingresado una opción incorrecta";
        	cont=s.length(); //Solo para propositos de saltarme el runtime error
    	}
    	if(s.length()<=cont){
    		return state;
    	}
	}
}


 int main()
{
     string line;
	 ifstream myfile ("Casos/L4.txt");
     int fila=1,col;
	if (myfile.is_open()){
		while ( getline (myfile,line) ){
			if(line.length()==0){
			}else{
				col=1;
     			int t=solve(line,fila,col);	
			}	
			fila++;
		}
    	myfile.close();
  	}else{
		  cout << "Unable to open file"<<endl; 
	}
   
     return 0;
}
#include <bits/stdc++.h>
#include <regex>
using namespace std; 

#define ll long long
#define rep(i,n) for (int i = 0; i < n; i++)

vector<string> keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", 
"class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", 
"if", "import", "in","is","lambda","nonlocal","not","or","pass","raise","return","try","while",
"with","yield","int","str"};



string search(string word){
	for(auto i:keywords){
		if(i==word){
			return i;
		}
	}
	return "";
}

int solve(string s){
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
                //Aun no manejo bien los indices
	        	cont++;
	        	string aux=s.substr(cont,1);
	        	if(s[cont]=='_' || regex_match(aux, letra)){
	        		state=1;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(regex_match(aux,numero)){
	        		state=3;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='"'){
	        		state=4;
	        		s2=s2+s[cont];
	        		cont++;
	        	}else if(s[cont]=='('){ //Suponiendo que (( seguidos son dos tk_par_izq
	        		cout<<"tk_par_izq"<<endl;
	        	}else if(s[cont]==')'){
	        		cout<<"tk_par_der"<<endl;
	        	}else if(s[cont]==':'){
	        		cout<<"tk_dos_puntos"<<endl;
	        	}else if(s[cont]=='%'){
	        		cout<<"tk_modulo"<<endl;
	        	}else if(s[cont]=='*'){
	        		cout<<"rk_multi"<<endl;
	        	}else if(s[cont]=='+'){
	        		cout<<"tk_suma"<<endl;
	        	}else if(s[cont]=='.'){
	        		cout<<"tk_punto"<<endl;
	        	}else if(s[cont]==' '){
	        		continue;
	        	}
	        	break;
        	}
        case 1: 
        	{
	        	while(s[cont]=='_' || regex_match(s.substr(cont,1), numletra) ){
	        		s2=s2+s[cont];
	        		cont++;
	        	}
	        	cont--;
	        	//cout<<s2<<endl;
	        	string key=search(s2); //Retornar la string
	        	if(key.empty()){
	        		cout<<"Identificador"<<endl;
	        	}else{
	        		cout<<key<<endl;
	        	}
	        	state=0;
	        	s2="";
	        	break;
        	}
        case 3:
        	{
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
        			cout<<"tk_entero"<<endl;
        			state=0;
        			s2="";
        		}
        		break;
    		}
    	case 4:
    		{
    			
    			while(regex_match(s.substr(cont,1), numletra) || s[cont]==' ' ){ //Mejorarlo para que solo admita ASCII del 32 al 126
    				s2=s2+s[cont];
    				cont++;
    			}
    			
    			if(s[cont]!='"'){
    				cout<<"error3"<<endl;
    				cont=s.length();
    			}else{
    				cout<<"tk_cadena"<<endl;
    				state=0;
    				s2="";
    			}
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
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     
     string line;
     while(getline(cin,line)){
     	int t=solve(line);
     	
     }
     
     
     return 0;
}
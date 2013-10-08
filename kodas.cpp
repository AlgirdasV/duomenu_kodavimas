#include "kodas.h"
#include "kunas.h"
#include "matrica.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#include <string>
using namespace std;

//vector<string> answer;
int min_svoris;
void tiesinis_kodavimas( Matrica& g ){//funkcija, atliekanti kodavima su generavimo matrica
	int n=g.sizeX();
	int k=g.sizeY();

	vector<string> answer;
	getStrings( answer, "", k ); //Paruosiam matricos eiluciu sumavimo produkcijas
	int last_el = pow(2, k)-1;
	int first_el = 0;
	string temp = answer[ first_el ];
	answer[ first_el ] = answer [last_el];
	answer [last_el] = temp;// sukeiciamia pirma ir paskutini sumavimo variantus,
							// kad jie prasidetu nuo 0.
	Matrica code(5,8); 
	vector <Elementas> sum;

	Kunas::reset_vector(sum, n);//pirmas codeword visada susideda is n nuliu.

	for (int i=0;i <answer.size();i++) {
		for (int j=0; j < answer[0].size(); j++) {
			if (answer[i][j]=='1'){//SUM IF answer[i][j] =1
				sum=Kunas::sudetis(g(j),sum);
			}
		}
		code(i)=sum;
		Kunas::reset_vector(sum, n);
	}
	code.Matrica::print();
	int qnk = pow(2, n-k);
	int qk = pow(2, k);
	kurti_standart_masyva(code, qk, qnk);
}


void getStrings(vector<string>& answer, string s, int digitsLeft ) {//grazina eilutes 
   	if( digitsLeft == 0 ) // the length of string is n
    	answer.push_back( s );
   	else
   	{
    	
    	getStrings(answer, s + "1", digitsLeft - 1 );
    	getStrings(answer, s + "0", digitsLeft - 1 );
   	}
}

void kurti_standart_masyva(Matrica code, int X, int Y) {//funkcija, kuri kuria standartini masyva is kodazodziu
	//vector<vector<Vektorius>>Vektorius stdArray [Y][X];
	vector< vector<Vektorius> > stdArray;
	Kunas::resize_2d_vector(stdArray,X,Y);//nustatome std. masyvo dydi
	for (int i = 0; i < X; i++) {//Inicializuojame pirma std. masyvo eilute
		stdArray[0][i] = code(i);
	} 
	int simbol_kiek = code.sizeX();
	min_svoris=1;
	coset_leaders(stdArray, simbol_kiek, 1);
	Kunas::print_vector(stdArray[1][0]);
	/*Vektorius eil1;
	eil1.push_back('1');
	for (int i =0; i< code.sizeX()-1; i++){
		eil1.push_back('0');
	}
	
	stdArray[1][0]=eil1;*/
	//Kunas::print_vector(stdArray[1][0]);
	/*Kunas::print_vector(stdArray[1][0]);
	cout << " + ";
	Kunas::print_vector(stdArray[0][1]);
	stdArray[1][1]=Kunas::sudetis( stdArray[1][0],stdArray[0][1] );
	Kunas::print_vector(stdArray[1][1]);
	stdArray[1][2]=Kunas::sudetis( stdArray[1][1],stdArray[0][2] );
	*/
	for (int eil = 0; eil < Y-1; eil++){//Inicializuojame likusias eilutes pagal tokia formule:
		for (int stulp = 0; stulp < X-1; stulp++){
			cout << "[" <<eil+1<<"]"<<"[" <<0<<"] (";
			Kunas::print_vector(stdArray[eil+1][0]);	
			cout << ") + ";
			cout << "[" <<0<<"]"<<"[" <<stulp+1<<"] (";
			Kunas::print_vector(stdArray[0][stulp+1]);
			cout <<") + "<<endl;
			stdArray[eil+1][stulp+1] = Kunas::sudetis( stdArray[eil+1][0],stdArray[0][stulp+1] );
			cout<<" = "; Kunas::print_vector(stdArray[eil+1][stulp+1]); cout <<endl;

		}
		coset_leaders(stdArray, simbol_kiek, eil+2);
	} 
	//Koordinatese [i+1][j+1] = [i+1][0]+[0][j+1]
	
	for (int eil = 0; eil < Y; eil++){
		for (int stulp = 0; stulp < X; stulp++){
			Kunas::print_vector(stdArray[eil][stulp]);
		}
	}
	
}

void coset_leaders(vector< vector<Vektorius> >& stdArray, int simboliu_kiekis,int eil){//sukuria coset lyderius std. masyve.
	int X = stdArray[0].size();//kiekis stulpeliu
	int Y = stdArray.size();//kiekis eiluciu
	cout << "iskviesta cl su eilutes nr" << eil<<endl; 
	Vektorius cos_lead;
	bool laisvas ;
	bool baigta = false;
	int position = eil-1;//pozicija, i kuria statyti vienetus
	//int riba = simboliu_kiekis-min_svoris+1;
	while (!baigta) {
		laisvas=true;//reset'iname laisvas flag'a
		for (int i = 0; i < simboliu_kiekis-min_svoris+1; i++){//sukuriame min. svorio vektoriu
			if (position == simboliu_kiekis-min_svoris+1){// jei pasibaige sio svorio imanomi variantai
				min_svoris++;
				position=0;
				cout<<"didinam svori\n";
			}

			if (i==position) {//reikia statyti vienetus nebutinai salia
				for (int j = 0; j < min_svoris; j++) {
					cos_lead.push_back('1');
				}
				for (int j = 0; j < min_svoris-1; j++) {
					//i++;
				}	
			}//jei i==simboliu_kiekis-1 tai isnaudojome si svori
			else cos_lead.push_back('0');			// reikia pradeti delioti svoris+1 vienetus
		}
		cout << "sugeneruota: ";Kunas::print_vector(cos_lead); cout <<endl;
		for (int i = 0; i<eil; i++){
			for (int j = 0; j< X; j++){
				if ( Kunas::lyginti(cos_lead, stdArray[i][j]) ) laisvas = false;//jei randame kad cos. leaderis 
			}																	//jau egzistuoja std. masyve
		}	
		if (laisvas) { 
			stdArray[eil][0] = cos_lead;
			baigta = true;
		}
		else {
			position++;
			cos_lead.clear();
		}//generuot nauja vektoriu bandant sekanti varianta, t.y. if i == eil
	}
}
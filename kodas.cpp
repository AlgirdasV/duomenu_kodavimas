#include "kodas.h"
#include "kunas.h"
#include "matrica.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#include <string>
using namespace std;
#include <cassert>

//vector<string> answer;
//int min_svoris;

void tiesinis_kodavimas( Matrica& g, vector< vector<Vektorius> >& stdArray ){//funkcija, atliekanti kodavima su generavimo matrica
	int n=g.sizeX();
	int k=g.sizeY();

	vector<string> answer;
	get_strings( answer, "", k ); //Paruosiam matricos eiluciu sumavimo produkcijas
	int last_el = pow(2, k)-1;
	int first_el = 0;
	string temp = answer[ first_el ];
	answer[ first_el ] = answer [last_el];
	answer [last_el] = temp;// sukeiciamia pirma ir paskutini sumavimo variantus,
							// kad jie prasidetu nuo 0.
	Matrica code(n, pow(2, k)); 
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
	//cout<<"Kodas: \n";
	//code.Matrica::print();
	int qnk = pow(2, n-k);
	int qk = pow(2, k);
	stdArray = kurti_standart_masyva(code, qk, qnk);
}


void get_strings(vector<string>& answer, string s, int digitsLeft ) {//grazina eilutes 
   	if( digitsLeft == 0 ) // the length of string is n
    	answer.push_back( s );
   	else
   	{
    	
    	get_strings(answer, s + "1", digitsLeft - 1 );
    	get_strings(answer, s + "0", digitsLeft - 1 );
   	}
}

void get_strings_with_weight(vector<string>& answer, string s, int digitsLeft, int weight, int digits) {//grazina eilutes 
	size_t vien_kiek = std::count(s.begin(), s.end(), '1');

   	if( digitsLeft == 0 ) {// the length of string is n
   		//cout <<"vien. kiekis : "<<vien_kiek<<endl;
   		if (vien_kiek == weight) {
    		answer.push_back( s );
    	}
	}
   	else
   	{	

   		size_t vien_kiekis = std::count(s.begin(), s.end(), '1');
   		if (vien_kiekis < weight) {
   			get_strings_with_weight(answer, s + "1", digitsLeft - 1, weight, digits);
   		}
    	//if string does not contain weight amount of '1's then
    	
    	size_t nul_kiekis = std::count(s.begin(), s.end(), '1');	
		if (nul_kiekis < digits-1) {
   			get_strings_with_weight(answer, s + "0", digitsLeft - 1, weight, digits);	
   		}
    	//end	
    	//if string does not contain (digits-1) amount of '0's then	
    		
    	//end
   	}
}

vector< vector<Vektorius> > kurti_standart_masyva(Matrica pirma_eil, int X, int Y) {//funkcija, kuri kuria standartini masyva is kodazodziu
	//vector<vector<Vektorius>>Vektorius stdArray [Y][X];
	vector< vector<Vektorius> > stdArray;
	Kunas::resize_2d_vector(stdArray,X,Y);//nustatome std. masyvo dydi
	for (int i = 0; i < X; i++) {//Inicializuojame pirma std. masyvo eilute
		stdArray[0][i] = pirma_eil(i);
	} 
	int simbol_kiek = pirma_eil.sizeX();
	vector<string> ans;
	int svoris = 1;
	
	for (int eil = 0; eil < Y-1; eil++){//Inicializuojame likusias eilutes pagal tokia formule:
										//Reiksme koordinatese [i+1][j+1] = [i+1][0]+[0][j+1]	
		coset_leaders(stdArray, simbol_kiek, eil+1, svoris);
		for (int stulp = 0; stulp < X-1; stulp++){
			stdArray[eil+1][stulp+1] = Kunas::sudetis( stdArray[eil+1][0],stdArray[0][stulp+1] );
		}	
	} 
	
	cout <<"standartinis masyvas:\n";
	for (int eil = 0; eil < Y; eil++){
		for (int stulp = 0; stulp < X; stulp++){
			Kunas::print_vector(stdArray[eil][stulp]);
			cout <<" ";
		}
		cout <<"\n";
	}
	return stdArray;
}

void coset_leaders(vector< vector<Vektorius> >& stdArray, int simboliu_kiekis,
						 int eil, int& svoris ){//sukuria coset lyderi std. masyvo nurodytoje eiluteje
	int X = stdArray[0].size();//kiekis stulpeliu
	int Y = stdArray.size();//kiekis eiluciu
	Vektorius cos_lead;
	bool laisvas = true;
	bool baigta = false;
	vector<string> potential_leaders;

	while( !baigta ){
		get_strings_with_weight(potential_leaders, "", simboliu_kiekis, svoris, simboliu_kiekis);
		int nr_of_potential = potential_leaders.size();
		for (int z = 0; (z < nr_of_potential)&&(!baigta); z++){
			Vektorius potential = Kunas::string_to_vector(potential_leaders[z]); //konvertuojame is string i vektoriu
			laisvas = true;

			for (int i = 0; i<eil; i++){
				for (int j = 0; j< X; j++){
					
					
					if ( Kunas::lyginti(potential, stdArray[i][j]) ) {laisvas = false; break;}//jei randame kad cos. leaderis 
																					//jau egzistuoja std. masyve
				}																	
			}
			//po palyginimo galime priskirti cos. leaderi, jei jis laisvas
			if (laisvas){
				stdArray[eil][0] = potential;
				baigta = true;

			}
			if (z==nr_of_potential-1){//jei patikrinome paskutini potencialu lyderi
				svoris++;
			}
			if (svoris > simboliu_kiekis){//jei per kazkokia klaida patikrinome visus imanomus simbolius
				baigta=true;
			}
		}
	}
}

Vektorius dauginti_matrica_su_vektoriumi(Matrica matrica, Vektorius vektorius) {
	
	assert(vektorius.size() == matrica.sizeY() );
	Vektorius galut_rezult;
	Vektorius daug_rezult;
	for (int i = 0; i < vektorius.size(); i++){
		if (vektorius[i]=='1')
			daug_rezult = matrica(i);
		galut_rezult = Kunas::sudetis(galut_rezult, daug_rezult);
		daug_rezult.clear();
	}
	
	return galut_rezult;
}


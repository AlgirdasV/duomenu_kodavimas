#include <stdio.h>
#include <iostream>
	using namespace std;
#include <string>         // std::string
	using namespace std;
#include <vector>         
	using namespace std;
#include "kunas.h"
#include "kodas.h"
#include "matrica.h"
#include "kanalas.h"
#include "dekodavimas.h"

int main( int argc, const char* argv[] )
{

	int n = 4;
	string input;
	bool incorrect=false;
/*
	cout << "Iveskite "<< n << " elementu ilgio vektoriu is kuno F2 elementu\n";
	cin >> input;
	for (int i=0; i<input.size(); i++){
			if (!isdigit(input[i])) incorrect=true;
	}
	while (input.size() !=n || incorrect) {
		cout << "Nekorektiskas vektorius. ";
		cout << "Iveskite "<< n << "elementu ilgio vektoriu is kuno F2 elementu\n";
		cin >> input;
		for (int i=0; i<input.size(); i++){
			if (!isdigit(input[i])) incorrect=true;
			else incorrect=false;
		}
	}*/
	
	Matrica m;
	m.from_file("matrica2.txt");
	m.print();
	vector< vector<Vektorius> > stdArray;
	tiesinis_kodavimas(m, stdArray);
	Matrica h = kontroline_matrica(m);
	skaiciuoti_sindromus(h, stdArray);
	//Vektorius pvz;
	//Kunas::string_to_vector("110",pvz);
	//Vektorius rezultatas = dauginti_matrica_su_vektoriumi(m2, pvz);
	//Kunas::print_vector(siuntimas_kanalu(rezultatas));
}
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
#include <math.h>

int main( int argc, const char* argv[] )
{

	
	string input;
	bool incorrect=false;

	
	
	Matrica m;
	m.from_file("matrica3.txt");
	int n = m.sizeY();
	cout << "Iveskite "<< n << " elementu ilgio vektoriu is kuno F2 elementu\n";
	cin >> input;
	for (int i=0; i<input.size(); i++){
			if (!isdigit(input[i])) incorrect=true;
	}
	while (input.size() !=n || incorrect) {
		cout << "Nekorektiskas vektorius. ";
		cout << "Iveskite "<< n << " elementu ilgio vektoriu is kuno F2 elementu\n";
		cin >> input;
		for (int i=0; i<input.size(); i++){
			if (!isdigit(input[i])) incorrect=true;
			else incorrect=false;
		}
	}
	cout << "\nGeneruojanti matrica:\n";
	m.print();
	Matrica h = kontroline_matrica(m);
	Standart_lentele s = skaiciuoti_sindromus(h, pow (2, m.sizeX()-m.sizeY() ) );

	Vektorius pradinis = Kunas::string_to_vector(input);
	Vektorius uzkoduotas = dauginti_matrica_su_vektoriumi(m,pradinis);
	cout << "uzkoduotas vektorius: ";
	Kunas::print_vector(uzkoduotas);
	cout << endl;
	Vektorius vekt_po_siuntimo = siuntimas_kanalu(uzkoduotas);
	cout << "vektorius po siuntimo: ";
	Kunas::print_vector(vekt_po_siuntimo);
	cout << endl;
	//PARASYTI KIEK KLAIDU IR KURIOSE POZICIJOSE
	//GALIMYBE REDAGUOTI VEKTORIU IS KANALO
	//T. Y. NURODYTI KLAIDAS KIEK IR KUR JAM REIKIA
	Vektorius rez = dekoduoti(vekt_po_siuntimo, h, s);
	cout << "dekoduotas vektorius: ";
	Kunas::print_vector(rez);
	cout << endl;
}
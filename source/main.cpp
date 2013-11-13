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
#include "pagalbines_funkcijos.h"
#include <stdlib.h>

Vektorius vektoriaus_ivedimas(int);

int main( int argc, const char* argv[] )
{
	Matrica m;
	//SUVESTI GENERUOJANCIA MATRICA PACIAM
	//ARBA SUGENERUOTI ATSITIKTINE PAGAL NURODYTA DYDI
	//m.from_file("../data/matrica3.txt");
	m.generuoti_matrica(5,6);
	cout << "\nGeneruojanti matrica:\n";
	m.print();
	Matrica h = kontroline_matrica(m);
	cout << "Kontroline matrica:\n";
	h.print();
	Standart_lentele s = skaiciuoti_sindromus(h, pow (2, m.sizeX()-m.sizeY() ) );
	int n = m.sizeY();
	
	Vektorius pradinis = vektoriaus_ivedimas(n);
	Vektorius uzkoduotas = dauginti_matrica_su_vektoriumi(m,pradinis);
	cout << "Uzkoduotas vektorius:  ";
	Kunas::print_vector(uzkoduotas);
	cout << endl;
	Vektorius vekt_po_siuntimo = siuntimas_kanalu(uzkoduotas);
	cout << "Vektorius po siuntimo: ";
	Kunas::print_vector(vekt_po_siuntimo);
	cout << endl;
	Kunas::spausdinti_klaidas(uzkoduotas, vekt_po_siuntimo);
	string input;
	do {
		cout << "ar norite pats redaguoti klaidas? (t/n)" << endl;
		cin >> input;
		remove_carriage_return(input);
	} while (input!="t" && input!="n");
	if (input == "t") {
		cout << "Iveskite vektoriu po siuntimo: ";
		vekt_po_siuntimo = vektoriaus_ivedimas(vekt_po_siuntimo.size());
	}
	Vektorius rez = dekoduoti(vekt_po_siuntimo, h, s);
	cout << "Dekoduotas vektorius: ";
	Kunas::print_vector(rez);
	cout << endl;
	cout << "\nNoredami baigti spauskite <enter>";
	cin.get();
	cin.get();
}

Vektorius vektoriaus_ivedimas(int n){//is konsoles ivedamas n simboliu vektorius is kuno F2 elementu
	string input;
	bool incorrect = false;
	do {
		if (input == "exit"){
			cout << "programa baigia darba.\n";
			exit (EXIT_FAILURE);
		}
		if (incorrect) 
			cout << "Nekorektiskas vektorius. ";
		cout << "Iveskite "<< n << " elementu ilgio vektoriu is kuno F2 elementu (arba \"exit\")\n";
		cin >> input;
		incorrect = false;
		for (int i=0; i<input.size(); i++){
			if (input[i]!='0' && input[i]!='1') incorrect = true;
		}
	} while (input.size() !=n || incorrect);
	return Kunas::string_to_vector(input);
}
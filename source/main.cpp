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
#include <sstream>
	using namespace std;

Vektorius vektoriaus_ivedimas(int);
bool isNum(string);
int StringToNumber(string&);

int main( int argc, const char* argv[] )//TODO generate matrix in standart form, add second user scenario
{
	Matrica m;
	string input1;
	do {
		cout << "Kodavimo programa pradeda darba\n";
		cout << "\nAr norite generuojancia matrica nuskaityti is failo? " ;
		cout <<	"Jei ne, matrica bus sugeneruota. (t/n)\n";
		cin >> input1;
		remove_carriage_return(input1);
	} while (input1!="t" && input1!="n");
	if (input1 == "t") {
		bool bad_file;
		do{
			bad_file=false;
			cout << "Iveskite failo, kuriame irasyti matricos duomenys, pavadinima:";
			string filename;
			cin >> filename;
			if (!m.from_file("../data/"+filename)){
				bad_file=true;
			}
		} while (bad_file);
	}
	else {
		string kodo_ilgis;
		string dimensija;
		bool incorrect = false;
		int k, n;
		do {
			if (incorrect) {
				cout << "\nKodo ilgis turi buti didesnis uz kodo dimensija.\n";
				cout << "Bandykite dar: ";
			}
			incorrect = false;
			do {
				cout << "Iveskite kodo ilgi n: ";
				cin >> kodo_ilgis;
				remove_carriage_return(kodo_ilgis);
			} while (!isNum(kodo_ilgis)); 
			do {
				cout << "Iveskite kodo dimensija k: ";
				cin >> dimensija;
				remove_carriage_return(dimensija);
			} while (!isNum(dimensija) ); 
			n = StringToNumber(kodo_ilgis);
			k = StringToNumber(dimensija);
			if (k > n)
				incorrect = true;
		} while (incorrect);
		
		m.generuoti_matrica(k, n);//dimensija atitinka eiluciu skaiciu, kodo_ilgis - stulpeliu sk
	}
	
	cout << "\nGeneruojanti matrica:\n";
	m.print();
	Matrica h = kontroline_matrica(m);
	cout << "Kontroline matrica:\n";
	h.print();
	int n = m.sizeY();
	int k = m.sizeX();
	Standart_lentele s = skaiciuoti_sindromus(h, pow (2, k-n ) );
	
	Vektorius pradinis = vektoriaus_ivedimas(n);
	Vektorius uzkoduotas = dauginti_matrica_su_vektoriumi(m,pradinis);
	cout << "Uzkoduotas vektorius:  ";
	Kunas::print_vector(uzkoduotas);
	cout << endl;
	string klaidos_tikimybe;
	bool tikimybe_klaidinga = false;
	double tikimybe;
	do{
		if (tikimybe_klaidinga){
			cout << "Tikimybe turi buti realus sk. intervale nuo 0.0 iki 1.0\n";
			cout << "Bandykite dar \n";
		}
		tikimybe_klaidinga = false;
		do {
					cout << "Iveskite klaidos tikimybe siunciant vektoriu kanalu: ";
					cin >> klaidos_tikimybe;
					remove_carriage_return(klaidos_tikimybe);
				} while (!isNum(klaidos_tikimybe) );
		tikimybe = ::atof(klaidos_tikimybe.c_str());
		if (tikimybe <= 0.0 || tikimybe > 1.0) 
			tikimybe_klaidinga = true;
	} while (tikimybe_klaidinga);
	Vektorius vekt_po_siuntimo = siuntimas_kanalu(uzkoduotas, tikimybe);
	cout << "Vektorius po siuntimo: ";
	Kunas::print_vector(vekt_po_siuntimo);
	cout << endl;
	Kunas::spausdinti_klaidas(uzkoduotas, vekt_po_siuntimo);
	string input2;
	do {
		cout << "Ar norite pats redaguoti klaidas? (t/n)" << endl;
		cin >> input2;
		remove_carriage_return(input2);
	} while (input2!="t" && input2!="n");
	if (input2 == "t") {
		cout << "Iveskite vektoriu po siuntimo: ";
		vekt_po_siuntimo = vektoriaus_ivedimas(vekt_po_siuntimo.size());
	}
	cout << "Vektorius po siuntimo: ";
	Kunas::print_vector(vekt_po_siuntimo);
	Vektorius rez = taisyti_klaidas(vekt_po_siuntimo, h, s);
	cout << "Vektorius su istaisytomis klaidomis: ";
	Kunas::print_vector(rez);
	cout << endl;
	dekoduoti(rez, m);
	cout << "\nNoredami baigti spauskite <enter>";
	cin.get();
	cin.get();
	cout << "\nKodavimo programa baiga darba";
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

bool isNum(string s) {
    int i = 0,  flag;

    while(s[i]){
            //if there is a letter in a string then string is not a number
        if(isalpha(s[i])){
            flag = 0;
            break;
        }
        else flag = 1;
        i++;
        }
    if (flag == 1) return true;
    else return false;
}

int StringToNumber( string &Text ){//Text not by const reference so that the function can be used with a                                //character array as argument
	stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}

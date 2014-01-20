#include "skaidymas.h"
#include "pagalbines_funkcijos.h"
#include "kunas.h"
#include "kanalas.h"
#include "kodas.h"
#include "matrica.h"
#include "dekodavimas.h"
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <exception>
#include <algorithm>
#include <iostream>
	using namespace std;
#include <fstream>
	using namespace std;
#include <string>
	using namespace std;
#include <vector>
	using namespace std;


	void skaidyti_faila(string txt_file_name, int dimensija, int ilgis){ // funkcija kuri realizuoja antra programos scenariju
																		 // Parametrais priima teksto failo pavadinima ir kodo parametrus.
//		Funkcija suskaido duotą tekstą į reikiamo ilgio vektorius iš kūno Fq elementų.
//		    Kiekvieną vektorių siunčia kanalu nenaudodama kodo, iš gautų vektorių atgamina tekstą ir jį parodo.
//		    Kiekvieną vektorių užkoduoja, siunčia kanalu, dekoduoja. Iš gautų vektorių atgamina tekstą ir jį parodo.

		ifstream txt_file(txt_file_name.c_str(), ios::binary);
		assert(txt_file.is_open());
		vector<unsigned char> file_contents((istreambuf_iterator<char>(txt_file)),
		                               istreambuf_iterator<char>()); // failo tekstas sukeliamas i vektoriu,
																	 //	   kad butu patogiau atlikti operacijas
		vector <char> file_contents_vector; // vektorius, kuriame saugomas failo tekstas bitais
		int simboliu_kiekis = 0;
		for (int byte = 0; byte < file_contents.size(); ++byte) { // ciklas, vercia failo simbolius i bitus
			Vektorius vector = char_to_binary(file_contents[byte]);
			for (int bit = 0; bit < 8; ++bit) {
				file_contents_vector.push_back(vector[bit]);
			}
			simboliu_kiekis++;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Duomenu srauto dalijimas i vektorius
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int viso_bitu = file_contents_vector.size();
		vector <Vektorius> vektoriai;

		int vektoriaus_indeksas = 0;
		int liekana = viso_bitu%dimensija;
		if (liekana != 0) // priklausomai nuo to kiek yra simboliu gali prireikti vienetu didesnes talpos vektoriams saugoti
			vektoriai.resize((viso_bitu/dimensija) +1);
		else
			vektoriai.resize(viso_bitu/dimensija);
		for (int i = 0; i < viso_bitu; i = i+dimensija) {
			for (int el = 0; el < dimensija && (el+i)<viso_bitu; ++el) { // po viena bita sukeliame visus bitus i atskirus vektorius
				assert( (file_contents_vector[i+el]=='0' || file_contents_vector[i+el]=='1')  );
				vektoriai[vektoriaus_indeksas].push_back(file_contents_vector[i+el]); // bitas '0' arba '1'
			}
			if (i == viso_bitu-liekana){ // pildomas paskutinis vektorius, kuri gali prireikti papildyti
				if (liekana != 0) { // jei yra liekana, vadinas reiks prie vektoriaus prideti nuliu
					for (int nuliai = 0; nuliai < dimensija-liekana; ++nuliai) {
						vektoriai[vektoriaus_indeksas].push_back('0');
					}

				}
			}
			vektoriaus_indeksas++;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Vektoriu siuntimas
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector <Vektorius> vektoriai_po_siuntimo;
		float klaidos_tikimybe = 0.02;
		for (int vekt = 0; vekt < vektoriai.size(); ++vekt) { // siunciame visus vektorius po viena
			assert(vektoriai[vekt].size()!=0);
			vektoriai_po_siuntimo.push_back(siuntimas_kanalu(vektoriai[vekt], klaidos_tikimybe));
		}

		vector <char> received_bits;
		for (int i = 0; i < vektoriai_po_siuntimo.size(); ++i) { // cikle sukeliam visus pavieniu vektoriu bitus i viena ilga vektoriu
			for (int bit = 0; bit < vektoriai_po_siuntimo[i].size(); ++bit) {
				received_bits.push_back(vektoriai_po_siuntimo[i][bit]);
			}

		}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Vektoriu kodavimas ir dekodavimas
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool neisprendziama;
		Matrica G;
		Matrica h;
		Standart_lentele s;
		vector <char> decoded_bits; // ilgas vektorius, kuriame saugomi dekoduoti bitai
		do {
			decoded_bits.clear();
			neisprendziama = false;
			G = generuoti_G_matrica(dimensija, ilgis);
			h = kontroline_matrica(G);
			int n = G.sizeY();
			int k = G.sizeX();
			s = skaiciuoti_sindromus(h, pow (2, k-n ) );
			for (int i = 0; i < vektoriai.size() && !neisprendziama; ++i) { //kiekvienam vektoriui
				assert(vektoriai[i].size()!=0);
				Vektorius uzkoduotas = dauginti_matrica_su_vektoriumi(G, vektoriai[i]); // ji uzkoduojame
				assert(uzkoduotas.size()!=0);
				Vektorius po_siuntimo = siuntimas_kanalu(uzkoduotas, klaidos_tikimybe); // siunciame kanalu
				assert (po_siuntimo.size() != 0);
				Vektorius rez = taisyti_klaidas(po_siuntimo, h, s); // istaisome klaidas
				assert (rez.size()!=0);
				Vektorius galutinis;
				try{
					galutinis = dekoduoti(rez, G); // dekoduojame
				}
				catch (...){ // gaudome klaidam, kuri rodo jog lygciu sistema neisprendziama
					neisprendziama = true; // kartoti visa cikla;
				}
				if (!neisprendziama){
					for (int i = 0; i < galutinis.size(); ++i) {
						decoded_bits.push_back(galutinis[i]);
					}
				}
			}
		} while (neisprendziama);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Vektoriu be kodavimo surinkimas atgal
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector <unsigned char> new_file_contents; // naujas vektorius su po siuntimo sujungtais bitais, paverstais i simbolius
		for (int byte = 0; byte < simboliu_kiekis; ++byte) { // ciklas, vercia atgal is bitu i simbolius
			vector<char> sub(&received_bits[byte*8],&received_bits[(byte*8)+8]);
			new_file_contents.push_back(binary_to_char(sub));
		}
		cout << "\n\nFailo turinys po siuntimo (be kodavimo):\n";
		cout << "_______________________________________________________________________\n\n";
		print_vector(new_file_contents);
		cout << "\n_______________________________________________________________________\n";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Vektoriu su kodavimu surinkimas atgal
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector <unsigned char> new_file_contents_decoded; // naujas vektorius su po siuntimo sujungtais bitais, paverstais i simbolius
		for (int byte = 0; byte < simboliu_kiekis; ++byte) { // ciklas, vercia atgal is bitu i simbolius
			vector<char> sub(&decoded_bits[byte*8],&decoded_bits[(byte*8)+8]);
			new_file_contents_decoded.push_back(binary_to_char(sub));
		}
		cout << "\n\nFailo turinys po siuntimo (naudojant koda C["<<ilgis  << ","<<dimensija<< "]):\n";
		cout << "_______________________________________________________________________\n\n";
		print_vector(new_file_contents_decoded);
		cout << "\n_______________________________________________________________________\n";
	}

Vektorius char_to_binary(char simbolis){ // Funkcija vercia teksto simboli i dvejetaini vektoriu
	vector <char> vektorius;
	int bitai[8];
	for (int bit = 0; bit < 8; ++bit) {
		bitai[bit] = ((simbolis >> bit) & 1);
	}
	for (int bit = 7; bit >= 0; --bit) {
		vektorius.push_back(bitai[bit] + '0'); // int to char
	}
	return vektorius;
}
unsigned char binary_to_char(Vektorius vektorius){ // Funkcija vercia dvejetaini vektoriu i simboli
	unsigned char simbolis;
	int decimal = 0;
	for (int bit = 0; bit < vektorius.size(); ++bit) {
		int bitas = vektorius[bit] - '0'; // char to int
		decimal = decimal << 1 | bitas; //
	}
	simbolis = (char)decimal; // int to char
	return simbolis;
}

#include "skaidymas.h"
#include "pagalbines_funkcijos.h"
#include "kunas.h"
#include <iostream>
	using namespace std;
#include <fstream>
	using namespace std;
#include <string>
	using namespace std;
#include <vector>
	using namespace std;


	void skaidyti_faila(string txt_file_name, int ilgis){
//		Vartotojas užrašo tekstą (tekstas gali būti sudarytas iš kelių eilučių). Programa suskaido duotą tekstą į reikiamo ilgio vektorius iš kūno Fq elementų.
//		    Kiekvieną vektorių siunčia kanalu nenaudodama kodo, iš gautų vektorių atgamina tekstą ir jį parodo.
//		    Kiekvieną vektorių užkoduoja, siunčia kanalu, dekoduoja. Iš gautų vektorių atgamina tekstą ir jį parodo.

		cout << "test 0 \n";
		ifstream txt_file(txt_file_name.c_str(), ios::binary);
		vector<unsigned char> file_contents((istreambuf_iterator<char>(txt_file)),
		                               istreambuf_iterator<char>());
		cout << "failo turinys bitais \n";
		vector <char> file_contents_vector; // vektorius, kuriame saugomas failo tekstas bitais '0' ir '1'
		int simboliu_kiekis = 0;
		for (int byte = 0; byte < file_contents.size(); ++byte) { // ciklas, vercia failo simbolius i bitus
			Vektorius vector = char_to_binary(file_contents[byte]);
			for (int bit = 0; bit < 8; ++bit) {
				file_contents_vector.push_back(vector[bit]);
			}
			simboliu_kiekis++;
		}
		cout << "vektoriai: \n";
		print_vector(file_contents_vector);
		//TODO dalijimas i tam tikro dydzio vektorius
		cout << "po print\n";
		int viso_bitu = file_contents_vector.size();
		vector <Vektorius> vektoriai;
		vektoriai.resize((viso_bitu/ilgis) +1);
		int vektoriaus_indeksas = 0;
		for (int i = 0; i < viso_bitu; i = i+ilgis) {

			for (int el = 0; el < ilgis && (el+i)<viso_bitu; ++el) {
				vektoriai[vektoriaus_indeksas].push_back(file_contents_vector[i+el]);
				//bitas '0' arba '1'
			}
			vektoriaus_indeksas++;
		}
		cout << "test: tekstas vektoriais, kuriu ilgis yra " << ilgis << " : \n";
		print_2d_vector(vektoriai);
		//TODO tu vektoriu kodavimas ir siuntimas bei dekodavimas
		vector <unsigned char> new_file_contents; // naujas vektorius su po siuntimo sujungtais bitais, paverstais i simbolius
		for (int byte = 0; byte < simboliu_kiekis; ++byte) { // ciklas, vercia atgal is bitu i simbolius
			vector<char> sub(&file_contents_vector[byte*8],&file_contents_vector[(byte*8)+8]);
			new_file_contents.push_back(binary_to_char(sub));
		}
		cout << "failo turinys po siuntimo: \n";
		print_vector(new_file_contents);
	}

Vektorius char_to_binary(char simbolis){
	vector <char> vektorius;
	int bitai[8];
	for (int bit = 0; bit < 8; ++bit) {
		bitai[bit] = ((simbolis >> bit) & 1);
	}
	for (int bit = 7; bit >= 0; --bit) {
		vektorius.push_back(bitai[bit] + '0');
	}
	return vektorius;
}
unsigned char binary_to_char(Vektorius vektorius){
	unsigned char simbolis;
	int decimal = 0;
	for (int bit = 0; bit < vektorius.size(); ++bit) {
		int bitas = vektorius[bit] - '0'; // char to int
		decimal = decimal << 1 | bitas; //
	}
	simbolis = (char)decimal; // int to char
	return simbolis;
}

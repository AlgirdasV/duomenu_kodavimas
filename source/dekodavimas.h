#ifndef DEKODAVIMAS_H
#define DEKODAVIMAS_H

#include "matrica.h"
#include <vector>

class Standart_lentele{ // klase realizuoja sumazinta standartine lentele ir veiksmus su ja
	std::vector < std::vector <Elementas> > sindromai;	// lenteles sindromai, gauti padauginus sugeneruotus vektorius is kontrolines matricos
	std::vector <int> vektoriu_svoriai;	// sugeneruotu vektoriu, atitinkanciu lenteles sindromus, svoriai
	int klasiu_kiekis;	// kiek viso lenteleje yra sindromu ir su jais susietu svoriu

	public:
		Standart_lentele(int );
		void isvalyti_sindroma(int );
		void prijungti_prie_sindromo(int, Elementas);
		void priskirti_svori(int, int);
		void spausdinti();
		bool lyginti_sindromus_iki_indekso(int);
		int rasti_svori_pagal_sindroma(Vektorius);
		void print();
};

class LygciuSistema { // Klase, realizuojanti lygciu sistema, sudaryta is matricos ir vektoriaus

	public:
	Matrica matrica;
	Vektorius vektorius;
	std::vector<int> isprestos_eilutes;
	std::vector<Elementas> kintamuju_reiksmes;
	std::vector<int> surasti_kintamieji;
	LygciuSistema(Matrica, Vektorius);
	void lygtis_eiluteje(int);
	void spresti();
};

Matrica kontroline_matrica(Matrica);
std::vector <std::vector<Elementas> > generuoti_vienetinius_vektorius(int );
Standart_lentele skaiciuoti_sindromus(Matrica, int);
Elementas skaliarine_sandauga(Vektorius, Vektorius);
Vektorius taisyti_klaidas(Vektorius , Matrica , Standart_lentele);
void dekoduoti(Vektorius, Matrica);


#endif

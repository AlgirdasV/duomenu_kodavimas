#ifndef DEKODAVIMAS_H
#define DEKODAVIMAS_H

#include "matrica.h"
#include <vector>

class Standart_lentele{
	std::vector < std::vector <Elementas> > sindromai;
	std::vector <int> vektoriu_svoriai;
	int klasiu_kiekis;

	public:
		Standart_lentele(int );
		void isvalyti_sindroma(int );
		void prijungti_prie_sindromo(int, Elementas);
		void priskirti_svori(int, int);
		void spausdinti();
		bool lyginti_sindromus_iki_indekso(int);
		int rasti_svori_pagal_sindroma(Vektorius);
};

Matrica kontroline_matrica(Matrica);
std::vector <std::vector<Elementas> > generuoti_vienetinius_vektorius(int );
Standart_lentele skaiciuoti_sindromus(Matrica, int);
Elementas skaliarine_sandauga(Vektorius, Vektorius);
Vektorius dekoduoti(Vektorius , Matrica , Standart_lentele );
#endif
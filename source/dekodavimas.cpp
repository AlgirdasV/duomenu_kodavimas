#include "dekodavimas.h"
#include "pagalbines_funkcijos.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;
#include "kodas.h"	
#include <cassert>


Standart_lentele::Standart_lentele(int klasiu_kiekis): klasiu_kiekis(klasiu_kiekis){
	sindromai.resize(klasiu_kiekis);
	vektoriu_svoriai.resize(klasiu_kiekis);
}

void  Standart_lentele::isvalyti_sindroma(int indeksas){
	assert( indeksas < klasiu_kiekis );
	sindromai[indeksas].clear();
}

void Standart_lentele::prijungti_prie_sindromo(int indeksas, Elementas elementas){
	assert( indeksas < klasiu_kiekis );
	sindromai[indeksas].push_back(elementas);
}

void Standart_lentele::priskirti_svori(int indeksas, int svoris){
	assert( indeksas < klasiu_kiekis );
	vektoriu_svoriai[indeksas] = svoris;
}

void Standart_lentele::spausdinti(){
	cout << "sumazinta standartine lentele:\n";
	for (int j = 0; j < klasiu_kiekis; j++){
		Kunas::print_vector(sindromai[j]);
		cout << " "<<vektoriu_svoriai[j];
		cout << endl;
	}
}

bool Standart_lentele::lyginti_sindromus_iki_indekso(int indeksas){
	assert( indeksas < klasiu_kiekis );
	bool yra_lygiu = false;
	for (int x = 0; x < indeksas; x++){
		if ( Kunas::lyginti(sindromai[x], sindromai[indeksas]) )
			yra_lygiu = true;
	}
	return yra_lygiu;
}

int Standart_lentele::rasti_svori_pagal_sindroma(Vektorius sindromas){
	int svoris;
	for (int i = 0; i < klasiu_kiekis; i++){
		if ( Kunas::lyginti(sindromai[i], sindromas ) )
			svoris = vektoriu_svoriai[i];
	}
	return svoris;
}


Matrica kontroline_matrica(Matrica G){
	G.i_rref();
	//cout << "rref forma\n";
	//G.print();
	vector<vector<int> > perstatymas = G.i_vienetine();
	cout << "G. matricos standartine forma: \n";
	G.print();
	int k = G.sizeY();
	int n = G.sizeX();
	Matrica H(n, n-k);
	for (int eil = 0; eil < k; eil++) {
		for (int stulp = k; stulp < n; stulp++){
			int i = stulp-k;
			H(i, eil) = G(eil, stulp);
			
		}
	}
	//cout << "H is G:\n";
	//H.print ();
	for (int eil = 0; eil < H.sizeY(); eil++) {
		for (int stulp = k; stulp < H.sizeX(); stulp++){
			if (eil+k==stulp)
				H(eil, stulp) = '1';
			else
				H(eil, stulp) = '0';
		}
	}
	for (int stulp = 0; stulp < n; stulp++){
		if (perstatymas[0][stulp] < perstatymas[1][stulp]){
			H.sukeisti_stulpelius(perstatymas[0][stulp], perstatymas[1][stulp]);
		}
	}
	//cout << "\nkontroline matrica\n";
	//H.print();
	return H;
}
Standart_lentele skaiciuoti_sindromus(Matrica H, int klasiu_sk){
	Standart_lentele standart_lentele(klasiu_sk);
	bool jau_uzimtas = false;	
	int skait_kiek = H.sizeX();
	int svoris = 0;
	int i = 0;

	while( i < klasiu_sk ){
	
		vector<string> galimi_vektoriai;	
		get_strings_with_weight(galimi_vektoriai, "", skait_kiek, svoris, skait_kiek);
		int kiekis_galimu = galimi_vektoriai.size();
		
		for (int z = 0; (z < kiekis_galimu) && (i < klasiu_sk); z++){
			jau_uzimtas = false;//tariame, kad is nauju galimu vektoriu visi yra laisvi
			Vektorius galimas_v = Kunas::string_to_vector(galimi_vektoriai[z]); //konvertuojame is string i vektoriu 
			standart_lentele.isvalyti_sindroma(i);
			for (int y = 0; y < H.sizeY(); y++){
					standart_lentele.prijungti_prie_sindromo(i, skaliarine_sandauga(galimas_v, H(y) ) );
			}
			jau_uzimtas = standart_lentele.lyginti_sindromus_iki_indekso(i);

			if (!jau_uzimtas) {
				standart_lentele.priskirti_svori(i, Kunas::rasti_svori(galimas_v) );
				i++;
			}
			if (z == kiekis_galimu-1){//jei patikrinome paskutini potencialu lyderi
				svoris++;
			}	
		}
	}
	standart_lentele.spausdinti();
	return standart_lentele;
} 

Elementas skaliarine_sandauga(Vektorius v1, Vektorius v2){
	Elementas sum = '0';
	for (int i = 0; i < v1.size(); i++){
		sum = Kunas::el_sudetis( sum, Kunas::el_daugyba(v1[i], v2[i]) );
	} 
	return sum;
}

Vektorius dekoduoti(Vektorius r, Matrica H, Standart_lentele standart_lentele){
	int i = 0;
	int svoris;
	bool baigta = false;
	vector <vector<Elementas> > e = generuoti_vienetinius_vektorius(H.sizeX());
	while (!baigta){
		vector <Elementas> sandaugos_rez;
		for (int y = 0; y < H.sizeY(); y++){
			sandaugos_rez.push_back( skaliarine_sandauga(r, H(y) ) );
		}
		svoris = standart_lentele.rasti_svori_pagal_sindroma(sandaugos_rez);
		if (svoris == 0)
			baigta = true;
		else {
			vector <Elementas> H_kart_r_plus_e;
			Vektorius r_plus_e = Kunas::sudetis(r, e[i]);
			for (int y = 0; y < H.sizeY(); y++){
				H_kart_r_plus_e.push_back( skaliarine_sandauga(r_plus_e, H(y) ) );
			}
			int svoris_r_plus_e = standart_lentele.rasti_svori_pagal_sindroma(H_kart_r_plus_e);
			if (svoris_r_plus_e < svoris)
				r =  r_plus_e;
			i++;
		}
	}
	//cout << "r: ";
	//Kunas::print_vector(r);
	cout << endl;
	return r;
}

vector <vector<Elementas> > generuoti_vienetinius_vektorius(int ilgis){
	vector <vector<Elementas> > vienetiniai_vektoriai; 
	vienetiniai_vektoriai.resize(ilgis);
	for (int i = 0; i < ilgis; i++){
		vienetiniai_vektoriai[i].resize(ilgis);
	}
	for (int i = 0; i < ilgis; i++){
		for (int j = 0; j < ilgis; j++){
			if (j == i)
				vienetiniai_vektoriai[i][j] = '1';
			else
				vienetiniai_vektoriai[i][j] = '0';
		}
	}

	return vienetiniai_vektoriai;
}


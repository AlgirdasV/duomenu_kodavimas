#include "dekodavimas.h"
#include "pagalbines_funkcijos.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;
#include "kodas.h"	
#include <cassert>
#include <math.h>
#include <exception>


Standart_lentele::Standart_lentele(): klasiu_kiekis(0){ // Standartines lenteles objekto konstruktorius
	sindromai.resize(klasiu_kiekis);
	vektoriu_svoriai.resize(klasiu_kiekis);
}
Standart_lentele::Standart_lentele(int klasiu_kiekis): klasiu_kiekis(klasiu_kiekis){ // Standartines lenteles objekto konstruktorius
	sindromai.resize(klasiu_kiekis);
	vektoriu_svoriai.resize(klasiu_kiekis);
}

void  Standart_lentele::isvalyti_sindroma(int indeksas){ // Funkcija isvalo nurodyta lenteles sindroma
	assert( indeksas < klasiu_kiekis );
	sindromai[indeksas].clear();
}

void Standart_lentele::prijungti_prie_sindromo(int indeksas, Elementas elementas){ // Funkcija prijungia viena elementa prie nurodyto lenteles sindromo
	assert( indeksas < klasiu_kiekis );
	sindromai[indeksas].push_back(elementas);
}

void Standart_lentele::priskirti_svori(int indeksas, int svoris){ // Funckija priskira nurodyto indekso sindromui ji atitinkancio vektoriaus svori
	assert( indeksas < klasiu_kiekis );
	vektoriu_svoriai[indeksas] = svoris;
}

void Standart_lentele::spausdinti(){ // Funkcija isspausdina i konsole standartine lentele
	cout << "sumazinta standartine lentele:\n";
	cout << "sindromai:   svoriai:\n";
	for (int j = 0; j < klasiu_kiekis; j++){
		Kunas::print_vector(sindromai[j]);
		cout << "       "<<vektoriu_svoriai[j];
		cout << endl;
	}
}

bool Standart_lentele::lyginti_sindromus_iki_indekso(int indeksas){ // Funkcija palygina visus sindromus iki nurodyto indekso, grazina true jei yra lygiu sindromu
	assert( indeksas < klasiu_kiekis );
	bool yra_lygiu = false;
	for (int x = 0; x < indeksas; x++){
		if ( Kunas::lyginti(sindromai[x], sindromai[indeksas]) )
			yra_lygiu = true;
	}
	return yra_lygiu;
}

int Standart_lentele::rasti_svori_pagal_sindroma(Vektorius sindromas){ // Funkcija grazina nurodyto sindromo atitinkama svori lenteleje
	int svoris;
	for (int i = 0; i < klasiu_kiekis; i++){
		if ( Kunas::lyginti(sindromai[i], sindromas ) )
			svoris = vektoriu_svoriai[i];
	}
	return svoris;
}


Matrica kontroline_matrica(Matrica G){ // Funkcija suranda kontroline matrica pagal duota generuojancia matrica
									   // Parametrai: generuojanti matrica G
									   // Rezultatas: kontroline matrica
	G.i_rref();
	vector<vector<int> > perstatymas = G.i_vienetine();
//	cout << "G. matricos standartine forma: \n";
//	G.print();
	int k = G.sizeY();
	int n = G.sizeX();
	Matrica H(n, n-k);
	for (int eil = 0; eil < k; eil++) { // transponuojame G matricos eilutes ir irasome i H matrica
		for (int stulp = k; stulp < n; stulp++){
			int i = stulp-k;
			H(i, eil) = G(eil, stulp);
			
		}
	}

	for (int eil = 0; eil < H.sizeY(); eil++) { // ciklas uzpildo matrica H vienetine matrica
		for (int stulp = k; stulp < H.sizeX(); stulp++){
			if (eil+k==stulp)
				H(eil, stulp) = '1';
			else
				H(eil, stulp) = '0';
		}
	}
	for (int stulp = 0; stulp < n; stulp++){ // pagal gauta perstatyma perstatome matricos H stulpelius
		if (perstatymas[0][stulp] < perstatymas[1][stulp]){
			H.sukeisti_stulpelius(perstatymas[0][stulp], perstatymas[1][stulp]);
		}
	}
	return H;
}
Standart_lentele skaiciuoti_sindromus(Matrica H, int klasiu_sk){ // Funkcija pagal perduotus duomenis sukuria sumazinta standartine lentele
	Standart_lentele standart_lentele(klasiu_sk);				 // Parametrai: kontroline matrica H ir busimos lenteles klasiu skaicius.
	bool jau_uzimtas = false;									 // Rezultatas: grazinama pilnai uzpildyta standartine lentele
	int skait_kiek = H.sizeX();
	int svoris = 0;
	int i = 0;

	while( i < klasiu_sk ){
		vector<string> galimi_vektoriai;	
		get_strings_with_weight(galimi_vektoriai, "", skait_kiek, svoris, skait_kiek); // I vektoriu "galimi_vektoriai" sugeneruojame
		int kiekis_galimu = galimi_vektoriai.size();								   // visus galimus variantus reikiamo ilgio ir svorio vektoriu.
		
		for (int z = 0; (z < kiekis_galimu) && (i < klasiu_sk); z++){
			jau_uzimtas = false;//tariame, kad is nauju galimu vektoriu visi yra laisvi
			Vektorius galimas_v = Kunas::string_to_vector(galimi_vektoriai[z]); //vienas is galimu vektoriu konvertuojamas is string i vektoriaus tipa

			standart_lentele.isvalyti_sindroma(i);
			for (int y = 0; y < H.sizeY(); y++){
					standart_lentele.prijungti_prie_sindromo(i, skaliarine_sandauga(galimas_v, H(y) ) );// vienas is galimu vektoriu  dauginamas is kontrolines matricos
			}																							// ir irasomas i sindroma [i]
			jau_uzimtas = standart_lentele.lyginti_sindromus_iki_indekso(i); // suzinome, ar paskutinis irasytas vektorius neduoda jau uzimto sindromo

			if (!jau_uzimtas) { // jei galimo vektoriaus gaminamas sindromas dar neuzimtas, pazymime vektoriaus svori
				standart_lentele.priskirti_svori(i, Kunas::rasti_svori(galimas_v) );
				i++;
			}
			if (z == kiekis_galimu-1){//jei patikrinome paskutini galima vektoriu su dabartiniu svoriu, tai didiname svori
				svoris++;
			}	
		}
	}

	return standart_lentele;
} 

Elementas skaliarine_sandauga(Vektorius v1, Vektorius v2){ // Funkcija realizuoja dvieju vektoriu skaliarine sandauga
	assert(v1.size() == v2.size());
	Elementas sum = '0';
	for (int i = 0; i < v1.size(); i++){
		sum = Kunas::el_sudetis( sum, Kunas::el_daugyba(v1[i], v2[i]) );
	} 
	return sum;
}

Vektorius taisyti_klaidas(Vektorius r, Matrica H, Standart_lentele standart_lentele){ // Funkcija duotam vektoriui istaiso klaidas.
	int i = 0;																		  // Parametrai: vektorius r, kuriam taisomos klaidos, kontroline matrica H
	int svoris;																		  // , standartine lentele.
	bool baigta = false;															  // Rezultatas: vektorius, su istaisytomis klaidomis.
	vector <vector<Elementas> > e = generuoti_vienetinius_vektorius(H.sizeX());

	while (!baigta){

		vector <Elementas> sandaugos_rez;
		for (int y = 0; y < H.sizeY(); y++){ // dauginame vektoriu is visu kontrolines matricos eiluciu
			sandaugos_rez.push_back( skaliarine_sandauga(r, H(y) ) );
		}
		svoris = standart_lentele.rasti_svori_pagal_sindroma(sandaugos_rez); // randame svori pagal gauta sandaugos rezultata

		if (svoris == 0) // jei priejome 0-lini svori, dekodavimo algoritmas baigtas
			baigta = true;
		else {
			vector <Elementas> H_kart_r_plus_e;
			Vektorius r_plus_e = Kunas::sudetis(r, e[i]); // pridedame prie vektoriaus r vienetini vektoriu e
			for (int y = 0; y < H.sizeY(); y++){
				H_kart_r_plus_e.push_back( skaliarine_sandauga(r_plus_e, H(y) ) ); // sudauginame sudeties rezultata su kiekviena h eilute
			}
			int svoris_r_plus_e = standart_lentele.rasti_svori_pagal_sindroma(H_kart_r_plus_e); // randame sios sandaugos svori
			if (svoris_r_plus_e < svoris){ // jei jis yra mazesnis
				r =  r_plus_e;	// priskiriame vektoriui r ta mazesnio svorio vektoriu
			}
			i++;
		}
	}

	return r;
}

vector <vector<Elementas> > generuoti_vienetinius_vektorius(int ilgis){ // Funkcija sugeneruoja visus reikiamo ilgio vienetinius vektorius
	vector <vector<Elementas> > vienetiniai_vektoriai; 					// Parametrai: ilgis
	vienetiniai_vektoriai.resize(ilgis);								// Rezultatas: dvimatis vektorius uzpildytas vienetiniais vektoriais
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

Vektorius dekoduoti(Vektorius vektorius, Matrica G){	// Funkcija paima vektoriu su istaisytomis klaidomis ir ji dekoduoja.
														// Parametrai: vektorius su istaisytomis klaidomis, generuojanti matrica G.
														// Rezultatas: grazinamas dekoduotas vektorius.
	G.transponuoti();
	int stulp_sk = G.sizeX();
	int eil_sk = G.sizeY();
	int nenuline_eil;
	gauso_eliminacija(vektorius, G);

	bool eil_nuline;
	bool neisprendziama;
	for (int eil = 0; eil < G.sizeY(); ++eil) { //perziurime, ar matricoje liko nuliniu eil.
		eil_nuline = true;
		for (int stulp = 0; stulp < G.sizeX(); ++stulp) {
			if ( G(eil, stulp) == '1')
				eil_nuline = false;
		}
		if (eil_nuline){
			if (vektorius[eil] == '1')
				throw("neisprendziama");
			G.pasalinti_eilute(eil);
			pasalinti_simboli(vektorius,eil);
			eil--;
		}
	}

	LygciuSistema lygciu_sist(G, vektorius);
	Vektorius galutinis = lygciu_sist.spresti();
	return galutinis;
}

void gauso_eliminacija(Vektorius& vektorius, Matrica& G){ // funkcija suveda parametrais perduotus matrica
														  //     ir vektoriu i virsutine trikampine forma.

	int stulp_sk = G.sizeX();
	int eil_sk = G.sizeY();
	int nenuline_eil;
	for (int stulp = 0; stulp < stulp_sk; ++stulp) {
			// randame nenulines eilutes stulpelyje stulp, pradedant nuo eilutes stulp
			nenuline_eil = stulp;
			bool rasta = false;
			for (int eil = stulp; eil < eil_sk && !rasta; ++eil) {
				if ( G(eil, stulp) == '1' ){
					nenuline_eil = eil;
					rasta = true;
				}
			}

			if ( rasta){
				G.sukeisti_eilutes(stulp, nenuline_eil);
				Kunas::sukeisti_simbolius(vektorius, stulp, nenuline_eil);
				for (int stulp_next = stulp+1; stulp_next < eil_sk; ++stulp_next) {
					Elementas daugiklis = G(stulp_next, stulp);
					G.dauginti_eilute_ir_prideti(stulp, daugiklis,stulp_next);
					Kunas::dauginti_simboli_ir_prideti(vektorius, stulp, daugiklis, stulp_next);
				}
			}
			else {
				cout << "klaida - egzistuoja daugiau nei 1 sprendinys\n";
			}
		}
}



Vektorius LygciuSistema::spresti(){		// Funkcija, kuri sprendzia tiesiniu lygciu sistema.
										// Parametrai: matrica ir vektorius,
										//     kurie sudaro lygciu sistema.
										// Rezultatas: lygciu sistemos sprendinys kaip sveiku sk. vektorius
	lygtis_eiluteje(0);
	bool yra_neispresta;
	int neispresta;
	bool baigta = false;
	int iteracija = 0;
	while (!baigta && iteracija<10){
		iteracija++;
		yra_neispresta = false;
		for (int eil = 0; eil < this->isprestos_eilutes.size() && !yra_neispresta; ++eil) {
			if (this->isprestos_eilutes[eil] == 0){ //	yra neispresta eilute
				yra_neispresta = true;
				neispresta = eil;
			}
		}
		if (yra_neispresta)
			lygtis_eiluteje(neispresta);
		else
			baigta = true;
	}
	assert(this->kintamuju_reiksmes.size()!=0);
	return this->kintamuju_reiksmes;
}
void LygciuSistema::lygtis_eiluteje(int eil){ 	// Funkcija kuri rekursyviai sprendzia tam tikra eilute lygciu sistemoje.
												// Parametrai: eilute, kuri bus sprendziama.
												// Rezultatas: pildomas LygciuSistema objektas, jame suzymimos isprestos eilutes
												// ir rasti kintamieji bei ju reiksmes.
	vector<int> eilutes_kintamieji;
	for (int stulp = 0; stulp < this->matrica.sizeX(); ++stulp) { // suzymime eilutes kintamuosius i vektoriu
		if (this->matrica(eil, stulp) == '1') {
			eilutes_kintamieji.push_back(stulp);
		}
	}

	if (eilutes_kintamieji.size() == 1) { // jei eiluteje yra tik 1 kintamasis
		int kintamasis = eilutes_kintamieji.back();
		this->surasti_kintamieji[kintamasis] = 1; // pasizymime, jog suradome kintamojo reiksme
		this->isprestos_eilutes[eil] = 1;		// pasizymime, kad isprendeme sia eilute
		this->kintamuju_reiksmes[kintamasis] = this->vektorius[eil];
	}
	else {
		for (int kint = eilutes_kintamieji.size()-1; kint >=0; --kint) { // kiekvienam eilutes kintamajam (pradedame nuo desines)
			bool rastas_vienetas = false;
			for (int eilute = eil+1; eilute < this->matrica.sizeY(); ++eilute) { //leistis zemyn matrica ir ieskoti reiksmiu '1'
				if (this->matrica(eilute, eilutes_kintamieji[kint]) == '1') {
					if (this->isprestos_eilutes[eilute] == 0)// jei eilutes lygtis dar neisspresta
						lygtis_eiluteje(eilute);
					rastas_vienetas = true;
				}
			}
			if (!rastas_vienetas) { // reiskia kintamasis yra eilutes pirmasis, vadinasi reikia skaiciuoti jo reiksme
				Vektorius eilutes_kintamuju_reiksmes;
				for (int kintam = 0; kintam < eilutes_kintamieji.size(); ++kintam) {
					int kint_index = eilutes_kintamieji[kintam]; // pasizymime eilutes kintamojo indeksa
					if (kintamuju_reiksmes[kint_index] == '1') { // jei reiksme butu 2, tai dar neapibrezta reiksme; jei 0 - sumai itakos netures
						eilutes_kintamuju_reiksmes.push_back(kintamuju_reiksmes[kint_index]);
					}
				}

				this->kintamuju_reiksmes[eilutes_kintamieji[kint]] = Kunas::el_atimtis(vektorius[eil],
																	sum_vector_elements(eilutes_kintamuju_reiksmes));
				this->surasti_kintamieji[eilutes_kintamieji[kint]] = 1; // pasizymime, jog suradome kintamojo reiksme
				this->isprestos_eilutes[eil] = 1; // pasizymime, kad isprendeme sia eilute
			}
		}
	}
}

LygciuSistema::LygciuSistema(Matrica matrica, Vektorius vektorius){ // LygciuSistema objekto konstruktorius
	assert(matrica.sizeY() == vektorius.size());
	this->matrica = matrica;
	this->vektorius = vektorius;
	reset_vector(this->isprestos_eilutes, matrica.sizeY());
	reset_vector(this->kintamuju_reiksmes, matrica.sizeX());
	reset_vector(this->surasti_kintamieji, matrica.sizeX());
}

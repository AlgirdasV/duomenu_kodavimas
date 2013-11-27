#include "dekodavimas.h"
#include "pagalbines_funkcijos.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;
#include "kodas.h"	
#include <cassert>
#include <math.h>


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
		cout << "    "<<vektoriu_svoriai[j];
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
		cout << "galimi vektoriai\n";
		print_vector(galimi_vektoriai);
		
		for (int z = 0; (z < kiekis_galimu) && (i < klasiu_sk); z++){
			jau_uzimtas = false;//tariame, kad is nauju galimu vektoriu visi yra laisvi
			Vektorius galimas_v = Kunas::string_to_vector(galimi_vektoriai[z]); //vienas is galimu vektoriu konvertuojamas is string i vektoriaus tipa

			standart_lentele.isvalyti_sindroma(i);
			for (int y = 0; y < H.sizeY(); y++){
					standart_lentele.prijungti_prie_sindromo(i, skaliarine_sandauga(galimas_v, H(y) ) );// vienas is galimu vektoriu  dauginamas is kontrolines matricos
			}																							// ir irasomas i sindroma [i]
			jau_uzimtas = standart_lentele.lyginti_sindromus_iki_indekso(i); // suzinome, ar paskutinis irasytas vektorius neduoda jau uzimto sindromo

			if (!jau_uzimtas) { // jei galimo vektoriaus gaminamas sindromas dar neuzimtas, pazymime vektoriaus svori
				cout << "i standartine lentele pridedamas vektorius: ";
				Kunas::print_vector(galimas_v);
				standart_lentele.priskirti_svori(i, Kunas::rasti_svori(galimas_v) );
				i++;
			}
			if (z == kiekis_galimu-1){//jei patikrinome paskutini galima vektoriu su dabartiniu svoriu, tai didiname svori
				svoris++;
			}	
		}
	}
	standart_lentele.spausdinti();
	return standart_lentele;
} 

Elementas skaliarine_sandauga(Vektorius v1, Vektorius v2){
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
	cout  << "vienetiniai vektoriai\n";
	for (int vekt = 0; vekt < e.size(); ++vekt) {
		Kunas::print_vector(e[vekt]);
	}

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

void dekoduoti(Vektorius vektorius, Matrica G){	// Funkcija paima vektoriu su istaisytomis klaidomis ir ji dekoduoja.
	G.transponuoti();							// Parametrai: vektorius su istaisytomis klaidomis, generuojanti matrica G.
	int stulp_sk = G.sizeX();					// Rezultatas: grazinamas dekoduotas vektorius.
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

		if ( G(nenuline_eil, stulp) == '1'){
			//cout << "sukeiciamos eiles " << stulp << " ir " << nenuline_eil << "\n";
//			swap rows i and max
			G.sukeisti_eilutes(stulp, nenuline_eil);
			cout << "vektorius pries simboliu "<< stulp <<" ir "<<nenuline_eil <<" sukeitima\n";
			Kunas::print_vector(vektorius);
			Kunas::sukeisti_simbolius(vektorius, stulp, nenuline_eil);
			cout << "vektorius po simboliu "<< stulp <<" ir "<<nenuline_eil <<" sukeitimo\n";
			Kunas::print_vector(vektorius);
			cout << endl;
			for (int stulp_next = stulp+1; stulp_next < eil_sk; ++stulp_next) {
//				Add A[u,i] * row i to row u, do this for BOTH, matrix A and RHS vector b
				Elementas daugiklis = G(stulp_next, stulp);
				G.dauginti_eilute_ir_prideti(stulp, daugiklis,stulp_next);
				cout << "vektorius pries simbolio "<< stulp <<" dauginima is "<< daugiklis <<" ir pridejima prie simbolio "<<stulp_next <<"\n";
							Kunas::print_vector(vektorius);
				Kunas::dauginti_simboli_ir_prideti(vektorius, stulp, daugiklis, stulp_next);
				cout << "vektorius po simbolio "<< stulp <<" dauginima is "<< daugiklis <<" ir pridejima prie simbolio "<<stulp_next <<"\n";
											Kunas::print_vector(vektorius);
											cout << endl;
			}
		}
		else {
			cout << "klaida - egzistuoja daugiau nei 1 sprendinys\n";
		}
	}

	bool eil_nuline;
	for (int eil = 0; eil < G.sizeY(); ++eil) { //perziurime, ar matricoje liko nuliniu eil.
		eil_nuline = true;
		for (int stulp = 0; stulp < G.sizeX(); ++stulp) {
			if ( G(eil, stulp) == '1')
				eil_nuline = false;
		}
		if (eil_nuline){
			if (vektorius[eil] == '1') {
				cout << "neisprendziama lygciu sistema\n";
			}
			else {
				G.pasalinti_eilute(eil);
				pasalinti_simboli(vektorius,eil);
				eil--;
			}

		}
	}
	cout << "matrica po gauso algoritmo\n";
	G.print();
	cout << "\nvektorius :\n";
	Kunas::print_vector(vektorius);

	LygciuSistema lygciu_sist(G, vektorius);
	lygciu_sist.spresti();
}

void LygciuSistema::spresti(){	// Funkcija, kuri sprendzia tiesiniu lygciu sistema.
											// Parametrai: matrica ir vektorius,
											//     kurie sudaro lygciu sistema.
											// Rezultatas: lygciu sistemos sprendinys kaip vektorius.

	lygtis_eiluteje(0);
	bool yra_neispresta;
	int neispresta;
	bool baigta = false;
	while (!baigta){
		yra_neispresta = false;
		for (int eil = 0; eil < this->isprestos_eilutes.size() && !yra_neispresta; ++eil) {
			if (this->isprestos_eilutes[eil] == 0){
				cout << "yra neispresta eilute "<< eil << endl;
				yra_neispresta = true;
				neispresta = eil;
			}
		}
		if (yra_neispresta)
			lygtis_eiluteje(neispresta);
		else
			baigta = true;
	}
	cout << "kintamuju reiksmes\n";
	Kunas::print_vector(this->kintamuju_reiksmes);
}
void LygciuSistema::lygtis_eiluteje(int eil){ 							// Funkcija kuri rekursyviai sprendzia tam tikra eilute lygciu sistemoje.
	cout << "iskviesta f-ja lygtis_eiluteje su param. " << eil << endl;	// Parametrai: eilute, kuri bus sprendziama.
	vector<int> eilutes_kintamieji;										// Rezultatas: pildomas LygciuSistema objektas, jame suzymimos isprestos eilutes
																		// ir rasti kintamieji bei ju reiksmes.
	for (int stulp = 0; stulp < this->matrica.sizeX(); ++stulp) { // suzymime eilutes kintamuosius i vektoriu
		if (this->matrica(eil, stulp) == '1') {
			eilutes_kintamieji.push_back(stulp);
		}
	}
	cout << "eilutes_kintamieji: ";
	print_vector(eilutes_kintamieji);
	if (eilutes_kintamieji.size() == 1) { // jei eiluteje yra tik 1 kintamasis
		cout << "eiluteje " << eil << " yra tik 1 kint" << endl;
		int kintamasis = eilutes_kintamieji.back();
		cout << "tas 1 kintamasis yra: " << kintamasis << endl;
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
				//kintamasis = vektorius[eilute] - sum(eilutes_kintamieji)
				cout << "eilutes " << eil << " kintamajam" <<eilutes_kintamieji[kint] << " iskviesta sprendimo dalis\n";
				Vektorius eilutes_kintamuju_reiksmes;
				for (int kintam = 0; kintam < eilutes_kintamieji.size(); ++kintam) {
					if (eilutes_kintamieji[kintam] == '1') {
						eilutes_kintamuju_reiksmes.push_back(kintamuju_reiksmes[kintam]);
					}
				}
				this->kintamuju_reiksmes[eilutes_kintamieji[kint]] = Kunas::el_atimtis(vektorius[eil],
																	sum_vector_elements(eilutes_kintamuju_reiksmes));
				cout << "jam priskirta reiksme: " << kintamuju_reiksmes[kint] << endl;
				this->surasti_kintamieji[eilutes_kintamieji[kint]] = 1; // pasizymime, jog suradome kintamojo reiksme
				this->isprestos_eilutes[eil] = 1;// pasizymime, kad isprendeme sia eilute
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

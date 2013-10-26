#include "dekodavimas.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;
#include "kodas.h"	



Matrica kontroline_matrica(Matrica G){
	G.i_rref();
	//G.print();
	vector<vector<int> > perstatymas = G.i_vienetine();
	//G.print();
	int k = G.sizeY();
	int n = G.sizeX();
	Matrica H(n, n-k);
	for (int eil = 0; eil < k; eil++) {
		for (int stulp = k; stulp < n; stulp++){
			int i = stulp-k;
			H(i, eil) = G(eil, stulp);
			
		}
	}
	for (int eil = 0; eil < H.sizeY(); eil++) {
		for (int stulp = k; stulp < H.sizeX(); stulp++){
			if (eil+k==stulp)
				H(eil, stulp) = '1';
			else
				H(eil, stulp) = '0';
		}
	}
	//H.print();
	for (int stulp = 0; stulp < n; stulp++){
		if (perstatymas[0][stulp] < perstatymas[1][stulp]){
			H.sukeisti_stulpelius(perstatymas[0][stulp], perstatymas[1][stulp]);
		}
	}
	cout << "\nkontroline matrica\n";
	H.print();
	return H;
}
void skaiciuoti_sindromus(Matrica H, vector< vector<Vektorius> > stdArray){
	vector < vector <Elementas> > sindromai;
	vector <int> vektoriu_svoriai;
	cout << "sindromu lentele: " << endl;
	sindromai.resize(stdArray.size());
	vektoriu_svoriai.resize(stdArray.size());
	for (int i = 0; i < stdArray.size(); i++){
		vektoriu_svoriai[i] = Kunas::rasti_svori(stdArray[i][0]);
		for (int j = 0; j < H.sizeY(); j++){
			sindromai[i].push_back( skaliarine_sandauga(stdArray[i][0], H(j) ) );
			
		}
		bool jau_uzimtas = false;
		for (int s = 0; s < i; s++){
			if ( Kunas::lyginti(sindromai[s], sindromai[i]) )
				jau_uzimtas = true;
		}
		if (!jau_uzimtas) {
			cout << "vekt. ";
			Kunas::print_vector(stdArray[i][0]);
			cout << "  ";

		}
		int skait_kiek = H.sizeX();
		int svoris = Kunas::rasti_svori(stdArray[i][0]);
		while( jau_uzimtas ){
			vector<string> galimi_vektoriai;	
			get_strings_with_weight(galimi_vektoriai, "", skait_kiek, svoris, skait_kiek);
			int kiekis_galimu = galimi_vektoriai.size();
			
			for (int z = 0; (z < kiekis_galimu)&&jau_uzimtas; z++){
				jau_uzimtas = false;//tariame, kad is nauju galimu vektoriu visi yra laisvi
				Vektorius galimas_v = Kunas::string_to_vector(galimi_vektoriai[z]); //konvertuojame is string i vektoriu 
				sindromai[i].clear();
				for (int y = 0; y < H.sizeY(); y++){
						sindromai[i].push_back( skaliarine_sandauga(galimas_v, H(y) ) );
				}
				for (int x = 0; x < i; x++){//tikrinsime visus iki siol sugeneruotus sindromus
					
					
					if ( Kunas::lyginti(sindromai[x], sindromai[i]) ){
							jau_uzimtas = true;
							
					}

					
				}

				if (!jau_uzimtas) {
					cout << "vekt. ";
					Kunas::print_vector(galimas_v);
					cout << "  ";
					vektoriu_svoriai[i] = Kunas::rasti_svori(galimas_v);
				}
				
				if (z == kiekis_galimu-1){//jei patikrinome paskutini potencialu lyderi
					svoris++;
				}	
			}
			

		}
		
		cout <<vektoriu_svoriai[i] << "     ";
		Kunas::print_vector(sindromai[i]);
		cout << endl;
	}
} 

Elementas skaliarine_sandauga(Vektorius v1, Vektorius v2){
	Elementas sum = '0';
	for (int i = 0; i < v1.size(); i++){
		sum = Kunas::el_sudetis( sum, Kunas::el_daugyba(v1[i], v2[i]) );
	} 
	return sum;
}


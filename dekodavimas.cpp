#include "dekodavimas.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;



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
	cout << "cos. leader   syndrome: " << endl;
	for (int i = 0; i < stdArray.size(); i++){
		Kunas::print_vector(stdArray[i][0]);
		cout << "        ";
		for (int j = 0; j < H.sizeY(); j++){
			cout << skaliarine_sandauga(stdArray[i][0], H(j) )<<" ";
		}
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


#include "dekodavimas.h"
#include <vector>
	using namespace std;
#include <iostream>
	using namespace std;

void kontroline_matrica(Matrica G){
	G.i_rref();
	G.print();
	vector<vector<int> > perstatymas = G.i_vienetine();
	G.print();
	
}


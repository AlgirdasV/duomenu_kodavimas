#include "kanalas.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>
using namespace std;

Vektorius siuntimas_kanalu(Vektorius v, float tikimybe){
	Vektorius rez;
	assert(v.size()!=0);
	int klaidu_sk = 0;
	float random;
	for ( int i = 0; i < v.size(); i++ ) {
		random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);//generuoja atsitiktini skaiciu nuo 0 iki 1
//		cout << "atsitiktinis sk. " << random << "\n";
		if (random < tikimybe){//simboli reikia iskraipyti
//			cout << "reikia kraipyti\n";
			rez.push_back(Kunas::el_sudetis(v[i], '1'));
			klaidu_sk++;
		}
		else rez.push_back(v[i]);
	}
	return rez;
	
}

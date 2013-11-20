#include "kanalas.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Vektorius siuntimas_kanalu(Vektorius v, float tikimybe){
	Vektorius rez;
	srand (time(NULL));
	int klaidu_sk = 0;
	for ( int i = 0; i < v.size(); i++ ) {
		float a = (float)rand()/(float)RAND_MAX;//generuoja atsitiktini skaiciu nuo 0 iki 1
		if (a < tikimybe){//simboli reikia iskraipyti
			//cout << "reikia kraipyti\n";
			rez.push_back(Kunas::el_sudetis(v[i], '1'));
			klaidu_sk++;
		}
		else rez.push_back(v[i]);
	}
	return rez;
	
}
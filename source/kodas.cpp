#include "kodas.h"
#include "kunas.h"
#include "matrica.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#include <string>
using namespace std;
#include <cassert>

Vektorius dauginti_matrica_su_vektoriumi(Matrica matrica, Vektorius vektorius) {
	
	assert(vektorius.size() == matrica.sizeY() );
	Vektorius galut_rezult;
	Vektorius daug_rezult;
	for (int i = 0; i < vektorius.size(); i++){
		if (vektorius[i]=='1')
			daug_rezult = matrica(i);
		galut_rezult = Kunas::sudetis(galut_rezult, daug_rezult);
		daug_rezult.clear();
	}
	
	return galut_rezult;
}


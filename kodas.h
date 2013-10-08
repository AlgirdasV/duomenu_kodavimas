#ifndef KODAS_H
#define KODAS_H
#include "matrica.h"
#include <string>
#include <vector>
	//typedef std::valarray<double> Matrix;
	void tiesinis_kodavimas( Matrica& );
	void getStrings(std::vector<std::string>& , std::string , int );
	void kurti_standart_masyva(Matrica, int, int);
	void coset_leaders(std::vector< std::vector<Vektorius> >&, int, int);
#endif
#ifndef KODAS_H
#define KODAS_H
#include "matrica.h"
#include <string>
#include <vector>
	//typedef std::valarray<double> Matrix;
	void tiesinis_kodavimas( Matrica& );
	void get_strings(std::vector<std::string>& , std::string , int );
	void get_strings_with_weight(std::vector<std::string>& , std::string , int, int, int);
	void kurti_standart_masyva(Matrica, int, int);
	void coset_leaders(std::vector< std::vector<Vektorius> >&, int, int, int&);
#endif
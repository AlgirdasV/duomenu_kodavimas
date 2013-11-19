#ifndef MATRICA_H
#define MATRICA_H
#include "kunas.h"
#include <vector>
#include <string>  

class Matrica {
	int x, y; 
	
	
	public:
		std::vector< std::vector<Elementas> > reiksme;
		Matrica(int, int);
		Matrica();
		~Matrica();
		int sizeX();
		int sizeY();
		bool from_file(const std::string&);
		void print();
		void keisti_dydi(const int,const int);
		char& operator()(const int , const int );
		std::vector<char>& operator()(const int );
		void dauginti_eilute(int, Elementas);
		void dauginti_eilute_ir_atimti(int, Elementas, int);
		void sukeisti_eilutes(int, int);
		void sukeisti_stulpelius(int, int);
		void i_rref();
		std::vector<std::vector<int> > i_vienetine();
		void generuoti_matrica(int, int);

};
#endif
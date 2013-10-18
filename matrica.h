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
		void from_file(const std::string&);
		void print();
		char& operator()(const int , const int );
		std::vector<char>& operator()(const int );
		void dauginti_eilute(int, Elementas);
		void dauginti_eilute_ir_prideti(int, Elementas, int);
		void sukeisti_eilutes(int, int);


};
#endif
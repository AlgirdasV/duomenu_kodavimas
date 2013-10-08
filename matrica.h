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


};
#endif
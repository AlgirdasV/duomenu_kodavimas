#ifndef PAGALBINES_H
#define PAGALBINES_H

#include <string>
#include <vector>
#include "kunas.h"
#include <iostream>

void remove_carriage_return(std::string& line);
void get_strings_with_weight(std::vector<std::string>& , std::string , int, int, int);
void reset_vector(std::vector <int>& , int );
void reset_vector(std::vector <Elementas>& , int );
Elementas sum_vector_elements(Vektorius );
template <typename T>
void print_vector( std::vector <T>);
void pasalinti_simboli(Vektorius& , int );
template <typename T>
void print_2d_vector(std::vector <std::vector <T> > vector);

template <typename T>
void print_vector( std::vector <T> v){
	std::cout << "f-ja print vector\n";
	std::cout << "vector size: " <<v.size() << "\n";
		for (int i=0; i < v.size(); i++){
			std::cout << v[i] << " ";
			if (i%8 == 0)
				std::cout << "\n";
		}
		std::cout << "test po ciklo\n";
}

template <typename T>
void print_2d_vector(std::vector <std::vector <T> > vector){
	for (int vekt = 0; vekt < vector.size(); ++vekt) {
		Kunas::print_vector(vector[vekt]);
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

#endif

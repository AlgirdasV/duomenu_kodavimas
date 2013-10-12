#ifndef KUNAS_H
#define KUNAS_H
#include <string>
#include <vector>


typedef char Elementas; 
typedef std::vector<Elementas> Vektorius;

	class Kunas{
	public:
		static Vektorius sudetis(Vektorius, Vektorius);
		static Vektorius daugyba(Vektorius, Vektorius);
		static void print_vector(Vektorius);
		static Elementas addElements(Elementas, Elementas);
		static void reset_vector( Vektorius& , int);
		static bool lyginti(Vektorius , Vektorius );
		static void resize_2d_vector (std::vector< std::vector<Vektorius> > &, int, int );
		static Vektorius string_to_vector (std::string, Vektorius&);
	};

	

#endif
#include "kunas.h"
#include <string>
using namespace std;
#include <iostream>
using namespace std;
#include <vector>
using namespace std;

	Vektorius Kunas::sudetis(Vektorius a, Vektorius b) {//sudeda vienodo ilgio vektorius
		vector<Elementas> naujas;						//ir grazina rezultata kaip vektoriu.
		vector<Elementas>::iterator it= naujas.begin();

		if ( (a.size()==b.size()) && a.size()!=0) {
			int limit =a.size();
			for (int i=0; i<limit; i++){//atbuline eiga
				Elementas rez = addElements( a.back(), b.back() );
    			it = naujas.insert ( it , rez );
    			b.pop_back();
    			a.pop_back();
    			it = naujas.begin();
    		}	
			return naujas;
		} 
		else cout << "Klaida sudeties veiksme\n";
	
	}

	bool Kunas::lyginti(Vektorius a, Vektorius b){
		bool lygu=true;
		/*
		cout<<"lyginami vektoriai: ";
		print_vector(a);
		cout << " ir ";
		print_vector(b);
		cout <<endl;*/
		if (a.size()==b.size()){
			for (int i = 0; i < a.size(); i++) {
				if (a[i]!=b[i]){
					lygu=false;
				}
			}
		}
		else {
			cout<<"vektoriai (";
			print_vector(a);
			cout << ") ir (";
			print_vector(b);
			cout << ") nevienodo dydzio. Palyginimas negalimas\n";
			return false;
		}
		return lygu;
	}

	Vektorius Kunas::daugyba(Vektorius a, Vektorius b) {
	    //return a & b;
	}

	Elementas Kunas::addElements(Elementas a,Elementas b){
		if (a=='0' && b=='0'){
			return '0';
		}
		else if (a=='1' && b=='0'){
			return '1';
		}
		else if (a=='0' && b=='1'){
			return '1';
		}
		else return '0';
	}

	void Kunas::print_vector( Vektorius v){
		for (int i=0; i < v.size(); i++){
			cout << v[i];
		}
		
	}

	void Kunas::reset_vector( Vektorius& v, int size){
		v.clear();
		for (int i=0; i<size; i++) {
			v.push_back('0');
		}
	}

	void Kunas::resize_2d_vector (vector< vector<Vektorius> >& v, int X, int Y){
		v.resize(Y);
		for (int i = 0; i < Y; i++){
			v[i].resize(X);
		}
	}

	Vektorius Kunas::string_to_vector (std::string str, Vektorius& v){
	v.resize( str.length() );
		for (int i = 0; i < str.length(); i++){
			v[i] = str[i];
		}
		return v;
	}
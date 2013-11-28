#include "kunas.h"
#include <string>
using namespace std;
#include <iostream>
using namespace std;
#include <vector>
using namespace std;
#include <cassert>

	

	bool Kunas::lyginti(Vektorius a, Vektorius b){
		bool lygu=true;
		assert(a.size()==b.size());
		/*
		cout<<"lyginami vektoriai: ";
		print_vector(a);
		cout << " ir ";
		print_vector(b);
		cout <<endl;*/
		for (int i = 0; i < a.size(); i++) {
			if (a[i]!=b[i]){
				lygu=false;
			}
		}
		return lygu;
	}

	void Kunas::spausdinti_klaidas(Vektorius a, Vektorius b){
		assert(a.size()==b.size());
		vector <int> klaidos;
		for (int i = 0; i < a.size(); i++) {
			if (a[i]!=b[i]){
				//cout << "pozicijoje " << i << "klaida.";
				klaidos.push_back(i);
			}
		}
		cout << "Viso siuntimo metu ivyko klaidu: " << klaidos.size() << endl;
		if (klaidos.size()!=0){
			cout << "Klaidos pozicijose: ";
			for (int i = 0; i < klaidos.size(); i++) {
				cout << klaidos[i]+1 << " ";
			}
			cout << endl;
		}
	}

	Vektorius Kunas::daugyba(Vektorius binary1, Vektorius binary2) {
		Vektorius multiply;
		char digit;
		int factor=1;

	    while( !binary2.empty() ) {
	    	
        	digit =  binary2.back();
        	
	        if(digit =='1'){
	        		if (factor==10)
	                	binary1.push_back('0');
	                
	                multiply = sudetis(binary1,multiply);
	
	        }
	        else {
	        	if (factor==10)
	                binary1.push_back('0');
	        }
	        binary2.pop_back();
	        factor = 10;
	        
	    }
	    
	    return multiply;
	}

	int Kunas::rasti_svori(Vektorius v){
		int svoris = 0;
		for (int i = 0; i < v.size(); i++ ) {
			if (v[i] == '1')
				svoris++;
		}
		return svoris;
	}
 
	Vektorius Kunas::sudetis(Vektorius binary1, Vektorius binary2){
		
		Vektorius binarySum;

	    int i=0,remainder = 0,sum[20];
		
	    while( ( !binary1.empty() ) || ( !binary2.empty() )){
	    	Elementas last_digit1;
	    	Elementas last_digit2;
	    	if (!binary1.empty())
	    		last_digit1=binary1.back();
	    	else 
	    		last_digit1='0';
	    	
	    	if ( !binary2.empty() ) {
	    		last_digit2=binary2.back();
	    	}
	    	else 
	    		last_digit2='0';
	    	
	    	Elementas tmp = el_sudetis( last_digit1, last_digit2 );
	    	int tmp2 = remainder + (tmp-'0');

	        sum[i++] =  tmp2 % 2;
	        remainder = tmp2 / 2;
	       	if (!binary1.empty())
	        	binary1.pop_back();
	        if (!binary2.empty())
	        	binary2.pop_back();
	    }

	    if(remainder!=0)
	         sum[i++] = remainder;
	    --i;
	    while(i>=0){
	    	Elementas tmp3 = '0'+sum[i--];
	        binarySum.push_back(tmp3);
	    }

	    return binarySum;
	    
	}

	Elementas Kunas::el_atimtis(Elementas a, Elementas b){//is elemento a atimamas elementas b
		assert( (a=='0' || a=='1') && (b=='0' || b=='1') );
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

	bool Kunas::lygus_nuliui(Vektorius v){
		bool lygus = true;
		for (int i = 0; i < v.size(); i++){
			if (v[i]=='1') lygus = false;
		}
		return lygus;
	}

	Elementas Kunas::el_sudetis(Elementas a,Elementas b){
		assert( (a=='0' || a=='1') && (b=='0' || b=='1') );
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

	Elementas Kunas::el_daugyba(Elementas a,Elementas b){
		assert( (a=='0' || a=='1') && (b=='0' || b=='1') );
		if (a=='0' && b=='0'){
			return '0';
		}
		else if (a=='1' && b=='0'){
			return '0';
		}
		else if (a=='0' && b=='1'){
			return '0';
		}
		else return '1';
	}

	
	void Kunas::print_vector( Vektorius v){
		for (int i=0; i < v.size(); i++){
			cout << v[i] << " ";
		}

	}

//	void Kunas::reset_vector( Vektorius& v, int size){
//		v.clear();
//		for (int i=0; i<size; i++) {
//			v.push_back('0');
//		}
//	}

	void Kunas::resize_2d_vector (vector< vector<Vektorius> >& v, int X, int Y){
		v.resize(Y);
		for (int i = 0; i < Y; i++){
			v[i].resize(X);
		}
	}

	Vektorius Kunas::string_to_vector (std::string str){
	Vektorius v;
	v.resize( str.length() );
		for (int i = 0; i < str.length(); i++){
			v[i] = str[i];
		}
		return v;
	}

	void Kunas::sukeisti_simbolius(Vektorius& v, int simb1, int simb2) {
		//cout << "sukeiciami simboliai " << simb1 << " ir " << simb2 << endl;
			assert(simb1 >= 0 && simb1 < v.size() );
			assert(simb2 >= 0 && simb2 < v.size() );
			char pagalb;
			pagalb = v[simb1];
			v[simb1] = v[simb2];
			v[simb2] = pagalb;
	}

	void Kunas::dauginti_simboli_ir_prideti(Vektorius& v, int simb1, Elementas el, int simb2) {
				//cout << "simbolis " << simb1 << " dauginamas is " << el << " ir pridedamas prie " << simb2 << endl;
				assert(simb1 >= 0 && simb1 < v.size() );
				assert(simb2 >= 0 && simb2 < v.size() );
				Elementas rez = Kunas::el_daugyba(v[simb1], el);

				v[simb2] = Kunas::el_sudetis(v[simb2], rez);
		}

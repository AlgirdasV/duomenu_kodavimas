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

	Elementas Kunas::el_atimtis(Elementas a, Elementas b){
		assert( (a=='0' || a=='1') && (b=='0' || b=='1') );
		if (a=='0' && b=='0'){
			return '0';
		}
		else if (a=='1' && b=='0'){
			return '0';
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
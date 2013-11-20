#include "matrica.h"
#include <iostream>
	using namespace std;
#include <cassert>
#include <string>         // std::string
	using namespace std;
#include <vector>
	using namespace std;
#include <fstream>
#include <cstring>
#include "pagalbines_funkcijos.h"	
#include <stdlib.h>
#include <time.h>

Matrica::Matrica(int sizeX, int sizeY): x(sizeX), y(sizeY) {
	reiksme.resize(sizeY);
	for (int i = 0; i < sizeY; i++) {
		reiksme[i].resize(sizeX);
	}
}

Matrica::Matrica(): x(0), y(0)  {
}

Matrica::~Matrica() {
}

void Matrica::keisti_dydi(const int sizeX,const int sizeY){//Funkcija keicia matricos dydi.
	this->x = sizeX;										//Parametrais ima stulpeliu ir eiluciu dydzius
	this->y = sizeY;										//Rezultatas: keicia matricos, kuriai funkcija iskviesta, dydi
	this->reiksme.resize(sizeY);
	for (int i = 0; i < sizeY; i++) {
		this->reiksme[i].resize(sizeX);
	}
}

char& Matrica::operator()(const int nRow, const int nCol)	//Funkcija leidzia prieti prie matricos reiksmes
{															//Parametrais nurodomi stulpelio ir eilutes nr.
    assert(nCol >= 0 && nCol < this->sizeX() );				//rezultatas: grazina matricos reiksme
    assert(nRow >= 0 && nRow < this->sizeY() );
 
    return this->reiksme[nRow][nCol];
}

std::vector<char>& Matrica::operator()(const int nRow) 	//Funkcija grazina eilute
{														//Parametras: eilutes nr
    assert(nRow >= 0 && nRow < this->sizeY() );			//Grazina matricos eilute kaip vektoriu
 
    return this->reiksme[nRow];
}

int Matrica::sizeX () {//Funkcija grazina matricos stulpeliu sk.
	return this->x;
}

int Matrica::sizeY () {//Funkcija grazina matricos eiluciu sk.
	return this->y;
}

bool Matrica::from_file(const string& file){//Funkcija uzkrauna matrica is failo
	ifstream myfile (file.c_str());			//Parametras: failo pavadinimas
	if (myfile.is_open()) {					//Rezultatas: i matrica, kuriai iskviesta funkcija, irasomi duomenis is failo
		string line;
		int col=0, row=0;
    	while ( getline (myfile,line) ) {
    		this->reiksme.resize(row+1);//didiname matricos eiluciu kieki
    		remove_carriage_return(line);//pasaliname \r simboli is eilutes
    		for (int i=0; i<line.length(); i++) {
    			if (line[i]!=' ') {
    				if ( line[i] == '1' )//yra simbolis 1
    					this->reiksme[row].push_back('1');
    				else if ( line[i] == '0' )//yra simbolis 0
    					this->reiksme[row].push_back('0');
    				else cout<< "klaidingas simbolis faile " << file<< endl;
    				col++;
    			}
    			
    		}
			row++;
			col=0;
		}
		myfile.close();
		this->x = this->reiksme[0].size();//pazymime laukus
		this->y = row;					//, kurie rodo matricos eiluciu ir stulpeliu sk.
		return true;
	}
	else {
		cout << "Nepavyko atidaryti failo \"" << file <<"\"";
		return false;
	}
}



void Matrica::print(){//Funkcija spausdina matrica i konsole
					//Rezultatas: matricos, kuriai iskviesta funkcija, skaitmenys yra spausdinami.
	for (int row=0; row< this->y; row++) {
		for (int col=0; col< this->x; col++){
			cout << this->reiksme[row][col]<<" ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrica::dauginti_eilute(int eil, Elementas daugiklis){//Funkcija daugina matricos eilute is daugiklio
															//Parametrai: eilutes nr. ir elemento tipo daugiklis
															//Rezultatas keiciama matricos, kuriai isvkiesta funkcija, eilute
	//cout<< "eilute ["<< eil<<"] dauginama is "<<daugiklis<<endl;
	assert(eil >= 0 && eil < this->y );
	for (int stulp = 0; stulp < this->x; stulp++){
		this->reiksme[eil][stulp] = Kunas::el_daugyba(this->reiksme[eil][stulp], daugiklis);
	}
	
}

void Matrica::dauginti_eilute_ir_atimti(int eil1, Elementas daugiklis, int eil2){
	//cout<< "eilute ["<< eil1<<"] dauginama is "<<daugiklis<<" ir atimama is eilutes ["<<eil2<<"]\n";
	assert(eil1 >= 0 && eil1 < this->y );
	assert(eil2 >= 0 && eil2 < this->y );
	Vektorius pagalb;
	pagalb.resize(this->x);
	for (int stulp = 0; stulp < this->x; stulp++){
		pagalb[stulp] = Kunas::el_daugyba( this->reiksme[eil1][stulp], daugiklis );
		this->reiksme[eil2][stulp] = Kunas::el_atimtis( pagalb[stulp], this->reiksme[eil2][stulp] );
	}
	
}

void Matrica::sukeisti_eilutes(int eil1, int eil2){
	//cout<< "sukeiciamos eilutes: "<< eil1<<" ir "<<eil2<<endl;
	assert(eil1 >= 0 && eil1 < this->y );
	assert(eil2 >= 0 && eil2 < this->y );
	Vektorius pagalb;
	pagalb.resize(this->x);
	for (int stulp = 0; stulp < this->x; stulp++){
		pagalb[stulp] = this->reiksme[eil1][stulp];
		this->reiksme[eil1][stulp] = this->reiksme[eil2][stulp];
		this->reiksme[eil2][stulp] = pagalb[stulp];
	}
}

void Matrica::sukeisti_stulpelius(int stulp1, int stulp2){
	//cout<< "sukeiciami stulpeliai: "<< stulp1<<" ir "<<stulp2<<endl;
	assert(stulp1 >= 0 && stulp1 < this->x );
	assert(stulp2 >= 0 && stulp2 < this->x );
	Elementas pagalb;

	for (int eil = 0; eil < this->y; eil++){
		pagalb = this->reiksme[eil][stulp1];
		this->reiksme[eil][stulp1] = this->reiksme[eil][stulp2];
		this->reiksme[eil][stulp2] = pagalb;
	}
}

void Matrica::i_rref() {
	 
	int lead = 0;
 
  	for (int row = 0; row < this->y; row++){
	    if (lead >= this->x)	//jeigu perejome visus stulpelius
	    	return;
	    int i = row;
	    //cout<<"i = "<<i<<" lead = "<<lead<<endl;
	    while (this->reiksme[i][lead] == '0')
	    {
		    i++;
		    if (i >= this->y){
			    i = row;
			    lead++;
			    if (lead >= this->x)
			    	return;
		    }
		    //cout<<"i = "<<i<<" lead = "<<lead<<endl;
	    }
	    this->sukeisti_eilutes(i, row);
	    if (this->reiksme[row][lead]!='0')
	    	this->dauginti_eilute(row, this->reiksme[row][lead]);
	    for (int j = 0; j < this->y; j++)
	    {
	    	if (j != row)
	    		this->dauginti_eilute_ir_atimti( row, this->reiksme[j][lead], j );
	    }
  	}
}

vector<vector<int> > Matrica::i_vienetine() {//grazina perstata
	int a, b;
	vector<vector<int> > perstatas;
	int stulp_sk = this->x;
	int eil_sk = this->y;
	perstatas.resize(2);
	perstatas[0].resize(this->x);
	perstatas[1].resize(this->x);
	
	for (int stulp = 0; stulp < stulp_sk; stulp++){
		perstatas[0][stulp]=stulp;
		perstatas[1][stulp]=stulp;
	}
	if (eil_sk > stulp_sk)
		eil_sk = stulp_sk;

	for (int eil = 0; eil < eil_sk; eil++){
		for (int stulp = 0; stulp < eil_sk; stulp++){	// Einame per stulpelius, kol stulpelio numeris nedidesnis uz eiluciu sk.
			if ( eil==stulp ){							//Jei stulpelio ir eil. numeris sutampa
				if ( this->reiksme[eil][stulp] != '1' ){ //ir reiksme nera 1,
					a = stulp;							// tuomet ieskome stulpeliu kuriuose reiksme butu 1.
					int stulp2 = a+1;
					
					while( this->reiksme[eil][stulp2] != '1' && stulp2 < stulp_sk) {	
						stulp2++;
					}
					if (stulp2 >= stulp_sk){
						cout << "Generavimo matrica nesuvedama i standartine forma\n";
						exit (EXIT_FAILURE);
					}
					b = stulp2;
					this->sukeisti_stulpelius(a, b);	//rade stulpelius su reiksme 1, 
													//sukeiciame juos su pries tai pasizymetu stulpeliu
					//Perstatymo vektoriuje taipogi sukeiciame stulpelius:
					int pagalb;
					pagalb = perstatas[1][a];
					perstatas[1][a] = perstatas[1][b];
					perstatas[1][b] = pagalb;
					//
					 
				}
			}
		}
	}
	return perstatas;
}

void Matrica::generuoti_matrica(int eil_sk, int stulp_sk){
	this->keisti_dydi(stulp_sk, eil_sk);
	srand (time(NULL));
	int naujas_elementas;
	for (int eil = 0; eil < eil_sk; eil++){
		for (int stulp = 0; stulp < stulp_sk; stulp++){
			naujas_elementas = rand() % 2; //atsitiktinis sveikas skaicius nuo 0 iki 1
			if (naujas_elementas == 1)
				this->reiksme[eil][stulp]='1';
			else 
				this->reiksme[eil][stulp]='0';
		}
	}
}
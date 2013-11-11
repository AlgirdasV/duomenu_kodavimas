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

void Matrica::keisti_dydi(const int sizeX,const int sizeY){
	this->x = sizeX;
	this->y = sizeY;
	this->reiksme.resize(sizeY);
	for (int i = 0; i < sizeY; i++) {
		this->reiksme[i].resize(sizeX);
	}
}

char& Matrica::operator()(const int nRow, const int nCol)	//leidzia prieti prie matricos reiksmes
{															//nurodytame stulpelyje ir eiluteje
    assert(nCol >= 0 && nCol < this->sizeX() );
    assert(nRow >= 0 && nRow < this->sizeY() );
 
    return this->reiksme[nRow][nCol];
}

std::vector<char>& Matrica::operator()(const int nRow) 	//grazina nurodytos eilutes vektoriu
{
    assert(nRow >= 0 && nRow < this->sizeY() );
 
    return this->reiksme[nRow];
}

int Matrica::sizeX () {//grazina matricos stulpeliu sk.
	return this->x;
}

int Matrica::sizeY () {//grazina matricos eiluciu sk.
	return this->y;
}

void Matrica::from_file(const string& file){
	ifstream myfile (file.c_str());
	if (myfile.is_open()) {
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
	}
	else cout << "Nepavyko atidaryti failo \"" << file <<"\"";
}



void Matrica::print(){
	
	for (int row=0; row< this->y; row++) {
		for (int col=0; col< this->x; col++){
			cout << this->reiksme[row][col]<<" ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrica::dauginti_eilute(int eil, Elementas daugiklis){
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
	    if (lead >= this->x)
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

vector<vector<int> > Matrica::i_vienetine() {//grazina perstatymo vektoriu
	int a, b;
	vector<vector<int> > perstatymas;
	int stulp_sk = this->x;
	perstatymas.resize(2);
	perstatymas[0].resize(this->x);
	perstatymas[1].resize(this->x);
	
	for (int stulp = 0; stulp < this->x; stulp++){
		perstatymas[0][stulp]=stulp;
		perstatymas[1][stulp]=stulp;
	}
	for (int eil = 0; eil < this->y; eil++){
		for (int stulp = 0; stulp < this->y; stulp++){
			if ( eil==stulp ){
				if ( this->reiksme[eil][stulp] != '1' ){
					a = stulp;
					int stulp2 = a+1;
					while(this->reiksme[eil][stulp2] != '1'){	
						stulp2++;
					}
					b = stulp2;
					this->sukeisti_stulpelius(a, b);
					//Perstatymo vektoriuje taipogi sukeiciame stulpelius:
					int pagalb;
					pagalb = perstatymas[1][a];
					perstatymas[1][a] = perstatymas[1][b];
					perstatymas[1][b] = pagalb;
					//
				}
			}
		}
	}
	return perstatymas;
}
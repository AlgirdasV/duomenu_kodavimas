#include "matrica.h"
#include <iostream>
using namespace std;
#include <cassert>
#include <string>         // std::string
using namespace std;
#include <fstream>
#include <cstring>

Matrica::Matrica(int sizeX, int sizeY): x(sizeX), y(sizeY) {
	reiksme.resize(sizeY);
	for (int i = 0; i < sizeY; i++) {
		reiksme[i].resize(sizeX);
	}
}

Matrica::~Matrica() {
}

char& Matrica::operator()(const int nCol, const int nRow)	//leidzia prieti prie matricos reiksmes
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
    		for (int i=0; i<line.length(); i++) {
    			if (line[i]!=' ') {
    				if ( line[i] == '1' )//yra simbolis 1
    					this->reiksme[row][col]='1';
    				else if ( line[i] == '0' )//yra simbolis 0
    					this->reiksme[row][col]='0';
    				else cout<< "klaidingas simbolis faile" << file<< endl;
    				col++;
    			}
    			
    		}
			row++;
			col=0;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void Matrica::print(){
	
	for (int row=0; row< this->y; row++) {
		for (int col=0; col< this->x; col++){
			cout << this->reiksme[row][col];
		}
		cout << endl;
	}
	cout << endl;
}
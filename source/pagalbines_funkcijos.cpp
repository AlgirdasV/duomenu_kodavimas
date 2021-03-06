#include "pagalbines_funkcijos.h"
#include <string>
    using namespace std;
#include <vector>
    using namespace std;
#include <algorithm>
#include "kunas.h"
#include <iostream>
    using namespace std;
#include <cassert>


void remove_carriage_return(std::string& line) // funkcija pasalina '\r' simboli
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}

void get_strings_with_weight(vector<string>& answer, string s,
                                int digitsLeft, int weight, int digits) { // rekursyvi funkcija, kuri generuoja vektorius su tam tikru svoriu ir ilgiu
                                                                          // parametrai: vektorius, i kuri bus generuojama
                                                                          // algoritmui reikalinga (is pradziu tuscia) eilute
                                                                          // reikiamu vektoriu svoris ir ilgis.

    size_t vien_kiek = std::count(s.begin(), s.end(), '1');

    if( digitsLeft == 0 ) { // sukureme eilute
        if (vien_kiek == weight) { // jei vienetu kiekis atitinka reikiama svori
            answer.push_back( s );
        }
    }
    else
    {
        size_t vien_kiekis = std::count(s.begin(), s.end(), '1');
        if (vien_kiekis < weight) { // jei eilute neturi svorio kiekio vienetu
            get_strings_with_weight(answer, s + "1", digitsLeft - 1, weight, digits);
        }

        size_t nul_kiekis = std::count(s.begin(), s.end(), '1');
        if (nul_kiekis < digits-1) { // jei eilute neturi digits-1 nuliu
            get_strings_with_weight(answer, s + "0", digitsLeft - 1, weight, digits);
        }
    }
}

void reset_vector(vector <int>& vektorius, int dydis){ // Funkcija, pagal nurodyta dydi uzpildo
                                                      //  vektoriu pradiniais elementas.
    vektorius.clear();
    for (int i=0; i<dydis; i++) {
        vektorius.push_back(0);
    }
}

void reset_vector(vector <Elementas>& vektorius, int dydis){ // Funkcija, pagal nurodyta dydi uzpildo
                                                            //  vektoriu pradiniais elementas.
    vektorius.clear();
    for (int i=0; i<dydis; i++) {
        vektorius.push_back('2');   // reiksme 2, dvinariame baigtiniame kune neturinti prasmes.
                                    // ja pazymime, kad kintamojo reiksme dar neatrasta.
    }
}

Elementas sum_vector_elements(Vektorius vektorius){ // Funkcija, susumuojanti visus vektoriaus el.
    Elementas sum = '0';
    for (int el = 0; el < vektorius.size(); ++el) {
        sum = Kunas::el_sudetis(vektorius[el], sum);
    }
    return sum;
}



void pasalinti_simboli(Vektorius& vektorius, int simbolis){ // funkcija pasalina is vektoriaus simboli
    assert(simbolis >= 0 && simbolis < vektorius.size() );
    for (int simb = simbolis; simb < vektorius.size() - 1; ++simb) {//perkopijuojami simoliai sekantys po to, kuris buvo istrintas
        vektorius[simb] = vektorius[simb+1];
    }
    vektorius.resize(vektorius.size() - 1);
}

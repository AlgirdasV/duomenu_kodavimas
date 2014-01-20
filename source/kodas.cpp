#include "kodas.h"
#include "kunas.h"
#include "matrica.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "pagalbines_funkcijos.h"
using namespace std;
#include <string>
using namespace std;
#include <cassert>
#include <exception>

Vektorius dauginti_matrica_su_vektoriumi(Matrica matrica, Vektorius vektorius) { // funkcija kuri uzkoduoja jai perduota vektoriu
                                                                                 // Parametrai: generuojanti matrica ir vektorius
                                                                                 // Rezultatai: grazinamas uzkoduotas vektorius
    assert(vektorius.size() == matrica.sizeY() );
    assert(vektorius.size()!=0);
    Vektorius galut_rezult;
    Vektorius daug_rezult;
    galut_rezult.resize(matrica.sizeX());
    Kunas::nulinti_vektoriu(galut_rezult);
    daug_rezult.resize(matrica.sizeX());
    for (int i = 0; i < vektorius.size(); i++){
        Kunas::nulinti_vektoriu(daug_rezult);
        if (vektorius[i]=='1'){
            assert(matrica(i).size()!=0);
            daug_rezult = matrica(i);
        }
        assert(daug_rezult.size()!=0);
        galut_rezult = Kunas::sudetis(galut_rezult, daug_rezult);
    }
    assert(galut_rezult.size()!=0);
    return galut_rezult;
}

Matrica generuoti_G_matrica(int eil_sk, int stulp_sk){  // Funkcija pagal pateiktus parametrus sukuria generuojancia matrica.
    //  this->keisti_dydi(stulp_sk, eil_sk);            // Parametrai: matricos eiluciu sk. ir stulpeliu sk.
                                                        // Rezultatas: matrica, kuriai iskviesta si funkcija, yra uzpildoma atsitiktiniais kuno elementais.
        Matrica G;
        int naujas_elementas;
        int eilute;
        for (int eil = 0; eil < eil_sk; eil++){
            G.keisti_dydi(eil+1);
            G.keisti_eilutes_dydi(eil, stulp_sk);
            for (int stulp = 0; stulp < stulp_sk; stulp++){ // ciklas uzpildo eilute atsitiktiniais elementais
                naujas_elementas = rand() % 2; //atsitiktinis sveikas skaicius nuo 0 iki 1
                if (naujas_elementas == 1){
                    G(eil, stulp) = '1';

                }
                else {
                    G(eil, stulp) = '0';
                }
            }

            if (!tikrinti_priklausomuma(G)){
//              cout << "nulinis stulp\n";
                // istrinti paskutini stulpeli
                G.pasalinti_eilute(eil);
                //kartoti paskutine ciklo dali
                eil--;
            }
        }
        return G;
}

bool tikrinti_priklausomuma(Matrica G){ // Funkcija realizuoja gauso eliminacija, padeda surasti kurie vektoriai yra tiesiskai nepriklausomi.
                                        // Parametras yra matrica sudaryta is vektoriu, kuriuos norima patikrinti
                                        // Rezultatas: meta klaida jei
    G.transponuoti();
    int stulp_sk = G.sizeX();
    int eil_sk = G.sizeY();
    int nenuline_eil;

    for (int stulp = 0; stulp < stulp_sk; ++stulp) {
        // randame stulpelio pivot:
        nenuline_eil = stulp;
        bool rasta = false;
        for (int eil = stulp; eil < eil_sk && !rasta; ++eil) {
            if ( G(eil, stulp) == '1' ){
                nenuline_eil = eil;
                rasta = true;
            }
        }
        if ( rasta){
            G.sukeisti_eilutes(stulp, nenuline_eil); // sukeiciame eilutes: pradine ir ta, kurioje rastas pivot
            for (int stulp_next = stulp+1; stulp_next < eil_sk; ++stulp_next) { // visoms eil zemiau pivot
                Elementas daugiklis = G(stulp_next, stulp);
                G.dauginti_eilute_ir_prideti(stulp, daugiklis,stulp_next);
            }
//          cout << "matrica po stulpelio " << stulp << " apdorojimo:\n";
//          G.print();
        }
        else {
            return false; // graziname pranesima, kad egzistuoja nulinis stulpelis
        }
    }
    return true;
}


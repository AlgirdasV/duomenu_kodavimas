#ifndef KUNAS_H
#define KUNAS_H
#include <string>
#include <vector>


typedef char Elementas;
typedef std::vector<Elementas> Vektorius;

    class Kunas{
    public:

        static Vektorius daugyba(Vektorius, Vektorius);
        static void print_vector(Vektorius);
        static Elementas el_sudetis(Elementas, Elementas);
        static Elementas el_atimtis(Elementas, Elementas);
        static Elementas el_daugyba(Elementas, Elementas);
        static void nulinti_vektoriu( Vektorius&);
        static bool lyginti(Vektorius , Vektorius );
        static void resize_2d_vector (std::vector< std::vector<Vektorius> > &, int, int );
        static Vektorius string_to_vector (std::string);//pavercia parametru perduota eilute
                                                        // i vektoriu ir ji grazina
        static Vektorius sudetis(Vektorius binary1, Vektorius binary2);
        static bool lygus_nuliui(Vektorius);
        static int rasti_svori(Vektorius);
        static void spausdinti_klaidas(Vektorius , Vektorius);
        static void sukeisti_simbolius(Vektorius&, int, int);
        static void dauginti_simboli_ir_prideti(Vektorius& , int ,Elementas , int );
    };



#endif

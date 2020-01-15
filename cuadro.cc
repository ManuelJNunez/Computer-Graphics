#include "cuadro.h"

Cuadro::Cuadro(float l){
    v.push_back(Tupla3f(-l/2, 0, -l/2));    v.push_back(Tupla3f(l/2, 0, -l/2));
    v.push_back(Tupla3f(-l/2, 0, l/2));     v.push_back(Tupla3f(l/2, 0, l/2));

    f.push_back(Tupla3i(1, 0, 2));          f.push_back(Tupla3i(1, 2, 3));

    ct.push_back(Tupla2f(0,0));             ct.push_back(Tupla2f(1,0));
    ct.push_back(Tupla2f(0,1));             ct.push_back(Tupla2f(1,1));
}
#include "cono.h"

Cono::Cono(int num_instancias_perf, float h, float r, bool duplicar_vertices, bool tapa_sup, bool tapa_inf){
    this->altura = h;
    this->radio = r;
    std::vector<Tupla3f> perfil_original;

    perfil_original.push_back(Tupla3f(0, 0, r));
    perfil_original.push_back(Tupla3f(0, h, 0));

    crearMalla(perfil_original, num_instancias_perf, duplicar_vertices, tapa_sup, tapa_inf);
}
#ifndef ESFERA_H
#define ESFERA_H

#include "aux.h"
#include "objrevolucion.h"

class Esfera: public ObjRevolucion{
    private:
        float radio;

    public:
        Esfera(int num_vert_perfil = 2, int num_instancias_perf = 20, float r = 1, bool duplicar_vertices = false, bool tapa_sup = true, bool tapa_inf = true);
        void calcularCoordTextura(std::vector<Tupla3f> perfil_original, int num_instancias);
};

#endif
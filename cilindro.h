#ifndef CILINDRO_H
#define CILINDRO_H

#include "aux.h"
#include "objrevolucion.h"

class Cilindro: public ObjRevolucion{
    private:
        float altura;
        float radio;

    public:
        Cilindro(int num_vert_perfil = 2, float h = 1, float r = 1, bool duplicar_vertices = false, bool tapa_sup = true, bool tapa_inf = true);
};

#endif

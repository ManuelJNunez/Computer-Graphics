#ifndef CONO_H
#define CONO_H

#include "aux.h"
#include "objrevolucion.h"

class Cono: public ObjRevolucion{
    private:
        float altura;
        float radio;

    public:
        Cono(int num_vert_perfil = 2, float h = 1, float r = 1, bool duplicar_vertices = false, bool tapa_sup = true, bool tapa_inf = true);
};

#endif
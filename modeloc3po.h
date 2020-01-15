#ifndef MODELOC3P0_H
#define MODELOC3P0_H

#include "aux.h"
#include "objply.h"
#include "materiales.h"

class ModeloC3PO{
    private:
        ObjPLY * cabeza;
        ObjPLY * body;
        ObjPLY * antebrazodcho;
        ObjPLY * brazodcho;
        ObjPLY * antebrazoizq;
        ObjPLY * brazoizq;
        ObjPLY * piernadcha;
        ObjPLY * piernaizq;

    public:
        ModeloC3PO();
        void draw(std::vector<bool> representacion, char modoDibujado, bool modoAjedrez);
};

#endif
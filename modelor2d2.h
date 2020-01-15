#ifndef MODELOR2D2_H
#define MODELOR2D2_H

#include "aux.h"
#include "objply.h"
#include "cilindro.h"
#include "materiales.h"

class ModeloR2D2{
    private:
        // Partes de R2D2
        ObjPLY * cabeza;
        ObjPLY * body;
        ObjPLY * patas;
        Cilindro * cilindro;

        // Grados de libertad
        float anguloBrazos;
        float anguloCabeza;
        float alturaCabeza;

    public:
        ModeloR2D2();
        void draw(std::vector<bool> representacion, char modoDibujado, bool modoAjedrez);
        void variarAnguloBrazos(float variacion);
        void variarAnguloCabeza(float variacion);
        void variarAlturaCabeza(float variacion);

        float getAlturaCabeza();
        float getAnguloBrazos();
        float getAnguloCabeza();

        void colorear(const Tupla3f& color);
};

#endif
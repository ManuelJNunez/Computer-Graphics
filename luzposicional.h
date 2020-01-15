#ifndef LUZ_POSICIONAL_H
#define LUZ_POSICIONAL_H

#include "luz.h"

class LuzPosicional: public Luz{
    public:
        LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
        void cambiarColores(Tupla4f colorEspecular, Tupla4f colorDifuso);
        void representar();
};

#endif
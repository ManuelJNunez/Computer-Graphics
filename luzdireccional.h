#ifndef LUZ_DIRECCIONAL_H
#define LUZ_DIRECCIONAL_H

#include "luz.h"

class LuzDireccional : public Luz{
    public:
        LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
        void variarAnguloAlpha(float incremento);
        void variarAnguloBeta(float incremento);
        void representar();
};

#endif
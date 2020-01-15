#ifndef LUZ_H
#define LUZ_H

#include "tuplasg.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Luz{
    protected:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente;
        Tupla4f colorDifuso;
        Tupla4f colorEspecular;

    public:
        Luz();
        void activar();
        void desactivar();
};

#endif
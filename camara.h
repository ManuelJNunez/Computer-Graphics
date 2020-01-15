#ifndef CAMARA_H
#define CAMARA_H

#include "aux.h"

typedef enum {ORTOGRAFICA, PERSPECTIVA} TipoCamara;

class Camara{
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;
        TipoCamara tipo;
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;

    public:
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up, TipoCamara tipo, float left, float right, float bottom, float top, float near, float far);
        void giroYOrbital(float anguloX);
        void giroYFirstPerson(float angle);
        void zoom(float factor);
        void setObserver();
        void setProyeccion();
        void setAt(Tupla3f at);
        void setEye(Tupla3f eye);
};

#endif
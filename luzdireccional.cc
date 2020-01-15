#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->posicion = Tupla4f(0,0,1,0);
    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    float px = (cos(incremento) * posicion(0)) + (sin(incremento) * this->posicion(2));
    float py = this->posicion(1);
    float pz = ((-sin(incremento)) * posicion(0)) + (cos(incremento) * this->posicion(2));

    this->posicion = Tupla4f(px, py, pz, 0);
}

void LuzDireccional::variarAnguloBeta(float incremento){
    float px = this->posicion(0);
    float py = (cos(incremento) * this->posicion(1)) - (sin(incremento) * this->posicion(2));
    float pz = (sin(incremento) * this->posicion(1)) + (cos(incremento) * this->posicion(2));

    this->posicion = Tupla4f(px, py, pz, 0);
}

void LuzDireccional::representar(){
    glLightfv(this->id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(this->id, GL_DIFFUSE, this->colorDifuso);
    glLightfv(this->id, GL_SPECULAR, this->colorEspecular);
    glLightfv(this->id, GL_POSITION, this->posicion);
}
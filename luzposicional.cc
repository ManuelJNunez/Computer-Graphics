#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->posicion = Tupla4f(posicion(0), posicion(1), posicion(2), 1.0);
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzPosicional::cambiarColores(Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzPosicional::representar(){
    glLightfv(this->id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(this->id, GL_DIFFUSE, this->colorDifuso);
    glLightfv(this->id, GL_SPECULAR, this->colorEspecular);
    glLightfv(this->id, GL_POSITION, this->posicion);
}
#include "luz.h"

void Luz::activar(){
    glEnable(this->id);
}

void Luz::desactivar(){
    glDisable(this->id);
}

Luz::Luz(){
    
}
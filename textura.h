#ifndef TEXTURA_H
#define TEXTURA_H

#include "aux.h"

class Textura{
    private:
        GLuint textura_id = 0;
        unsigned char * data;
        int width, height;

    public:
        Textura(std::string archivo);
        void activar();
};

#endif
#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){
    jpg::Imagen * pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();

    data = pimg->leerPixels();

    glGenTextures(1, &textura_id);
    glBindTexture(GL_TEXTURE_2D, textura_id);
}

void Textura::activar(){
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}
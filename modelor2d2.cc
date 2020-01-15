#include "modelor2d2.h"

ModeloR2D2::ModeloR2D2(){
    // Declaramos material y las partes de R2D2
    Material * m = new Plata();
    cabeza = new ObjPLY("./plys/r2d2cabeza.ply");
    body = new ObjPLY("./plys/r2d2body.ply");
    patas = new ObjPLY("./plys/r2d2patas.ply");
    cilindro = new Cilindro(20, 3.68, 0.25);

    // Inicializamos grados de libertad
    //anguloBrazos = -30;
    //anguloCuerpo = 15;
    //anguloCabeza = 20;
    //alturaCabeza = 0;
    anguloBrazos = 0;
    anguloCabeza = 0;
    alturaCabeza = 0;

    // Aplicamos el material a las partes de su cuerpo
    cabeza->setMaterial(m);
    body->setMaterial(m);
    patas->setMaterial(m);
}

void ModeloR2D2::draw(std::vector<bool> representacion, char modoDibujado, bool modoAjedrez){
    glPushMatrix();

        glPushMatrix();
            glTranslatef(0, alturaCabeza, 0);
            glRotatef(anguloCabeza, 0, 1, 0);
            
            cabeza->draw(representacion, modoDibujado, modoAjedrez);
            
            glPushMatrix();
                glTranslatef(0, 2.32, 0);
                cilindro->draw(representacion, modoDibujado, modoAjedrez);
            glPopMatrix();
        glPopMatrix();

        body->draw(representacion, modoDibujado, modoAjedrez);

        glPushMatrix();
            glTranslatef(0, 5.5, 0);
            glRotatef(anguloBrazos, 0, 0, 1);
            glTranslatef(0, -5.5, 0);
            patas->draw(representacion, modoDibujado, modoAjedrez);
        glPopMatrix();
    glPopMatrix();
}

void ModeloR2D2::variarAnguloBrazos(float variacion){
    this->anguloBrazos = fmod(anguloBrazos + variacion, 360);
}

void ModeloR2D2::variarAnguloCabeza(float variacion){
    this->anguloCabeza = fmod(anguloCabeza + variacion, 360);
}

void ModeloR2D2::variarAlturaCabeza(float variacion){
    this->alturaCabeza += variacion;
}

float ModeloR2D2::getAlturaCabeza(){
    return alturaCabeza;
}

float ModeloR2D2::getAnguloBrazos(){
    return anguloBrazos;
}

float ModeloR2D2::getAnguloCabeza(){
    return anguloCabeza;
}

void ModeloR2D2::colorear(const Tupla3f& color){
    cabeza->colorear(color);
    body->colorear(color);
    patas->colorear(color);
    cilindro->colorear(color);
}
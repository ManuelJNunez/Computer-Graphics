#include "modeloc3po.h"

ModeloC3PO::ModeloC3PO() {
    Material * m = new Dorado();
    cabeza = new ObjPLY("./plys/cabezaC3PO.ply");
    body = new ObjPLY("./plys/troncoC3PO.ply");
    antebrazodcho = new ObjPLY("./plys/antebrazodchoC3PO");
    brazodcho = new ObjPLY("./plys/brazodchoC3PO.ply");
    antebrazoizq = new ObjPLY("./plys/antebrazoizqC3PO");
    brazoizq  = new ObjPLY("./plys/brazoizqC3PO.ply");
    piernadcha = new ObjPLY("./plys/piernadchaC3PO.ply");
    piernaizq  = new ObjPLY("./plys/piernaizqC3PO.ply");

    cabeza->setMaterial(m);
    body->setMaterial(m);
    brazodcho->setMaterial(m);
    brazoizq->setMaterial(m);
    piernadcha->setMaterial(m);
    piernaizq->setMaterial(m);
}

void ModeloC3PO::draw(std::vector<bool> representacion, char modoDibujado, bool modoAjedrez){
    glPushMatrix();
        glRotatef(-90,1,0,0);

        cabeza->draw(representacion, modoDibujado, modoAjedrez);
        body->draw(representacion, modoDibujado, modoAjedrez);

        glPushMatrix();
            glTranslatef(-20.56, 0, 144.46);
            glRotatef(20,-1,0,0);
            glTranslatef(20.56, 0, -144.46);
            brazodcho->draw(representacion, modoDibujado, modoAjedrez);

            glPushMatrix();
                glTranslatef(-30.37, 0, 131.16);
                glRotatef(45,0,-1,0);
                glTranslatef(30.37, 0, -131.16);
            antebrazodcho->draw(representacion, modoDibujado, modoAjedrez);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(20.56, 0, 144.46);
            glRotatef(20,-1,0,0);
            glTranslatef(-20.56, 0, -144.46);
            brazoizq->draw(representacion, modoDibujado, modoAjedrez);

            glPushMatrix();
                glTranslatef(30.37, 0, 131.16);
                glRotatef(45,0,1,0);
                glTranslatef(-30.37, 0, -131.16);
            antebrazoizq->draw(representacion, modoDibujado, modoAjedrez);
            glPopMatrix();
        glPopMatrix();

        piernadcha->draw(representacion, modoDibujado, modoAjedrez);
        piernaizq->draw(representacion, modoDibujado, modoAjedrez);
    glPopMatrix();
}
#include "luzdireccional.h"
#include "luzposicional.h"

#ifndef LUCES
#define LUCES

class LuzVerdeDireccional: public LuzDireccional{
    public:
        LuzVerdeDireccional(): LuzDireccional(Tupla2f(0, 0), GL_LIGHT0, Tupla4f(0,0,0, 1), Tupla4f(0, 0, 0, 1), Tupla4f(0, 1, 0, 1)){
        }
};

class LuzVerdePosicional: public LuzPosicional{
    public:
        LuzVerdePosicional(): LuzPosicional(Tupla3f(0,0,0), GL_LIGHT1, Tupla4f(1, 1, 1, 1), Tupla4f(0.0, 0.0, 0.0, 1), Tupla4f(0, 1, 0, 1)){

        }
};

class LuzBlancaDireccional: public LuzDireccional{
    public:
        LuzBlancaDireccional(): LuzDireccional(Tupla2f(0, 0), GL_LIGHT0, Tupla4f(0,0,0, 1), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1)){
        }
};

class LuzBlancaPosicional: public LuzPosicional{
    public:
        LuzBlancaPosicional(): LuzPosicional(Tupla3f(0,100,0), GL_LIGHT1, Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1)){

        }
};

#endif
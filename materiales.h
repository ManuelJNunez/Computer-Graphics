#ifndef MATERIALES
#define MATERIALES

#include "material.h"

class BlancoGoma: public Material{
    public:
        BlancoGoma(): Material(Material(Tupla4f(0.05, 0.05, 0.05, 1), Tupla4f(0.5, 0.5, 0.5, 1), Tupla4f(0.7, 0.7, 0.7, 1), 100.0)){

        }
};

class NegroPlastico: public Material{
    public:
        NegroPlastico(): Material(Tupla4f(0.0, 0.0, 0.0, 1), Tupla4f(0.01, 0.01, 0.01, 1), Tupla4f(0.5, 0.5, 0.5, 1), 32.0){

        }
};

class Bronce: public Material{
    public:
        Bronce(): Material(Tupla4f(0.2125, 0.12175, 0.054, 1), Tupla4f(0.714, 0.4284, 0.18144, 1), Tupla4f(0.393548, 0.271906, 0.166721, 1), 25.6){

        }
};

class Plata: public Material{
    public:
        Plata(): Material(Tupla4f(0.19225, 0.19225, 0.19225, 1), Tupla4f(0.50754, 0.50754, 0.50754, 1), Tupla4f(0.508273, 0.508273, 0.508273, 1), 51.2){

        }
};

class Dorado: public Material{
    public:
        Dorado(): Material(Tupla4f(0.24725, 0.1995, 0.0745, 1), Tupla4f(0.75164, 0.60648, 0.22648, 1), Tupla4f(0.628281, 0.555802, 0.366065, 1), 51.2){
            
        }
};

class Amarillo: public Material{
    public:
        Amarillo(): Material(Tupla4f(0.24725, 0.1995, 0.0745, 1), Tupla4f(1, 1, 0, 1), Tupla4f(1, 1, 0, 1), 128){
            
        }
};

class Verde: public Material{
    public:
        Verde(): Material(Tupla4f(0.24725, 0.1995, 0.0745, 1), Tupla4f(0, 1, 0, 1), Tupla4f(0, 1, 0, 1), 128){
            
        }
};

class Jade: public Material{
    public:
        Jade(): Material(Tupla4f(0.135, 0.2225, 0.1575, 1), Tupla4f(0.54, 0.89, 0.63, 1), Tupla4f(0.316228, 0.316228, 0.316228, 1), 12.8){
            
        }
};

class Obsidiana: public Material{
    public:
        Obsidiana(): Material(Tupla4f(0.05375, 0.05, 0.06625, 1), Tupla4f(0.18275, 0.17, 0.22525, 1), Tupla4f(0.332741, 0.328634, 0.346435, 1), 51.2){
            
        }
};

#endif
// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   void draw_Ajedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(std::vector<bool> representacion,char modoDibujado, bool modoAjedrez);

   void colorear(const Tupla3f & color);

   void setMaterial(Material *& mat);

   void setTextura(Textura *& text);

   void vaciarColor();

   void dibuja();

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)


   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> c;
   std::vector<Tupla3f> nv;

   //Material de la malla
   Material * m = nullptr;

   //Textura de la malla y coordenadas de textura
   Textura * textura = nullptr;
   std::vector<Tupla2f> ct;

   //Variables y método necesario para el dibujado en modo diferido
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;
   GLuint id_vbo_col = 0;
   GLuint id_vbo_nv = 0;
   GLuint id_vbo_tex = 0;

   // Para visualización de tapas
   int num_tri = 0;

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
} ;


#endif

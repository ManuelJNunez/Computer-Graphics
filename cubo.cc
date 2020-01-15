#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.push_back(Tupla3f(0.0f, 0.0f, 0.0f));  v.push_back(Tupla3f(0.0f, 0.0f, lado));
   v.push_back(Tupla3f(lado, 0.0f, lado));  v.push_back(Tupla3f(lado, 0.0f, 0.0f));
   v.push_back(Tupla3f(0.0f, lado, 0.0f));  v.push_back(Tupla3f(0.0f, lado, lado));
   v.push_back(Tupla3f(lado, lado, lado));  v.push_back(Tupla3f(lado, lado, 0.0f));

   v.push_back(Tupla3f(0.0f, 0.0f, 0.0f));  v.push_back(Tupla3f(0.0f, 0.0f, lado));
   v.push_back(Tupla3f(lado, 0.0f, lado));  v.push_back(Tupla3f(lado, 0.0f, 0.0f));
   v.push_back(Tupla3f(0.0f, lado, 0.0f));  v.push_back(Tupla3f(0.0f, lado, lado));
   v.push_back(Tupla3f(lado, lado, lado));  v.push_back(Tupla3f(lado, lado, 0.0f));


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   //f.push_back(Tupla3i(2, 1, 0)); f.push_back(Tupla3i(3, 2, 0));
   f.push_back(Tupla3i(8,11,9));    f.push_back(Tupla3i(9,11,10));   
   //f.push_back(Tupla3i(5, 7, 4)); f.push_back(Tupla3i(5, 6, 7));
   f.push_back(Tupla3i(12,13,15));  f.push_back(Tupla3i(13,14,15));
   f.push_back(Tupla3i(5, 2, 6));   f.push_back(Tupla3i(5, 1, 2));
   f.push_back(Tupla3i(4, 7, 0));   f.push_back(Tupla3i(7, 3, 0));
   f.push_back(Tupla3i(2, 3, 7));   f.push_back(Tupla3i(2, 7, 6));
   f.push_back(Tupla3i(1, 5, 0));   f.push_back(Tupla3i(5, 4, 0));

   //Inicializar la tabla de coordenadas de textura   
   ct.push_back(Tupla2f(0,0));      ct.push_back(Tupla2f(1,0));
   ct.push_back(Tupla2f(0,0));      ct.push_back(Tupla2f(1,0));
   ct.push_back(Tupla2f(0,1));      ct.push_back(Tupla2f(1,1));
   ct.push_back(Tupla2f(0,1));      ct.push_back(Tupla2f(1,1));
   
   ct.push_back(Tupla2f(1,1));      ct.push_back(Tupla2f(1,0));
   ct.push_back(Tupla2f(0,0));      ct.push_back(Tupla2f(0,1));
   ct.push_back(Tupla2f(0,1));      ct.push_back(Tupla2f(1,1));
   ct.push_back(Tupla2f(1,0));      ct.push_back(Tupla2f(0,0));
}

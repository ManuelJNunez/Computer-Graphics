#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   // inicializar la tabla de vértices
   v.push_back(Tupla3f(lado/2, 0, lado)); v.push_back(Tupla3f(0, 0, 0));
   v.push_back(Tupla3f(lado/2, lado, lado/2));  v.push_back(Tupla3f(lado, 0, 0));

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.push_back(Tupla3i(1, 0, 2));   f.push_back(Tupla3i(2, 0, 3));
   f.push_back(Tupla3i(1, 3, 0));   f.push_back(Tupla3i(1, 2, 3));
}
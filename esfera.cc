#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float r, bool duplicar_vertices, bool tapa_sup, bool tapa_inf){
    this->radio = r;
    std::vector<Tupla3f> perfil_original;

    perfil_original.push_back(Tupla3f(0 ,-r, 0));

    for(int i = 1; i < num_vert_perfil; ++i){
        float x = 0;
        float y = cos(M_PI * i / num_vert_perfil) * (-r);
        float z = sin(M_PI * i / num_vert_perfil) * (-r);

        perfil_original.push_back(Tupla3f(x, y, z));
    }

    perfil_original.push_back(Tupla3f(0 ,r, 0));

    crearMalla(perfil_original, num_instancias_perf, duplicar_vertices, tapa_sup, tapa_inf);

    calcularCoordTextura(perfil_original, num_instancias_perf);
}

void Esfera::calcularCoordTextura(std::vector<Tupla3f> perfil_original, int num_instancias){
   std::vector<float> d;
   float sq, s, t;

   d.push_back(0);

   for(int i = 1; i < perfil_original.size(); ++i){
      sq = sqrt(pow(perfil_original[i](0) - perfil_original[i-1](0),2) + pow(perfil_original[i](1) - perfil_original[i-1](1),2) + pow(perfil_original[i](2) - perfil_original[i-1](2),2));
      d.push_back(d[i-1] + sq);
   }

   for(int i = 0; i <= num_instancias; ++i){
      s = i / float(num_instancias);
      for(int j = 1; j < perfil_original.size() -1; ++j){
         t = d[j] / d[perfil_original.size()-1];

         ct.push_back(Tupla2f(s, t));
      }
   }

   ct.push_back(Tupla2f(0.5,0));
   ct.push_back(Tupla2f(0.5,1));
}

#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool duplicar_vertices, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   std::vector<Tupla3f> perfil_original;

   ply::read_vertices(archivo, perfil_original);
   crearMalla(perfil_original, num_instancias, duplicar_vertices, tapa_inf, tapa_sup);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool duplicar_vertices, bool tapa_sup, bool tapa_inf) {
   this->v = perfil;

   crearMalla(this->v, num_instancias, duplicar_vertices, tapa_inf, tapa_sup);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool duplicar_vertices,  bool tapa_inf, bool tapa_sup) {
   if(perfil_original.size() > 0){
      this->n_instancias = num_instancias;

      Tupla3f tapainf, tapasup;
      bool abajoarriba = perfil_original[0](1) < perfil_original[1](1);
      
      // Detección existencia de tapas
      if(perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ){
         tapainf = perfil_original[0];
         perfil_original.erase(perfil_original.begin());
      }else{
         tapainf = Tupla3f(0 , perfil_original[0](1), 0);
      }

      if(perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0 ){
         tapasup = perfil_original[perfil_original.size()-1];
         perfil_original.pop_back();
      }else{
         tapasup = Tupla3f(0, perfil_original[perfil_original.size()-1](1), 0);
      }

      // Generación de vértices
      for(int i = 0; i < num_instancias; ++i){
         for(int j = 0; j < perfil_original.size(); ++j){
            float x = (perfil_original[j](0) * cos(2*M_PI * i / num_instancias)) + (perfil_original[j](2) * sin(2*M_PI * i / num_instancias));
            float y = perfil_original[j](1);
            float z = (perfil_original[j](0) * (- sin(2*M_PI * i / num_instancias))) + (perfil_original[j](2) * cos(2*M_PI * i / num_instancias));

            this->v.push_back(Tupla3f(x, y, z));
         }
      }

      int num_instances_aux = num_instancias;

      if(duplicar_vertices){
         for(int i = 0; i < perfil_original.size(); ++i){
            v.push_back(perfil_original[i]);
         }

         num_instances_aux++;
      }

      // Generación de triángulos
      if(perfil_original.size() > 1){
         for(int i = 0; i < num_instancias; ++i){
            for(int j = 0; j < perfil_original.size() - 1; ++j){
               int a = perfil_original.size() * i + j;
               int b = perfil_original.size() * ((i+1) % num_instances_aux) + j;

               if(abajoarriba){
                  this->f.push_back(Tupla3i(a, b, b+1));
                  this->f.push_back(Tupla3i(a, b+1, a+1));
               }else{
                  this->f.push_back(Tupla3i(a, b+1, b));
                  this->f.push_back(Tupla3i(a, a+1, b+1));
               }
            }
         }
      }

      // Generación de tapas
      if(tapa_inf){
         v.push_back(tapainf);

         for(int i = 0; i < num_instancias - 1; ++i){
            if(abajoarriba)
               f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * (i+1), perfil_original.size() * i));
            else
               f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * i, perfil_original.size() * (i+1)));
         }

         Tupla3i carafinal;

         if(abajoarriba)
            carafinal = Tupla3i(v.size()-1, 0, perfil_original.size() * (num_instancias - 1));
         else
            carafinal = Tupla3i(v.size()-1, perfil_original.size() * (num_instancias - 1), 0);

         this->f.push_back(carafinal);
      }

      if(tapa_sup){
            v.push_back(tapasup);

            for(int i = 0; i < num_instancias - 1; ++i){
               if(abajoarriba)
                  f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * (i+1) - 1, perfil_original.size() * (i+2) - 1));
               else
                  f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * (i+2) - 1, perfil_original.size() * (i+1) - 1));
            }

            Tupla3i carafinal;
            
            if(abajoarriba)
               if(!duplicar_vertices)
                  carafinal = Tupla3i(v.size()-1, v.size() - 3, perfil_original.size() - 1);
               else
                  carafinal = Tupla3i(v.size() -1, v.size() - perfil_original.size() - 3, perfil_original.size() - 1);
            else
               carafinal = Tupla3i(v.size()-1, perfil_original.size() - 1, v.size() - perfil_original.size() - 3);

            this->f.push_back(carafinal);
      }
   }
}

void ObjRevolucion::drawRev(std::vector<bool> representacion,char modoDibujado, bool modoAjedrez){
   if(representacion[4]){
      this->num_tri = f.size() - this->n_instancias * 2;
   }else{
      this->num_tri = f.size();
   }

   this->draw(representacion, modoDibujado, modoAjedrez);
}

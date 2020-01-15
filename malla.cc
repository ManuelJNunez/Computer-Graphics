#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
   //Colores
   if(!c.empty()){
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3, GL_FLOAT, 0, c.data());
   }

   // Normales
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());

   // Vértices
   glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());

   //Textura
   if(ct.size() > 0){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   //Pintamos triángulos
   glDrawElements(GL_TRIANGLES, num_tri * 3, GL_UNSIGNED_INT, f.data());

   // Deshabilitamos todos los modos antes habilitados.
   if(!c.empty()){
      glDisableClientState(GL_COLOR_ARRAY);
   }
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState (GL_NORMAL_ARRAY);
   if(ct.size() > 0){
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   if( id_vbo_ver == 0 ) {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * sizeof(float) * 3, v.data());
   }

   if( id_vbo_tri == 0 ) {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(int) * 3, f.data());
   }

   if( id_vbo_col == 0 ) {
      id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c.size() * sizeof(float) * 3, c.data());
   }

   if( id_vbo_nv == 0 ) {
      id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, nv.size() * sizeof(float) * 3, nv.data());
   }

   if( id_vbo_tex == 0 && !ct.empty() ) {
      id_vbo_tex = CrearVBO(GL_ARRAY_BUFFER, ct.size() * sizeof(float) * 2, ct.data());
   }

   glEnableClientState( GL_VERTEX_ARRAY);
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
   glVertexPointer( 3, GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );

   glEnableClientState(GL_COLOR_ARRAY);
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
   glColorPointer( 3, GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );

   glEnableClientState(GL_NORMAL_ARRAY);
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nv );
   glNormalPointer( GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );

   if(ct.size() > 0){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_tex );
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      glBindBuffer( GL_ARRAY_BUFFER, 0 );
   }

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );
   glDrawElements( GL_TRIANGLES, 3* num_tri, GL_UNSIGNED_INT, 0 );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Malla3D::draw_Ajedrez(){
   std::vector<Tupla3i> pares, impares;

   for(int i = 0; i < f.size(); ++i){
      if(i % 2 == 0)
         pares.push_back(f[i]);
      else
         impares.push_back(f[i]);
   }

   colorear(Tupla3f(0, 0, 1));
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data());
   glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
   glDrawElements(GL_TRIANGLES, pares.size() * 3, GL_UNSIGNED_INT, pares.data());
   glDisableClientState(GL_VERTEX_ARRAY | GL_COLOR_ARRAY);

   colorear(Tupla3f(0, 1, 0));
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data());
   glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
   glDrawElements(GL_TRIANGLES, impares.size() * 3, GL_UNSIGNED_INT, impares.data());
   glDisableClientState(GL_VERTEX_ARRAY | GL_COLOR_ARRAY);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(std::vector<bool> representacion, char modoDibujado, bool modoAjedrez)
{
   //Si no se han generado las normales, se generan
   if(nv.size() == 0){
      calcular_normales();
   }

   //Si hay material, se aplica
   if(m){
      m->aplicar();
   }

   //Si no se ha calculado antes el número de triángulos
   if(num_tri == 0){
      num_tri = f.size();
   }

   // completar .....(práctica 1)
   // Si no se ha activado el modo ajedrez o la luz, mostrar en sólido, líneas o puntos.
   if(ct.size() > 0 && textura != 0){
      glEnable(GL_TEXTURE_2D);
      textura->activar();

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if( modoDibujado == 'D' )
            draw_ModoDiferido();
         else if (modoDibujado == 'I')
            draw_ModoInmediato();
      
      glDisable(GL_TEXTURE_2D);
   }else if(!modoAjedrez && !representacion[3]){
      glDisable(GL_LIGHTING);

      // Si activo el modo puntos
      if(representacion[0]){
         
         if(c.size() == 0)
            colorear(Tupla3f(0, 0, 1));
         
         glPointSize(2);
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         
         if( modoDibujado == 'D' )
            draw_ModoDiferido();
         else if (modoDibujado == 'I')
            draw_ModoInmediato();
      }

      // Si activo el modo línea
      if(representacion[1]){
         
         if(c.size() == 0)
            colorear(Tupla3f(1, 0.5, 0));
         
         glLineWidth(1);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

         if( modoDibujado == 'D' )
            draw_ModoDiferido();
         else if (modoDibujado == 'I')
            draw_ModoInmediato();

         glLineWidth(1);
      }

      // Si activo el modo sólido
      if(representacion[2]){

         glShadeModel(GL_SMOOTH);
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         
         if( modoDibujado == 'D' )
            draw_ModoDiferido();
         else if (modoDibujado == 'I')
            draw_ModoInmediato();
      }

   // SI activo el ajedrez, ignorar los demás
   }else if(modoAjedrez){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      draw_Ajedrez();

   // SI activo las luces, ignorar lo demás (puntos, sólido, líneas)
   }else if(representacion[3]){
      glShadeModel(GL_SMOOTH);
      glEnable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if( modoDibujado == 'D' )
         draw_ModoDiferido();
      else if (modoDibujado == 'I')
         draw_ModoInmediato();
   }
}

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ) {
   GLuint id_vbo ;
   glGenBuffers( 1, & id_vbo );
   glBindBuffer( tipo_vbo, id_vbo );
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0 );
   return id_vbo;
}

void Malla3D::colorear(const Tupla3f & color){
   c.clear();
   for(int i = 0; i < v.size(); ++i){
      c.push_back(color);
   }
}

void Malla3D::calcular_normales(){
   nv.clear();
   Tupla3f p, q, r, a, b, mc;
   std::vector<Tupla3f> nc;
   for(int i = 0; i < f.size(); ++i){
      p = v[f[i](0)];
      q = v[f[i](1)];
      r = v[f[i](2)];

      a = (q - p);
      b = (r - p);

      mc = a.cross(b);

      nc.push_back(mc.normalized());
   }

   for(int i = 0; i < v.size(); ++i){
      nv.push_back(Tupla3f(0, 0, 0));
   }

   for(int i = 0; i < f.size(); ++i){
      nv[f[i](0)] = nv[f[i](0)] + nc[i];
      nv[f[i](1)] = nv[f[i](1)] + nc[i];
      nv[f[i](2)] = nv[f[i](2)] + nc[i];
   }

   for(int i = 0; i < f.size(); ++i){
      nv[f[i](0)] = nv[f[i](0)].normalized();
      nv[f[i](1)] = nv[f[i](1)].normalized();
      nv[f[i](2)] = nv[f[i](2)].normalized();
   }
}

void Malla3D::setMaterial(Material *& mat){
   this->m = mat;
}

void Malla3D::setTextura(Textura *& text){
   this->textura = text;
}

void Malla3D::vaciarColor(){
   c.clear();
}

void Malla3D::dibuja()
{
   // Vértices
   glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());

   //Pintamos triángulos
   glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());

   // Deshabilitamos todos los modos antes habilitados.
   glDisableClientState(GL_VERTEX_ARRAY);
}

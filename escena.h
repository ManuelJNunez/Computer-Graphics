#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "cono.h"
#include "cilindro.h"
#include "cilindro.h"
#include "esfera.h"
#include "luces.h"
#include "materiales.h"
#include "modelor2d2.h"
#include "modeloc3po.h"
#include "map"
#include "cuadro.h"
#include "textura.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, SELGRADO, SELAUTOANIM, SELCAMARA} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection();
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   std::map<const char*, std::pair<bool, Malla3D*> > objetos;
   
   // Variables para guardar datos sobre la representación
   std::vector<bool> representacion;
   char modoDibujado;
   bool ajedrez;
   bool verTapas = true;

   // Map con la información con el estado de las luces
   std::map<const char*, std::pair<bool, Luz*> > luces;

   // Para variar el ángulo de las luces
   bool variarAlpha = false;

   // Materiales
   std::vector<Material*> materiales;

   // Para ver modelos jerárquicos o no
   bool verModJer = false;

   // Modelos jerárquicos
   ModeloR2D2 r2d2;
   ModeloC3PO c3po;

   // Selección de grado de libertad
   int gradSelec;

   // Texturas
   std::vector<Textura*> texturas;

   // Variables de control de animación automática
   double velocidad;
   bool animarLuzPuntual;
   int cambioLuz;
   bool levantarCabeza;
   bool bajarCabeza;
   bool idle;
   float idling;
   float angulor2;
   bool girando1;
   bool prepararr2;
   bool andardistancia1;
   float totalandado;
   float zcoordr2;
   bool girando2;
   bool andardistancia2;
   float xcoordr2;
   bool girarcabeza;
   float angulocuerpor2;

   //Cámaras de la escena
   std::vector<Camara*> camaras;
   std::vector<int> objCamara;
   int camaraActiva;
   static const int ESFERA = 1, CUBO = 2;

   //Variables para controlar la interacción de las cámaras con el ratón
   bool MOVIENDO_CAMARA;
   int xant, yant;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight );

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void animarModelosJerarquicos();

    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    int procesaClick(int x, int y);
    void dibujaSeleccion();
    void posicionRaton(int x, int y);
};
#endif

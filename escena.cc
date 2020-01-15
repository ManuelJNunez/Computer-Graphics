

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0;
    Observer_angle_y  = 0.0;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    // Cargamos los objetos en el map
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("cubo", std::pair<bool,Malla3D*>(false, new Cubo(25))));
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("cuadro", std::pair<bool,Malla3D*>(true, new Cuadro(25))));
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("tetraedro", std::pair<bool,Malla3D*>(false, new Tetraedro(25))));
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("cono", std::pair<bool,Malla3D*>(false, new Cono(25, 25, 10))));
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("cilindro", std::pair<bool,Malla3D*>(false, new Cilindro(25, 187.5, 10))));
    objetos.insert(std::pair<const char*, std::pair<bool, Malla3D*> >("esfera", std::pair<bool,Malla3D*>(false, new Esfera(25, 25, 15, true))));

    // Cargamos las luces en el map
    luces.insert(std::pair<const char*, std::pair<bool, Luz*> >("verdedir", std::pair<bool,Luz*>(false, new LuzVerdeDireccional())));
    luces.insert(std::pair<const char*, std::pair<bool, Luz*> >("verdepos", std::pair<bool,Luz*>(false, new LuzVerdePosicional())));
    luces.insert(std::pair<const char*, std::pair<bool, Luz*> >("blancadir", std::pair<bool,Luz*>(false, new LuzBlancaDireccional())));
    luces.insert(std::pair<const char*, std::pair<bool, Luz*> >("blancapos", std::pair<bool,Luz*>(false, new LuzBlancaPosicional())));
    
    // Reservamos memoria e inicializamos los datos sobre la visualización de los objetos
    representacion.resize(5);
    representacion[2] = true;
    modoDibujado = 'I';
    ajedrez = false;

    // Declaramos los materiales introduciéndolos en su vector correspondiente
    materiales.push_back(new BlancoGoma());
    materiales.push_back(new NegroPlastico());
    materiales.push_back(new Bronce());
    materiales.push_back(new Jade());
    materiales.push_back(new Amarillo());
    materiales.push_back(new Verde());

    //Inicializamos el grado de libertad escogido a uno imposible para que el usuario deba escoger.
    gradSelec = 10;

    // Declaramos las texturas y las introducimos al vector correspondiente
    texturas.push_back(new Textura("./textures/crate_opt.jpg"));
    texturas.push_back(new Textura("./textures/MetalPlates01_opt.jpg"));
    texturas.push_back(new Textura("./textures/spheretext-min.jpg"));

    // Contador para que haya un tiempo entre los cambios de color de la luz
    cambioLuz = 0;

    // Velocidad de animación del modelo jerárquico
    velocidad = 0.01;

    // Booleanos para controlar el orden de las acciones de R2D2
    animarLuzPuntual = false;
    levantarCabeza = true;
    bajarCabeza = false;
    idle = false;
    prepararr2 = false;
    andardistancia1 = false;

    // Valores para controlar algunos parámetros de la animación en la escena
    idling = 0;
    angulor2 = 180;
    totalandado = 0;
    zcoordr2 = 12.5;
    xcoordr2 = 135;
    angulocuerpor2 = 0;

    // Inicialización de variables que controlan la interacción con la cámara
    MOVIENDO_CAMARA = false;
    xant = 0;
    yant = 0;

    // Coloreo de todas las figuras
    r2d2.colorear(Tupla3f(0,0,1));
    objetos["cubo"].second->colorear(Tupla3f(1,1,1));
    objetos["cuadro"].second->colorear(Tupla3f(1,1,1));
    objetos["cono"].second->colorear(Tupla3f(0.4, 0.6, 0.3));
    objetos["cilindro"].second->colorear(Tupla3f(0, 1, 1));
    objetos["tetraedro"].second->colorear(Tupla3f(0, 0.1, 0.3));
    objetos["esfera"].second->colorear(Tupla3f(1,1,1));

    // Hacemos set de los materiales
    objetos["cubo"].second->setMaterial(materiales[0]);
    objetos["cuadro"].second->setMaterial(materiales[0]);
    objetos["cuadro"].second->setMaterial(materiales[0]);
    objetos["tetraedro"].second->setMaterial(materiales[2]);
    objetos["cono"].second->setMaterial(materiales[3]);
    objetos["cilindro"].second->setMaterial(materiales[1]);
    objetos["esfera"].second->setMaterial(materiales[0]);

    // Hacemos set de las texturas
    objetos["cubo"].second->setTextura(texturas[0]);
    objetos["cuadro"].second->setTextura(texturas[1]);
    objetos["esfera"].second->setTextura(texturas[2]);

    objCamara.resize(3);
    objCamara[0] = 0;
    objCamara[1] = 0;
    objCamara[2] = 0;

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 0.0, 0.0, 0.0, 0.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);

	Width  = UI_window_width/2;
	Height = UI_window_height/2;

   camaras.push_back(new Camara(Tupla3f(93.75,100,88.75), Tupla3f(0,75,0), Tupla3f(0,1,0), PERSPECTIVA, -Width/6.7, Width/6.7, -Height/6.7, Height/6.7, 15, 500));
   camaras.push_back(new Camara(Tupla3f(93.75,100,88.75), Tupla3f(0,75,0), Tupla3f(0,1,0), ORTOGRAFICA, -Width/6, Width/6, -Height/6, Height/6, 15, 500));
   camaras.push_back(new Camara(Tupla3f(-93.75,100,-88.75), Tupla3f(0,75,0), Tupla3f(0,1,0), ORTOGRAFICA, -Width/6, Width/6, -Height/6, Height/6, 15, 500));
   camaraActiva = 0;

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   // Dibujamos los ejer de forma que no les afecte a luz
   glDisable(GL_LIGHTING);

   ejes.draw();

   if(representacion[3]){
     glEnable(GL_LIGHTING);
   }
    
    // Situando objetos que el usuarios quiere ver en la escena con su color y material
    if(objetos["cubo"].first){
      glPushMatrix();
         glTranslatef(100,0,0);
         objetos["cubo"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

   //Creación del fondo de la escena
    if(objetos["cuadro"].first){
      glPushMatrix();
         glScalef(15,0,15);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,187.5,0);
         glRotatef(180,1,0,0);
         glScalef(15,0,15);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,93.75,-187.5);
         glRotatef(90,1,0,0);
         glScalef(15,0,7.5);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-187.5,93.75,0);
         glRotatef(90,0,1,0);
         glRotatef(90,1,0,0);
         glScalef(15,0,7.5);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(187.5,93.75,0);
         glRotatef(-90,0,1,0);
         glRotatef(90,1,0,0);
         glScalef(15,0,7.5);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,93.75,187.5);
         glRotatef(180,0,1,0);
         glRotatef(90,1,0,0);
         glScalef(15,0,7.5);
         objetos["cuadro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

    if(objetos["tetraedro"].first){
      glPushMatrix();
         glTranslatef(-100,0,25);
         objetos["tetraedro"].second->draw(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

    if(objetos["cono"].first){
      glPushMatrix();
         glTranslatef(-40,0,0);
         ((ObjRevolucion*&)objetos["cono"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

    if(objetos["cilindro"].first){
       glPushMatrix();
         glTranslatef(-93.75,0,-93.75);
         ((ObjRevolucion*&)objetos["cilindro"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(93.75,0,-93.75);
         ((ObjRevolucion*&)objetos["cilindro"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(93.75,0,93.75);
         ((ObjRevolucion*&)objetos["cilindro"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-93.75,0,93.75);
         ((ObjRevolucion*&)objetos["cilindro"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

    if(objetos["esfera"].first){
       glPushMatrix();
         glTranslatef(-40,35,0);
         ((ObjRevolucion*&)objetos["esfera"].second)->drawRev(representacion, modoDibujado, ajedrez);
      glPopMatrix();
    }

    if(verModJer){
       glPushMatrix();
         //glTranslatef(50, 0, 0);
         glTranslatef(xcoordr2, 0, zcoordr2);
         glScalef(2.5, 2.5, 2.5);
         glRotatef(angulor2, 0, 1, 0);
         glRotatef(angulocuerpor2, 0, 0, 1);
         r2d2.draw(representacion, modoDibujado, ajedrez);
       glPopMatrix();
       glPushMatrix();
         glTranslatef(-20,0,0);
         glScalef(0.2, 0.2, 0.2);
         glRotatef(-90, 0, 1, 0);
         c3po.draw(representacion, modoDibujado, ajedrez);
       glPopMatrix();
    }

   //Situando las luces que el usuario desea ver en la escena
   if(luces["verdedir"].first){
      ((LuzDireccional*&)luces["verdedir"].second)->representar();
   }

   if(luces["verdepos"].first){
      ((LuzPosicional*&)luces["verdepos"].second)->representar();
   }
    
   if(luces["blancadir"].first){
      ((LuzDireccional*&)luces["blancadir"].second)->representar();
   }

   if(luces["blancapos"].first){
      ((LuzPosicional*&)luces["blancapos"].second)->representar();
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   //cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   string mensaje;

   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            modoMenu=NADA;

            mensaje = "No estás en ningún modo, seleccione el modo al que desea entrar:\n";
            mensaje += "\t·Tecla 'O' para entrar al modo de selección de objetos\n";
            mensaje += "\t·Tecla 'V' para entrar al modo de selección de visualización\n";
            mensaje += "\t·Tecla 'A' para activar/desactivar el modo de animación automática de los modelos jerárquicos\n";
            mensaje += "\t·Tecla 'M' para entrar al modo de animación manual de los modelos jerárquicos\n";
            mensaje += "\t·Tecla 'D' para entrar al modo de selección de dibujado\n";
            mensaje += "\t·Tecla 'Q' para salir del programa\n";      
         }else {
            salir=true ;
         }
      break;

      case 'O' :
      cout << modoMenu << endl;
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         mensaje = "Has entrado en el modo de selección de objeto, tienes las siguientes opciones disponibles:\n";
         mensaje += "\t·Tecla 'C' se visualiza/oculta el Cubo\n";
         mensaje += "\t·Tecla 'T' se visualiza/oculta el Tetraedro\n";
         mensaje += "\t·Tecla '/' se visualiza/oculta el Cono\n";
         mensaje += "\t·Tecla '(' se visualiza/oculta el Cilindro\n";
         mensaje += "\t·Tecla ')' se visualiza/oculta la Esfera\n";
         mensaje += "\t·Tecla 'J' se visualizan/ocultan los modelos jerárquicos\n";
         mensaje += "\t·Tecla 'Q' para salir del modo de selección de objeto\n";
      break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu = SELVISUALIZACION;

         mensaje = "Has entrado en el modo de selección de visualización, tienes las siguientes opciones disponibles:\n";
         mensaje += "\t·Tecla 'P' se activa/desactiva la visualización en modo puntos y se desactiva la iluminación.\n";
         mensaje += "\t·Tecla 'L' se activa/desactiva la visualización en modo líneas y se desactiva la iluminación.\n";
         mensaje += "\t·Tecla 'S' se activa/desactiva la visualización en modo sólido y se desactiva la iluminación.\n";
         mensaje += "\t·Tecla 'A' se activa/desactiva la visualización en modo ajedrez.\n";
         mensaje += "\t·Tecla 'I' se activa la visualización con iluminación.\n";
         mensaje += "\t·Tecla 'T' se activa/desactiva la visualización de las tapas.\n";
         mensaje += "\t·Tecla 'Q' para salir del modo de selección de visualización.\n";
      break ;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         mensaje = "Has entrado en el modo de selección de dibujado, tienes las siguientes opciones disponibles:\n";
         mensaje += "\t·Tecla '1' modo inmediato\n";
         mensaje += "\t·Tecla '2' modo inmediato\n";
         mensaje += "\t·Tecla 'Q' para salir del modo de selección de dibujado.\n";
      break ;

      case 'M' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELGRADO;
         mensaje = "Has entrado en el modo de animación manual, tienes las siguientes opciones disponibles:\n";
         mensaje += "\t·Teclas 0-3 para seleccinar los grados de libertad de R2D2\n";
         mensaje += "\t·Tecla '+' para incrementar el grado el valor del grado de libertad seleccionado.\n";
         mensaje += "\t·Tecla '-' para decrementar el grado el valor del grado de libertad seleccionado.\n";
         mensaje += "\t·Tecla 'Q' para salir del modo de selección de dibujado.\n";
      break ;
         // COMPLETAR con los diferentes opciones de teclado

      // Objetos dibujados:
      case 'C' :
         if( modoMenu == SELOBJETO ){
            objetos["cubo"].first = !objetos["cubo"].first;
         }else{
            modoMenu = SELCAMARA;
            mensaje = "Has entrado en el modo de selección de cámaras, tienes las siguientes opciones disponibles:\n";
            mensaje += "\t·Teclas 0-2 para seleccinar las distintas cámaras.\n";
            mensaje += "\t·Tecla 'Q' para salir del modo de selección de dibujado.\n";
         }
      break;

      case 'T' :
         if(modoMenu == SELVISUALIZACION){
            representacion[4] = !representacion[4];
         }
         else if( modoMenu == SELOBJETO ){
            objetos["tetraedro"].first = !objetos["tetraedro"].first;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case '/' :
         if( modoMenu == SELOBJETO ){
            objetos["cono"].first = !objetos["cono"].first;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case '(' :
         if( modoMenu == SELOBJETO ){
            objetos["cilindro"].first = !objetos["cilindro"].first;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case ')' :
         if( modoMenu == SELOBJETO ){
            objetos["esfera"].first = !objetos["esfera"].first;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case 'J':
         if(modoMenu == SELOBJETO){
            verModJer = !verModJer;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      // Opciones visualización:
      case 'P' :
         if(representacion[3]){
            animarLuzPuntual = !animarLuzPuntual;
         }else if(modoMenu == SELVISUALIZACION){
            representacion[0] = !representacion[0];
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case 'L':
         representacion[3] = false;
         if(modoMenu == SELVISUALIZACION){
            representacion[1] = !representacion[1];
         }else{
            cout << "Opción no válida" << endl;
         }
      break;
            
      case 'S':
         representacion[3] = false;
         if(modoMenu == SELVISUALIZACION){
            representacion[2] = !representacion[2];
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case 'A':
         if(modoMenu == NADA){
            modoMenu = SELAUTOANIM;
         }else if(modoMenu == SELAUTOANIM){
            modoMenu = NADA;
         }else if(representacion[3]){
            variarAlpha = true;
         }else if(modoMenu == SELVISUALIZACION){
            ajedrez = !ajedrez;
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case 'I':  
         if(modoMenu == SELVISUALIZACION){
            representacion[3] = true;

            mensaje = "Has activado la iluminación, puedes hacer lo siguiente:\n";
            mensaje += "\t·Teclas 0-3 para activar/desactivar cualquiera de las luces.\n";
            mensaje += "\t·Tecla 'A' para activar la variación del ángulo alfa de las luces direccionales.\n";
            mensaje += "\t·Tecla 'B' para activar la variación del ángulo beta de las luces direccionales.\n";
            mensaje += "\t·Tecla '>' incrementa el ángulo escogido.\n";
            mensaje += "\t·Tecla '<' decrementa el ángulo escogido.\n";
            mensaje += "\t·Tecka 'P' se activa/desactiva la animación automática de la luz puntual.\n";
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case 'F':
         if(modoMenu == SELVISUALIZACION){
            representacion[4] = !representacion[4];
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      // Opciones dibujado y luces 1 y 2
      case '1':
         if(modoMenu == SELGRADO){
            gradSelec = 1;
         }else if(modoMenu == SELDIBUJADO){
            modoDibujado = 'I';

            mensaje = "Has activado el modo inmediato.\n";
         }else if(modoMenu == SELCAMARA){
            camaraActiva = 1;
            change_projection();
         }else if(representacion[3]){
            luces["verdepos"].first = !luces["verdepos"].first;

            if(luces["verdepos"].first){
               luces["verdepos"].second->activar();
               ((LuzPosicional*&)luces["verdepos"].second)->representar();
            }else{
               luces["verdepos"].second->desactivar();
            }
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case '2':
         if(modoMenu == SELGRADO){
            gradSelec = 2;
         }else if(modoMenu == SELDIBUJADO){
            modoDibujado = 'D';
            
            mensaje = "Has activado el modo diferido.\n";
         }else if(modoMenu == SELVISUALIZACION){
            luces["blancadir"].first = !luces["blancadir"].first;

            if(luces["blancadir"].first){
               luces["blancadir"].second->activar();
               ((LuzDireccional*&)luces["blancadir"].second)->representar();
            }else{
               luces["blancadir"].second->desactivar();
            }
         }else if(SELCAMARA){
            camaraActiva = 2;
            change_projection();
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      // Luces y grados de libertad 0 y 3
      case '0':
         if(modoMenu == SELGRADO){
            gradSelec = 0;
         }else if(modoMenu == SELVISUALIZACION){
            luces["verdedir"].first = !luces["verdedir"].first;

            if(luces["verdedir"].first){
               luces["verdedir"].second->activar();
               ((LuzDireccional*&)luces["verdedir"].second)->representar();
            }else{
               luces["verdedir"].second->desactivar();
            }
         }else if(modoMenu == SELCAMARA){
            camaraActiva = 0;
            change_projection();
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      case '3':
         if(modoMenu == SELVISUALIZACION){
            luces["blancapos"].first = !luces["blancapos"].first;

            if(luces["blancapos"].first){
               luces["blancapos"].second->activar();
               ((LuzPosicional*&)luces["blancapos"].second)->representar();
            }else{
               luces["blancapos"].second->desactivar();
            }
         }else{
            cout << "Opción no válida" << endl;
         }
      break;

      // Alterar ángulo luz direccional
      case 'B':
         if(representacion[3]){
            variarAlpha = false;
         }
      break;

      case '<':
         if(variarAlpha){
            ((LuzDireccional*&)luces["verdedir"].second)->variarAnguloAlpha(-0.1);
            ((LuzDireccional*&)luces["blancadir"].second)->variarAnguloAlpha(-0.1);
         }else{
            ((LuzDireccional*&)luces["verdedir"].second)->variarAnguloBeta(-0.1);
            ((LuzDireccional*&)luces["blancadir"].second)->variarAnguloBeta(-0.1);
         }
      break;

      case '>':
         if(variarAlpha){
            ((LuzDireccional*&)luces["verdedir"].second)->variarAnguloAlpha(0.1);
            ((LuzDireccional*&)luces["blancadir"].second)->variarAnguloAlpha(0.1);
         }else{
            ((LuzDireccional*&)luces["verdedir"].second)->variarAnguloBeta(0.1);
            ((LuzDireccional*&)luces["blancadir"].second)->variarAnguloBeta(0.1);
         }
      break;

      // Teclas de variación de grados de libertad
      case '+':
         if(modoMenu == SELAUTOANIM){
            if(velocidad < 1){
               velocidad += 0.01;
            }
         }else if(gradSelec == 0){
            r2d2.variarAnguloBrazos(5);
         }else if(gradSelec == 1){
            r2d2.variarAnguloCabeza(5);
         }else if(gradSelec == 2){
            r2d2.variarAlturaCabeza(0.1);
         }
      break;

      case '-':
         if(modoMenu == SELAUTOANIM){
            if(velocidad >= 0.02){
               velocidad -= 0.01;
            }
         }else if(gradSelec == 0){
            r2d2.variarAnguloBrazos(-5);
         }else if(gradSelec == 1){
            r2d2.variarAnguloCabeza(-5);
         }else if(gradSelec == 2){
            r2d2.variarAlturaCabeza(-0.1);
         }

      break;

      default:
         cout << "Esa opción no existe\n";
   }

   if(mensaje.size() > 0){
      cout << mensaje;
   }

   if(modoMenu == SELCAMARA){
      if(objCamara[camaraActiva] == ESFERA){
         objetos["esfera"].second->colorear(Tupla3f(1, 1, 0));
         objetos["esfera"].second->setMaterial(materiales[4]);
      }else{
         objetos["esfera"].second->colorear(Tupla3f(1, 1, 1));
         objetos["esfera"].second->setMaterial(materiales[0]);
      }

      if(objCamara[camaraActiva] == CUBO){
         objetos["cubo"].second->colorear(Tupla3f(1, 1, 0));
         objetos["cubo"].second->setMaterial(materiales[4]);
      }else{
         objetos["cubo"].second->colorear(Tupla3f(1, 1, 1));
         objetos["cubo"].second->setMaterial(materiales[0]);
      }
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   /*glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );*/
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camaras[camaraActiva]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   /*glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
   */
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva]->setObserver();
}

void Escena::animarModelosJerarquicos(){
   const double AlturaMaxCabeza = 2.4, ANGULOGIRO = 90.0, ANGULOR2 = -30.0, DISTANCIA1 = 30.0, DISTANCIA2 = 160.0, ANGULOCABEZA = 20.0;
   const int TIEMPOIDLE = 50, TIEMPOAZUL = 50, TIEMPOROJA = 100;
   double incremento;

   if(modoMenu == SELAUTOANIM){
      if(idle && idling < TIEMPOIDLE){
         idling += TIEMPOIDLE * velocidad;
      }else if(idle){
         idling = 0;
         idle = false;
      }else if(r2d2.getAlturaCabeza() < AlturaMaxCabeza && levantarCabeza ){
         incremento = AlturaMaxCabeza * velocidad;
         r2d2.variarAlturaCabeza(incremento);
      }else if(levantarCabeza){
         levantarCabeza = false;
         idle = true;
         bajarCabeza = true;
      }else if(r2d2.getAlturaCabeza() > 0 && bajarCabeza){
         incremento = AlturaMaxCabeza * velocidad;
         r2d2.variarAlturaCabeza(-incremento);
      }else if(bajarCabeza){
         bajarCabeza = false;
         girando1 = true;
      }else if(girando1 && angulor2 > ANGULOGIRO){
         incremento = ANGULOGIRO * velocidad;
         angulor2 -= incremento;
      }else if(girando1){
         girando1 = false;
         prepararr2 = true;
      }else if(prepararr2 && r2d2.getAnguloBrazos() > ANGULOR2){
         incremento = (-ANGULOR2) * velocidad;
         r2d2.variarAnguloBrazos(-incremento);
         angulocuerpor2 += incremento/2;
      }else if(prepararr2){
         prepararr2 = false;
         andardistancia1 = true;
      }else if(andardistancia1 && totalandado < DISTANCIA1){
         incremento = DISTANCIA1 * velocidad;
         zcoordr2 -= incremento;
         totalandado += incremento;
      }else if(andardistancia1){
         totalandado = 0;
         andardistancia1 = false;
         girando2 = true;
      }else if(girando2 && angulor2 < ANGULOGIRO*2){
         incremento = ANGULOGIRO * velocidad;
         angulor2 += incremento;
      }else if(girando2){
         girando2 = false;
         andardistancia2 = true;
      }else if(andardistancia2 && totalandado < DISTANCIA2){
         incremento = DISTANCIA1 * velocidad;
         xcoordr2 -= incremento;
         totalandado += incremento;
      }else if(andardistancia2){
         andardistancia2 = false;
         girarcabeza = true;
      }else if(girarcabeza && r2d2.getAnguloCabeza() < ANGULOCABEZA){
         incremento = ANGULOCABEZA * velocidad;
         r2d2.variarAnguloCabeza(+incremento);
      }else if(girarcabeza){
         girarcabeza = false;
      }
   }

   //Animar la luz posicional 3 como si fuera una luz de emergencia
   if(luces["blancapos"].first && animarLuzPuntual){
      cambioLuz++;

      if(cambioLuz == TIEMPOAZUL){
         ((LuzPosicional*&)luces["blancapos"].second)->cambiarColores(Tupla4f(0,0,1,1), Tupla4f(0,0,1,1));
      }else if(cambioLuz == TIEMPOROJA){
         ((LuzPosicional*&)luces["blancapos"].second)->cambiarColores(Tupla4f(1,0,0,1), Tupla4f(1,0,0,1));
         cambioLuz = 0;
      }
   }
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   if(boton == GLUT_LEFT_BUTTON){
      if(estado == GLUT_DOWN){
         dibujaSeleccion();
         int objSeleccionado = procesaClick(x,y);

         std::cout << objSeleccionado << std::endl;

         if(objSeleccionado == ESFERA){
            if(objSeleccionado != objCamara[camaraActiva]){
               camaras[camaraActiva]->setAt(Tupla3f(-25, 40, 0));
               objCamara[camaraActiva] = ESFERA;
            }else{
               camaras[camaraActiva]->setAt(Tupla3f(0, 75, 0));
               objCamara[camaraActiva] = 0;
               objetos["esfera"].second->colorear(Tupla3f(1,1,1));
               objetos["esfera"].second->setMaterial(materiales[0]);
            }
         }else if(objSeleccionado == CUBO){
            if(objSeleccionado != objCamara[camaraActiva]){
               camaras[camaraActiva]->setAt(Tupla3f(112.5, 12.5, 0));
               objCamara[camaraActiva] = CUBO;
            }else{
               camaras[camaraActiva]->setAt(Tupla3f(0, 75, 0));
               objCamara[camaraActiva] = 0;
               objetos["cubo"].second->colorear(Tupla3f(1,1,1));
               objetos["cubo"].second->setMaterial(materiales[0]);
            }
         }

         if(objCamara[camaraActiva] == ESFERA){
            objetos["esfera"].second->colorear(Tupla3f(1, 1, 0));
            objetos["esfera"].second->setMaterial(materiales[4]);
            objetos["cubo"].second->colorear(Tupla3f(1,1,1));
            objetos["cubo"].second->setMaterial(materiales[0]);
         }else if (objCamara[camaraActiva] == CUBO){
            objetos["cubo"].second->colorear(Tupla3f(1, 1, 0));
            objetos["cubo"].second->setMaterial(materiales[4]);
            objetos["esfera"].second->colorear(Tupla3f(1,1,1));
            objetos["esfera"].second->setMaterial(materiales[0]);

         }
      }
   }else if(boton == GLUT_RIGHT_BUTTON){
      if(estado == GLUT_DOWN){
         MOVIENDO_CAMARA = true;
      }else{
         MOVIENDO_CAMARA = false;
      }
   }else if( boton == 3){
      if(estado == GLUT_DOWN){
         camaras[camaraActiva]->zoom(0.9);
         change_projection();
      }
   }else if( boton == 4){
      if(estado == GLUT_DOWN){
         camaras[camaraActiva]->zoom(1.1);
         change_projection();
      }
   }
}

void Escena::ratonMovido(int x, int y){
   if(MOVIENDO_CAMARA){
      camaras[camaraActiva]->giroYOrbital(x-xant);
      xant = x;
      yant = y;
   }
}

int Escena::procesaClick(int x, int y){
   GLint viewport[4];
   GLubyte pixels[3];

   glGetIntegerv(GL_VIEWPORT, viewport);
   glReadBuffer(GL_BACK);
   glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixels);

   //printf("%d %d %d\n",pixels[0],pixels[1],pixels[2]);

   if(pixels[0] == 255)
      return 1;
   else if(pixels[1] == 255)
      return 2;

   return 0;
}

void Escena::dibujaSeleccion(){
   glDrawBuffer(GL_BACK);

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glDisable(GL_DITHER); // deshabilita el degradado
   glDisable(GL_LIGHTING);

      if(objetos["esfera"].first){
         glPushMatrix();
            glColor3ub(255, 0, 0);
            glTranslatef(-40,35,0);
            objetos["esfera"].second->dibuja();
         glPopMatrix();
      }

      if(objetos["cubo"].first){
         glPushMatrix();
            glColor3ub(0, 255, 0);
            glTranslatef(100,0,0);
            objetos["cubo"].second->dibuja();
         glPopMatrix();
      }

   glEnable(GL_DITHER);

   if(representacion[3])
      glEnable(GL_LIGHTING);
}

void Escena::posicionRaton(int x, int y){
   dibujaSeleccion();
   int objSeleccionado = procesaClick(x,y);

   //std::cout << objSeleccionado << std::endl;

   if(objSeleccionado == ESFERA){
      objetos["esfera"].second->colorear(Tupla3f(0, 1, 0));
      objetos["esfera"].second->setMaterial(materiales[5]);
   }else if (objCamara[camaraActiva] != ESFERA){
      objetos["esfera"].second->colorear(Tupla3f(1, 1, 1));
      objetos["esfera"].second->setMaterial(materiales[0]);
   }
   
   if (objSeleccionado == CUBO){
      objetos["cubo"].second->colorear(Tupla3f(0, 1, 0));
      objetos["cubo"].second->setMaterial(materiales[5]);
   }else if (objCamara[camaraActiva] != CUBO){
      objetos["cubo"].second->colorear(Tupla3f(1, 1, 1));
      objetos["cubo"].second->setMaterial(materiales[0]);
   }
}

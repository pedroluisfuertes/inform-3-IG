/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/


#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "ply_reader.h"
//#include "malla.h" // objetos: Cubo y otros....
#include <string>

using namespace std;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
    //num_texturas = 2; // se usa para cambiar las texturas 't'

    objetos.resize(num_objetos);
    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    objetos[CUBO] = new Cubo();
    objetos[TETRAEDRO] = new Tetraedro();
    objetos[CILINDRO] = new Cilindro(1,4);
    objetos[CONO] = new Cono(1,4);
    objetos[ESFERA] = new Esfera(40,40);
    objetos[OBJ_JERARQUICO] = new ObjJerarquico();

    /* Creamos las luces */
    // Luz 1    
    GLenum  luz_indice = GL_LIGHT0; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
    Tupla4f luz_posicion  = { 0.0, 0.0, 1.0, 0.0 }; // W  = 0 ==> luz en el infinito
    Tupla4f luz_ambiente  = { 0.0, 0.0, 0.0, 1.0 };
    Tupla4f luz_difusa    = { 1.0, 1.0, 1.0, 1.0 };
    Tupla4f luz_especular = { 1.0, 1.0, 1.0, 1.0 };
    luz1 = new Luz(luz_indice, luz_posicion, luz_ambiente, luz_difusa, luz_especular); 

    // Luz 2
    luz_indice = GL_LIGHT1; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
    luz_posicion  = { 0.0, 0.0, 4.0, 1.0 }; // w != 1 ==> Luz no en el infinito
    luz_ambiente  = { 0.0, 0.0, 0.0, 1.0 };
    luz_difusa    = { 1.0, 0.0, 1.0, 1.0 };
    luz_especular = { 1.0, 0.0, 1.0, 1.0 };
    luz2 = new Luz(luz_indice, luz_posicion, luz_ambiente, luz_difusa, luz_especular);

 
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	/*Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );*/
  redimensionar( UI_window_width, UI_window_height );

}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   if(objeto_actual == OBJ_PLY){
      if(leer_ply)
        leerPLY();
   }else{
      leer_ply = true;
  }
    objetos[objeto_actual]-> draw((ModoVis) modo_actual, modo_diferido);
  
}

void Escena::leerPLY(){
    
    cout << "Introduzca el nombre del archivo PLY que desa cargar" << endl;

    unsigned
      num_vertices = 0,
      num_caras   = 0 ;
      string ruta;
      getline (cin,ruta);
      if(ruta.find("/") == string::npos){
        ruta = "./plys/" + ruta; 
      }

      if(ruta.find(".") == 0){
        ruta += ".ply"; 
      }

    ply::leer_cabecera(ruta, num_vertices, num_caras);
    if(num_caras > 0){
      objetos[OBJ_PLY] = new ObjPLY(ruta);
    }else{
      objetos[OBJ_PLY] = new ObjRevolucion(ruta);
    }
    leer_ply = false;

    
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
  ejes.draw();
	dibujar_objeto_actual();
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
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   switch( tecla )
   {  
      case 'q' :
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'o' :
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "Objeto actual == " << objeto_actual << endl ;
         break ;
      case 'm' :
         modo_actual = (modo_actual+1) % num_modos ;
         cout << "Modo actual == " << modo_actual << endl ;
         break ;
      case 'v' :
      case 'V' : // Cambiamos la visualización
        modo_diferido = !modo_diferido;
        if(modo_diferido)
          cout << "Modo cambiado a diferido"<< endl ;
        else
          cout << "Modo cambiado a inmediato"<< endl ;
      break ;
      case 'c' :
      case 'C' :
        objetos[objeto_actual]->siguienteColor();
      break ;
      case 'M' :
        objetos[objeto_actual]->siguienteMaterial();
      break ;
      case 'p' :
      case 'P' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->siguienteParametro();
      break ;
      case 'a' :
      case 'A' :
        conmutarAnimaciones(); 
      break ;
      case 'u' :
      case 'U' :
        glShadeModel(GL_FLAT);
      break;
      case 'y' :
      case 'Y' :
        glShadeModel(GL_SMOOTH);
      break;
      case 'j' :
      case 'J' :
        luz1->activar();
      break ;
      case 'k' :
      case 'K' :
        luz2->activar();
      break ;
      case 'Z' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->incrementaParamAct();
      break ;
      case 'z' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->decrementaParamAct();
      break ;
      case '>' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->decelerar();
      break ;
      case '<' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->acelerar();
      break ;
      case '1' :
        objeto_actual = CUBO;
      break ;
      case '2' :
        objeto_actual = TETRAEDRO;
      break ;
      case '3' :
        objeto_actual = CILINDRO;
      break ;
      case '4' :
        objeto_actual = CONO;
      break ;
      case '5' :
        objeto_actual = ESFERA;
      break ;
      case '6' :
        objeto_actual = OBJ_PLY;
      break ;
      case '7' :
        objeto_actual = OBJ_JERARQUICO;
      break ;
      case '!' :
        modo_actual = 0;
      break ;
      case '"' :
        modo_actual = 3;
      break ;
      case '#' :
        glShadeModel(GL_FLAT);
      break ;
      case '$' :
        glShadeModel(GL_SMOOTH);
      break ;
      case '%' :
      break ;
      case '&' :
      break ;
      case '/' :
      break ;
      
   }
   return false ;
}

void Escena::conmutarAnimaciones(){
    activarAnimaciones = !activarAnimaciones;
    if(activarAnimaciones){
      if(objeto_actual == OBJ_JERARQUICO){
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->inicioAnimaciones( );
      }
        glutIdleFunc( funcion_desocupado );
        luz2->inicioGiro();
    }else{
      glutIdleFunc( nullptr );
    }
}

void Escena::mgeDesocupado(){
  if(objeto_actual == OBJ_JERARQUICO){
    static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->actualizarEstado( );
  }
  luz2->gira();
    glutPostRedisplay();
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

	//std::cout << "Tecla especial " << Tecla1 << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  const float wy = 0.84*Front_plane,
  wx = ratio_xy*wy ;
  glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
  Width = newWidth;
  Height = newHeight;
  change_projection( float(Width)/float(Height) );
  glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef( 0.0, 0.0, -Observer_distance );
  glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
  glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

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

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo            = new Cubo();
    tetraedro       = new Tetraedro();
    cilindro        = new Cilindro(1,4);
    cono            = new Cono(4,4);
    esfera          = new Esfera(40,40);
    objJerarquico   = new ObjJerarquico();
    

    objeto_actual = 0; 
    num_objetos = 7 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modos = 4;  // se usa añ pulsar la letra 'm' 

    num_colores = 3, 
    color_actual = 0;
    leer_ply = true;
    //num_texturas = 2; // se usa para cambiar las texturas 't'
    modo_diferido = false; 
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

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)

    // Definimos la textura
    

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
      case Objetos::CUBO:
         if ( cubo != nullptr )       cubo->      draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         break ;
      case 1:
         if ( tetraedro != nullptr )  tetraedro-> draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         break;
      case 2:
         if ( cilindro != nullptr )   cilindro->  draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         break;
      case 3:
         if ( cono != nullptr )       cono->      draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         break;
      case 4:
         if ( esfera != nullptr )     esfera->    draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         leer_ply = true; 
         break;
      case 5:
        /*if(leer_ply)
         if ( (es_ply && objPLY != nullptr) || (!es_ply && objRevolucion != nullptr) ){
          cout << "¿Quieres leer otro archivo PLY? (si/no)" << endl;
          string respues;
          getline (cin,respues);
          if(respues.find("s") != string::npos){
            cout << "Introduzca el nombre del archivo PLY que desa cargar" << endl;
            leerPLY();
          }
         }   
         else{
            cout << "Introduzca el nombre del archivo PLY que desa cargar" << endl;
            leerPLY();
         }
         if(es_ply){
           objPLY->       draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         }
         else{
           objRevolucion->draw((ModoVis) modo_actual, modo_diferido, color_actual) ;
         }
         leer_ply = false; */
         break;
      case 6:
           objJerarquico->draw((ModoVis) modo_actual, modo_diferido) ;
        break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

void Escena::leerPLY(){

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
      objPLY = new ObjPLY(ruta);
      es_ply = true; 
    }else{
      objRevolucion = new ObjRevolucion(ruta);

      es_ply = false; 
    }

    
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
      case 'M' :
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
        color_actual = (color_actual+1) % num_colores ;
        cout << "Color actual == " << color_actual << endl ;
      break ;
      case 'p' :
      case 'P' :
        objJerarquico->siguienteParametro();
      break ;
      case 'a' :
      case 'A' :
        conmutarAnimaciones(); 
      break ;
      case 'Z' :
        objJerarquico->incrementaParamAct();
      break ;
      case 'z' :
        objJerarquico->decrementaParamAct();
      break ;
      case '>' :
        objJerarquico->decelerar();
      break ;
      case '<' :
        objJerarquico->acelerar();
      break ;
      
   }
   return false ;
}

void Escena::conmutarAnimaciones(){

  activarAnimaciones = !activarAnimaciones; 
    if(objeto_actual == 6){
      activarAnimaciones = !activarAnimaciones;
      if(activarAnimaciones){
        objJerarquico->inicioAnimaciones( );
        glutIdleFunc( funcion_desocupado );
      }else{
        glutIdleFunc( nullptr );
      }

    }else{
      cout << "Este objeto no tiene animaciones" << endl; 
    }
        
}


void Escena::mgeDesocupado(){
  if(objeto_actual == 6){
    objJerarquico->actualizarEstado( );
    glutPostRedisplay();
  }
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

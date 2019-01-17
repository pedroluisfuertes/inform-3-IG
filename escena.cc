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
    objetos[CUBO] = new Cubo();
    objetos[TETRAEDRO] = new Tetraedro();
    objetos[CILINDRO] = new Cilindro(2,4);
    objetos[CONO] = new Cono(2,40);
    objetos[ESFERA] = new Esfera(40,40);
    objetos[OBJ_JERARQUICO] = new ObjJerarquico();
    objetos[CUADRO] = new Cuadro();

    /* Creamos las luces */
    // Luz 1    
    GLenum  luz_indice = GL_LIGHT0; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
    Tupla4f luz_posicion  = { 0.0, 1.0, 0.0, 0.0 }; // W  = 0 ==> luz en el infinito
    Tupla4f luz_ambiente  = { 0.0, 0.0, 0.0, 1.0 };
    Tupla4f luz_difusa    = { 1.0, 1.0, 1.0, 1.0 };
    Tupla4f luz_especular = { 1.0, 1.0, 1.0, 1.0 };
    luces.push_back(new Luz(luz_indice, luz_posicion, luz_ambiente, luz_difusa, luz_especular)); 

    // Luz 2
    luz_indice = GL_LIGHT1; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
    luz_posicion  = { 0.0, 2.0, 5.0, 1.0 }; // w != 1 ==> Luz no en el infinito
    luz_ambiente  = { 0.0, 0.0, 0.0, 1.0 };
    luz_difusa    = { 1.0, 0.0, 1.0, 1.0 };
    luz_especular = { 1.0, 0.0, 1.0, 1.0 };
    luces.push_back(new Luz(luz_indice, luz_posicion, luz_ambiente, luz_difusa, luz_especular));

    //Cámaras
    camaras.push_back(new Camara({20,  20, 20}, // Posición
                                 {0,0,0}, // Dirección
                                 {0,1,0}, // sentido
                                 -0.0084, 0.0084,   // Ancho
                                 -0.0084, 0.0084,   // Alto
                                 0.1,200, // Profundo
                                 false));  // Ortogonal

    camaras.push_back(new Camara({0, 20, 20}, // Posición
                                 {0,0,0}, // Dirección
                                 {0,1,0}, // sentido
                                 -0.0084, 0.0084,   // Ancho
                                 -0.0084, 0.0084,   // Alto
                                 2,200, // Profundo
                                 true)); // Ortogonal

    //camaras.push_back(new Camara());

	/*Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );*/
  //redimensionar( UI_window_width, UI_window_height );

}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************
void Escena::dibujar_luces(){
  if(glIsEnabled(GL_LIGHTING))
    for(Luz* luz:luces)
      if(luz->getActiva())
        luz->dibujar();
}

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   if(objeto_actual == OBJ_PLY){
      if(leer_ply)
        leerPLY();
   }else{
      leer_ply = true;
      
  }

//objetos[CUADRO] = new Cuadro();
  if(objeto_actual == SELECCION)
        dibuja_seleccion();
  else
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
  glEnable( GL_NORMALIZE );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	//change_observer();
  camaras[camaraActual]->draw();
  bool lucesEncendidas = glIsEnabled(GL_LIGHTING);
  if(lucesEncendidas)
    glDisable(GL_LIGHTING);
  ejes.draw();
  if(lucesEncendidas)
    glEnable(GL_LIGHTING);
  dibujar_luces();
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
         objeto_actual = (objeto_actual+1) % objetos.size() ;
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
        camaraActual = (camaraActual + 1) % camaras.size();
        cout << "Camara actual = " << camaraActual << endl; 
        //cout  << camaras.size() << endl; 
      break;
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
        luces[0]->activar();
      break ;
      case 'k' :
      case 'K' :
        luces[1]->activar();
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
      case '8' :
        objeto_actual = CUADRO;
      break ;
      case '9' :
        objeto_actual = SELECCION;
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
        luces[1]->inicioGiro();
    }else{
      glutIdleFunc( nullptr );
    }
}

void Escena::mgeDesocupado(){
  if(objeto_actual == OBJ_JERARQUICO){
    static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO])->actualizarEstado( );
  }
  luces[1]->gira();
  glutPostRedisplay();
}
//**************************************************************************

void Escena::mouseFunc(GLint button, GLint state, GLint x, GLint y){
  //cout << "button = " << button << endl; 
  //cout << "state = " << state << endl; 
  //cout << "x = " << x << endl; 
  //cout << "y = " << y << endl; 

  switch( button ){
  case GLUT_LEFT_BUTTON:
    // mover cámara
    botonIzquierdoPulsado = state == GLUT_DOWN;
    cx = x;
    cy = y;
  break;
  case GLUT_RIGHT_BUTTON:
    //Selecciono triángulo
  break;
  case 3:
    // Rueda del ratón zoon-
    camaras[camaraActual]->zoom(-1.2) ;
  break;
  case 4:
    // Rueda del ratón zoon+
    camaras[camaraActual]->zoom(+1.2) ;
  break;
  }

  
}
void Escena::motionFunc( int x, int y){
  //cout << "x = " << x << endl; 
  //cout << "y = " << y << endl;
  float ang = 1; 
  if(botonIzquierdoPulsado){
    if(cx > x)
      //Observer_angle_y--;
      camaras[camaraActual]->girarY(-ang);
    else if(cx < x)
      camaras[camaraActual]->girarY(ang);
      //Observer_angle_y++;

    if (cy > y)
      camaras[camaraActual]->girarX(-ang);
      //Observer_angle_x--;
    else if(cy < y)
      camaras[camaraActual]->girarX(ang);
      //Observer_angle_x++;

    cx = x;
    cy = y;

  }


}
void Escena::teclaEspecial( int Tecla1, int x, int y )
{
  float ang = 5; 
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
          camaras[camaraActual]->girarY(-ang);
         //Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
          camaras[camaraActual]->girarY(ang);
         //Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
        camaras[camaraActual]->girarX(ang);
         //Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
          camaras[camaraActual]->girarX(-ang);
         //Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActual]->zoom(1.2) ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActual]->zoom(-1.2) ;
         break;
	}

	//std::cout << "Tecla especial " << Tecla1 << std::endl;
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
  camaras[camaraActual]->redimensionar( newWidth, newHeight );
}
/*
void Escena::pick( int x, int y) {
  GLint hits, viewport[4];
  glGetIntegerv (GL_VIEWPORT, viewport);
  glSelectBuffer (BUFSIZE, selectBuf);
  glRenderMode (GL_SELECT);
  glInitNames();
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPickMatrix ( x, viewport[3] - y, 5.0, 5.0, viewport[0]);
  glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  dibujar();
  hits = glRenderMode (GL_RENDER);
  glMatrixMode (GL_PROJECTION); // Volvemos a poner el volumen original
  glLoadIdentity();
  glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  // interpretar el buffer de selección
  if (hits!=0)
  procesarHits(hits,selectBuf);
}

void Escena::procesarHits (GLint hits, GLuint buffer[])
{
  unsigned int i, j;
  GLuint names, *ptr, minZ,*ptrNames, numberOfNames;
  printf ("Primitivas intersecadas = %d\n", hits);
  ptr = (GLuint *) buffer;
  minZ = 0xffffffff;
  for (i = 0; i < hits; i++) {
    names = *ptr;
    ptr++;
    if (*ptr < minZ) {
      numberOfNames = names;
      minZ = *ptr;
      ptrNames = ptr+2;
    } 
    ptr += names+2;
  }
  printf ("Los nombres de la primitiva más cercana son: ");
  ptr = ptrNames;
  for (j = 0; j < numberOfNames; j++,ptr++) {
    printf ("%d ", *ptr);
  }
  printf ("\n");

}
*/
void Escena::dibuja_seleccion() {

  // Dibuja cuatro patos
  int n = 2; 
  int m = 3; 
  objetos_seleccion.resize(n*m);
  glDisable(GL_DITHER); // deshabilita el degradado
  for(int i = 0; i < n; i++){
    //cout << "i = " << i << endl; 
    for(int j = 0; j < m; j++) {
      glPushMatrix();
      switch (i*n+j) { // Un color para cada pato
        case 0: glColor3ub(255,0,0);break;
        case 1: glColor3ub(0,255,0);break;
        case 2: glColor3ub(0,0,255);break;
        case 3: glColor3ub(250,0,250);break;
        default: glColor3ub(250,0,250);break;
    }

    glTranslatef(i*3.0,0,-j * 3.0);
    objetos_seleccion[i*n+j] = new Cilindro(2,4);
    objetos_seleccion[i*n+j]->draw((ModoVis) modo_actual, modo_diferido);
    glPopMatrix();
    }
  }
  //cout << "final" << endl; 
  glEnable(GL_DITHER);
  //cout << "final 2" << endl; 

 }
/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/


#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "ply_reader.h"
//#include "malla.h" // objetos: Cubo y otros....
#include <string>
#include <time.h>       /* time */

using namespace std;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    ejes.changeAxisSize( 5000 );
    srand (time(NULL));
    //num_texturas = 2; // se usa para cambiar las texturas 't'

    //objetos.resize(num_objetos);
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
    std::vector<Objeto*> v;

    for(int i = 0; i < 9; i++){
      int nObj; 
      if( i != SELECCION ){
        nObj = 1; 
      }else{
        nObj = 5; 
      }
      for(int j = 0; j < nObj; j++){
        int obj;
        if(i != SELECCION)
          obj = i;
        else
          obj = rand() % 6;
        //cout << "j = " << j << endl; 
        switch( obj )
       {  
          case CUBO :
            v.push_back(new Cubo());
          break;
          case TETRAEDRO :
            v.push_back(new Tetraedro());
          break;
          case CILINDRO :
            v.push_back(new Cilindro(2,4));
          break;
          case CONO :
            v.push_back(new Cono(2,40));
          break;
          case ESFERA :
            v.push_back(new Esfera(40,40));
          break;
          case OBJ_JERARQUICO :
            v.push_back(new ObjJerarquico());
          break;
          case CUADRO:
            v.push_back(new Cuadro());
          break;
          case OBJ_PLY:
            v.push_back(new ObjPLY(rutasPLYs[rand() % (rutasPLYs.size()-1)]));
          break;
          /*default:
            cout << "objeto = " <<  obj << endl; 
            v.push_back(new Cubo());
          break;*/

        }
        if(i == SELECCION){
          v[v.size()-1]->setPosicion({rand() % 100-50, rand() % 100-50, rand() % 100-50});
        }
        else{
          v[v.size()-1]->setPosicion({0, 0, 0});
        }

      }
      
      objetos.push_back(v);
      //coloresAleatorios.push_back(v2);
      v.clear(); 
  }

    //Cubo
    //v.push_back(new Cubo());
    


    //v.push_back(new Tetraedro());
    //objetos.push_back(v);
    //v.clear();
    /*
    objetos[TETRAEDRO] = new Tetraedro();
    objetos[CILINDRO] = new Cilindro(2,4);
    objetos[CONO] = new Cono(2,40);
    objetos[ESFERA] = new Esfera(40,40);
    objetos[OBJ_JERARQUICO] = new ObjJerarquico();
    objetos[CUADRO] = new Cuadro();
    */

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
    camaras.push_back(new Camara({0,  0, 60}, // Posición
                                 {0,0,0}, // Dirección
                                 {0,1,0}, // sentido
                                 true,
                                 -0.5, 0.5,   // Ancho
                                 -0.5, 0.5,   // Alto
                                  0.1, 100 // Profundo
                                 ));  // Ortogonal

    camaras.push_back(new Camara({0, 20, 20}, // Posición
                                 {0,0,0}, // Dirección
                                 {0,1,0}, // sentido
                                 false,
                                 -0.5, 0.5,   // Ancho
                                 -0.5, 0.5,   // Alto
                                 2,200 // Profundo
                                 )); // Ortogonal

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
   //cout << "objetos[objeto_actual].size() = " << objetos[objeto_actual].size() << endl; 
   for(int i = 0; i < objetos[objeto_actual].size(); i++){
    //if(objetos[objeto_actual][i]->getTipo() == OBJ_PLY && leer_ply)
      //leerPLY();
    //if(objeto_actual == SELECCION){
      glPushMatrix();
      //cout << " Posicion = " << objetos[objeto_actual][i]->getPosicion()(0) << "\t" << objetos[objeto_actual][i]->getPosicion()(1) << "\t" << objetos[objeto_actual][i]->getPosicion()(2) << "\t" << endl;
      glTranslatef(objetos[objeto_actual][i]->getPosicion()(0), objetos[objeto_actual][i]->getPosicion()(1), objetos[objeto_actual][i]->getPosicion()(2));
      //glScalef(rand() % 10, rand() % 10, rand() % 10);
      objetos[objeto_actual][i]->draw((ModoVis) modo_actual, modo_diferido);
      glPopMatrix();
    //}else
      //objetos[objeto_actual][i]->draw((ModoVis) modo_actual, modo_diferido);
   }

//objetos[CUADRO] = new Cuadro();
   /*
  if(objeto_actual == SELECCION)
        dibuja_seleccion();
  else*/
    
      
  
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
      objetos[OBJ_PLY][0] = new ObjPLY(ruta);
    }else{
      objetos[OBJ_PLY][0] = new ObjRevolucion(ruta);
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

  camaras[camaraActual]->setProyeccion();
  camaras[camaraActual]->setObserver();
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
   int obj;
   switch( tecla )
   {  
      case 'q' :
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'o' :
      case 'O' :
        leer_ply = true; 
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
        for(int i = 0; i <objetos[objeto_actual].size(); i++)
          objetos[objeto_actual][i]->siguienteColor();
      break ;
      case 'M' :
        for(int i = 0; i <objetos[objeto_actual].size(); i++)
          objetos[objeto_actual][i]->siguienteMaterial();
      break ;
      case 'p' :
      case 'P' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->siguienteParametro();
      break ;
      case 'a' :
        conmutarAnimaciones(); 
      break;
      case 'A' :
        obj = rand() % 6;
        //cout << "j = " << j << endl; 
        switch( obj )
       {  
          case CUBO :
            objetos[objeto_actual].push_back(new Cubo());
          break;
          case TETRAEDRO :
            objetos[objeto_actual].push_back(new Tetraedro());
          break;
          case CILINDRO :
            objetos[objeto_actual].push_back(new Cilindro(2,4));
          break;
          case CONO :
            objetos[objeto_actual].push_back(new Cono(2,40));
          break;
          case ESFERA :
            objetos[objeto_actual].push_back(new Esfera(40,40));
          break;
          case OBJ_JERARQUICO :
            objetos[objeto_actual].push_back(new ObjJerarquico());
          break;
          case CUADRO:
            objetos[objeto_actual].push_back(new Cuadro());
          break;
          case OBJ_PLY:
            objetos[objeto_actual].push_back(new ObjPLY(rutasPLYs[rand() % (rutasPLYs.size())]));
          break;
          /*default:
            cout << "objeto = " <<  obj << endl; 
            v.push_back(new Cubo());
          break;*/

        }
        objetos[objeto_actual][objetos[objeto_actual].size()-1]->setPosicion({rand() % 100-50, rand() % 100-50, rand() % 100-50});
        cout << "Se ha creado un nuevo objeto de tipo " << obj << endl; 
      break ;
      case 'S' :
        if(!objetos[objeto_actual].empty())
          objetos[objeto_actual].erase(objetos[objeto_actual].end()-1);
        cout << "Se ha eliminado un objeto de manera secuencial "<< endl; 
      break;
      case 'D' :
        if(!objetos[objeto_actual].empty())
          objetos[objeto_actual].erase(objetos[objeto_actual].begin() + rand() % objetos[objeto_actual].size());
        cout << "Se ha eliminado un objeto de manera aleatoria "<< endl; 
      break;
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
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->incrementaParamAct();
      break ;
      case 'z' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->decrementaParamAct();
      break ;
      case '>' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->decelerar();
      break ;
      case '<' :
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->acelerar();
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
        leer_ply = true; 
        objeto_actual = OBJ_PLY;
      break ;
      case '7' :
        objeto_actual = OBJ_JERARQUICO;
      break ;
      case '8' :
        objeto_actual = CUADRO;
      break ;
      case '9' :
        leer_ply = true; 
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
        static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->inicioAnimaciones( );
      }
        glutIdleFunc( funcion_desocupado );
        luces[1]->inicioGiro();
    }else{
      glutIdleFunc( nullptr );
    }
}

void Escena::mgeDesocupado(){
  if(objeto_actual == OBJ_JERARQUICO){
    static_cast<ObjJerarquico*>(objetos[OBJ_JERARQUICO][0])->actualizarEstado( );
  }
  luces[1]->gira();
  glutPostRedisplay();
  camaras[camaraActual]->rotarYExaminar(0.05);
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
    if(state == GLUT_DOWN)
     seleccionar(x, y);
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
      camaras[camaraActual]->rotarYExaminar(-ang);
    else if(cx < x)
      camaras[camaraActual]->rotarYExaminar(ang);
      //Observer_angle_y++;

    if (cy > y)
      camaras[camaraActual]->rotarXExaminar(+ang);
      //Observer_angle_x--;
    else if(cy < y)
      camaras[camaraActual]->rotarXExaminar(-ang);
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
          camaras[camaraActual]->rotarYExaminar(ang);
         //Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
          camaras[camaraActual]->rotarYExaminar(-ang);
         //Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
          camaras[camaraActual]->rotarXExaminar(ang);
         //Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
          camaras[camaraActual]->rotarXExaminar(-ang);
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


void Escena::seleccionar(GLint x, GLint y){


    glEnable( GL_NORMALIZE );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    std::vector<Tupla3c> coloresAntes, coloresAleatorios;

    //Le damos un color ramdom
    
    for(int i = 0; i < objetos[objeto_actual].size(); i++){
      //cout << "Color actual (Antes) = " << (int) objetos[objeto_actual][i]->getColorActual()[0](0) << "\t" << (int) objetos[objeto_actual][i]->getColorActual()[0](1) << "\t" << (int) objetos[objeto_actual][i]->getColorActual()[0](2) <<endl;  
      coloresAntes.push_back(objetos[objeto_actual][i]->getColorActual()[0]);
      coloresAleatorios.push_back({rand() % 255, rand() % 255, rand() % 255});
      objetos[objeto_actual][i]->setColorActual(coloresAleatorios[i]);
      objetos[objeto_actual][i]->draw((ModoVis) modo_actual, modo_diferido);
    }
    // Dibujamos el objeto
    dibujar_objeto_actual();
  


  Tupla3c colorRamdom, colorAntes; 
  int nSeleccionado = -1; 
  // Selección

  
  for(int i = 0; i < objetos[objeto_actual].size(); i++){

    colorRamdom = coloresAleatorios[i];
    colorAntes = coloresAntes[i];
    objetos[objeto_actual][i]->setColorActual(colorRamdom);
    Tupla3c colorsel = leerPixel(x,y);
    //cout << "colorsel = " << (int) colorsel(0) << "\t" << (int) colorsel(1) << "\t" << (int) colorsel(2) << "\t" << endl;
    //cout << "colorRamdom = " << (int) colorRamdom(0) << "\t" << (int) colorRamdom(1) << "\t" << (int) colorRamdom(2) << "\t" << endl;
    if(colorsel(0) == colorRamdom(0) && 
       colorsel(1) == colorRamdom(1) &&
       colorsel(2) == colorRamdom(2) ){       
      objetos[objeto_actual][i]->setColorActual(colorAntes);
      objetos[objeto_actual][i]->seleccionado();

      // Centramos la cámara en el objeto
      if(objetos[objeto_actual][i]->getSeleccionado())
        camaras[camaraActual]->setAt(objetos[objeto_actual][i]->getPosicion());
      else
        camaras[camaraActual]->setAt({0, 0, 0});

       //cout << "Se ha seleccionado un objeto tipo " << objetos[objeto_actual][i]->getTipo() << endl; 
    }else{
      objetos[objeto_actual][i]->setColorActual(colorAntes);

    }

  }
}

Tupla3c Escena::leerPixel(GLint x, GLint y){

  GLint viewport[4];

  glGetIntegerv(GL_VIEWPORT, viewport);

  vector< unsigned int > pixels(3);
  Tupla3c salida; 
  //cout << "x = " << x << endl; 
  //cout << "y = " << y << endl; 

  GLsizei width = 1;
  GLsizei height = 1; 
  GLenum format = GL_RGB;
  GLenum type = GL_UNSIGNED_INT;
  GLvoid * data = pixels.data();

  glReadPixels( x, viewport[3]-y,
                     width,
                     height,
                     format,
                     type,
                     data);

  for(int i = 0; i < pixels.size(); i++)
    salida(i) = pixels[i];

  //cout << "Pixel R = " << salida(0) << "\tPixel G = " << salida(1) << "\tPixel B = " << salida(2) <<endl;  

  return salida; 
}

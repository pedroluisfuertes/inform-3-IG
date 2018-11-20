/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "objeto.h"
#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "objPLY.h"

#include "luz.h"


class Escena
{

   private:
    enum Objetos
   {
     CUBO = 0, 
     TETRAEDRO = 1,
     CILINDRO = 2,
     CONO = 3,
     ESFERA = 4,
     OBJ_PLY = 5,
     OBJ_JERARQUICO = 6 

   };

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   int objeto_actual = 0; // objeto actual (el que se visualiza)
   int num_objetos = 7; // número de objetos (actualizado al crear los objetos en el constructor)

   int num_modos = 4, 
       modo_actual = 0;

   int color_actual = 0;

   bool modo_diferido = false;
   bool leer_ply = true;
   bool activarAnimaciones = false; 

   // Objetos de la escena
   std::vector<Objeto*> objetos;

   Luz * luz1 = nullptr; 
   Luz * luz2 = nullptr; 

   void leerPLY();

   void conmutarAnimaciones();

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

  void mgeDesocupado(); 

};
#endif

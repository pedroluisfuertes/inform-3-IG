/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
//#include "malla.h"
#include "jerarquico.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "objPLY.h"


class Escena
{

   private:

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

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos = 0   ; // número de objetos (actualizado al crear los objetos en el constructor)

   int num_modos = 0, 
       modo_actual = 0;

   int num_colores = 0, 
       color_actual = 0;

   bool modo_diferido = false;
   bool leer_ply;
   bool es_ply;

   // Objetos de la escena
   Cubo           * cubo            = nullptr;
   Tetraedro      * tetraedro       = nullptr;
   Cilindro       * cilindro        = nullptr;
   Cono           * cono            = nullptr;
   Esfera         * esfera          = nullptr;
   ObjPLY         * objPLY          = nullptr;
   ObjRevolucion  * objRevolucion   = nullptr;

   // completar: añadir punteros a tetraedro u otros (práctica 1),
   //            y a un objeto PLY y de revolución (práctica 2),
   //           y a un objeto jerarquico (práctica 3).
   // ......
   void leerPLY();

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif

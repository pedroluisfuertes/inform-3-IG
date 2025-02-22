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
#include "cuadro.h"

#include "luz.h"

#include "camara.h"


class Escena
{

   private:

   Ejes ejes;

  void clear_window();
	void dibujar_objeto_actual();
  void dibujar_luces();

  std::vector<string> rutasPLYs = {
    "./plys/ant.ply",
    "./plys/big_dodge.ply",
    "./plys/beethoven.ply"
  };

  // Objetos de la escena
    int objeto_actual = 0; // objeto actual (el que se visualiza)
    int num_objetos = 9; // número de objetos 
    
    enum Estado
    {
     DEFAULT = 0,
     SELECCION_OBJETO = 1,
     SELECCION_COLOR = 2,
     SELECCION_MATERIAL = 3

    };
    std::vector< std::vector<Objeto*> > objetos;
    
    bool botonIzquierdoPulsado = false;
    int cx = 0, cy = 0;

   int num_modos = 4, 
       modo_actual = 0;

   bool modo_diferido = false;
   bool leer_ply = true;
   bool activarAnimaciones = false; 

   std::vector<Luz*> luces;

   std::vector<Camara*> camaras;
   int camaraActual = 0;

   void leerPLY();

   void conmutarAnimaciones();
   void seleccionar(GLint x, GLint y);
   Tupla3c leerPixel(GLint x, GLint y);

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
  void mouseFunc( GLint button, GLint state, GLint x, GLint y);
  void motionFunc( int x, int y);

	void teclaEspecial( int Tecla1, int x, int y );

  void mgeDesocupado(); 

};
#endif

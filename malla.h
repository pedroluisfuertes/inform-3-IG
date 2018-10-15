/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/

// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

enum ModoVis
{
  SOLIDO, 
  LINEAS,
  PUNTOS,
  AJEDREZ 

};

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(ModoVis modo, int color);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(ModoVis modo, int color);

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw( ModoVis modo, bool modo_diferido,int color);

   void draw( ModoVis modo, bool modo_diferido);

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void colorear(); 

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<std::vector<Tupla3f> > colores ; // una terna de 3 enteros por cada cara o triángulo
   
   GLuint id_vbo_vertices   = 0 ; // resultado: identificador de VBO de vertices
   GLuint id_vbo_triangulos = 0 ; // resultado: identificador de VBO de triángulos
   GLuint id_vbo_colores = 0 ; // resultado: identificador de VBO de triángulos

   // completar: tabla de colores, tabla de normales de vértices
   private:
   void dibujaInmediato(int color); 
   void dibujaDiferido(int color); 


    
} ;

#endif

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
#include "objeto.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada:public Objeto
{
   public:

    ObjMallaIndexada();
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(ModoVis modo);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(ModoVis modo);

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw( ModoVis modo, bool modo_diferido);

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );
   void eliminarVBO(GLuint id);

   void activarMaterial();
   void setColor(int color);
   void siguienteColor();
   void setMaterial(int material);
   void siguienteMaterial();

   private:
      struct Material
     {
       Tupla4f ambiente;
       Tupla4f difusa;
       Tupla4f especular;
       float brillo; 

       Material(Tupla4f ambiente, Tupla4f difusa, Tupla4f especular, float brillo){
        this->ambiente = ambiente; 
        this->difusa = difusa;
        this->especular = especular;
        this->brillo = brillo; 
       }
     };

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void inicializar(); 

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<std::vector<Tupla3f> > colores ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> normales_vertices;
   std::vector<Material> materiales;
   std::vector<Textura> texturas;
   int materialActivo = 0;
   int colorActivo = 0;
   int colorActivoAntDif = 0; 
   int texturaActiva = 0; 
   
   GLuint id_vbo_vertices   = 0 ; // resultado: identificador de VBO de vertices
   GLuint id_vbo_triangulos = 0 ; // resultado: identificador de VBO de triángulos
   GLuint id_vbo_colores = 0 ; // resultado: identificador de VBO de colores
   GLuint id_vbo_normales = 0 ; // resultado: identificador de VBO de normales



   // completar: tabla de colores, tabla de normales de vértices
   private:
   void colorear(); 
   void dibujaInmediato(); 
   void dibujaDiferido(); 
    
} ;

#endif

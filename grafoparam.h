// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "objPLY.h"

constexpr int num_parametros = 4 ; // número de parámetros o grados de libertad
                                   // de este modelo


class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const ModoVis p_modo_vis, const bool p_usar_diferido );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void columna( const float altura, const float ag_rotacion,
                             const float radio_cil );

   void pala   ( );
   void barraVerticalMenor( );
   void barraHorizontal(  );
   void barraVerticalSuperior( );


   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Cubo *     cubo     = nullptr ;

   // parámetros de la llamada actual (o última) a 'draw'
   ModoVis modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   const int ALTURA_BRAZO_MENOR = 8,
             LONGITUD_BRAZO_HORIZONTAL = 15,
             ALTURA_GRUA = 20;

   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float rotacionPala,
         alturaPala, 
         movimientoPala,
         rotacionBrazoPala, 
         alturaBrazo,
         rotacionBrazo;

} ;

#endif

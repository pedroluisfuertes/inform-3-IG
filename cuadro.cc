// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

#include "cuadro.h"

Cuadro::Cuadro()
{

   // inicializar la tabla de vértices
   vertices =  {  { -1, -0.5, 0.0 }, // 0
                  { -1, +0.5, 0.0 }, // 1
                  { +1, -0.5, 0.0 }, // 2
                  { +1, +0.5, 0.0 }, // 3
               };

   /*vertices = {{ -1, 0, 0},
               {  1, 0, 0},
               {  1, 1, 0},
               { -1, 1, 0}};*/

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 3, 1 }, { 0, 2, 3 } };
   //triangulos = { { 0, 3, 1 }, { 0, 2, 1 } };
                
   inicializar();

   std::vector<Tupla2f> coordenadas_texturas_vertices; 
   
   coordenadas_texturas_vertices.push_back(Tupla2f(0,1));
   coordenadas_texturas_vertices.push_back(Tupla2f(0,0));
   coordenadas_texturas_vertices.push_back(Tupla2f(1,1));
   coordenadas_texturas_vertices.push_back(Tupla2f(1,0));
   
   /*
   coordenadas_texturas_vertices.push_back(Tupla2f(0,1));
   coordenadas_texturas_vertices.push_back(Tupla2f(1,1));
   coordenadas_texturas_vertices.push_back(Tupla2f(1,0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0,0));
   */

   tipo = CUADRO; 
   
   texturas.push_back(Textura("./img/logo2.jpg", coordenadas_texturas_vertices)); 
}
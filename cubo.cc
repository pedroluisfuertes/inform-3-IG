// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

#include "cubo.h"

Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
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
   
   //texturas.push_back(Textura("./img/logo2.jpg", coordenadas_texturas_vertices)); 
   
}
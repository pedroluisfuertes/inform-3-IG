// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   /*
   No se queda centrada, se queda sonbre el eje XY*/
   Tupla3f sup = {    0.0, 1.0,  0.0  }; // 0
   Tupla3f izq = {   -1.0,  0.0,  0.0  }; // 1
   Tupla3f der = {   +1.0,  0.0,  0.0 }; // 2
   Tupla3f atr = {   0.00, 0.0,  -1.00  }; // 1

   vertices.push_back (sup);
   vertices.push_back (der);
   vertices.push_back (izq);

   vertices.push_back (sup);
   vertices.push_back (atr);
   vertices.push_back (der);

   vertices.push_back (sup);
   vertices.push_back (izq);
   vertices.push_back (atr);

   vertices.push_back (izq);
   vertices.push_back (atr);
   vertices.push_back (der);               

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 1 },
                  { 3, 5, 4 },
                  { 6, 8, 7 },
                  { 9, 10, 11 },
                } ;
   inicializar();

   std::vector<Tupla2f> coordenadas_texturas_vertices; 
   
   coordenadas_texturas_vertices.push_back(Tupla2f(0.125,0.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.25,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0,1.0));
   
   coordenadas_texturas_vertices.push_back(Tupla2f(0.375,0.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.25,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.5,1.0));
   
   coordenadas_texturas_vertices.push_back(Tupla2f(0.625,0.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.5,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.75,1.0));
   
   coordenadas_texturas_vertices.push_back(Tupla2f(0.875,0.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.75,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   
   texturas.push_back(Textura("./img/Piramides.jpg", coordenadas_texturas_vertices)); 
}
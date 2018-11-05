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
   vertices =  {  {  0.0,  +0.50,  0.0  }, // 0
                  { -0.50, -0.50,  0.0  }, // 1
                  { +0.50, -0.50, -0.50 }, // 2
                  { +0.50, -0.50, +0.50 }, // 3
               };

               

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 1 },
                  { 0, 1, 3 },
                  { 0, 3, 2 },
                  { 1, 2, 3 },
                } ;

}
// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

#include "yunque.h"

Yunque::Yunque()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { -1.3, +0.0, +0.0 }, // dsf

                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 },  // 7
                  { +1.3, +0.0, +0.0 }  // sdfsd
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


   triangulos = { { 2, 0, 4 }, { 3, 2, 4 },
                  { 1, 3, 4 }, { 0, 1, 4 },

                  { 2, 3, 8 }, { 8, 7, 2 },
                  { 3, 1, 6 }, { 6, 8, 3 },
                  { 2, 7, 5 }, { 2, 5, 0 },
                  { 0, 6, 1 }, { 0, 5, 6 },


                  { 6, 5, 9 }, { 8, 6, 9 },
                  { 5, 7, 9 }, { 7, 8, 9 }
                } ;

}
#ifndef __OBJREVOLUCION_H__
#define __OBJREVOLUCION_H__

#include "malla.h"
#include "aux.h"

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      
      ObjRevolucion( );
      ObjRevolucion( const std::string & nombre_ply_perfil );

   protected: 
        void crearMalla( const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int eje, const bool tapaSuperior, const bool tapaInferior);
        float const PI = 3.14159265;

   private:
        /*
         true: descendente
         false: ascendente
        */
        bool calcularSentidoPuntos(int eje, const std::vector<Tupla3f> &tup); 

} ;

#endif
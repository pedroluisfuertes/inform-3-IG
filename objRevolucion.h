#ifndef __OBJREVOLUCION_H__
#define __OBJREVOLUCION_H__

#include "malla.h"
//#include "aux.h"
#include <utility>

using namespace std;

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
        pair<bool,bool> calcularPuntosTapas (const std::vector<Tupla3f> & perfil_original, const int eje, const bool sentidoPuntosAscendente);
        void calcularPuntos(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int eje, const bool sentidoPuntosAscendente,const pair<bool,bool> puntosTapas);
        Tupla3f calcularPuntoRotado(const std::vector<Tupla3f> & perfil_original, const int eje, const int i, const float alfa);
        int forzarTapas(const bool tapaSuperior, const bool tapaInferior, pair<bool,bool> &puntosTapas, const std::vector<Tupla3f> & perfil_original, const int eje, const bool sentidoPuntosAscendente) ;
        Tupla3f proyectarPunto(const std::vector<Tupla3f> & perfil_original, const int eje, const bool tapaInferior, const bool sentidoPuntosAscendente); 
        void generarTriangulos(const pair<bool,bool> &puntosTapas, const int N, const int num_instancias_perf);


} ;

#endif
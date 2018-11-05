#ifndef __CIRCULO_H__
#define __CIRCULO_H__

#include "objRevolucion.h"
#include "aux.h"

class Circulo : public ObjRevolucion
{
	private:
		void construir( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior);
	public:
		Circulo( const int num_vert_perfil,
		const int num_instancias_perf );
		Circulo( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior);
} ;

#endif
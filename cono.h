
#ifndef __CONO_H__
#define __CONO_H__

#include "objRevolucion.h"
#include "aux.h"

class Cono : public ObjRevolucion
{
	private:
		void construir( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaInferior);
	public:
		Cono( const int num_vert_perfil,
		const int num_instancias_perf );
		Cono( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaInferior);
} ;

#endif
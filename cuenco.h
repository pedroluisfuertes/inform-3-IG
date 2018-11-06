#ifndef __CUENCO_H__
#define __CUENCO_H__

#include "objRevolucion.h"
#include "aux.h"

class Cuenco : public ObjRevolucion
{
	private:
		void construir( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const int eje);
	public:
		Cuenco( const int num_vert_perfil,
		const int num_instancias_perf );
		Cuenco( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const int eje);
} ;

#endif
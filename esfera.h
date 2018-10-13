#include "objRevolucion.h"
#include "aux.h"

class Esfera : public ObjRevolucion
{
	private:
		void construir( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const int eje);
	public:
		Esfera( const int num_vert_perfil,
		const int num_instancias_perf );
		Esfera( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const int eje);
} ;
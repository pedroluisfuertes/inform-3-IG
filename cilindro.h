#include "objRevolucion.h"
#include "aux.h"

class Cilindro : public ObjRevolucion
{
	private:
		void construir( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior);
	public:
		Cilindro( const int num_vert_perfil,
		const int num_instancias_perf );
		Cilindro( const int num_vert_perfil,
		const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior);
} ;
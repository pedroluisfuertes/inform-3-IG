#include "cono.h"
#include "iostream"
#include "aux.h"

using namespace std;

Cono::Cono( const int num_vert_perfil, const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaInferior){

	construir( num_vert_perfil, num_instancias_perf, radio,  altura, eje, tapaInferior );
}
/*
Construye un cilindro unidad, centrado en el origen
*/
Cono::Cono( const int num_vert_perfil, const int num_instancias_perf){
	construir( num_vert_perfil, num_instancias_perf, 1,  1, 1, true );
}

void Cono::construir( const int num_vert_perfil, const int num_instancias_perf, const float radio, const float altura, const int eje,  const bool tapaInferior){

		std::vector<Tupla3f> perfil; 
		Tupla3f vertice; 
		  float x;
		  float y; 
		  float z;

		switch (eje){
			case 0:
				z = 0;

				for(int i = 0; i <= num_instancias_perf; i++){
					x = altura/num_instancias_perf*i;
					y = radio - radio/num_instancias_perf*i;
					vertice = {x,y,z}; 
				  	perfil.push_back(vertice);

				};
			break; 
			case 1:
				z = 0;
				for(int i = 0; i <= num_instancias_perf; i++){
					y = altura/num_instancias_perf*i;
					x = radio - radio/num_instancias_perf*i;
					vertice = {x,y,z}; 
				  	perfil.push_back(vertice);
				};
			break; 
			case 2:
			 perfil = { { 0,  radio,   0 },
				        { 0,  radio,   altura }

			};
			break; 
		}

		

		crearMalla(perfil, num_instancias_perf, eje, false, tapaInferior); 
   		inicializar();
}

#include "esfera.h"
#include "iostream"
#include "aux.h"
#include <math.h>

using namespace std;

Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf, const float radio, const int eje){

	construir( num_vert_perfil, num_instancias_perf, radio, eje);
}
/*
Construye un esfera unidad, centrado en el origen
*/
Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf){
	construir( num_vert_perfil, num_instancias_perf, 1,  1);
}

void Esfera::construir( const int num_vert_perfil, const int num_instancias_perf, const float radio, const int eje){

		std::vector<Tupla3f> perfil; 
		Tupla3f vertice; 
		  float x;
		  float y; 
		  float z;
		  
		switch (eje){
			case 0:
				y = 0;
				for(int i = 0; i < num_instancias_perf; i++){
					x = radio * cos(PI/num_instancias_perf*i) + radio; // Para que esté sobre el plano XZ
					z = radio * sin(PI/num_instancias_perf*i);
					vertice = {x,y,z}; 
				  	perfil.push_back(vertice);

				};
				x = 0;
				y = 0; 
				vertice = {x,y,z}; 
				perfil.push_back(vertice);

				
			break; 
			case 1:

				z = 0;
				for(int i = 0; i < num_instancias_perf; i++){
					y = radio * cos(PI/num_instancias_perf*i) + radio; // Para que esté sobre el plano XZ
					x = radio * sin(PI/num_instancias_perf*i);
					vertice = {x,y,z}; 
				  	perfil.push_back(vertice);

				};
				x = 0;
				y = 0; 
				vertice = {x,y,z}; 
				perfil.push_back(vertice);

			break; 
			case 2:
			 perfil = { { 0,  radio,   0 },
				        { 0,  radio,   radio }

			};
			break; 
		}

		

		crearMalla(perfil, num_instancias_perf, eje, false, false); 


		colorear(); 
}

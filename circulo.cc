#include "circulo.h"
#include "iostream"
#include "aux.h"

using namespace std;

Circulo::Circulo( const int num_vert_perfil, const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior){

	construir( num_vert_perfil, num_instancias_perf, radio,  altura, eje, tapaSuperior, tapaInferior );
}
/*
Construye un circulo unidad, centrado en el origen
*/
Circulo::Circulo( const int num_vert_perfil, const int num_instancias_perf){
	construir( num_vert_perfil, num_instancias_perf, 1,  1, 0,true, true );
}

void Circulo::construir( const int num_vert_perfil, const int num_instancias_perf, const float radio, const float altura, const int eje, const bool tapaSuperior, const bool tapaInferior){

		std::vector<Tupla3f> perfil; 
		Tupla3f vertice; 
		  float x;
		  float y; 
		  float z;

		switch (eje){
			case 0:
				y = radio; 
				z = 0;
				x = 0;
				vertice = {x,y,z}; 
				perfil.push_back(vertice);
			break; 
			case 1:
				x = radio; 
				z = 0;
				y = 0;
				vertice = {x,y,z}; 
				perfil.push_back(vertice);
			break; 
			case 2:
			 perfil = { { 0,  radio,   0 } };
			break; 
		}

		

		crearMalla(perfil, num_instancias_perf, eje, tapaSuperior,tapaInferior); 
		colorear(); 
}

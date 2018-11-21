#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include <chrono>

// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;

class Luz {
	protected:
		static int lucesActivas;
		GLenum  luz_indice; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
		Tupla4f luz_posicion; 
		Tupla4f luz_ambiente;
		Tupla4f luz_difusa;
		Tupla4f luz_especular;
		bool activa;
		float	rotX = 0,
				rotY = 0,
				rotZ = 0;
      Instante ultima_actu  ;



	public:
		Luz(GLenum p_luz_indice, Tupla4f p_luz_posicion, Tupla4f p_luz_ambiente, Tupla4f p_luz_difusa, Tupla4f p_luz_especular);
		void activar(); 
		static void activarLuces(); 
		static void desactivarLuces(); 
		void rotar(float alfa, float x, float y, float z);
		void aumentarRotacionEnX(float alfa);
		void aumentarRotacionEnY(float alfa);
		void aumentarRotacionEnZ(float alfa);
		void inicioGiro();
		void gira();


};

#endif
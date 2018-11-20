#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++


class Luz {
	protected:
		static int lucesActivas;
		GLenum  luz_indice; // ïndice de la funte de luz, entre GL_LIGHT0 y GL_LIGHT7
		Tupla4f luz_posicion; 
		Tupla4f luz_ambiente;
		Tupla4f luz_difusa;
		Tupla4f luz_especular;
		bool activa;

	public:
		Luz(GLenum p_luz_indice, Tupla4f p_luz_posicion, Tupla4f p_luz_ambiente, Tupla4f p_luz_difusa, Tupla4f p_luz_especular);
		void activar(); 

};

#endif
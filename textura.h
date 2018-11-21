#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++


class Textura {
	protected:
		static int texturasActivas;
		bool activa;
		GLuint idTex; 

	public:
		Textura();
		void activar(); 
		static void activarTexturas(); 
		static void desactivarTexturas(); 

};

#endif
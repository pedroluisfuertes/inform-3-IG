#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include <string>

typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} AUX_RGBImageRec;

class Textura {
	protected:
		static int texturasActivas;
		bool activa;
		GLuint textura_id = 0;
   		std::vector<Tupla2f> coordenadas_texturas_vertices;


	public:
		Textura(const char *filename, std::vector<Tupla2f> coordenadas_texturas_vertices);
		void activar(); 
		static void activarTexturas(); 
		static void desactivarTexturas(); 


};

#endif
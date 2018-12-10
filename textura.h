#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include <string>
#include "CImg.h"
using namespace cimg_library;

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
   		std::vector<unsigned char> data;
   		CImg<unsigned char> logo;

	public:
		Textura(const char *filename, std::vector<Tupla2f> coordenadas_texturas_vertices);
		void activar(); 
		static void activarTexturas(); 
		static void desactivarTexturas();
		std::vector<Tupla2f> get_coordenadas_texturas_vertices();


};

#endif
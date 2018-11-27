#include "textura.h"
#include <string>

#include <GL/glut.h>

#include "CImg.h"
using namespace cimg_library;

using namespace std ;

int Textura::texturasActivas = 0;

Textura::Textura(const char *filename, std::vector<Tupla2f> coordenadas_texturas_vertices){

	activa = false; 
	this->coordenadas_texturas_vertices = coordenadas_texturas_vertices;
	std::vector<unsigned char> data;

   CImg<unsigned char> logo;
   logo.load(filename);

   // empaquetamos bien los datos
   for (long y = 0; y < logo.height(); y ++)
      for (long x = 0; x < logo.width(); x ++)
      {
	 unsigned char *r = logo.data(x, y, 0, 0);
	 unsigned char *g = logo.data(x, y, 0, 1);
	 unsigned char *b = logo.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }
   //cout << "textura_id antes " << textura_id << endl; 
   glGenTextures(1, &textura_id);
   glBindTexture( GL_TEXTURE_2D, textura_id ); // activa textura con id textura_id
   //cout << "textura_id después " << textura_id << endl; 
   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //cout << "logo.width() = " << logo.width() << "\tlogo.height() = " << logo.height() << endl;

   // TRASFIERE LOS DATOS A GPU
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
	//	0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
   gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, logo.width(), logo.height(), GL_RGB, GL_UNSIGNED_BYTE, data.data());
}

void Textura::activar(){
	//cout << "activar " << textura_id << endl; 
	//for ( int i = 0; i < coordenadas_texturas_vertices.size(); i++)
	//	cout << "coordenada " << i << " " << coordenadas_texturas_vertices[i](0) << " " << coordenadas_texturas_vertices[i](1) << endl; 
	
	glTexCoordPointer(2, GL_FLOAT, 0, coordenadas_texturas_vertices.data());
}

void Textura::activarTexturas(){
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnable( GL_TEXTURE_2D ) ; // habilita texturas
}

void Textura::desactivarTexturas(){
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisable( GL_TEXTURE_2D );
}
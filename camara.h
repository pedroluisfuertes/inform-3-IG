#ifndef _CAMARA_H
#define _CAMARA_H
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++

class Camara{

public:
	Camara();
	Camara(	Tupla3f eye,
 			Tupla3f at,
 			Tupla3f up,
 			GLdouble left_p, 		GLdouble right_p,
 			GLdouble bottom_p, 	GLdouble top_p,
 			GLdouble near_p, 		GLdouble far_p,
 			bool ortho_p);

	void redimensionar( int newWidth, int newHeight );
	void draw();
	void drawFrustum();
	void cambiarPosicion(Tupla3f eyeInicial);
	void zoom(float incremento);
	void girarX(double alfa);
	void girarY(double alfa);
	void girarZ(double alfa);

private:
	void girar();
	std::vector<Tupla3f> traspuesta(std::vector<Tupla3f> a);
	std::vector<Tupla3f> producto_matricial3x3(std::vector<Tupla3f> a, std::vector<Tupla3f> b);
	Tupla3f producto_matricial3x1(std::vector<Tupla3f> a, Tupla3f b);
	float producto_escalar(Tupla3f v1, Tupla3f v2);
	float producto_escalar(Tupla3f v1, Tupla3f v2, int d);
	void cambiaSistemaCoordenadasACoordenadasDelMundo(Tupla3f &n, Tupla3f &u,Tupla3f &v);
	void cambiaSistemaCoordenadasACoordenadasDeLaCamara(Tupla3f &n, Tupla3f &u,Tupla3f &v);

	// gluLookAt
	Tupla3f eyeInicial = {0, 0, 0};
	Tupla3f eyeReal = {0, 0, 0};
	Tupla3f at  = {0, 0, 0};
	Tupla3f up  = {0, 1, 0};
	//GLdouble eyeX = 0, eyeY = 0, eyeZ = 2;
 	//GLdouble  atX = 0,  atY = 0,  atZ = 0;
 	//GLdouble  upX = 0,  upY = 1,  upZ = 0;


 	// glFrustum
 	GLdouble left, right;
 	GLdouble bottom, top;
 	GLdouble near, far;
 	Tupla3f angulo = {0, 0, 0}; 
 	Tupla3f distancia = {0, 0, 0}; 
 	//float angX = 0, angY = 90, angZ = 0;

 	bool ortho;
};

#endif
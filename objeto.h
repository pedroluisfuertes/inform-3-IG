
#ifndef __OBJETO_H__
#define __OBJETO_H__
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include <limits.h>  

    enum ModoVis
	{
	  SOLIDO, 
	  LINEAS,
	  PUNTOS,
	  AJEDREZ 

	};

	enum TipoObjeto
    {
     CUBO = 0, 
     TETRAEDRO = 1,
     CILINDRO = 2,
     CONO = 3,
     ESFERA = 4,
     OBJ_PLY = 5,
     OBJ_JERARQUICO = 6,
     CUADRO = 7,
     SELECCION = 8

    };

class Objeto{

protected:
	TipoObjeto tipo;
	Tupla3c colorSeleccionado = {0, 255, 0}; 
	bool selec = false; 
	Tupla3f posicion = {0, 0, 0}; 

public:
	TipoObjeto getTipo();
	bool getSeleccionado();
	void setSeleccionado(bool selec);
	void seleccionado();
	Tupla3f getPosicion();
	void setPosicion(Tupla3f posicion);

	virtual void siguienteColor() = 0;
	virtual void addColor(Tupla3c color) = 0;
	virtual std::vector<Tupla3c> getColorActual() = 0;
	virtual void setColorActual(Tupla3c vColor) = 0;
	virtual int getIndColorActual() = 0;
	virtual void setIndColorActual(int c) = 0;
	virtual std::vector<std::vector<Tupla3c> > getColores() = 0; 
	virtual void siguienteMaterial() = 0; 
    virtual void draw( ModoVis modo, bool modo_diferido) = 0;
	virtual ~Objeto(){};
};

#endif
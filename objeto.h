
#ifndef __OBJETO_H__
#define __OBJETO_H__

    enum ModoVis
	{
	  SOLIDO, 
	  LINEAS,
	  PUNTOS,
	  AJEDREZ 

	};

class Objeto{

public:
	virtual void siguienteColor() = 0;
	virtual void siguienteMaterial() = 0; 
    virtual void draw( ModoVis modo, bool modo_diferido) = 0;
	virtual ~Objeto(){};
};

#endif
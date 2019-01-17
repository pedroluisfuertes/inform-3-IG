
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
	//virtual void addColor(Tupla3f color) = 0;
	//virtual Tupla3f getColorActual() = 0;
	//virtual std::vector<Tupla3f> getColores() = 0; 
	virtual void siguienteMaterial() = 0; 
    virtual void draw( ModoVis modo, bool modo_diferido) = 0;
	virtual ~Objeto(){};
};

#endif
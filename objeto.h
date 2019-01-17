
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
	virtual void addColor(Tupla3u color) = 0;
	virtual std::vector<Tupla3u> getColorActual() = 0;
	virtual std::vector<std::vector<Tupla3u> > getColores() = 0; 
	virtual void siguienteMaterial() = 0; 
    virtual void draw( ModoVis modo, bool modo_diferido) = 0;
	virtual ~Objeto(){};
};

#endif
#include "objeto.h"

TipoObjeto Objeto::getTipo(){
   return tipo;
}

bool Objeto::getSeleccionado(){
   return selec;
}
void Objeto::setSeleccionado(bool selec){
   this->selec = selec; 
}

void Objeto::seleccionado(){
//std::cout << "sele = " << selec << std::endl; 
   selec = !selec; 
}

Tupla3f Objeto::getPosicion(){
	return posicion; 
}

void Objeto::setPosicion(Tupla3f posicion){
	this->posicion = posicion; 
}
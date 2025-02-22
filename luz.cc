#include "luz.h"
#include <chrono>
#include "iostream"

int Luz::lucesActivas = 0;
   using namespace std ;

Luz::Luz(GLenum p_luz_indice, Tupla4f p_luz_posicion, Tupla4f p_luz_ambiente, Tupla4f p_luz_difusa, Tupla4f p_luz_especular){

	luz_indice 	  = p_luz_indice;
	luz_posicion  = p_luz_posicion;
	luz_ambiente  = p_luz_ambiente;
	luz_difusa 	  = p_luz_difusa;
	luz_especular = p_luz_difusa;
	activa = false; 

	/*
	cout << "luz_indice = " << luz_indice << endl;
	cout << "luz_posicion = " << luz_posicion << endl;
	cout << "luz_ambiente = " << luz_ambiente << endl;
	cout << "luz_difusa = " << luz_difusa << endl;
	cout << "luz_especular = " << luz_especular << endl;
	*/
}
void Luz::dibujar(){
	glLightfv(luz_indice, GL_AMBIENT,  (GLfloat*) &luz_ambiente);
	glLightfv(luz_indice, GL_DIFFUSE,  (GLfloat*) &luz_difusa);
	glLightfv(luz_indice, GL_SPECULAR, (GLfloat*) &luz_especular);
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	    //lLoadIdentity();
	    glRotatef( rotX, 1, 0, 0 );
	    glRotatef( rotY, 0, 1, 0 );
	    glRotatef( rotZ, 0, 0, 1 );
		glLightfv(luz_indice, GL_POSITION, (GLfloat*) &luz_posicion);
    glPopMatrix();
}
void Luz::activar(){
	if (!activa){
		cout << "Activada luz " << luz_indice << endl;
		if(lucesActivas == 0) // Si no había luces activas, activamos el modo luces
			activarLuces();
		glEnable(luz_indice);
		lucesActivas++;
		activa = true;
	}else{
		desactivar();
	}

}

void Luz::desactivar(){
	cout << "Desactivada luz " << luz_indice << endl;
	glDisable(luz_indice);
	lucesActivas--;
	if(Luz::lucesActivas == 0) // Si no quedan mas luces activas, desactivamos el modo luces
		desactivarLuces();
	activa = false; 
}

void Luz::activarLuces(){
	glEnable(GL_LIGHTING);
}

void Luz::desactivarLuces(){
    glDisable(GL_LIGHTING);
}

void Luz::aumentarRotacionEnX(float alfa){
	rotX += alfa;
	if(rotX > 360)
        rotX -= 360;
    else if(rotX < 0)
        rotX += 360;
}

void Luz::aumentarRotacionEnY(float alfa){
	rotY += alfa;
	if(rotY > 360)
        rotY -= 360;
    else if(rotY < 0)
        rotY += 360;
}

void Luz::aumentarRotacionEnZ(float alfa){
	rotZ += alfa;
	if(rotZ > 360)
        rotZ -= 360;
    else if(rotZ < 0)
        rotZ += 360;
}

void Luz::inicioGiro( )
{
   using namespace std::chrono ;
   ultima_actu = steady_clock::now() ;
}

void Luz::gira(){

   using namespace std::chrono ;

   const Instante   ahora       =  steady_clock::now();
   const Duracion_s duracion_s  =  ahora - ultima_actu;
   ultima_actu = ahora ;
   //cout << "Duración s " << duracion_s.count() << endl;
   aumentarRotacionEnY(duracion_s.count() * 100);

}

bool Luz::getActiva(){
	//cout << "activa = " << activa << endl;
	return activa;
}

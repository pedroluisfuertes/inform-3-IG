#include "camara.h"
#include <cmath>
#include "iostream"
   using namespace std ;
   #define PI 3.14159265f


void imprimeMatriz(string s,  std::vector<Tupla3f> a){
	cout << s << endl; 
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i](0) << "\t" << a[i](1) << "\t" << a[i](2) << endl;
	}
}
void imprimeMatriz(std::vector<Tupla3f> a){


	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i](0) << "\t" << a[i](1) << "\t" << a[i](2) << endl;
	}
}


Camara::Camara(){}

Camara::Camara(	Tupla3f eyeInicial,
 			Tupla3f at,
 			Tupla3f up,
 			GLdouble left_p, 		GLdouble right_p,
 			GLdouble bottom_p, 	GLdouble top_p,
 			GLdouble near_p, 		GLdouble far_p,
 			bool ortho_p){

	// gluLookAt
	cambiarPosicion(eyeInicial);
	this->up = up;
	this->at = at;

 	// glFrustum
 	left = left_p;	 right = right_p;
 	bottom = bottom_p;	 top = top_p;
 	near = near_p;	 far = far_p;
 	ortho = ortho_p;

}

void Camara::draw(){
	// Posicionamos y direccionamos la cámara
	//cout << "Cámara: eyeInicial(0) = " << eyeInicial(0) << "\t eyeInicial(1) = " << eyeInicial(1) << "\teyeZ = " << eyeInicial(2) << endl; 
	drawFrustum();
	//if(!ortho)
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
	//gluLookAt( 	eyeInicial(0),  	eyeInicial(1),  	eyeInicial(2),		// Posición
	gluLookAt( 	eyeReal(0),  	eyeReal(1),  	eyeReal(2),		// Posición
    			at(0), 	at(1),  	at(2),	// Dirección
 				up(0), 	up(1), 	up(2)); 	// Orientación

}

void Camara::redimensionar( int newWidth, int newHeight )
{
  top = 0.84 * near;
  bottom = -top;

  right = float(newWidth) / float(newHeight) * top ;
  left = -right;

  cout << "near = " << near << endl; 
  cout << "top = " << 0.84*near << endl;
  cout << "right = " << float(newWidth)/float(newHeight)*top << endl;

  //drawFrustum();
  glViewport( 0, 0, newWidth, newHeight );
  

}

void Camara::drawFrustum(){
	glMatrixMode( GL_PROJECTION );
 	glLoadIdentity();
 	if (!ortho)
		glFrustum( left, right, bottom, top, near, far);
	else
		glOrtho(   left, right, bottom, top, near, far);
		
	//glViewport( 0, 0, right - left, top - bottom );

}

void Camara::cambiarPosicion(Tupla3f eyeInicial){
	this->eyeInicial = {0, 0, sqrt(eyeInicial(0) * eyeInicial(0) + eyeInicial(1) * eyeInicial(1) + eyeInicial(2) * eyeInicial(2))};
	//this->eyeInicial = eyeInicial;
	this->eyeReal = eyeInicial;
	angulo(1) = atan(sqrt(eyeInicial(2) / eyeInicial(0))) / PI * 180;
	angulo(0) = atan(sqrt(eyeInicial(1) / eyeInicial(2))) / PI * 180;
	cout << "angulo(0) = " << angulo(0) << endl; 
	cout << "angulo(1) = " << angulo(1) << endl; 
}
void Camara::zoom(float incremento){
	if(incremento > 0){

		left 	*= incremento;
		right 	*= incremento;
		bottom 	*= incremento;
		top 	*= incremento;
		
	}else if(incremento < 0){

		left 	/= -incremento;
		right 	/= -incremento;
		bottom 	/= -incremento;
		top 	/= -incremento;
		
	}else{
		cout << "El incremento no puede ser 0" << endl; 
	}

	/*cout << "\n\nZoom: " << endl; 
	cout << "eyeInicial(0) = " << eyeInicial(0) << endl;
	cout << "eyeInicial(1) = " << eyeInicial(1) << endl;
	cout << "eyeZ = " << eyeZ << endl;
	cout << "left = " << left << endl;
	cout << "right = " << right << endl;
	cout << "bottom = " << bottom << endl;
	cout << "top = " << top << endl << endl;*/
	
}

void Camara::cambiaSistemaCoordenadasACoordenadasDeLaCamara(Tupla3f &n, Tupla3f &u,Tupla3f &v){

	//std::cout << "eyeInicial original :" << eyeInicial(0) << "," << eyeInicial(1) << "," << eyeInicial(2) << std::endl;

	Tupla3f vup;

	float modulo_u, modulo_v, modulo_n;
	Tupla3f up = {0, 1, 0}; 
	// Eje z Cámara
	n = eyeInicial - at; // Calculamos e vector
	modulo_n = sqrt(n(0)*n(0) + n(1)*n(1) + n(2)*n(2)); // Obtenemos el módulo
	n = {n(0)/modulo_n, n(1)/modulo_n, n(2)/modulo_n}; // Normalizamos
	//std::cout << "eje z: " << n(0) << "," << n(1) << "," << n(2) << std::endl;

	// Eje x Cámara
	vup = up - at;

	u = {vup(1) * n(2) - vup(2) * n(1), vup(2) * n(0) - vup(0) * n(2), vup(0) * n(1) - vup(1) * n(0)};
	modulo_u = sqrt(u(0)*u(0) + u(1)*u(1) + u(2)*u(2));
	u = {u(0)/modulo_u, u(1)/modulo_u, u(2)/modulo_u};
	//std::cout << "eje x: " << u(0) << "," << u(1) << "," << u(2) << std::endl;

	// Eje y Cámara
	v = {n(1) * u(2) - n(2) * u(1), n(2) * u (0) - n(0) * u(2), n(0) * u(1) - n(1) * u(0)};
	modulo_v = sqrt(v(0)*v(0) + v(1)*v(1) + v(2)*v(2));
	v = {v(0)/modulo_v, v(1)/modulo_v, v(2)/modulo_v};
	//std::cout << "eje y: " << v(0) << "," << v(1) << "," << v(2) << std::endl;

	// Pasamos las coordenadas del mundo a coordenadas de la cámara
	//eyeInicial = {producto_escalar(-eyeInicial, u, 3), producto_escalar(-eyeInicial, v, 3), producto_escalar(-eyeInicial, n, 3)};
	
	eyeReal = {producto_escalar(-eyeInicial, u, 3), producto_escalar(-eyeInicial, v, 3), producto_escalar(-eyeInicial, n, 3)};

	//std::cout << "eyeInicial escalar :" << eyeInicial(0) << "," << eyeInicial(1) << "," << eyeInicial(2) << std::endl;

}

void Camara::cambiaSistemaCoordenadasACoordenadasDelMundo(Tupla3f &n, Tupla3f &u,Tupla3f &v){

	float x, y, z, s;

	//std::cout << "eyeInicial en el origen :" << eyeInicial(0) << "," << eyeInicial(1) << "," << eyeInicial(2) << std::endl;

	//s =   u(0) *   v(1) *   n(2) +   u(1) *   v(2) *   n(0) +   u(2) *   v(0) *   n(1) - 
	//   (  u(2) *   v(1) *   n(0) +   u(1) *   v(0) *   n(2) +   u(0) *   v(2) *   n(1)  );
	/*
	x = eyeInicial(0) *   v(1) *   n(2) +   u(1) *   v(2) * eyeInicial(2) +   u(2) * eyeInicial(1) *   n(1) - 
	   (  u(2) *   v(1) * eyeInicial(2) +   u(1) * eyeInicial(1) *   n(2) + eyeInicial(0) *   v(2) *   n(1));

	y =   u(0) * eyeInicial(1) *   n(2) + eyeInicial(0) *   v(2) *   n(0) +   u(2) *   v(0) * eyeInicial(2) - 
	   (  u(2) * eyeInicial(1) *   n(0) + eyeInicial(0) *   v(0) *   n(2) +   u(0) *   v(2) * eyeInicial(2));

	z =   u(0) *   v(1) * eyeInicial(2) +   u(1) * eyeInicial(1) *   n(0) + eyeInicial(0) *   v(0) *   n(1) - 
	   (eyeInicial(0) *   v(1) *   n(0) +   u(1) *   v(0) * eyeInicial(2) +   u(0) * eyeInicial(1) *   n(1));

	x = x;
	y = y;
	z = z;

	eyeInicial = {x, y, z};
	*/

	x = eyeReal(0) *   v(1) *   n(2) +   u(1) *   v(2) * eyeReal(2) +   u(2) * eyeReal(1) *   n(1) - 
	   (  u(2) *   v(1) * eyeReal(2) +   u(1) * eyeReal(1) *   n(2) + eyeReal(0) *   v(2) *   n(1));

	y =   u(0) * eyeReal(1) *   n(2) + eyeReal(0) *   v(2) *   n(0) +   u(2) *   v(0) * eyeReal(2) - 
	   (  u(2) * eyeReal(1) *   n(0) + eyeReal(0) *   v(0) *   n(2) +   u(0) *   v(2) * eyeReal(2));

	z =   u(0) *   v(1) * eyeReal(2) +   u(1) * eyeReal(1) *   n(0) + eyeReal(0) *   v(0) *   n(1) - 
	   (eyeReal(0) *   v(1) *   n(0) +   u(1) *   v(0) * eyeReal(2) +   u(0) * eyeReal(1) *   n(1));

	x = x;
	y = y;
	z = z;

	eyeReal = {x, y, z};

	//std::cout << "eyeInicial final " << x << "," << y << "," << z << std::endl;
}


void Camara::girar(){

	//double hip = sqrt(eyeInicial(0) * eyeInicial(0) + eyeInicial(1) * eyeInicial(1) + eyeInicial(2) * eyeInicial(2));
	/*
	double hip = 5;

	std::cout << "Eye Antes Transformación Y:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	cout << "angulo(0) = " << angulo(0) << endl;
	cout << "angulo(1) = " << angulo(1) << endl;

	eyeReal(0) = hip * sin(angulo(0) * PI / 180) * cos(angulo(1) * PI / 180);
	eyeReal(1) = hip * sin(angulo(1) * PI / 180);
	eyeReal(2) = hip * cos(angulo(0) * PI / 180) * sin(angulo(1 ) * PI / 180);

	std::cout << "Eye Después Transformación Y:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	*/

	

	Tupla3f n, u, v; 
	//int a = eyeInicial(2) > 0 ? 1: -1;
	//int a = eyeReal(2) > 0 ? 1: -1;
	//int a = eyeReal(2) > 0 ? 1: -1;
	std::cout << "\nEye Antes Transformación X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;
	// Pasamos de coordenadas del mundo a coordenadas de la cámara
	cambiaSistemaCoordenadasACoordenadasDeLaCamara(n, u, v);

	double hip1 = sqrt(eyeReal(1) * eyeReal(1) + eyeReal(2) * eyeReal(2));
	std::cout << "Eye Antes Giro X:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;

	//eyeInicial(1) = eyeInicial(1) >= 0 ? (hip * sin(angle * PI / 180)) : (-hip * sin(angle * PI / 180));
	//float a = (hip * sin(angle * PI / 180)) ; 
	//float b = eyeInicial(2) >= 0 ? (hip * cos(angle * PI / 180)) : (-hip * cos(angle * PI / 180));

	float alfa = angulo(0);
	float beta = angulo(1);

	
	if(alfa >= 90 && alfa <= 270){
		alfa += 270;
		beta += 180; 
		up = {0, -1 , 0};
	}else{
		up = {0, 1 , 0};
	}

	if(angulo(0) == 90)
		up = {-1, 0 , -1};
	else if( angulo(0) == 270)
		up = {1, 0, 1};
	//up(1) = cos(angulo(0) * PI / 180);
	//up(2) = cos(angulo(0) * PI / 180);

	
	
	cout << "angulo(0) = " << angulo(0) << endl;
	cout << "angulo(1) = " << angulo(1) << endl;
	//cout << "alfa = " << alfa<< endl;
	//cout << "beta = " << beta << endl;
	cout << "hip1 = " << hip1 << endl;
	//cout << "hip2 = " << hip2 << endl;

	//eyeReal = {hip2 * cos(angulo(1)*PI/180), hip1 * sin(angulo(0) * PI / 180), hip1 * cos(angulo(0) * PI / 180) + hip2 * sin(angulo(1) * PI / 180)};
	//eyeReal = {hip * cos(angulo(1)*PI/180), hip * sin(angulo(0) * PI / 180), hip * cos(angulo(0) * PI / 180) * sin(angulo(1) * PI / 180)};
	//eyeReal = {hip2 * cos(angulo(1)*PI/180), eyeReal(1), hip2 * sin(angulo(1) * PI / 180)};
	
	//eyeReal = {eyeReal(0), hip1 * sin(beta * PI / 180), hip1 * abs(cos(beta * PI / 180))};
	eyeReal = {eyeReal(0), hip1 * sin(angulo(0) * PI / 180), hip1 * cos(angulo(0) * PI / 180)};
	std::cout << "Eye Después Giro X:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;

	// Pasamos de coordenadas de la cámara a coordenadas del mundo
	cambiaSistemaCoordenadasACoordenadasDelMundo(n, u, v);
	std::cout << "Eye Después Transformación X:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	//std::cout << "Eye eyeInicial X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl << endl;

	
	if(angulo(0) >= 90 && angulo(0) <= 270){
		//eyeReal(1) *= -1;
		up(1) = -1; 
	}
	else{
		up(0) = 0;
		up(1) = 1;
		up(2) = 0;
	}
	
	
	for(int i= 0; i < 3; i++)
		if(eyeReal(i) < 0.000001 && eyeReal(i) > -0.000001)
			eyeReal(i) = 0; 
	

	int a = eyeReal(2) > 0 ? 1: -1;
	//int a = 1; 
	
	//Giro en Y
	double hip2 = sqrt(eyeReal(0) * eyeReal(0) + eyeReal(2) * eyeReal(2));
	eyeReal = {hip2 * cos(beta * PI/180), eyeReal(1), a * hip2 * sin(angulo(1) * PI / 180)};
	//eyeReal = {hip2 * cos(angulo(1) * PI / 180), eyeReal(1), a * hip2 * sin(angulo(1) * PI / 180)};
	std::cout << "Eye Después Transformación Y:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	std::cout << "UP = :\t" << up(0) << ", \t" << up(1) << ", \t" << up(2) << std::endl;

	//if( a > 0 && eyeInicial(2) < 0 || a < 0 && eyeInicial(2) > 0)
	for(int i= 0; i < 3; i++)
		if(eyeReal(i) < 0.000001 && eyeReal(i) > -0.000001)
			eyeReal(i) = 0; 

	//up = {eyeReal(0), up(1), eyeReal(2)};
		//up = {-sin(alfa * PI / 180) * sin(beta * PI / 180), cos(alfa * PI / 180), -sin(alfa * PI / 180) * cos(beta * PI / 180)};
	std::cout << "Eye Después Transformación Y:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	std::cout << "UP = :\t" << up(0) << ", \t" << up(1) << ", \t" << up(2) << std::endl;
	//up(1) = cos(angulo(0));
	

}

void Camara::girarX(double angle){
	
	angulo(0) += angle;
	if(angulo(0) < 0)
		angulo(0) += 360;
	else if (angulo(0) > 360)
		angulo(0) -= 360;

	girar();

	/*
	Tupla3f n, u, v; 
	cambiaSistemaCoordenadasACoordenadasDeLaCamara(n, u, v);

	std::vector<Tupla3f> a, b, c;

	c.push_back(u);
	c.push_back(v); 
	c.push_back(n); 

	a = traspuesta(c);
	//a = c;
	//c = traspuesta(a);

	b = {{1,          0,           0}, 
	     {0, cos(angulo(0) * PI / 180), sin(angulo(0) * PI / 180) }, 
	     {0, sin(angulo(0) * PI / 180), cos(angulo(0) * PI / 180)} };

	//imprimeMatriz("\n\nimprimeMatriz A", a);
	//imprimeMatriz("imprimeMatriz B", b);

	a = producto_matricial3x3(a,b);
	//imprimeMatriz("\nimprimeMatriz axb" ,a);

	//imprimeMatriz("imprimeMatriz C", c);

	 
	a = producto_matricial3x3(a,c);
	//imprimeMatriz("\n\nimprimeMatriz axbxc", a); 
	eyeReal = producto_matricial3x1(a,eyeInicial);
	std::cout << "Eye Después Transformación X:\t" << eyeReal(0) << ", \t" << eyeReal(1) << ", \t" << eyeReal(2) << std::endl;
	
	//if( eyeReal(2) < 0 )
	//	up(1) = -1;  

	//imprimeMatriz("\n\nimprimeMatriz A", a);
	//imprimeMatriz("imprimeMatriz B", b);
	//imprimeMatriz("imprimeMatriz C", c);
	//imprimeMatriz("imprimeMatriz C"c);
	*/

	/*
	angulo(0) += angle;
	if(angulo(0) < 0)
		angulo(0) += 360;
	else if (angulo(0) > 360)
		angulo(0) -= 360;


	girar();
	*/
	/*Tupla3f n, u, v; 
	//int a = eyeInicial(2) > 0 ? 1: -1;
	int a = eyeReal(2) > 0 ? 1: -1;
	
	std::cout << "\nEye Antes Transformación X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;
	// Pasamos de coordenadas del mundo a coordenadas de la cámara
	cambiaSistemaCoordenadasACoordenadasDeLaCamara(n, u, v);

	angulo(0) += angle;
	angle = angulo(0);

	double hip = sqrt(eyeInicial(1) * eyeInicial(1) + eyeInicial(2) * eyeInicial(2));
	std::cout << "Eye Antes Giro X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;
	cout << "cos(" << angle <<" * PI / 180) = " << cos(angle * PI / 180) << endl;
	cout << "sin(" << angle <<" * PI / 180) = " << sin(angle * PI / 180) << endl;
	cout << "hip = " << hip << endl;
	//eyeInicial(1) = eyeInicial(1) >= 0 ? (hip * sin(angle * PI / 180)) : (-hip * sin(angle * PI / 180));
	//float a = (hip * sin(angle * PI / 180)) ; 
	//float b = eyeInicial(2) >= 0 ? (hip * cos(angle * PI / 180)) : (-hip * cos(angle * PI / 180));

	eyeReal = {eyeInicial(0), hip * sin(angle * PI / 180), hip * cos(angle * PI / 180)};
	std::cout << "Eye Después Giro X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;

	// Pasamos de coordenadas de la cámara a coordenadas del mundo
	cambiaSistemaCoordenadasACoordenadasDelMundo(n, u, v);
	std::cout << "Eye Después Transformación X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl << endl;

	//if( a > 0 && eyeInicial(2) < 0 || a < 0 && eyeInicial(2) > 0)
	if( a > 0 && eyeReal(2) < 0 || a < 0 && eyeReal(2) > 0)
		up(1) = -up(1);  

	*/
}



void Camara::girarY(double angle){

	/*
	Tupla3f n, u, v; 
	cambiaSistemaCoordenadasACoordenadasDeLaCamara(n, u, v);

	std::vector<Tupla3f> a, b, c;

	c.push_back(u);
	c.push_back(v); 
	c.push_back(n); 

	a = traspuesta(c);
	//a = c;
	//c = traspuesta(a);

	angulo(1) += angle;
	if(angulo(1) < 0)
		angulo(1) += 360;
	else if (angulo(1) > 360)
		angulo(1) -= 360;

	b = {{cos(angle * PI / 180),          0,  -sin(angle * PI / 180)}, 
	     {					  0,          1,                      0},
	     {sin(angle * PI / 180),          0,  cos(angle * PI / 180)}};

	//imprimeMatriz("\n\nimprimeMatriz A", a);
	//imprimeMatriz("imprimeMatriz B", b);

	a = producto_matricial3x3(a,b);
	//imprimeMatriz("\nimprimeMatriz axb" ,a);

	//imprimeMatriz("imprimeMatriz C", c);

	 
	a = producto_matricial3x3(a,c);
	//imprimeMatriz("\n\nimprimeMatriz axbxc", a); 
	eyeReal = producto_matricial3x1(a,eyeReal);
	//up = producto_matricial3x1(a,eyeReal);
	*/

	
	angulo(1) += angle;
	if(angulo(1) < 0)
		angulo(1) += 360;
	else if (angulo(1) > 360)
		angulo(1) -= 360;

	girar();
	
	/*
	Tupla3f n, u, v; 

	std::cout << "\nEye Antes Transformación X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;
	// Pasamos de coordenadas del mundo a coordenadas de la cámara
	cambiaSistemaCoordenadasACoordenadasDeLaCamara(n, u, v);
	
	angulo(1) += angle;
	angle = angulo(1);

	double hip = sqrt(eyeInicial(1)*eyeInicial(1) + eyeInicial(2)*eyeInicial(2));
	std::cout << "Eye Antes Giro X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;
	cout << "cos(" << angle <<" * PI / 180) = " << cos(angle * PI / 180) << endl;
	cout << "sin(" << angle <<" * PI / 180) = " << sin(angle * PI / 180) << endl;
	cout << "hip = " << hip << endl;
	// Aplicamos el giro
	eyeReal = {sin(angle*PI/180)*hip, eyeInicial(1), cos(angle*PI/180)*hip};
	std::cout << "Eye Después Giro X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl;

	// Pasamos de coordenadas de la cámara a coordenadas del mundo
	cambiaSistemaCoordenadasACoordenadasDelMundo(n, u, v);
	std::cout << "Eye Después Transformación X:\t" << eyeInicial(0) << ", \t" << eyeInicial(1) << ", \t" << eyeInicial(2) << std::endl << endl;
	*/

}
void Camara::girarZ(double angle){
	
}

float Camara::producto_escalar(Tupla3f v1, Tupla3f v2){
	return producto_escalar(v1, v2, 3); 
}
float Camara::producto_escalar(Tupla3f v1, Tupla3f v2, int d)
{
	float resultado = 0;

	for (int i=0; i < d; i++) {
		resultado += v1(i) * v2(i);
	}
	return resultado;
}


std::vector<Tupla3f> Camara::traspuesta(std::vector<Tupla3f> a){
	//cout << "Traspuesta  Antes" << endl; 
	//imprimeMatriz(a);
	vector<Tupla3f> salida = {{a[0](0), a[1](0), a[2](0)},
							  {a[0](1), a[1](1), a[2](1)},
							  {a[0](2), a[1](2), a[2](2)}};

	//cout << "Traspuesta  Después" << endl; 
	//imprimeMatriz(salida);

	return salida; 

}

std::vector<Tupla3f> Camara::producto_matricial3x3(std::vector<Tupla3f> a, std::vector<Tupla3f> b){
	
	std::vector<Tupla3f> c = traspuesta(b);

	vector<Tupla3f> salida = {{producto_escalar(a[0],c[0]), producto_escalar(a[0],c[1]), producto_escalar(a[0],c[2])},
							  {producto_escalar(a[1],c[0]), producto_escalar(a[1],c[1]), producto_escalar(a[1],c[2])},
							  {producto_escalar(a[2],c[0]), producto_escalar(a[2],c[1]), producto_escalar(a[2],c[2])},};

	return salida; 

}

Tupla3f Camara::producto_matricial3x1(std::vector<Tupla3f> a, Tupla3f b){
	Tupla3f salida = {producto_escalar(a[0],b), producto_escalar(a[1], b), producto_escalar(a[2],b)};

	return salida; 
}


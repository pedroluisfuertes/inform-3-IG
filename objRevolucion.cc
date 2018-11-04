// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


#include "aux.h"
#include "objRevolucion.h"
#include "iostream"
#include <math.h>
#include <utility>
#include "ply_reader.h"


using namespace std;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion( ){}; 
ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil )
{
   std::vector<Tupla3f> perfil;
      ply::read_vertices(nombre_ply_perfil, perfil);

      int num_instancias_perf = 20;
      bool tapaSuperior = true; 
      bool tapaInferior = true; 
      int eje = 1;
      crearMalla(perfil, num_instancias_perf, eje, tapaSuperior, tapaInferior); 
      colorear(); 
}
void ObjRevolucion::crearMalla( const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int eje, const bool tapaSuperior, const bool tapaInferior){

  ////cout << " M = " << M << endl; 
  ////cout << " N = " << N << endl; 
  
  /*
  puntosTapas.fisrt punto superior
  puntosTapas.second punto inferior
  */
  //bool puntosTapas.first = false;
  //bool puntosTapas.second = false;

  //int eje = calcularEjeGiro(perfil_original);
  //int eje = 1; 
bool sentidoPuntosAscendente = calcularSentidoPuntos(eje, perfil_original); 
pair<bool,bool> puntosTapas = calcularPuntosTapas(perfil_original, eje, sentidoPuntosAscendente);
calcularPuntos(perfil_original, num_instancias_perf, eje, sentidoPuntosAscendente, puntosTapas);
const int N  = forzarTapas(tapaSuperior, tapaInferior,  puntosTapas, perfil_original, eje, sentidoPuntosAscendente) ;
for (int i = 0; i < vertices.size(); i ++){
  cout << "Vertice " << i << endl; 
  cout << "  x = " << vertices[i](0) << endl;
  cout << "  y = " << vertices[i](1) << endl;
  cout << "  z = " << vertices[i](2) << endl << endl;
}
generarTriangulos(puntosTapas, N, num_instancias_perf); 



}

bool ObjRevolucion::calcularSentidoPuntos(int eje, const std::vector<Tupla3f> &tup){
  return tup[0](eje) < tup[1](eje);
}

pair<bool,bool> ObjRevolucion::calcularPuntosTapas (const std::vector<Tupla3f> & perfil_original, const int eje, const bool sentidoPuntosAscendente){
  
  pair<bool, bool> puntosTapas;
  switch ( eje ){

    case 0:
      if(sentidoPuntosAscendente){
        puntosTapas.second = perfil_original[0](1) == 0 && perfil_original[0](2) == 0 ;
        puntosTapas.first = perfil_original[perfil_original.size()-1](1) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
      }else{
        puntosTapas.first = perfil_original[0](1) == 0 && perfil_original[0](2) == 0 ;
        puntosTapas.second = perfil_original[perfil_original.size()-1](1) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
      }
    break;
    case 1:
    if(sentidoPuntosAscendente){
        puntosTapas.second = perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ;
        puntosTapas.first = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
      }else{
        puntosTapas.first = perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ;
        puntosTapas.second = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
      }
    break;
    case 2:
    if(sentidoPuntosAscendente){
        puntosTapas.second = perfil_original[0](0) == 0 && perfil_original[0](1) == 0 ;
        puntosTapas.first = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](1) == 0;
      }else{
        puntosTapas.first = perfil_original[0](0) == 0 && perfil_original[0](1) == 0 ;
        puntosTapas.second = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](1) == 0;
      }
    break;

  }
  return puntosTapas;
}

void ObjRevolucion::calcularPuntos(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int eje, const bool sentidoPuntosAscendente,const pair<bool,bool> puntosTapas){
  
const int N = perfil_original.size(); 

int inicio, fin;

  if(sentidoPuntosAscendente){ 
    inicio = puntosTapas.second ? 1 : 0;
    fin = puntosTapas.first ? N - 1 : N;

    for(int i = inicio; i < fin; i++){
      for(int j = 0; j < num_instancias_perf; j++){        
        vertices.push_back(calcularPuntoRotado(perfil_original ,eje, i, PI*j/(num_instancias_perf - 1)));
      }
    }
    if(puntosTapas.second) vertices.push_back(perfil_original[0]);
    if(puntosTapas.first) vertices.push_back(perfil_original[perfil_original.size() - 1]);
  }else{
    fin = puntosTapas.second ? 1 : 0;
    inicio = puntosTapas.first ? N - 2 : N - 1;
    for(int i = inicio; i >= fin; i--){
      for(int j = 0; j < num_instancias_perf; j++){
        vertices.push_back(calcularPuntoRotado(perfil_original ,eje, i, PI*j/(num_instancias_perf - 1)));
      }
    }
    if(puntosTapas.second) vertices.push_back(perfil_original[perfil_original.size() - 1]);
    if(puntosTapas.first) vertices.push_back(perfil_original[0]);
  }
}
Tupla3f ObjRevolucion::calcularPuntoRotado(const std::vector<Tupla3f> & perfil_original, const int eje, const int i, const float alfa){
  Tupla3f vertice; 
  float x;
  float y; 
  float z;

  switch ( eje ){
    case 0:
      x = perfil_original[i](0);                                                  // Coordenada x (No cambia)
      y = perfil_original[i](1) * sin(alfa) -  perfil_original[i](2) * cos(alfa); // Coordenada y 
      z = perfil_original[i](1) * cos(alfa) +  perfil_original[i](2) * sin(alfa); // Coordenada z
    break;
    case 1:
      x = perfil_original[i](0) * cos(alfa) + perfil_original[i](2) * sin(alfa);  // Coordenada x
      y = perfil_original[i](1);                                                  // Coordenada y (No cambia)
      z = perfil_original[i](2) * cos(alfa) - perfil_original[i](0) * sin(alfa);  // Coordenada z
    break;
    case 2:
     x = perfil_original[i](0) * cos(alfa) - perfil_original[i](1) * sin(alfa); // Coordenada x
     y = perfil_original[i](0) * sin(alfa) + perfil_original[i](1) * cos(alfa); // Coordenada y 
     z = perfil_original[i](2); 
    break;

  }
  vertice = {x, y, z};
  return vertice;

}

int ObjRevolucion::forzarTapas(const bool tapaSuperior, const bool tapaInferior, pair<bool,bool> &puntosTapas, const std::vector<Tupla3f> & perfil_original, const int eje, const bool sentidoPuntosAscendente){
  Tupla3f vertice; 

  int N = perfil_original.size();
 // Forzar tapas
 if(tapaInferior && !puntosTapas.second){
   N++;
   puntosTapas.second = true;
   vertice = proyectarPunto(perfil_original, eje, true, sentidoPuntosAscendente);
   // Si en la figura ya había un vertice superior
   if (!puntosTapas.first)
     vertices.push_back(vertice);
   else{
     vector<Tupla3f>::iterator it = vertices.end();
     it--;
     vertices.insert ( it , vertice );
   }
 }
 if(tapaSuperior && !puntosTapas.first){
   N++;
   puntosTapas.first = true;
   vertices.push_back(proyectarPunto(perfil_original, eje, false, sentidoPuntosAscendente));
 }

 return N; 

}

Tupla3f ObjRevolucion::proyectarPunto(const std::vector<Tupla3f> & perfil_original, const int eje, const bool tapaInferior, const bool sentidoPuntosAscendente){
   Tupla3f vertice; 
  float x;
  float y; 
  float z;

  int i;
  if(!sentidoPuntosAscendente)
    i = tapaInferior ? perfil_original.size() - 1 : 0;
  else
   i = tapaInferior ? 0 : perfil_original.size() - 1;

  switch ( eje ){
    case 0:
      x = perfil_original[i](0);
      y = 0;
      z = 0;
    break;
    case 1:
      x = 0;
      y = perfil_original[i](1);
      z = 0; 
    break;
    case 2:
     x = 0;
     y = 0;
     z = perfil_original[i](2); 
    break;

  }
  vertice = {x, y, z};
  return vertice;

}

void ObjRevolucion::generarTriangulos(const pair<bool,bool> &puntosTapas, const int N, const int num_instancias_perf){
  
  Tupla3i triangulo; 
  int v1;
  int v2; 
  int v3;

  int fin = N - 1;
  if (puntosTapas.first){ fin--;}  
  if (puntosTapas.second){ fin--;} 
  int inicio;  
  for(int i = 0; i < fin; i++){
    for(int j = 0; j < num_instancias_perf; j++){

      /* Triángulos inferiores */
      v1 = num_instancias_perf * i + j;
      v2 = ((v1 + 1) % num_instancias_perf) + (num_instancias_perf * i); 
      v3 = v2 + num_instancias_perf;
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  |  "; 
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);

      /* Triángulos Superiores */
      v3 = (i + 1) * num_instancias_perf + j;
      v2 = ((v3 + 1) % num_instancias_perf) + (num_instancias_perf * (i +1));
      v1 = v3 - num_instancias_perf;
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  " << endl;
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);

    }
  }
  // Tapa inferior
  if(puntosTapas.second){
    v1 = puntosTapas.first ? num_instancias_perf*(N-2) : num_instancias_perf*(N-1);
    //cout << "Tapa inferior:" << endl;
    for(int j = 0; j < num_instancias_perf; j++){
      /* Triángulos Superiores */
      v3 = j;
      v2 = (j + 1) % num_instancias_perf;
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  " << endl;
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);
    }
  }
  // Tapa Superior
  if(puntosTapas.first){
    v1 = puntosTapas.second ? num_instancias_perf*(N-2) + 1 : num_instancias_perf*(N-1);
    int num_instancias_perfaux = puntosTapas.second ?  num_instancias_perf * (N-2): num_instancias_perf * (N-1);
    inicio = puntosTapas.second ? num_instancias_perf * (N-3) : num_instancias_perf * (N-2);
    //cout << "Tapa superior:" << endl;
    for(int j = 0; j <  num_instancias_perf; j++){
    /* Triángulos Superiores */
      v2 = inicio + j;
      v3 = inicio + ((j + 1) % num_instancias_perf);
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  " << endl;
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);
    }
  }

}

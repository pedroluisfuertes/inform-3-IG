// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


#include "aux.h"
#include "objRevolucion.h"
#include "iostream"
#include <math.h>
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
  
  int N = perfil_original.size(); 
  const int M = num_instancias_perf;

  //cout << " M = " << M << endl; 
  //cout << " N = " << N << endl; 
  Tupla3f vertice; 
  float x;
  float y; 
  float z;
  float alfa;
  bool puntoTapaSuperior = false;
  bool puntoTapaInferior = false;

  //int eje = calcularEjeGiro(perfil_original);
  //int eje = 1; 
  bool sentidoPuntosAscendente = calcularSentidoPuntos(eje, perfil_original); 
 
  //cout << "eje = " << eje << endl;
  int inicio;
  int fin; 

  switch ( eje ){

    case 0: // Eje x
      //cout << "Eje de rotación: X" << endl;
      if(!sentidoPuntosAscendente){
        puntoTapaInferior = perfil_original[0](1) == 0 && perfil_original[0](2) == 0 ;
        puntoTapaSuperior = perfil_original[perfil_original.size()-1](1) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
        inicio = puntoTapaInferior ? 1 : 0;
        fin = puntoTapaSuperior ? N - 1 : N;
        for(int i = inicio; i < fin; i++){
          for(int j = 0; j < M; j++){
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0);                                                  // Coordenada x (No cambia)
            y = perfil_original[i](1) * sin(alfa) -  perfil_original[i](2) * cos(alfa); // Coordenada y 
            z = perfil_original[i](1) * cos(alfa) +  perfil_original[i](2) * sin(alfa); // Coordenada z
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[0]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[perfil_original.size() - 1]);

        
      }else{
        puntoTapaSuperior = perfil_original[0](1) == 0 && perfil_original[0](2) == 0 ;
        puntoTapaInferior = perfil_original[perfil_original.size()-1](1) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
        //puntoTapaSuperior = 0; 
        fin = puntoTapaInferior ? 1 : 0;
        inicio = puntoTapaSuperior ? N - 2 : N - 1;
        for(int i = inicio; i >= fin; i--){
          for(int j = 0; j < M; j++){
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0);                                                  // Coordenada x (No cambia)
            y = perfil_original[i](1) * sin(alfa) -  perfil_original[i](2) * cos(alfa); // Coordenada y 
            z = perfil_original[i](1) * cos(alfa) +  perfil_original[i](2) * sin(alfa); // Coordenada z
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[perfil_original.size() - 1]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[0]);
      }
    break; 
    case 1: // Eje y
      // Generamos los vértices gigrando sobre el eje Y
      //cout << "Eje de rotación: Y" << endl;
      if(sentidoPuntosAscendente){ 
        puntoTapaInferior = perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ;
        puntoTapaSuperior = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
        inicio = puntoTapaInferior ? 1 : 0;
        fin = puntoTapaSuperior ? N - 1 : N;

        for(int i = inicio; i < fin; i++){
          for(int j = 0; j < M; j++){ 
          
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0) * cos(alfa) + perfil_original[i](2) * sin(alfa);  // Coordenada x
            y = perfil_original[i](1);                                                  // Coordenada y (No cambia)
            z = perfil_original[i](2) * cos(alfa) - perfil_original[i](0) * sin(alfa);  // Coordenada z
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[0]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[perfil_original.size() - 1]);
        
        // Forzar tapas
        if(tapaInferior && !puntoTapaInferior){
          N++;
          puntoTapaInferior = true;
          x = 0;
          y = perfil_original[0](1);
          z = 0; 
          vertice = {x, y, z};
          // Si en la figura ya había un vertice superior
          if (!puntoTapaSuperior)
            vertices.push_back(vertice);
          else{
            vector<Tupla3f>::iterator it = vertices.end();
            it--;
            vertices.insert ( it , vertice );
          }

        }
        if(tapaSuperior && !puntoTapaSuperior){
          N++;
          puntoTapaSuperior = true;
          x = 0;
          y = perfil_original[perfil_original.size() - 1](1);
          z = 0; 
          vertice = {x, y, z};
          vertices.push_back(vertice);
        }
          

      }else{
        puntoTapaSuperior = perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ;
        puntoTapaInferior = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0;
        //puntoTapaSuperior = 0; 
        fin = puntoTapaInferior ? 1 : 0;
        inicio = puntoTapaSuperior ? N - 2 : N - 1;
        for(int i = inicio; i >= fin; i--){
          for(int j = 0; j < M; j++){
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0) * cos(alfa) + perfil_original[i](2) * sin(alfa);  // Coordenada x
            y = perfil_original[i](1);                                                  // Coordenada y (No cambia)
            z = perfil_original[i](2) * cos(alfa) - perfil_original[i](0) * sin(alfa);  // Coordenada z
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[perfil_original.size() - 1]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[0]);

        // Forzar tapas
        if(tapaInferior && !puntoTapaInferior){
          N++;
          puntoTapaInferior = true;
          x = 0;
          y = perfil_original[perfil_original.size() - 1](1);
          z = 0; 
          vertice = {x, y, z};
          vertices.push_back(vertice);
          // Si en la figura ya había un vertice superior
          if (!puntoTapaSuperior)
            vertices.push_back(vertice);
          else{
            vector<Tupla3f>::iterator it = vertices.end();
            it--;
            vertices.insert ( it , vertice );
          }

        }
        if(tapaSuperior && !puntoTapaSuperior){
          N++;
          puntoTapaSuperior = true;
          x = 0;
          y = perfil_original[0](1);
          z = 0; 
          vertice = {x, y, z};
          vertices.push_back(vertice);
        }

      }
    break;
    case 2: // Eje z
      //cout << "Eje de rotación: Z" << endl;
      if(sentidoPuntosAscendente){ 
        puntoTapaInferior = perfil_original[0](0) == 0 && perfil_original[0](1) == 0 ;
        puntoTapaSuperior = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](1) == 0;
        inicio = puntoTapaInferior ? 1 : 0;
        fin = puntoTapaSuperior ? N - 1 : N;
        for(int i = inicio; i < fin; i++){
          for(int j = 0; j < M; j++){
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0) * cos(alfa) - perfil_original[i](1) * sin(alfa); // Coordenada x
            y = perfil_original[i](0) * sin(alfa) + perfil_original[i](1) * cos(alfa); // Coordenada y 
            z = perfil_original[i](2);                                                 // Coordenada z (No cambia)
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[0]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[perfil_original.size() - 1]);
      }else{
        puntoTapaSuperior = perfil_original[0](0) == 0 && perfil_original[0](1) == 0 ;
        puntoTapaInferior = perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](1) == 0;
        //puntoTapaSuperior = 0; 
        fin = puntoTapaInferior ? 1 : 0;
        inicio = puntoTapaSuperior ? N - 2 : N - 1;
        for(int i = inicio; i >= fin; i--){
          for(int j = 0; j < M; j++){
            alfa = 2*PI*j/M; 
            x = perfil_original[i](0) * cos(alfa) - perfil_original[i](1) * sin(alfa); // Coordenada x
            y = perfil_original[i](0) * sin(alfa) + perfil_original[i](1) * cos(alfa); // Coordenada y 
            z = perfil_original[i](2);                                                 // Coordenada z (No cambia)
            vertice = {x, y, z};
            vertices.push_back(vertice);
          }
        }
        if(puntoTapaInferior) vertices.push_back(perfil_original[perfil_original.size() - 1]);
        if(puntoTapaSuperior) vertices.push_back(perfil_original[0]);
      }
    break;
    default:
      //cout << "ERROR: Eje de rotación inválido." << endl;
    break;

  }
for (int i = 0; i < vertices.size(); i++){
  //cout << "Vertice " << i << ": " << endl;
  //cout << " x = " << vertices[i](0) << endl; 
  //cout << " y = " << vertices[i](1) << endl; 
  //cout << " z = " << vertices[i](2) << endl << endl; 

}

  //cout << "sentidoPuntosAscendente = " << sentidoPuntosAscendente << endl; 
  //cout << "puntoTapaSuperior = " << puntoTapaSuperior << endl;
  //cout << "puntoTapaInferior = " << puntoTapaInferior << endl;

  // Generamos los triángulos
  Tupla3i triangulo; 
  int v1;
  int v2; 
  int v3;

  //cout << "\n\ntriangulos: " << endl;
  fin = N-1; 
  if (puntoTapaInferior){ fin--;}  
  if (puntoTapaSuperior){ fin--;} 
  //cout << "inicio = " << inicio << "  fin = " << fin << endl; 

  for(int i = 0; i < fin; i++){
    for(int j = 0; j < M; j++){

      /* Triángulos inferiores */
      v1 = M * i + j;
      v2 = ((v1 + 1) % M) + (M * i); 
      v3 = v2 + M;
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  |  "; 
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);

      /* Triángulos Superiores */
      v3 = (i + 1) * M + j;
      v2 = ((v3 + 1) % M) + (M * (i +1));
      v1 = v3 - M;
      //cout << "v1 = " << v1 << "  "; 
      //cout << "v2 = " << v2 << "  "; 
      //cout << "v3 = " << v3 << "  " << endl;
      triangulo = { v1, v2, v3};
      triangulos.push_back(triangulo);

    }
  }
  if(puntoTapaInferior){
    v1 = puntoTapaSuperior ? M*(N-2) : M*(N-1);
    //cout << "Tapa inferior:" << endl;
    for(int j = 0; j < M; j++){
      /* Triángulos Superiores */
        v3 = j;
        v2 = (j + 1) % M;
        //cout << "v1 = " << v1 << "  "; 
        //cout << "v2 = " << v2 << "  "; 
        //cout << "v3 = " << v3 << "  " << endl;
        triangulo = { v1, v2, v3};
        triangulos.push_back(triangulo);
      }
  }
  if(puntoTapaSuperior){
    v1 = puntoTapaInferior ? M*(N-2) + 1 : M*(N-1);
    int Maux = puntoTapaInferior ?  M * (N-2): M * (N-1);
    inicio = puntoTapaInferior ? M * (N-3) : M * (N-2);
    //cout << "Tapa superior:" << endl;
    for(int j = 0; j <  M; j++){
      /* Triángulos Superiores */
        v2 = inicio + j;
        v3 = inicio + ((j + 1) % M);
        //cout << "v1 = " << v1 << "  "; 
        //cout << "v2 = " << v2 << "  "; 
        //cout << "v3 = " << v3 << "  " << endl;
        triangulo = { v1, v2, v3};
        triangulos.push_back(triangulo);
      }
    }



}

bool ObjRevolucion::calcularSentidoPuntos(int eje, const std::vector<Tupla3f> &tup){
  return tup[0](eje) < tup[1](eje);
}
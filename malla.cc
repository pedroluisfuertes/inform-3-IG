/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include "iostream"
#include <math.h>

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

using namespace std;

void ObjMallaIndexada::draw_ModoInmediato(int modo, int color)
{   

    // habilitar uso de un array de vértices
    glEnableClientState( GL_VERTEX_ARRAY );

    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;

    switch( modo )
   {
      case 0:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        dibujaInmediato(color);
      break ;
      case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Con líneas
        dibujaInmediato(color);
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Con puntos
        glPointSize(8); // Cambiamos el tamaño de los puntos para que se vean mejor
        //glEnable(GL_POINT_SMOOTH); // Para que se vean redondos
        //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
        //glEnable(GL_BLEND);
        dibujaInmediato(color);
      break;
      case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        /*
        void glColorPointer(  GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
        GLint size: indica si son 3 o 4 colores, para el color alfa
        GLsizei stride: indica si los números están escritos con float o con int
        GLsizei stride: si hay que poner ofset
        const GLvoid * pointer: y donde empieza el puntero
        */
        glEnableClientState( GL_COLOR_ARRAY );
        
        glColorPointer( 3, GL_FLOAT, 0, colores[color].data());

        std::vector<Tupla3i> triangulos1 ; // una terna de 3 enteros por cada cara o triángulo
        std::vector<Tupla3i> triangulos2 ; // una terna de 3 enteros por cada cara o triángulo

        for(int i = 0; i < triangulos.size(); i++){
          if( i % 2 == 0)
            triangulos1.push_back(triangulos[i]);
          else
            triangulos2.push_back(triangulos[i]);
        }

        glDrawElements( GL_TRIANGLES, triangulos1.size()*3, GL_UNSIGNED_INT, triangulos1.data() );
        glColorPointer( 3, GL_FLOAT, 0, colores[(color + 1)%colores.size()].data());
        glDrawElements( GL_TRIANGLES, triangulos2.size()*3, GL_UNSIGNED_INT, triangulos2.data() );
        glDisableClientState(GL_COLOR_ARRAY);
      break ;
      
   }

    // deshabilitar array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );
}

void ObjMallaIndexada::dibujaInmediato(int color){
  // visualizar, indicando: tipo de primitiva, número de índices,
      // tipo de los índices, y dirección de la tabla de índices
      glEnableClientState( GL_COLOR_ARRAY );
      glColorPointer( 3, GL_FLOAT, 0, colores[color].data());
      glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
      glDisableClientState(GL_COLOR_ARRAY);
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(int modo, int color)
{ 

   switch( modo )
   {
      case 0:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        dibujaDiferido(color);
      break ;
       case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Solido
        dibujaDiferido(color);
      break ;
       case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Solido
        dibujaDiferido(color);
      break ;
      case 3:
        //cout << "No soportado para el modo diferido" << endl;
      break;
    }
    

}
void ObjMallaIndexada::dibujaDiferido(int color){

  if(!id_vbo_vertices) // Si el VBO no existe, lo creamos
      id_vbo_vertices   = CrearVBO(GL_ARRAY_BUFFER,         3*vertices.size()*sizeof(float),          vertices.data());        
    
    if(!id_vbo_triangulos) // Si el VBO no existe, lo creamos
      id_vbo_triangulos = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangulos.size()*sizeof(unsigned int), triangulos.data());        
    
    if(!id_vbo_colores) // Si el VBO no existe, lo creamos
      id_vbo_colores    = CrearVBO(GL_ARRAY_BUFFER,         3*colores[0].size()*sizeof(float),        colores[color].data());        
    

    // especificar localización y formato de la tabla de vértices, habilitar tabla
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_vertices );  // activar VBO de vértices
    glVertexPointer( 3, GL_FLOAT, 0, 0 );              // especifica formato y offset (=0)
    glBindBuffer( GL_ARRAY_BUFFER, 0 );                // desactivar VBO de vértices.
    glEnableClientState( GL_VERTEX_ARRAY );            // habilitar tabla de vértices
    
    // Colores
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_colores ); // activar VBO de colores     
    glColorPointer( 3, GL_FLOAT, 0, 0);              // 
    glBindBuffer( GL_ARRAY_BUFFER, 0 );              // Desactivar el VBO de colores 
    glEnableClientState( GL_COLOR_ARRAY );           // Habili


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos  
    glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 ) ; // Pintar el array de triángulos
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos

    // Desactivamos el array de colores
    glDisableClientState(GL_COLOR_ARRAY); 
    // desactivar uso de array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );

}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(bool modo_diferido, int modo, int color)
{

  glEnable(GL_CULL_FACE);
  if(modo_diferido)
    draw_ModoDiferido(modo, color);
  else
    draw_ModoInmediato(modo, color);


}

void ObjMallaIndexada::colorear(){
  // Damos colores a los objetos, independeientemente del número de caras
  const std::vector<Tupla3f> colores_model = { { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 1 } }; 
    colores.resize(colores_model.size()); 
    for(int i = 0; i < colores_model.size(); i++){
      for(int j = 0; j < vertices.size(); j++){
        colores[i].push_back(colores_model[i]); 
      }
    }
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 2)
}

GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
    //if (!id_vbo) // Para generarlo sólo si es distinto de 0
    GLuint id_vbo;
    glGenBuffers( 1, &id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
    glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador

    // esta instrucción hace la transferencia de datos desde RAM hacia GPU
    glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
    glBindBuffer( tipo_vbo, 0 ); // desactivación del VBO (activar 0)

    return id_vbo ; // devolver el identificador resultado
}

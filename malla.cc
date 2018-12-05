/*+
Autor: Pedro Luis Fuertes Moreno
Grupo: 3º A3
*/

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include "textura.h"
#include "iostream"
#include <math.h>

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

using namespace std;

ObjMallaIndexada::ObjMallaIndexada(){
  
  Tupla4f ambiente  ;
  Tupla4f difusa    ;
  Tupla4f especular ;
  float brillo      ;

  /* Materiales por defecto */
  //Material 1
  ambiente  = {  0.3,  0.3,  0.3, 1.0};
  difusa    = {  0.1,  0.1,  0.1, 1.0};
  especular = { 0.05, 0.05, 0.05, 1.0};
  brillo    = 1;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

  //Material 2
  ambiente  = {  0.3,  0.3,  0.3, 1.0 };
  difusa    = {  0.8,  0.8,  0.8, 1.0 };
  especular = { 0.05, 0.05, 0.05, 1.0 };
  brillo    = 1;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

  //Material 3
  ambiente  = {  0.3,  0.3,  0.3, 1.0 };
  difusa    = {  0.1,  0.1,  0.1, 1.0 };
  especular = {  0.6,  0.6,  0.6, 1.0 };
  brillo    = 10;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

  //Material 4
  ambiente  = {  0.3,  0.3,  0.3, 1.0 };
  difusa    = {  1.0,  1.0,  1.0, 1.0 };
  especular = {  1.0,  1.0,  1.0, 1.0 };
  brillo    = 1;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

 //Rubber Yellow
  ambiente  = {  0.05,  0.05,     0, 1.0};
  difusa    = {   0.5,   0.5,   0.4, 1.0};
  especular = {   0.7,   0.7,  0.04, 1.0};
  brillo    = 10;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

 //Ruby
  ambiente  = {  0.175,  0.192,  0.192, 1.0 };
  difusa    = {  0.614,  0.041,  0.041, 1.0 };
  especular = {  0.728,  0.627,  0.627, 1.0 };
  brillo    = 76.8;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

 //Material 4
  ambiente  = {  0.175,  0.012,  0.012, 1.0 };
  difusa    = {  0.508,  0.0508, 0.508, 1.0 };
  especular = {  0.508,  0.0508, 0.508, 1.0 };
  brillo    = 51.2;
  materiales.push_back(Material(ambiente, difusa,especular,brillo));

 
}


void ObjMallaIndexada::draw_ModoInmediato(ModoVis modo)
{   

    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    if(glIsEnabled(GL_LIGHTING)){
      glNormalPointer( GL_FLOAT, 0, normales_vertices.data() ) ;
      glEnableClientState( GL_NORMAL_ARRAY );
    }
    

    // habilitar uso de un array de vértices
    glEnableClientState( GL_VERTEX_ARRAY );

    switch( modo )
   {
      case SOLIDO:
        //cout << "Modo solido" << endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        dibujaInmediato();
      break ;
      case LINEAS:
        //cout << "Modo lineas" << endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Con líneas
        dibujaInmediato();
        break;
      case PUNTOS:
        //cout << "Modo puntos" << endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Con puntos
        glPointSize(8); // Cambiamos el tamaño de los puntos para que se vean mejor
        glEnable(GL_POINT_SMOOTH); // Para que se vean redondos
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
        glEnable(GL_BLEND);
        dibujaInmediato();
        glDisable(GL_BLEND);
        glDisable(GL_POINT_SMOOTH);
      break;
      case AJEDREZ:
        //cout << "Modo ajedrez" << endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        /*
        void glColorPointer(  GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
        GLint size: indica si son 3 o 4 colores, para el color alfa
        GLsizei stride: indica si los números están escritos con float o con int
        GLsizei stride: si hay que poner ofset
        const GLvoid * pointer: y donde empieza el puntero
        */
        glEnableClientState( GL_COLOR_ARRAY );
        
        

        std::vector<Tupla3i> triangulos1 ; // una terna de 3 enteros por cada cara o triángulo
        std::vector<Tupla3i> triangulos2 ; // una terna de 3 enteros por cada cara o triángulo

        for(int i = 0; i < triangulos.size(); i++){
          if( i % 2 == 0)
            triangulos1.push_back(triangulos[i]);
          else
            triangulos2.push_back(triangulos[i]);
        }
        glColorPointer( 3, GL_FLOAT, 0, colores[colorActivo].data());
        glDrawElements( GL_TRIANGLES, triangulos1.size()*3, GL_UNSIGNED_INT, triangulos1.data() );
        glColorPointer( 3, GL_FLOAT, 0, colores[(colorActivo + 1) % colores.size()].data());
        glDrawElements( GL_TRIANGLES, triangulos2.size()*3, GL_UNSIGNED_INT, triangulos2.data() );
        glDisableClientState(GL_COLOR_ARRAY);
      break ;
      
   }

    // deshabilitar array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );
    if(glIsEnabled(GL_LIGHTING))
      glDisableClientState( GL_NORMAL_ARRAY );
      
}

void ObjMallaIndexada::dibujaInmediato(){
  // visualizar, indicando: tipo de primitiva, número de índices,
      // tipo de los índices, y dirección de la tabla de índices
        if(!texturas.empty()){
          glColor3f(1,1,1);
          //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //glMatrixMode(GL_MODELVIEW);
          //glLoadIdentity();
          texturas[texturaActiva].activar();
          Textura::activarTexturas();
          glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
          //glDrawArrays(GL_QUADS, 0, 4);
          Textura::desactivarTexturas();
          //glutSwapBuffers();
        }else if (!glIsEnabled(GL_LIGHTING)){
          glEnableClientState( GL_COLOR_ARRAY );
          glColorPointer( 3, GL_FLOAT, 0, colores[colorActivo].data());
          glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
          glDisableClientState(GL_COLOR_ARRAY);
        }else{
          glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
        }
      
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(ModoVis modo)
{ 

   switch( modo )
   {
      case SOLIDO:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
        dibujaDiferido();
      break ;
       case LINEAS:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Solido
        dibujaDiferido();
      break ;
       case PUNTOS:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Solido
        dibujaDiferido();
      break ;
      case AJEDREZ:
        //cout << "No soportado para el modo diferido" << endl;
      break;
    }
    

}
void ObjMallaIndexada::dibujaDiferido(){

  if(!id_vbo_vertices) // Si el VBO no existe, lo creamos
      id_vbo_vertices   = CrearVBO(GL_ARRAY_BUFFER,         3*vertices.size()*sizeof(float),          vertices.data());        
    
    if(!id_vbo_triangulos) // Si el VBO no existe, lo creamos
      id_vbo_triangulos = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangulos.size()*sizeof(unsigned int), triangulos.data());        
    
    if(!id_vbo_colores || colorActivoAntDif!=colorActivo){
      if(colorActivoAntDif!=colorActivo)
        eliminarVBO(id_vbo_colores);
      id_vbo_colores    = CrearVBO(GL_ARRAY_BUFFER,         3*colores[0].size()*sizeof(float),        colores[colorActivo].data());    
      colorActivoAntDif = colorActivo;    
    }
    
    if(!id_vbo_normales)
      id_vbo_normales    = CrearVBO(GL_ARRAY_BUFFER,       3*normales_vertices.size()*sizeof(float), normales_vertices.data()); 
    
    // especificar localización y formato de la tabla de vértices, habilitar tabla
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_vertices );  // activar VBO de vértices
    glVertexPointer( 3, GL_FLOAT, 0, 0 );              // especifica formato y offset (=0)
    glBindBuffer( GL_ARRAY_BUFFER, 0 );                // desactivar VBO de vértices.
    glEnableClientState( GL_VERTEX_ARRAY );            // habilitar tabla de vértices
    

    if (!glIsEnabled(GL_LIGHTING) && texturas.empty()){
      // Colores
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_colores ); // activar VBO de colores     
      glColorPointer( 3, GL_FLOAT, 0, 0);              // 
      glBindBuffer( GL_ARRAY_BUFFER, 0 );              // Desactivar el VBO de colores 
      glEnableClientState( GL_COLOR_ARRAY );           // Habili      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos  

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos 
      glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 ) ; // Pintar el array de triángulos
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos      // Desactivamos el array de colores
      glDisableClientState(GL_COLOR_ARRAY); 
    }else{
      if(!glIsEnabled(GL_LIGHTING)){
        //Texturas
        glColor3f(1,1,1);
        texturas[texturaActiva].activar();
        Textura::activarTexturas();

        //Triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos 
        glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 ) ; // Pintar el array de triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos      // Desactivamos el array de colores
        Textura::desactivarTexturas();
      }else if(texturas.empty()){
        //Luces
        glBindBuffer( GL_ARRAY_BUFFER, id_vbo_normales ); // activar VBO de colores     
        glNormalPointer( GL_FLOAT, 0, 0);              // 
        glBindBuffer( GL_ARRAY_BUFFER, 0 );              // Desactivar el VBO de colores 
        glEnableClientState( GL_NORMAL_ARRAY );           // Habili      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos  

        //Triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos 
        glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 ) ; // Pintar el array de triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos      // Desactivamos el array de colores
        glDisableClientState(GL_NORMAL_ARRAY); 
        
      }else{
        //Textures y luces
        //Normales
        glBindBuffer( GL_ARRAY_BUFFER, id_vbo_normales ); // activar VBO de colores     
        glNormalPointer( GL_FLOAT, 0, 0);              // 
        glBindBuffer( GL_ARRAY_BUFFER, 0 );              // Desactivar el VBO de colores 
        glEnableClientState( GL_NORMAL_ARRAY );           // Habili      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos  

        //Texturas
        glColor3f(1,1,1);
        texturas[texturaActiva].activar();
        Textura::activarTexturas();

        //Triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos );// activar VBO de triángulos 
        glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 ) ; // Pintar el array de triángulos
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos      // Desactivamos el array de colores
        glDisableClientState(GL_NORMAL_ARRAY); 
        Textura::desactivarTexturas();

      }
    }


    
    // desactivar uso de array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );

}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(ModoVis modo, bool modo_diferido)
{

  glEnable(GL_CULL_FACE);
 activarMaterial();
  
  if(modo_diferido)
    draw_ModoDiferido(modo);
  else
    draw_ModoInmediato(modo);


}

void ObjMallaIndexada::inicializar(){
  calcular_normales(); 
  colorear();
}

void ObjMallaIndexada::colorear(){
  // Damos colores a los objetos, independeientemente del número de caras
  const std::vector<Tupla3f> colores_model = { { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 1 } }; 
    colores.resize(colores_model.size() + 2); 
    for(int i = 0; i < colores_model.size(); i++){
      for(int j = 0; j < vertices.size(); j++){
        colores[i].push_back(colores_model[i]); 
      }
    }
    // Color aleatorio
    Tupla3f color; 
    for(int j = 0; j < vertices.size(); j++){
      color[0] = (rand() % 10000 + 1) / 10000.0;
      color[1] = (rand() % 10000 + 1) / 10000.0;
      color[2] = (rand() % 10000 + 1) / 10000.0;
      //cout << "color = " << color[0] << endl; 
      //cout << "color = " << color[1] << endl; 
      //cout << "color = " << color[2] << endl; 
      colores[colores_model.size()].push_back(color); 
    }


    for(int i= 0; i < normales_vertices.size(); i++){
      color[0] = abs(normales_vertices[i](0));
      color[1] = abs(normales_vertices[i](1));
      color[2] = abs(normales_vertices[i](2));
      colores[colores_model.size() + 1].push_back(color); 
    }
    //colores[colores_model.size() + 1] = normales_vertices;


}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
  std::vector<Tupla3f> normales_triangulos;
  for(int i = 0; i < vertices.size(); i++){
    normales_vertices.push_back(Tupla3f(0,0,0));
  }

  std::vector<int> aux(5,8);

  //std::vector<Tupla3f> aux(Tupla3f(0,0,0));
  //&normales_vertices = &aux;  

  std::vector<int> m_vertices(vertices.size(), 0);
  //Calculamos las normales de las caras
  for(int i = 0; i < triangulos.size(); i++){
    // Calculamos el valor de la normal de la cara
    Tupla3f a1 = vertices[triangulos[i](1)] - vertices[triangulos[i](0)],
            a2 = vertices[triangulos[i](2)] - vertices[triangulos[i](0)],
            n  = {a1(1) * a2(2) - a1(2) * a2(1),
                  a1(2) * a2(0) - a1(0) * a2(2),
                  a1(0) * a2(1) - a1(1) * a2(0)};

    //Módulo
    float m = sqrt(pow(n(0),2) + pow(n(1),2) + pow(n(2),2));

    //Normalización e inserción
    normales_triangulos.push_back(Tupla3f(n(0)/m, n(1)/m, n(2)/m));

    // Cuenta el número de aritas que tiene el vertice
    m_vertices[triangulos[i](0)] += 1;
    m_vertices[triangulos[i](1)] += 1;
    m_vertices[triangulos[i](2)] += 1;

    //Valor del vértice
    normales_vertices[triangulos[i](0)] = normales_vertices[triangulos[i](0)] + normales_triangulos[i];
    normales_vertices[triangulos[i](1)] = normales_vertices[triangulos[i](1)] + normales_triangulos[i];
    normales_vertices[triangulos[i](2)] = normales_vertices[triangulos[i](2)] + normales_triangulos[i];
  }

  // Normalizamos el valor de las normales de ls vertices
  for(int i = 0; i < m_vertices.size(); i++){
    normales_vertices[i] = normales_vertices[i]/m_vertices[i];
  }

  /*for(int i = 0; i < m_vertices.size(); i++){

    cout << "vertice (" << i << "): " << m_vertices[i]<< endl;
  }
  
  for(int j = 0; j < normales_triangulos.size(); j++){
    cout << "Cara:" << triangulos[j](0) << "\tNormal cara (" << j << ") = " << normales_triangulos[j](0) << endl; 
    cout << "Cara:" << triangulos[j](1) << "\tNormal cara (" << j << ") = " << normales_triangulos[j](1) << endl; 
    cout << "Cara:" << triangulos[j](2) << "\tNormal cara (" << j << ") = " << normales_triangulos[j](2) << endl << endl; 
  }

  for(int j = 0; j < normales_vertices.size(); j++){
      cout << "vertice = " << vertices[j](0) << "\tNormal vertice (" << j << ") = " << normales_vertices[j](0) << endl; 
      cout << "vertice = " << vertices[j](1) << "\tNormal vertice (" << j << ") = " << normales_vertices[j](1) << endl; 
      cout << "vertice = " << vertices[j](2) << "\tNormal vertice (" << j << ") = " << normales_vertices[j](2) << endl << endl; 
    }*/

}

void ObjMallaIndexada::setColor(int color){
  colorActivo = (color) % colores.size();
  cout << "Color activo = " << colorActivo << endl; 

}

void ObjMallaIndexada::siguienteColor(){
  colorActivo = (++colorActivo) % colores.size();
  cout << "Color activo = " << colorActivo << endl; 

}

void ObjMallaIndexada::setMaterial(int material){
  materialActivo = (material) % materiales.size();
  cout << "Material activo = " << materialActivo << endl; 
  activarMaterial();
}

void ObjMallaIndexada::siguienteMaterial(){
  materialActivo = (++materialActivo) % materiales.size();
  cout << "Material activo = " << materialActivo << endl; 
  activarMaterial();
}

void ObjMallaIndexada::activarMaterial(){
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,  (GLfloat *) &materiales[materialActivo].difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (GLfloat *) &materiales[materialActivo].especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,  (GLfloat *) &materiales[materialActivo].ambiente);
  glMaterialf( GL_FRONT_AND_BACK,GL_SHININESS, materiales[materialActivo].brillo);
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

void ObjMallaIndexada::eliminarVBO(GLuint id){
  glDeleteBuffers(1, &id);
}

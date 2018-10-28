// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 4, 16 );
   cubo     = new Cubo();
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;
   int valorMinimo = 0;
   int intervalo = 5;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         rotacionPala = sin( 2.0*M_PI*valor_na );
         break ;
      case 1:
         alturaPala = valorMinimo;
         break ;
      case 2:
         movimientoPala = 4; 
         break ;
      case 3:
         rotacionBrazoPala = sin( 2.0*M_PI*valor_na );
         break ;
      case 4:
         alturaBrazo = 10;
         break ;
      case 5:
         rotacionBrazo  = sin( 2.0*M_PI*valor_na );
         break ;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos

   constexpr float
      sep       = 1.5,  // separación entre centros de las columnas
      radio_cil = 0.5 , // radio del cilindro más fino
      radio_cil2 = radio_cil+0.1 ; // radio del cilindro más grueso

   glPushMatrix();
      // primera columna
      //glColor3f( 0.6, 0.2, 0.0 );
      //columna( altura_1, ag_rotacion_1, radio_cil );
      // segunda columna
      /*glPushMatrix();
         glTranslatef( sep, 0.0, 0.0 );
         glColor3f( 0.0, 0.2, 0.6 );
         columna( altura_2, ag_rotacion_2, radio_cil2 );
      glPopMatrix();*/
      // base
      /*glColor3f( 0.1, 0.6, 0.1 );
      glTranslatef( -radio_cil2, -0.1*radio_cil2, -radio_cil2 );
      glScalef( sep+2.0*radio_cil2, 0.1*radio_cil2, 2.0*radio_cil2 );
      glTranslatef( 0.5, 0.5, 0.5 );
      cubo->draw( modo_vis, usar_diferido );*/

      int longitudBrazoHorizontal = 15; 
      

      glPushMatrix();
      // Barra Vertical Superior
      glColor3f( 1, 1, 0.0 );
      barraVerticalSuperior( );
      glPopMatrix();

      

      glPopMatrix();
   
}
// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es una columna (cilindro) de altura = 'altura', con un cubo encima,
// rotado entorno a Y un ángulo en grados = 'ag_rotacion'

void GrafoParam::columna( const float altura, const float ag_rotacion,
                          const float radio_cil )
{


   glPushMatrix();
      glScalef( radio_cil, altura, radio_cil );
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
   glPushMatrix( );
      glTranslatef( 0.0, 0.5+altura, 0.0 );
      glRotatef( ag_rotacion, 0.0, 1.0, 0.0 );
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

   void GrafoParam::pala( ){
      
      // Engranche
      glPushMatrix();
         glTranslatef(0,-0.25/2,0);
         glScalef( 0.35, 0.25, 0.35 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Pala
      glPushMatrix();
         glScalef( 1.2, 0.1, 1.2 );
         glTranslatef(4-0.6,0,0);
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Brazo pala
      glPushMatrix();
         glTranslatef(4,0,0);
         glScalef( 4, 0.125, 0.125 );
         glRotatef( 90, 0.0, 0.0, 1.0 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
   }
   void GrafoParam::barraVerticalMenor( ){
      
      // Engranche
      glPushMatrix();
         glTranslatef(0.5,0,0);
         glRotatef( 90, 0.0, 0.0, 1.0 );
         glScalef( 0.5, 1, 0.5 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Brazo
      glPushMatrix();
         glTranslatef(0,-ALTURA_BRAZO_MENOR,0);
         glScalef( 0.25, ALTURA_BRAZO_MENOR, 0.25 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();

      glTranslatef( 0.0, -ALTURA_BRAZO_MENOR, 0.0 );
      glPushMatrix();

      //Pala
      glColor3f( 1, 1, 0.0 );
      glTranslatef( 0.0, alturaPala, 0.0 );
      glRotatef( rotacionPala, 0.0, 1.0, 0.0 );
      pala();
      glPopMatrix();
   }
   void GrafoParam::barraHorizontal(  ){
       
       // Engranche
      glPushMatrix();
         glTranslatef(0, -0.5/2, 0);
         glScalef( 0.75, 0.5, 0.75 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Barra
      glPushMatrix();
         glTranslatef(3*LONGITUD_BRAZO_HORIZONTAL/4, 0, 0);
         glRotatef( 90, 0.0, 0.0, 1.0 );
         glScalef( 0.25, LONGITUD_BRAZO_HORIZONTAL, 0.25 );
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Contrapeso
      glPushMatrix();
         glTranslatef(-LONGITUD_BRAZO_HORIZONTAL/4, 0, 0);
         glScalef( 0.75, 0.75, 0.75 );
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();

      glPushMatrix();
      // Varra Vertical Menor
      glColor3f( 1, 1, 0.0 );
      glTranslatef( movimientoPala, 0.0, 0.0 );
      glRotatef( rotacionPala, 1.0, 0.0, 0.0 );
      barraVerticalMenor();
      glPopMatrix();
      
   }
   void GrafoParam::barraVerticalSuperior( ){
      // Apoyo
      glPushMatrix();
         glTranslatef(0, 2, 0);
         glPushMatrix();
            glTranslatef(0, ALTURA_GRUA, 0);
            glScalef( 1, 0.05, 1);
            cilindro->draw( modo_vis, usar_diferido );
         glPopMatrix();
         // Apoyo
         glPushMatrix();
            glScalef( 0.75, 1, 0.75 );
            cilindro->draw( modo_vis, usar_diferido );
         glPopMatrix();
         // Barra
         glPushMatrix();
            glScalef( 0.5, ALTURA_GRUA, 0.5 );
            cilindro->draw( modo_vis, usar_diferido );
         glPopMatrix();
      glPopMatrix();
      // Base
      glPushMatrix();
         glTranslatef(0, 1, 0);
         glScalef( 3, 2, 3 );
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();

      glTranslatef( 0.0, 10, 0.0 );

      glPushMatrix();
      // Barra Horizontal
      glColor3f( 1, 1, 0.0 );
      glTranslatef( 0.0, alturaBrazo, 0.0 );
      glRotatef( rotacionBrazo, 0.0, 1.0, 0.0 );
      barraHorizontal();
      glPopMatrix();

   }
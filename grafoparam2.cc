// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam2.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cubo = new Cubo(  );

   rotacionPala = 0; 
   rotacionBrazo = 0; 
   rotacionBrazoPala = 0; 
   alturaPala = ALTURA_MIN_PALA;
   movimientoPala = MOV_MIN_BRAZO_VER; 
   alturaBrazo = ALTURA_MAX_BRAZO_HOR;   
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
void GrafoParam::actualizarValorEfe( const unsigned iparam, const float delta_valores_na, const bool crece)
{
   actualizarValorEfe( iparam, delta_valores_na, crece, 7);
}
void GrafoParam::actualizarValorEfe( const unsigned iparam, const float delta_valores_na, const bool crece, const float paso)
{
   assert( iparam < num_parametros );

   using namespace std ;

   constexpr float vp = 2.5 ;

   /*cout << "Valores actualizados Antes (Delta = " << delta_valores_na << "): " << endl; 
   cout << "rotacionPala = " << rotacionPala << endl;
   cout << "alturaPala = " << alturaPala << endl;
   cout << "movimientoPala = " << movimientoPala << endl;
   cout << "rotacionBrazoPala = " << rotacionBrazoPala << endl;
   cout << "alturaBrazo = " << alturaBrazo << endl;
   cout << "rotacionBrazo = " << rotacionBrazo << endl;*/
   float delta; 

   switch( iparam )
   {
      case 0:
      //cout << "rotacionPala" << endl;
      delta = (delta_valores_na * 360/paso);
         if(crece)
            rotacionBrazoPala += delta;
         else
            rotacionBrazoPala -= delta;

         // Evita desbordamientos
         if(rotacionBrazoPala > 360)
            rotacionBrazoPala -= 360;
         else if(rotacionBrazoPala < 0)
            rotacionBrazoPala += 360;
         break ;
      case 1:
      //cout << "alturaPala" << endl;
      delta = (ALTURA_MAX_PALA - ALTURA_MIN_PALA) / paso * delta_valores_na;
         if(crece){
            //cout << "Altura pala antes " << alturaPala <<endl;
            movimientoPala +=  delta;
            //cout << "Altura pala despues " << alturaPala <<endl;
            //cout << "crece" << endl;
         }
         else{
            movimientoPala -= delta;
         }

         if(movimientoPala > ALTURA_MAX_PALA)
            movimientoPala = ALTURA_MAX_PALA;
         else if(movimientoPala < ALTURA_MIN_PALA)
            movimientoPala = ALTURA_MIN_PALA;
         break ;
   }

   /*cout << "Valores actualizados (Delta = " << delta_valores_na << "): " << endl; 
   cout << "rotacionPala = " << rotacionPala << endl;
   cout << "alturaPala = " << alturaPala << endl;
   cout << "movimientoPala = " << movimientoPala << endl;
   cout << "rotacionBrazoPala = " << rotacionBrazoPala << endl;
   cout << "alturaBrazo = " << alturaBrazo << endl;
   cout << "rotacionBrazo = " << rotacionBrazo << endl << endl << endl << endl << endl;*/
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );

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
         glScalef(0.3, 0.3, 0.3);
         barraHorizontal( );
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
         glTranslatef( 1, 0, 0.0 );
         glScalef( 2, 1, 2 );
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();
      // Pala
      glPushMatrix();
         glTranslatef( 0, 0.5, 0 );
         glScalef( 1, 2, 2 );
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();
   }
   void GrafoParam::barraVerticalMenor( ){
      glPushMatrix();
      glTranslatef( 0.5, 0, 0.0 );
      // Engranche
      glPushMatrix();
         glTranslatef( 0, ALTURA_MAX_PALA/2, 0.0 );
         glScalef( 1, ALTURA_MAX_PALA, 2 );
         cubo->draw( modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glColor3f( 1, 1, 0.0 );
         glTranslatef( 1.0, movimientoPala, 0.0 );
         pala();
      glPopMatrix();
      glPopMatrix();
   }
   void GrafoParam::barraHorizontal(  ){
       
      // Contrapeso
      glPushMatrix();
         
         glTranslatef(-1, 1, 0);
         glScalef( 2, 2, 2 );
         cubo->draw( modo_vis, usar_diferido );
         glColor3f( 1, 0, 0.0 );
      glPopMatrix();

      glPushMatrix();
      // Varra Vertical Menor
      glRotatef( rotacionBrazoPala, 0.0, 0.0, 1.0 );
      barraVerticalMenor();
      glColor3f( 1, 0, 1 );
      glPopMatrix();
      
   }
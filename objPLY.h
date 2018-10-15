#ifndef __BJPLY_H__
#define __BJPLY_H__


#include "malla.h"

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

#endif
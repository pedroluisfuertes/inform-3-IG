#include "objPLY.h"
#include "ply_reader.h"

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
    // leer la lista de caras y vértices
    ply::read( nombre_archivo, vertices, triangulos );
   	inicializar();

}
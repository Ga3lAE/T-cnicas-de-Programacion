/* 
 * File:   NodoAtencion.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:54 PM
 */

#ifndef NODOATENCION_H
#define NODOATENCION_H

#include "Atencion.h"

struct NodoAtencion{
    struct Atencion atencion;
    struct NodoAtencion *siguiente;
};

#endif /* NODOATENCION_H */


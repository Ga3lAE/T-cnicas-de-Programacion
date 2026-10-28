/* 
 * File:   NodoAlumno.h
 * Author: arias
 *
 * Created on 5 de julio de 2025, 06:14 PM
 */

#ifndef NODOALUMNO_H
#define NODOALUMNO_H

#include "Alumno.h"

struct NodoAlumno{
    struct Alumno alumno;
    struct NodoAlumno *siguiente;  
};

#endif /* NODOALUMNO_H */


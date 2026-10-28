/* 
 * File:   NodoEscala.h
 * Author: arias
 *
 * Created on 5 de julio de 2025, 05:12 PM
 */

#ifndef NODOESCALA_H
#define NODOESCALA_H

#include "Escala.h"

struct NodoEscala{
    struct Escala escala;
    struct NodoEscala *siguiente;
};

#endif /* NODOESCALA_H */


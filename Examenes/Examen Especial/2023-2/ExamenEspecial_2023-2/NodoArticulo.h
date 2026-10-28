/* 
 * File:   NodoArticulo.h
 * Author: arias
 *
 * Created on 27 de junio de 2025, 07:27 PM
 */

#ifndef NODOARTICULO_H
#define NODOARTICULO_H

#include "Articulo.h"

struct NodoArticulo{
    struct Articulo articulo;
    struct NodoArticulo *siguiente;
};

#endif /* NODOARTICULO_H */


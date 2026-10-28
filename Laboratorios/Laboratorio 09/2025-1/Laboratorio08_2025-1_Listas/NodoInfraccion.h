/* 
 * File:   NodoInfraccion.h
 * Author: arias
 *
 * Created on 21 de junio de 2025, 11:52 PM
 */

#ifndef NODOINFRACCION_H
#define NODOINFRACCION_H

#include "Infraccion.h"

struct NodoInfraccion{
    struct Infraccion infraccion;
    struct NodoInfraccion *siguiente;
};

#endif /* NODOINFRACCION_H */


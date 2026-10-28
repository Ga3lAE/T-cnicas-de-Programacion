/* 
 * File:   NodoPalabra.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:28 PM
 */

#ifndef NODOPALABRA_H
#define NODOPALABRA_H

#include "Palabra.h"

struct NodoPalabra{
    struct Palabra palabra;
    struct NodoPalabra *siguiente;    
};

#endif /* NODOPALABRA_H */


/* 
 * File:   NodoPlato.h
 * Author: arias
 *
 * Created on 23 de junio de 2025, 11:49 PM
 */

#ifndef NODOPLATO_H
#define NODOPLATO_H

#include "Plato.h"

struct NodoPlato{
    struct Plato plato;
    struct NodoPlato *siguiente;
};


#endif /* NODOPLATO_H */


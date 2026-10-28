/* 
 * File:   NodoPlato.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:45 PM
 */

#ifndef NODOPLATO_H
#define NODOPLATO_H

#include "Plato.h"

struct NodoPlato{
    struct Plato plato;
    struct NodoPlato *siguiente;
};

#endif /* NODOPLATO_H */


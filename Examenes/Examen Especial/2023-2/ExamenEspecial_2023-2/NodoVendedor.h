/* 
 * File:   NodoVendedor.h
 * Author: arias
 *
 * Created on 27 de junio de 2025, 08:10 PM
 */

#ifndef NODOVENDEDOR_H
#define NODOVENDEDOR_H

#include "Vendedor.h"

struct NodoVendedor{
    struct Vendedor vendedor;
    struct NodoVendedor *siguiente;
};

#endif /* NODOVENDEDOR_H */


/* 
 * File:   NodoCliente.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 12:02 AM
 */

#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H

#include "Cliente.h"

struct NodoCliente{
    struct Cliente cliente;
    struct NodoCliente *siguiente;
};

#endif /* NODOCLIENTE_H */


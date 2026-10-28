/* 
 * File:   NodoEmpresa.h
 * Author: arias
 *
 * Created on 21 de junio de 2025, 11:51 PM
 */

#ifndef NODOEMPRESA_H
#define NODOEMPRESA_H

#include "Empresa.h"

struct NodoEmpresa{
    struct Empresa empresa;
    struct NodoEmpresa *siguiente;
};

#endif /* NODOEMPRESA_H */


/* 
 * File:   Empresa.h
 * Author: arias
 *
 * Created on 21 de junio de 2025, 11:49 PM
 */

#ifndef EMPRESA_H
#define EMPRESA_H

#include "Fecha.h"

struct Empresa{
    int dni;
    char *nombre;
    char *distrito;
    char *placas[10];
    int cantidadPlacas;
    struct Fecha fechaInfraccion;
    struct Fecha fechaPago;
    double totalMultas;
    double totalPagado;
    double totalAdeudado;
    int cantidadFaltas;
};

#endif /* EMPRESA_H */


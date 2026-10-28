/* 
 * File:   Venta.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:24 AM
 */

#ifndef VENTA_H
#define VENTA_H

#include "Cliente.h"

struct Venta{
    int dniComprador;
    char nombreComprador[MAX_CLIENTE_NOMBRE];
    int fecha;
    int calificacion;
};

#endif /* VENTA_H */


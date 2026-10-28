/* 
 * File:   Libreria.h
 * Author: arias
 *
 * Created on 13 de junio de 2025, 10:46 AM
 */

#ifndef LIBRERIA_H
#define LIBRERIA_H

#include "Venta.h"

#define MAX_CANT_LIBRERIA_VENTAS 10

struct Libreria{
    int codigo;
    struct Venta venta[MAX_CANT_LIBRERIA_VENTAS];
    int cantidadVentas;
    double totalVentas;
};

#endif /* LIBRERIA_H */


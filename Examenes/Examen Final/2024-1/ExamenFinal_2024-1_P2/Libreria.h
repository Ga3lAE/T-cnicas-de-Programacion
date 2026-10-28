/* 
 * File:   Libreria.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:26 AM
 */

#ifndef LIBRERIA_H
#define LIBRERIA_H

#include "Venta.h"

#define MAX_LIBRERIAS_VENTAS 10

struct Libreria{
    int codigo;
    struct Venta ventas[MAX_LIBRERIAS_VENTAS];
    int cantidadVentas;
    double totalVentas;
};

#endif /* LIBRERIA_H */


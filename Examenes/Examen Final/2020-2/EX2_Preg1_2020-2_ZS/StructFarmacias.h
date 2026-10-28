

/* 
 * File:   StructFarmacias.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:23 PM
 */

#ifndef STRUCTFARMACIAS_H
#define STRUCTFARMACIAS_H

#include "StructProductos.h"

struct Farmacia{
    int codigo;
    char distrito[30];
    struct Producto productosVendidos[10];
    int cantidadProductos;
};

#endif /* STRUCTFARMACIAS_H */


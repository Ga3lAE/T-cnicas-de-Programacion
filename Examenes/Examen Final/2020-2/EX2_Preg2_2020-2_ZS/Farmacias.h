

/* 
 * File:   Farmacias.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 18 de junio de 2023, 09:36 PM
 */

#ifndef FARMACIAS_H
#define FARMACIAS_H

#include "Productos.h"
struct Farmacia{
    int codigoFarmacia;
    char *distrito;
    struct Producto *productosVendidos;
    int cantidadProductos;
};

#endif /* FARMACIAS_H */


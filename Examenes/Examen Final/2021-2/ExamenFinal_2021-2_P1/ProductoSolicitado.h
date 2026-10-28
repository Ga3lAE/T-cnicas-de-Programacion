/* 
 * File:   ProductoSolicitado.h
 * Author: arias
 *
 * Created on 30 de noviembre de 2024, 06:36 PM
 */

#ifndef PRODUCTOSOLICITADO_H
#define PRODUCTOSOLICITADO_H

#include "StockDeProductos.h"

struct ProductoSolicitado{
    char codigo[MAX_PRODUCTO_CODIGO];
    char descripcion[MAX_PRODUCTO_DESCRIPCION];
    int cantidad;
    double precioUnitario;
    double subtotal;
};

#endif /* PRODUCTOSOLICITADO_H */


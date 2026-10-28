/* 
 * File:   StockDeProductos.h
 * Author: arias
 *
 * Created on 30 de noviembre de 2024, 06:25 PM
 */

#ifndef STOCKDEPRODUCTOS_H
#define STOCKDEPRODUCTOS_H

#define MAX_PRODUCTO_CODIGO 10
#define MAX_PRODUCTO_DESCRIPCION 60

struct StockDeProductos{
    char codigo[MAX_PRODUCTO_CODIGO];
    char descripcion[MAX_PRODUCTO_DESCRIPCION];
    int stock;
    double precio;
};

#endif /* STOCKDEPRODUCTOS_H */


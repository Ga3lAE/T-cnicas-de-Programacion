/* 
 * File:   ProductoPedido.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 06:02 PM
 */

#ifndef PRODUCTOPEDIDO_H
#define PRODUCTOPEDIDO_H

#define TAM_PRODUCTO_NOMBRE 60

struct ProductoPedido{
    char nombre[TAM_PRODUCTO_NOMBRE];
    int cantidad;
    double precio;
};

#endif /* PRODUCTOPEDIDO_H */


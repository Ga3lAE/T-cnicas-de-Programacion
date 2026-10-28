/* 
 * File:   ProductoPedido.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 06:00 PM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include "ProductoPedido.h"
#include "Direccion.h"

#define MAX_PRODUCTOS_VENDIDOS 10
#define TAM_REPARTIDOR_NOMBRE 60

struct Pedido{
    int codigo;
    struct ProductoPedido productos[MAX_PRODUCTOS_VENDIDOS];
    int cantidad;
    int hora;
    char repartidor [TAM_REPARTIDOR_NOMBRE];
    char codigoUsuario [TAM_USUARIO_CODIGO];
    struct Direccion direccion;
    double distancia;
    double montoTotal;
};

#endif /* PEDIDO_H */


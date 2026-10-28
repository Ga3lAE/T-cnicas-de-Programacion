/* 
 * File:   PedidoPorInternet.h
 * Author: arias
 *
 * Created on 30 de noviembre de 2024, 06:33 PM
 */

#ifndef PEDIDOPORINTERNET_H
#define PEDIDOPORINTERNET_H

#include "ProductoSolicitado.h"

#define MAX_PRODUCTOS_PEDIDOS 20

struct PedidoPorInternet{
    int numero;
    int fecha;
    int hora;
    int clienteDNI;
    struct ProductoSolicitado productosPedidos[MAX_PRODUCTOS_PEDIDOS];
    int cantidadPedida;
};

#endif /* PEDIDOPORINTERNET_H */


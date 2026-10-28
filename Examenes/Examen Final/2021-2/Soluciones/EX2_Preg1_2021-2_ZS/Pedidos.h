

/* 
 * File:   Pedido.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 25 de junio de 2023, 09:04 PM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include "ProductoSolicitado.h"

struct Pedido{
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct ProductoSolicitado productosPedidos[20];
    int cantProdPed;
};

#endif /* PEDIDO_H */


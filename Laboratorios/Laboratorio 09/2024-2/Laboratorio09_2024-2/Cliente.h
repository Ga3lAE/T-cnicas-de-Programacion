/* 
 * File:   Cliente.h
 * Author: arias
 *
 * Created on 15 de junio de 2025, 02:24 PM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include "Distrito.h"
#include "PlatoPedido.h"

#define MAX_CANT_CLIENTE_PEDIDOS 30

struct Cliente{
    int dni;
    char *nombre;
    struct Distrito distrito;
    struct PlatoPedido pedidos[MAX_CANT_CLIENTE_PEDIDOS]{};
    int cantidadDePedidos;
    double montoTotal;
};

#endif /* CLIENTE_H */


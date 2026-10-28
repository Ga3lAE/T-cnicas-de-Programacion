/* 
 * File:   Pedido.h
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 11:40 AM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include "Entregado.h"
#include "NoEntregado.h"

#define MAX_PEDIDO_ENTREGADO 20
#define MAX_PEDIDO_NO_ENTREGADO 20

struct Pedido{
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct Entregado* productosEntregados;
    int cantidadEntregado;
    struct NoEntregado* productosNoEntregados;
    int cantidadNoEntregado;
};

#endif /* PEDIDO_H */


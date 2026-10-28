

/* 
 * File:   stPedidos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 15 de junio de 2023, 12:55 PM
 */

#ifndef STPEDIDOS_H
#define STPEDIDOS_H

#include "Entregado.h"
#include "NoEntregado.h"

struct stPedidos{
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct Entregado *productosEntregados;
    int cantProdEnt;
    struct NoEntregado *productosNoEntregados;
    int cantProdNoEnt;
};

#endif /* STPEDIDOS_H */


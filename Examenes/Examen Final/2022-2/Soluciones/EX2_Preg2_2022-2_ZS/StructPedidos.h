

/* 
 * File:   StructPedidos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 08:22 PM
 */

#ifndef STRUCTPEDIDOS_H
#define STRUCTPEDIDOS_H


#include "StructProductoPedidos.h"
#include "StructDirecciones.h"

struct Pedido{
    int codigo;
    struct ProductoPedido productos[10];
    int cantProd;
    int hora;
    char repartidorRappi[60];
    char codigoUs[7];
    struct Direccion direccionRappi;
    double distancia;
    double montoTotal;
};

#endif /* STRUCTPEDIDOS_H */


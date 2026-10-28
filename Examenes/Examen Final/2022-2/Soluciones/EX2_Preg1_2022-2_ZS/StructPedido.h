

/* 
 * File:   StructPedido.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 30 de junio de 2023, 09:25 AM
 */

#ifndef STRUCTPEDIDO_H
#define STRUCTPEDIDO_H

#include "StructProductoPedido.h"

struct Pedido{
    int codigo;
    struct ProductoPedido *productos;
    int cantidadProductos;
    int hora;
    char *repartidorRappi;
    char *codigoUsuario;
    char *distrito;
    char *direccion;
    double montoTotal;
};

#endif /* STRUCTPEDIDO_H */


/* 
 * File:   Pedido.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 12:26 PM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include "ProductoPedido.h"

struct Pedido{
    int codigo;
    struct ProductoPedido* productos;
    int cantidadProductosPedidos;
    int hora;
    char *repartidorRappi;
    char* codigoUsuario;
    char* distrito;
    char* direccion;
    double montoTotal;
    
};


#endif /* PEDIDO_H */


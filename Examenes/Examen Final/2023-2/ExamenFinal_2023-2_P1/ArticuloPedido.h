/* 
 * File:   ArticuloPedido.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 03:09 PM
 */

#ifndef ARTICULOPEDIDO_H
#define ARTICULOPEDIDO_H

struct ArticuloPedido{
    char* codigo;
    int cantidad;
    int fechaUltPedido;
    double montoTotal;
};

#endif /* ARTICULOPEDIDO_H */


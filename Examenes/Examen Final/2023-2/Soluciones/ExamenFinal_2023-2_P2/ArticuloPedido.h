/* 
 * File:   ArticuloPedido.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:24 PM
 */

#ifndef ARTICULOPEDIDO_H
#define ARTICULOPEDIDO_H

#include "Articulo.h"

struct ArticuloPedido{
    char codigo[MAX_ART_COD];
    int cantidad;
    int fechaUltPed;
    double montoTotal;
};

#endif /* ARTICULOPEDIDO_H */


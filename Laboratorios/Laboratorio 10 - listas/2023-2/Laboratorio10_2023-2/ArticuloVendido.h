/* 
 * File:   ArticuloVendido.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:12 AM
 */

#ifndef ARTICULOVENDIDO_H
#define ARTICULOVENDIDO_H

#include "Articulo.h"

struct ArticuloVendido{
    char codigo[TAM_ART_COD];
    int cantidad;
    double montoVendido;
    double pagoVendedor;
};

#endif /* ARTICULOVENDIDO_H */


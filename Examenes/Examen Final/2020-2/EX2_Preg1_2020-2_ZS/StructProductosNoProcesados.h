

/* 
 * File:   StructProductosNoProcesados.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:37 PM
 */

#ifndef STRUCTPRODUCTOSNOPROCESADOS_H
#define STRUCTPRODUCTOSNOPROCESADOS_H

struct ProductoNoProcesado{
    int codigoFarmacia;
    char codigoProducto[8];
    char nombreProducto[50];
    int cantidadVendida;
    double precio;
};

#endif /* STRUCTPRODUCTOSNOPROCESADOS_H */




/* 
 * File:   StructProductos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:23 PM
 */

#ifndef STRUCTPRODUCTOS_H
#define STRUCTPRODUCTOS_H

struct Producto{
    char codigo[8];
    char nombre[50];
    int cantidadVendida;
    double recaudacion;
};

#endif /* STRUCTPRODUCTOS_H */


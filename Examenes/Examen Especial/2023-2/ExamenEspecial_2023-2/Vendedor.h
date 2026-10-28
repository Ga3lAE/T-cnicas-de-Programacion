/* 
 * File:   Vendedor.h
 * Author: arias
 *
 * Created on 27 de junio de 2025, 07:24 PM
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H

#define MAX_CANT_ARTICULOS_VENDEDOR 50

struct Vendedor{
    int codigo;
    char *nombre;
    double porcentajeVentas;
    double cuotaMinima;
    struct ArticuloPedido *articulosVendidos;
    int cantidadArticulosVendidos;
    double montoVendido;
    struct ArticuloPedido *articulosNoVendidos;
    int cantidadArticulosNoVendidos;
    double montoNoVendido;    
};

#endif /* VENDEDOR_H */


/* 
 * File:   Vendedor.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 03:10 PM
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H

#define MAX_VENDEDOR_VENDIDOS 50
#define MAX_VENDEDOR_PERDIDOS 50

struct Vendedor{
    int codigo;
    char* nombre;
    double porcVentas;
    double cuotaMin;
    struct ArticuloPedido* articulosVendidos;
    int cantArtVendidos;
    struct ArticuloPedido* articulosPerdidos;
    int cantArtPerdidos;
    double montoTotalVendido;
    double montoTotalPerdido;
    
};

#endif /* VENDEDOR_H */


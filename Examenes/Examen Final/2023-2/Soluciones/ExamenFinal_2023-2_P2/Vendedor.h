/* 
 * File:   Vendedor.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:25 PM
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H

#define MAX_VEND_NOMBRE 60
#define MAX_ART_VENDIDOS 50
#define MAX_ART_PERDIDOS 50

struct Vendedor{
    int codigo;
    char nombre[MAX_VEND_NOMBRE];
    double porcVentas;
    double cuotaMin;
    
    struct ArticuloPedido articulosVendidos[MAX_ART_VENDIDOS];
    int cantArtVendidos;
    struct ArticuloPedido articulosPerdidos[MAX_ART_PERDIDOS];
    int cantArtPerdidos;
    double montoTotalVendido;
    double montoTotalPerdido;
};

#endif /* VENDEDOR_H */


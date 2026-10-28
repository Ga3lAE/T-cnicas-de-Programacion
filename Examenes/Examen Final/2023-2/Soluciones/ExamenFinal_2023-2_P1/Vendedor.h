/* 
 * File:   Vendedor.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:25 PM
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H

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


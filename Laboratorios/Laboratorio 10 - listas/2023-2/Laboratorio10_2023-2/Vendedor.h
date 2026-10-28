/* 
 * File:   Vendedor.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:13 AM
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H

#define TAM_VEND_NOMBRE 60
#define MAX_ART_VENDIDOS 50

struct Vendedor{
    int codigo;
    char nombre[TAM_VEND_NOMBRE];
    double porcentajeVentas;
    double cuotaMinima;
    
    struct ArticuloVendido articulosVendidos[MAX_ART_VENDIDOS];
    int cantidadVendidos;
    double montoTotal;
    bool superaCuota;
   
};

#endif /* VENDEDOR_H */


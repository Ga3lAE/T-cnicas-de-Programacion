/* 
 * File:   Articulo.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:10 AM
 */

#ifndef ARTICULO_H
#define ARTICULO_H

#define TAM_ART_COD 10
#define TAM_ART_DESC 80

struct Articulo{
    char  codigo[TAM_ART_COD];
    char descripcion[TAM_ART_DESC];
    double precio;
    int cantidadVendidos;
    double montoVendido;
};

#endif /* ARTICULO_H */


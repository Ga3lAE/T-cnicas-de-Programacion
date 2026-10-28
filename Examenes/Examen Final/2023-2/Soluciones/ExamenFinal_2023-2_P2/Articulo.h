/* 
 * File:   Articulo.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:03 PM
 */

#ifndef ARTICULO_H
#define ARTICULO_H

#define MAX_ART_COD 10
#define MAX_ART_DESC 60

struct Articulo{
    char codigo[MAX_ART_COD];
    char descripcion[MAX_ART_DESC];
    int stock;
    double precio;

    int cantVendidos;
    double montoVendido;
    int cantPerdidos;
    double montoPerdido;
    
};

#endif /* ARTICULO_H */


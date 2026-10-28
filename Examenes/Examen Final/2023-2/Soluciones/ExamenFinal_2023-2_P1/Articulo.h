/* 
 * File:   Articulo.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:03 PM
 */

#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char* codigo;
    char* descripcion;
    int stock;
    double precio;

    int cantVendidos;
    double montoVendido;
    int cantPerdidos;
    double montoPerdido;
    
};

#endif /* ARTICULO_H */


/* 
 * File:   Articulo.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 02:52 PM
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


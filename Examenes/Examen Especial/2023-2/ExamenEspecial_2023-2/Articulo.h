/* 
 * File:   Articulo.h
 * Author: arias
 *
 * Created on 27 de junio de 2025, 07:22 PM
 */

#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char *codigo;
    char *descripcion;
    int stock;
    double precio;
    int cantidadVendida;
    double montoVendido;
    int cantidadNoVendida;
    double montoNoVendido;
};

#endif /* ARTICULO_H */


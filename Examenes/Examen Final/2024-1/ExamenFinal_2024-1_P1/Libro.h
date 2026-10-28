/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:27 AM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "Libreria.h"

#define MAX_LIBRO_LIBRERIAS 5

struct Libro{
    char* codigo;
    char* titulo;
    char* autor;
    double precio;
    struct Libreria* librerias;
    int cantidadLibrerias;
    double totalVentas;
    int unidadsVendidas;
    int cantidadBuenasCalificaciones;
    double sumaBuenasCalificaciones;
    int cantidadMalasCalificaciones;
    double sumaMalasCalificaciones;    
};

#endif /* LIBRO_H */


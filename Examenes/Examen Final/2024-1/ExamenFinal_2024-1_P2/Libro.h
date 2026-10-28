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

#define MAX_LIBRO_CODIGO 10
#define MAX_LIBRO_TITULO 60
#define MAX_LIBRO_AUTOR 40

struct Libro{
    char codigo[MAX_LIBRO_CODIGO];
    char titulo[MAX_LIBRO_TITULO];
    char autor[MAX_LIBRO_AUTOR];
    double precio;
    struct Libreria librerias[MAX_LIBRO_LIBRERIAS];
    int cantidadLibrerias;
    double totalVentas;
    int unidadsVendidas;
    int cantidadBuenasCalificaciones;
    double sumaBuenasCalificaciones;
    int cantidadMalasCalificaciones;
    double sumaMalasCalificaciones;    
};

#endif /* LIBRO_H */


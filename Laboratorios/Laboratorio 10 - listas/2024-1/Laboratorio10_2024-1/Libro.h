/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 12:00 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "Venta.h"
#include "Fecha.h"

#define MAX_CODIGO_LIBRO 10
#define MAX_AUTOR_LIBRO 50
#define MAX_TITULO_LIBRO 60

struct Libro{
    char codigo[MAX_CODIGO_LIBRO];
    char titulo[MAX_TITULO_LIBRO];
    char autor[MAX_AUTOR_LIBRO];
    double precio;
    struct Venta *ventas;
    int librosVendidos;
    struct Fecha fechaMasReciente;
    int sumaCalificaciones;
    int ranking;
    
};

#endif /* LIBRO_H */


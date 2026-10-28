/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 13 de junio de 2025, 10:47 AM
 */

#ifndef LIBRO_H
#define LIBRO_H

#define MAX_CANT_LIBRO_LIBRERIA 5

struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    double precio;
    struct Libreria librerias[MAX_CANT_LIBRO_LIBRERIA];
    int cantidadLibrerias;
    double totalVentas;
    int unidadesVendidas;
    int cantidadBuenasCalificaciones;
    double sumaBuenasCalificaciones;
    int cantidadMalasCalificaciones;
    double sumaMalasCalificaciones;
    
};

#endif /* LIBRO_H */


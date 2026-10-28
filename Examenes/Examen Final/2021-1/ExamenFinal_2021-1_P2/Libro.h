/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 09:14 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

struct Libro{
    char* codigo;
    char* titulo;
    char* autor;
    int aPublicacion;
    int cantidad;
    int prestamos;
};

#endif /* LIBRO_H */


/* 
 * File:   RegistroPrestamo.h
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 09:28 PM
 */

#ifndef REGISTROPRESTAMO_H
#define REGISTROPRESTAMO_H

#include "LibroPrestado.h"
#define MAX_LIBROS_PRESTADOS 7

struct RegistroPrestamo{
    int codigo;
    char* nombre;
    struct LibroPrestado* libros;
    int cantidadLibros;
};

#endif /* REGISTROPRESTAMO_H */


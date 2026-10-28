/* 
 * File:   Usuario.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:29 PM
 */

#ifndef USUARIO_H
#define USUARIO_H

#include "LibroEnSuPoder.h"

#define TAM_USUARIO_NOMBRE 60
#define MAX_LIBROS_PODER 10

struct Usuario{
    int dni;
    char nombre[TAM_USUARIO_NOMBRE]{};
    char categoria;
    double calificacion;
    struct LibroEnSuPoder libros[MAX_LIBROS_PODER]{};
    int cantLibros;
};


#endif /* USUARIO_H */


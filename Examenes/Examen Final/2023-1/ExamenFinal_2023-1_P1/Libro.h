/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 09:55 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "UsuariosConElLibro.h"

struct Libro{
    char* codigo;
    char* titulo;
    char* autor;
    int cantidad;
    double precio;
    struct UsuariosConElLibro* usuarios;
    int cantUsuarios;
    
    
};

#endif /* LIBRO_H */


/* 
 * File:   Usuario.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:29 PM
 */

#ifndef USUARIO_H
#define USUARIO_H

#include "LibroEnSuPoder.h"

struct Usuario{
    int dni;
    char* nombre;
    char categoria;
    double calificacion;
    struct LibroEnSuPoder *libros;
    int cantLibros;
};


#endif /* USUARIO_H */


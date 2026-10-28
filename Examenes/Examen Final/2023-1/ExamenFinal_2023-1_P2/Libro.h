/* 
 * File:   Libro.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 09:55 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "UsuariosConElLibro.h"

#define TAM_LIBRO_COD 8
#define TAM_LIBRO_TITULO 40
#define TAM_LIBRO_AUTOR 60
#define MAX_USUARIOS_LIBRO 60

struct Libro{
    char codigo[TAM_LIBRO_COD]{};
    char titulo[TAM_LIBRO_TITULO]{};
    char autor[TAM_LIBRO_AUTOR]{};
    int cantidad;
    double precio;
    struct UsuariosConElLibro usuarios[MAX_USUARIOS_LIBRO]{};
    int cantUsuarios;
    
    
};

#endif /* LIBRO_H */


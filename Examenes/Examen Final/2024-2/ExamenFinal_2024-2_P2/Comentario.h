/* 
 * File:   Comentario.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 09:48 PM
 */

#ifndef COMENTARIO_H
#define COMENTARIO_H

#include "Palabra.h"

#define MAX_TAM_COMENTARIO_TEXTO 100
#define MAX_CANT_COMENTARIO_PALABRAS 20

struct Comentario{
    char texto[MAX_TAM_COMENTARIO_TEXTO];
    char pre_procesado[MAX_TAM_COMENTARIO_TEXTO];
    struct Palabra palabras[MAX_CANT_COMENTARIO_PALABRAS];
    int cantidad_palabras;
    int polaridadTotal;
};

#endif /* COMENTARIO_H */


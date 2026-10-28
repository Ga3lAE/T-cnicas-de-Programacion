/* 
 * File:   Comentario.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 03:48 PM
 */

#ifndef COMENTARIO_H
#define COMENTARIO_H

#include "Palabra.h"

#define MAX_CANT_PALABRAS 20

struct Comentario{
    char *texto;
    char *pre_procesado;
    struct Palabra palabras[MAX_CANT_PALABRAS];
    int cantidad_palabras;
    int polaridad_total;
};

#endif /* COMENTARIO_H */


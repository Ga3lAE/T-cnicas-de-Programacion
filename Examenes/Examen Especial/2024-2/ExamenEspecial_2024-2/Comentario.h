/* 
 * File:   Comentario.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:19 PM
 */

#ifndef COMENTARIO_H
#define COMENTARIO_H

#include "Palabra.h"

#define  MAX_CANT_COMENTARIO_PALABRAS 20

struct Comentario{
    char *texto;
    char *preProcesado;
    struct Palabra palabras[MAX_CANT_COMENTARIO_PALABRAS];
    int cantidadPalabras;
    int polaridadTotal;   
};

#endif /* COMENTARIO_H */


/* 
 * File:   CursoMatriculado.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:54 PM
 */

#ifndef CURSOMATRICULADO_H
#define CURSOMATRICULADO_H

#include "Curso.h"

struct CursoMatriculado{
    char codigo[MAX_CURSO_CODIGO];
    char nombre[MAX_CURSO_NOMBRE];
    double creditos;
    int nota;
};


#endif /* CURSOMATRICULADO_H */


/* 
 * File:   Curso.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:31 PM
 */

#ifndef CURSO_H
#define CURSO_H

#define MAX_CURSO_CODIGO 8
#define MAX_CURSO_NOMBRE 70

struct Curso{
    char codigo[MAX_CURSO_CODIGO];
    char nombre[MAX_CURSO_NOMBRE];
    double creditos;
};


#endif /* CURSO_H */


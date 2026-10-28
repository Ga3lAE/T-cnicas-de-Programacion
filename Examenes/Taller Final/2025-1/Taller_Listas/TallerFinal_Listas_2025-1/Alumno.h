/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 5 de julio de 2025, 04:59 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Escala.h"

#define MAX_CANT_ALUMNO_CURSOS 8

struct Alumno{
    int codigo;
    char *nombre;
    struct Escala escala;
    struct Curso *cursos;
    int cantidadCursos;
    double totalCreditos;
    double totalPago;

};

#endif /* ALUMNO_H */


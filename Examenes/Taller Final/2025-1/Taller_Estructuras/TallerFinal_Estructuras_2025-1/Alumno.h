/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 6 de julio de 2025, 12:12 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Escala.h"
#include "Curso.h"

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


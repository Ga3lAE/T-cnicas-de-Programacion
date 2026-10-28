/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:51 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "CursoMatriculado.h"

#define MAX_ALUMNO_NOMBRE 60
#define MAX_ALUMNO_CURSOS_MATRICULADOS 10

struct Alumno{
    int codigo;
    char nombre[MAX_ALUMNO_NOMBRE];
  
    double cantidadCreditosAprobados;
    double cantidadCreditosDesaprobados;
    double cantidadCreditosPaseFacultad;
    
    struct CursoMatriculado cursosMatriculados[MAX_ALUMNO_CURSOS_MATRICULADOS];
    int cantidadCursosMatriculados;                
    
};

#endif /* ALUMNO_H */


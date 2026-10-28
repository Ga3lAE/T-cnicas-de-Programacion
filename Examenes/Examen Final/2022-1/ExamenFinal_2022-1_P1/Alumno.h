/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:51 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "CursoMatriculado.h"

struct Alumno{
    int codigo;
    char* nombre;
  
    struct CursoMatriculado* cursosMatriculados;
    
    int cantidadCursosMatriculados;
    
    
    int cantidadCursosAprobados;
    int cantidadCursosDesaprobados;
    
    double cantidadCreditosMatriculados;
    double cantidadCreditosAprobados;
    double cantidadCreditosDesaprobados;
    double cantidadCreditosPaseFacultad;
    
    double promedioCursosMatriculados;
    double promedioCursosAprobados;
    double promedioCursosDesaprobados;
    
    int sumaPonderadaAprobado;
    int sumaPonderadaDesaprobado;
    int sumaPonderadaCursos;
    
};

#endif /* ALUMNO_H */




/* 
 * File:   StructAlumno.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 29 de junio de 2023, 01:28 PM
 */

#ifndef STRUCTALUMNO_H
#define STRUCTALUMNO_H

#include "StructCursoMatriculado.h"

struct Alumno{
    int codigo;
    char *nombre;
    double credTotalAprob;
    double credTotalDesaprob;
    double credFaltantes;
    struct CursoMatriculado *cursosMatriculados;
    int cantCursosMatric;
    double promedioPonderado;
    double promedioPonderadoAprobados;
    double promedioPonderadoDesaprobados;
};

#endif /* STRUCTALUMNO_H */


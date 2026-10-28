

/* 
 * File:   Alumnos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 27 de junio de 2023, 03:23 PM
 */

#ifndef ALUMNOS_H
#define ALUMNOS_H

#include "CursoMatric.h"

struct Alumno{
    int codigo;
    char nombre[60];
    double cantCredAprob;
    double cantCredDesap;
    double credPasarFac;
    struct CursoMatric cursosMatriculados[10];
    int cantCursosMat;
};

#endif /* ALUMNOS_H */


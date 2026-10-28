/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 14 de junio de 2025, 08:31 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Facultad.h"

struct Alumno{
    int codigo;
    char *nombre;
    int numeroCursos;
    double sumaPonderada;
    double numeroCreditos;
    double promedioPonderado;
    struct Facultad facultad;
};

#endif /* ALUMNO_H */


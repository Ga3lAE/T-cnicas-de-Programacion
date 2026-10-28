

/* 
 * File:   Areas.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 28 de junio de 2023, 06:45 PM
 */

#ifndef AREAS_H
#define AREAS_H

#include "Empleados.h"

struct Area{
    int codigo;
    char *nombre;
    double horasLaborales;
    struct Empleado *empleados;
    int numeroEmpleados;
};

#endif /* AREAS_H */


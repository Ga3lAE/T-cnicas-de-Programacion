

/* 
 * File:   Empleados.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 28 de junio de 2023, 06:45 PM
 */

#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include "TotalHoraxMes.h"

struct Empleado{
    int dni;
    char *nombre;
    int diaIngreso;
    int mesIngreso;
    int anioIngreso;
    struct TotalHoraxMes *horasTrabajadas; 
    int numeroMesesLaborales;
    int codigoArea;
};

#endif /* EMPLEADOS_H */


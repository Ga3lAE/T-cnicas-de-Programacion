

/* 
 * File:   StructRegPrestamos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 14 de junio de 2023, 12:02 PM
 */

#ifndef STRUCTREGPRESTAMOS_H
#define STRUCTREGPRESTAMOS_H
#include "StructLibroPrestado.h"

struct RegPrestamo{
    int codigo;
    char *nombre;
    struct LibroPrestado *libro;
    int cantidadDeLibros;
};

#endif /* STRUCTREGPRESTAMOS_H */


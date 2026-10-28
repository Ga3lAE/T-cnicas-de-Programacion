/* 
 * File:   Venta.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 11:58 AM
 */

#ifndef VENTA_H
#define VENTA_H

#include "Fecha.h"

struct Venta{
    int nDNI;
    char nombre[60];
    struct Fecha fecha;
    int calificacion;
};


#endif /* VENTA_H */


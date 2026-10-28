/* 
 * File:   Plato.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 09:50 PM
 */

#ifndef PLATO_H
#define PLATO_H

#define MAX_TAM_PLATO_CODIGO 7
#define MAX_TAM_PLATO_NOMBRE 50

struct Plato{
    char codigo[MAX_TAM_PLATO_CODIGO];
    char nombre[MAX_TAM_PLATO_NOMBRE];
    double precio;
};

#endif /* PLATO_H */


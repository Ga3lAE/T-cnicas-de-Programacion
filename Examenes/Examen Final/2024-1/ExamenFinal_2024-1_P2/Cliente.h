/* 
 * File:   Cliente.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:24 AM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTE_NOMBRE 60

struct Cliente{
    int dni;
    char nombre[MAX_CLIENTE_NOMBRE];
    double montoComprado;
    double descuentoFuturo;
};


#endif /* CLIENTE_H */


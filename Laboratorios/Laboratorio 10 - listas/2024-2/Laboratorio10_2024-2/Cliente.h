/* 
 * File:   Cliente.h
 * Author: arias
 *
 * Created on 23 de junio de 2025, 11:47 PM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

struct Cliente{
    int dni;
    char *nombre;
    char *distrito;
    int cantidad;
    double pagoBruto;
    double total;
};

#endif /* CLIENTE_H */


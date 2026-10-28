/* 
 * File:   Direccion.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 05:48 PM
 */

#ifndef DIRECCION_H
#define DIRECCION_H

#define TAM_USUARIO_CODIGO 10
#define TAM_DISTRITO 40
#define TAM_DIRECCION 80

struct Direccion{
    char codigoUsuario[TAM_USUARIO_CODIGO];
    char distrito[TAM_DISTRITO];
    char direccion[TAM_DIRECCION];
    double latitud;
    double longitud;
};

#endif /* DIRECCION_H */


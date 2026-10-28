/* 
 * File:   Alumno.h
 * Author: arias
 *
 * Created on 10 de noviembre de 2024, 04:33 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#define TAM_ALUMNO_NOMBRE 60

// 20227341,Landa Piscoya Christian,D
struct Alumno{
    int codigo;
    char nombre[TAM_ALUMNO_NOMBRE]{};
    char codigoEscala;
};


#endif /* ALUMNO_H */


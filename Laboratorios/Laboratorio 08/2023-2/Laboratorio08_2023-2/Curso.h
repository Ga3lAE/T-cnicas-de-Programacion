/* 
 * File:   Curso.h
 * Author: arias
 *
 * Created on 10 de noviembre de 2024, 04:35 PM
 */

#ifndef CURSO_H
#define CURSO_H

#define TAM_CURSO_NOMBRE 80

// 109263,Algoritmia,4.25
struct Curso{
    int codigo;
    char nombre[TAM_CURSO_NOMBRE]{};
    double creditos;
    int cantidadMatriculados=0;
    double pagoMatriculados=0;
};


#endif /* CURSO_H */


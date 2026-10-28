/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 08:34 PM
 */

#ifndef STRUCTUSUARIO_H
#define STRUCTUSUARIO_H


#include "StructLibrosEnSuPoder.h"

struct Usuario{
    int dni;
    char nombre[60];
    char categoria;
    double calificacion;
    struct LibrosEnSuPoder libros[6];
    int cantidadDeLibros;
};

#endif /* STRUCTUSUARIO_H */


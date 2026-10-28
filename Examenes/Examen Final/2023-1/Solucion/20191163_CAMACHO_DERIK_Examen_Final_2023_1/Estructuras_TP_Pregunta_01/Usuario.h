/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 07:25 PM
 */

#ifndef USUARIO_H
#define USUARIO_H

#include "LibroEnSuPoder.h"

struct Usuario{
    int dni;
    char *nombre;
    char categoria;
    double calificacion;
    struct LibroEnSuPoder *libros;
    int cantLibros;
};

#endif /* USUARIO_H */


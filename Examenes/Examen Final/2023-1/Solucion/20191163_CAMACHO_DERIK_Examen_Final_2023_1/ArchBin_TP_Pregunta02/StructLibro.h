/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 08:07 PM
 */

#ifndef STRUCTLIBRO_H
#define STRUCTLIBRO_H

#include "StructUsuariosConElLibro.h"

struct Libro{
    char codigo[8];
    char titulo[60];
    char autor[60];
    int cantidadDeLibros;
    double precio;
    struct UsuariosConElLibro usuarios[40];
    int cantUsuarios;
};

#endif /* STRUCTLIBRO_H */


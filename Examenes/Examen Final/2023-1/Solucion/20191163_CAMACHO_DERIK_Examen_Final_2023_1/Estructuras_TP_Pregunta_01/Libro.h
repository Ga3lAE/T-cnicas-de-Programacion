/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 06:39 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include "UsuarioConElLibro.h"

struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    int cantidad;
    double precio;
    struct UsuarioConElLibro *usuarios;
    int cantUsuarios;
    
};

#endif /* LIBRO_H */


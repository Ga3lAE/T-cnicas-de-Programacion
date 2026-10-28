/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Registros.h
 * Author: aml
 *
 * Created on 20 de junio de 2023, 04:49 PM
 */

#ifndef REGISTROS_H
#define REGISTROS_H

#include "LibroPrestado.h"

struct Registros{
    int codigo;
    char nombre[60];
    struct LibroPrestado libro[7];
    int cantidadDeLibros;
};

#endif /* REGISTROS_H */


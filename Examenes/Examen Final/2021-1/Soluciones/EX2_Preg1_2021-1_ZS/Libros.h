/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Libros.h
 * Author: aml
 *
 * Created on 20 de junio de 2023, 04:48 PM
 */

#ifndef LIBROS_H
#define LIBROS_H

struct Libro{
    char codigo[8];
    char titulo[60];
    char autor[60];
    int aPublicacion;
    int cantidad;
    int prestamos;
};

#endif /* LIBROS_H */


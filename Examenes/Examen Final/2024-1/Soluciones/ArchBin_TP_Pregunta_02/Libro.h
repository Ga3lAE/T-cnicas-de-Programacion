/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Libro.h
 * Author: aml
 *
 * Created on 1 de julio de 2024, 08:17 PM
 */

#ifndef LIBRO_H
#define LIBRO_H
#include "Libreria.h"
struct Libro{
    char codigo[8];
    char titulo[60];
    char autor[60];
    double precio;
    //max5libreria per book
    struct Libreria librerias[8];
    int cantidadLibrerias;
    double totalVentas;
    int unidadesVendidas;
    int cantidadBuenasCalificaciones;
    double sumaBuenasCalificaciones;
    int cantidadMalasCalificaciones;
    double sumaMalasCalificaciones;
};


#endif /* LIBRO_H */


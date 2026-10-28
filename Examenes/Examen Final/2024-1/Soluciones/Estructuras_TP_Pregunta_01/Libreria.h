/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Libreria.h
 * Author: aml
 *
 * Created on 1 de julio de 2024, 06:36 PM
 */

#ifndef LIBRERIA_H
#define LIBRERIA_H
#include "Venta.h"

struct Libreria{
    int codigo;
    struct Venta*ventas;
    //10 per book
    int cantidadVentas;
    double totalVentas;
    
};

#endif /* LIBRERIA_H */


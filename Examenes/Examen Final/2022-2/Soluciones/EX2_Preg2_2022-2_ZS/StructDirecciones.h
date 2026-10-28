/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   StructDirecciones.h
 * Author: aml
 *
 * Created on 26 de junio de 2023, 06:30 PM
 */

#ifndef STRUCTDIRECCIONES_H
#define STRUCTDIRECCIONES_H

struct Direccion{
    char codigoUsuario[7];
    char distrito[20];
    char direccion[50];
    double latitud;
    double longitud;
};

#endif /* STRUCTDIRECCIONES_H */


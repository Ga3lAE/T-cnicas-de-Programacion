/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: aml
 *
 * Created on 20 de junio de 2023, 04:48 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    crearLibrosBin("Libros.csv","Libros.bin");
    mostrarLibrosBin("Libros.bin","DatosLibros.txt");
    crearRegistrosBin("RegistroDePrestamos.csv","RegistroDePrestamos.bin");
    mostrarRegistrosBin("RegistroDePrestamos.bin","DatosRegistros.txt");
    actualizarSolicitudes("SolicitudesDePrestamos.csv","Libros.bin",
            "RegistroDePrestamos.bin","Reporte.txt");
    return 0;
}


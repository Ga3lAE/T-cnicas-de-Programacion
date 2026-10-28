/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 09:14 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Libro.h"
#include "RegistroPrestamo.h"
#include "LibroPrestado.h"
#include "funciones.h"

#define MAX_LIBROS 100

/*
 * 
 */
int main(int argc, char** argv) {

    struct Libro* libros;
    int cantidadLibros=0;
    libros = new struct Libro[MAX_LIBROS]{};
    leeLibros("Libros.csv", libros, cantidadLibros);
    confirmaLibros("ConfirmaLibros.txt", libros, cantidadLibros);
    
    struct RegistroPrestamo* prestamos;
    int cantidadPrestamos=0;
    prestamos = new struct RegistroPrestamo[MAX_LIBROS]{};
    leePrestamos("RegistroDePrestamos.csv", prestamos, cantidadPrestamos);
    confirmaPrestamos("ConfirmaPrestamos.txt", prestamos, cantidadPrestamos);
    
    leeSolicitudes("SolicitudesDePrestamos.csv", "ReporteDePrestamos.txt",
            prestamos, cantidadPrestamos,
            libros, cantidadLibros);
    
    
    return 0;
}


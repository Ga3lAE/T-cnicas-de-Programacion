

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 14 de junio de 2023, 11:56 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "StructLibroPrestado.h"
#include "StructRegPrestamos.h"
#include "StructLibros.h"
#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Libro *libros;
    struct RegPrestamo *regPrestamos;
    libros = new struct Libro[50];
    regPrestamos = new struct RegPrestamo[40];
    
    int numLibros,numRegistros;
    leerLibros(libros,numLibros);
    imprimeLibros(libros,numLibros);
    leerRegistrosPrestamos(regPrestamos,numRegistros);
    imprimeRegistrosPrestamos(regPrestamos,numRegistros);
    emiteReporteAtencionPrestamos(libros,numLibros,regPrestamos,numRegistros);
    return 0;
}


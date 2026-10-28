/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:23 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Cliente.h"
#include "Libreria.h"
#include "Libro.h"
#include "Venta.h"
#include "funciones.h"

/*
 * 
 */

#define MAX_CLIENTES 60
#define MAX_LIBROS 300

int main(int argc, char** argv) {
    
    struct Cliente* clientes;
    int cantidadClientes = 0;
    clientes = new struct Cliente [MAX_CLIENTES]{};
    leeClientes("Clientes.csv", clientes, cantidadClientes);
    confirmaClientes("ConfrimaClientes.txt", clientes, cantidadClientes);
    
    struct Libro* libros;
    int cantidadLibros = 0;
    libros = new struct Libro [MAX_LIBROS]{};
    leeLibros("Libros.csv", libros, cantidadLibros);
    
    emiteReporte("ConfrimaLibros.txt", libros, cantidadLibros);
    
    leeVentas("Ventas.txt", 
            libros, cantidadLibros, 
            clientes, cantidadClientes);    
    
    confirmaClientes("FinalClientes.txt", clientes, cantidadClientes);
    emiteReporte("FinalLibros.txt", libros, cantidadLibros);
    return 0;
}


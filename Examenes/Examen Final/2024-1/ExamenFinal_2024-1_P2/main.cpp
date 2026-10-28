/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 12:19 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include"Cliente.h"
#include"Libreria.h"
#include"Libro.h"
#include"Venta.h"
#include"funciones.h"


/*
 * 
 */
int main(int argc, char** argv) {

    leeClientes("Clientes.csv", "Clientes.bin");
    confirmaClientes("PruebaClietnes.txt", "Clientes.bin");
    
    leeLibros("Libros.csv", "Libros.bin");
    emiteReporte("PruebaLibros.txt", "Libros.bin");
    
    leeVentas("Ventas.txt", "Libros.bin", "Clientes.bin");
    confirmaClientes("FinalClientes.txt", "Clientes.bin");
     emiteReporte("FinalLibros.txt", "Libros.bin");
    
    return 0;
}


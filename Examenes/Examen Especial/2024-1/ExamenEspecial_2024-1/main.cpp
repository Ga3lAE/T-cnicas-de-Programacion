/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 13 de junio de 2025, 10:39 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

/*
 * 
 */

int main(int argc, char** argv) {
    
    struct NodoCliente *listaClientes = NULL;
    leeClientes("Clientes.csv", listaClientes);
    verificaClientes("PruebaDeClientes.txt", listaClientes);    
    
    struct NodoLibro *listaLibros = NULL;
    leeLibros("Libros.csv", listaLibros);
    verificaLibros("PruebaDeLibros.txt", listaLibros);
    
    leeVentas("Ventas.txt", listaClientes, listaLibros);
    
    verificaClientes("ReporteFinalClientes.txt", listaClientes);    
    verificaLibros("ReporteFinalLibros.txt", listaLibros);
    
    
    return 0;
}


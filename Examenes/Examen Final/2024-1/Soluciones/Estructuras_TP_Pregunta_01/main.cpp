/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: aml
 *
 * Created on 1 de julio de 2024, 06:34 PM
 */
//Oscar Sebastian Cespedes Vasquez 20221473 1/7/2024 
//El presente programa hara empleo de estrcturas 
//para el finroemde una libreria, con los libros registrados en ella
//a su vez se detallara los datso como rankings buenos,rankings malos
//con ellos tambien se determinara las ventas realizadas con calificacion y fecha
#include <iostream>
#include <iomanip>

using namespace std;
#include "funcionesaux.h"
#include "Libro.h"
#include "Cliente.h"
#include "Libreria.h"
#include "Venta.h"
#define MAXCLIENTES 70
#define MAXLIBROS 280
/*
 * 
 */
int main(int argc, char** argv) {
    //paso1
    struct Cliente*arrCliente;
    arrCliente=new struct Cliente[MAXCLIENTES]{};
    int cantClientes;
    leyendoClientes("Clientes.csv",arrCliente,cantClientes);
    corroborandoClientes("PruebaClientes.txt",arrCliente,cantClientes);
    //paso2
    struct Libro*arrLibros;
    arrLibros=new struct Libro[MAXLIBROS]{};
    int cantLibros;
    leyendoLibros("Libros.csv",arrLibros,cantLibros);
    //pas3
    emitiendoReporte("PruebaLibros.txt",arrCliente,arrLibros,cantClientes,
            cantLibros);
    //paso4
    leyendoVentas("Ventas.txt",arrLibros,arrCliente,cantLibros,cantClientes);
    //paso5
    corroborandoClientes("ClientesActualizado.txt",arrCliente,cantClientes);
    //paso6
    emitiendoReporte("LibrosActualizado.txt",arrCliente,arrLibros,cantClientes,
            cantLibros);
    return 0;
}


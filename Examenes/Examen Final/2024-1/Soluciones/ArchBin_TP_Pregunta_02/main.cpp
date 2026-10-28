/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: aml
 *
 * Created on 1 de julio de 2024, 08:15 PM
 */
//Oscar Sebastian Cespedes Vasquez 20221473 1/7/2024 
//El presente programa hara empleo de archivosBinarios
//para el finroemde una libreria, con los libros registrados en ella
//a su vez se detallara los datso como rankings buenos,rankings malos
//con ellos tambien se determinara las ventas realizadas con calificacion y fecha
#include <iostream>
#include <iomanip>

using namespace std;
#include "funcionesaux.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    leyendoClientes("Clientes.csv","Clientes.bin");
    
    corroborandoClientes("PruebaClientes.txt","Clientes.bin");
    
    leyendoLibros("Libros.csv","Libros.bin");
    
    emitiendoReporte("PruebaLibros.txt","Clientes.bin","Libros.bin");
    
    leyendoVentas("Ventas.txt","Clientes.bin","Libros.bin");
    
    corroborandoClientes("ClientesActualizado.txt","Clientes.bin");
    
    emitiendoReporte("LibrosActualizado.txt","Clientes.bin","Libros.bin");
    return 0;
}


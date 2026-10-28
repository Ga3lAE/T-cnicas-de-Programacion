/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 11:57 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Cliente.h"
#include "Fecha.h"
#include "Libro.h"
#include "Venta.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {

   leeClientes("Clientes.csv", "Clientes.bin") ;   
   leeLibros("Libros.csv", "Libros.bin") ;
   
   emiteReporte("Reporte.txt", "Libros.bin");
   
   leeVentas("Ventas.csv", "Libros.bin", "Clientes.bin");

   asignaRankings("Libros.bin");
   oredenaLibros("Libros.bin");
   emiteReporte("ReporteFin.txt", "Libros.bin");
   
    return 0;
}
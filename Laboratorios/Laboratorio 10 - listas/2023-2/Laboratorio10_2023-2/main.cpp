/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:05 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "ArticuloVendido.h"
#include "Vendedor.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {

    leeArticulos("Articulos.csv", "Articulos.bin");
    
    leeVendedores("Vendedores.csv", "Vendedores.bin");
    
    leeVentas("Ventas.txt", "Vendedores.bin", "Articulos.bin");
    
    emiteReporte("ReporteDepPagos.txt", "Vendedores.bin", "Articulos.bin");         
    
    
    
    return 0;
}


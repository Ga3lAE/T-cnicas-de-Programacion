/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 09:50 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "ArticuloPedido.h"
#include "Vendedor.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {

    leeArticulos("Articulos.csv", "Articulos.bin");   
    confirmaArticulos("PruebaArticulos.txt", "Articulos.bin");
    
    leeVendedores("Vendedores.csv", "Vendedores.bin");
    emiteReporte("PruebaVendedores.txt", "Vendedores.bin");
    
    leeVentas("Ventas.csv", "Vendedores.bin", "Articulos.bin");
    
    confirmaArticulos("ReporteArticulos.txt", "Articulos.bin");
    emiteReporte("ReporteVentas.txt", "Vendedores.bin");
    return 0;
}


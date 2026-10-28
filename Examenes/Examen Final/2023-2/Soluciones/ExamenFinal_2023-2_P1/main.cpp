/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 05:57 PM
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

#define MAX_ARTICULOS 200
#define MAX_VENDEDORES 150

/*
 * 
 */
int main(int argc, char** argv) {

    
    struct Articulo* articulos;
    int cantidadArticulos=0;
    articulos = new struct Articulo [MAX_ARTICULOS]{};
    
    leeArticulos("Articulos.csv", articulos, cantidadArticulos);
    confirmaArticulos("PruebaArticulos.txt", articulos, cantidadArticulos);
    
    struct Vendedor* vendedores;
    int cantidadVendedores=0;
    vendedores = new struct Vendedor [MAX_VENDEDORES]{};
    leeVendedores("Vendedores.csv", vendedores, cantidadVendedores);
    
    emiteReporte("PruebaVendedores.txt", vendedores, cantidadVendedores, 
            articulos, cantidadArticulos);
    
    leeVentas("Ventas.csv", vendedores, cantidadVendedores, 
            articulos, cantidadArticulos);
    
    confirmaArticulos("ReporteArticulos.txt", articulos, cantidadArticulos);
    emiteReporte("ReporteVentas.txt", vendedores, cantidadVendedores, 
            articulos, cantidadArticulos);
    
    return 0;
}


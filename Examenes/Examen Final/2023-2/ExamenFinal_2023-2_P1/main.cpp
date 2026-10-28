/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 02:51 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "Vendedor.h"
#include "ArticuloPedido.h"
#include "funciones.h"

#define MAX_ARTICULOS 200
#define MAX_VENDEDORES 150

/*
 * 
 */
int main(int argc, char** argv) {

    struct Articulo* articulos;
    int cantidadArticulos=0;
    articulos = new struct Articulo[MAX_ARTICULOS]{};
    leeArticulos("Articulos.csv", articulos, cantidadArticulos);
    pruebaArticulos("PruebaArticulos.txt", articulos, cantidadArticulos);
    
    struct Vendedor* vendedores;
    int cantidadVendedores=0;
    vendedores = new struct Vendedor[MAX_VENDEDORES]{};
    leeVendedores("Vendedores.csv", vendedores, cantidadVendedores);    
    
    emiteReporte("PruebaVendedores.txt", vendedores, cantidadVendedores);
    
    leeVentas("Ventas.csv", vendedores, cantidadVendedores, 
            articulos, cantidadArticulos);
    pruebaArticulos("FinalArticulos.txt", articulos, cantidadArticulos);
    emiteReporte("FinalVendedores.txt", vendedores, cantidadVendedores);
    
    return 0;
}


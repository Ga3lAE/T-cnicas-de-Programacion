/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 27 de junio de 2025, 07:19 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "NodoArticulo.h"
#include "NodoVendedor.h"

/*
 * 
 */

int main(int argc, char** argv) {

    struct NodoArticulo *listaArticulos = NULL;
    leeArticulos("Articulos.csv", listaArticulos);
    imprimeArticulos("PruebaArticulos.txt", listaArticulos);               
    
    struct NodoVendedor *listaVendedores = NULL;
    leeVendedores("Vendedores.csv", listaVendedores);
    imprimeVendedores("PruebaVendedores.txt", listaVendedores);
    
    leeVentas("Ventas.txt", listaArticulos, listaVendedores);
    imprimeArticulos("ReporteArticulos.txt", listaArticulos);
    imprimeVendedores("ReporteVendedores.txt", listaVendedores);
    
    return 0;
}


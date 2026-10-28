

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 18 de junio de 2023, 09:26 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "Farmacias.h"
#include "ProductoNoProcesado.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Farmacia *farmacias;
    struct ProductoNoProcesado *productosNoProcesados;
    
    farmacias = new struct Farmacia[30];
    productosNoProcesados = new struct ProductoNoProcesado[300];
    
    
    int numFarmacias,numProductosNoProcesados;
    
    leerFarmacias(farmacias,numFarmacias);
    leerVentas(farmacias,numFarmacias,productosNoProcesados,
            numProductosNoProcesados);
    emiteReporte(farmacias,numFarmacias,productosNoProcesados,numProductosNoProcesados);
    return 0;
}


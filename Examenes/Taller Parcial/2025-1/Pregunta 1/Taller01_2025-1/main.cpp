/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 13 de mayo de 2025, 10:36 AM
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
    
    procesaArchivos("Vendedores.txt", "Articulos.txt", 
            "Ventas.txt", "Reporte.txt");

    return 0;
}


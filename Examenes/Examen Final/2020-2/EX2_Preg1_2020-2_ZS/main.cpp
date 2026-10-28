

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:20 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    crearFarmaciasBin("Farmacias.csv","Farmacias.bin");
    mostrarFarmaciasBin("Farmacias.bin","reporteFarmacias.txt");
    actualizarFarmaciasBin("Farmacias.bin","ProductosNoProcesados.bin","Ventas.csv");
    emiteReporte("Farmacias.bin","ProductosNoProcesados.bin","ReporteVentas.txt");
    return 0;
}


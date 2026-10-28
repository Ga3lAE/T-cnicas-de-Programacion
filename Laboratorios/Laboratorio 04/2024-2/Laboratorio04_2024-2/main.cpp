/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 22 de abril de 2025, 06:04 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "funciones.h"

#define MAX_CANT_PLATOS 120

/*
 * 
 */
int main(int argc, char** argv){       
    //31796 ANTICUCHO_DE_CORAZON_AL_PLATO   31.90   ESPECIALES
    int codigosPlatos[MAX_CANT_PLATOS]{}, 
            cantidadPlatos=0;
    double preciosPlatos[MAX_CANT_PLATOS]{};
    leePlatos("PlatosOfrecidos.txt", 
            cantidadPlatos, 
            codigosPlatos, preciosPlatos);
    
    leeDatosEmiteReporte(cantidadPlatos, codigosPlatos, preciosPlatos, 
            "Repartidores.txt", 
            "RepartosARealizar.txt", 
            "Reporte.txt");
//    //nombredelapersona P123-456
//    char tipoCarro, descC;
//    int placa1, placa2;
//    cin>>tipoCarro>>placa1>>descC>>placa2;
    
//    int char double bool;
    char tipoVehiculos[100];
    
    return 0;
}


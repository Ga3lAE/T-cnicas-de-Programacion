/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 27 de mayo de 2025, 05:24 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_PLATOS 200

/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadPlatos=0;
    int arrCodigosPlatos[MAX_CANT_PLATOS]{}, 
            arrNumPlatosVendidos[MAX_CANT_PLATOS]{};
    
    leeRepartos("RepartosARealizar.txt", cantidadPlatos, 
            arrCodigosPlatos, arrNumPlatosVendidos);
    
    double arrPrecio[MAX_CANT_PLATOS]{}, 
            arrIngresoBruto[MAX_CANT_PLATOS]{}, 
            arrDescuento[MAX_CANT_PLATOS]{}, 
            arrTotal[MAX_CANT_PLATOS]{};
    bool arrTieneDescuento[MAX_CANT_PLATOS]{};
    
    leePlatos("PlatosOfrecidos.txt", cantidadPlatos,
            arrCodigosPlatos, arrNumPlatosVendidos, 
            arrPrecio, arrIngresoBruto, 
            arrTieneDescuento, arrDescuento, arrTotal);
    
    verificaArreglos("Verificacion.txt", cantidadPlatos, 
            arrCodigosPlatos, arrPrecio, arrNumPlatosVendidos, 
            arrIngresoBruto, arrTotal, 
            arrTieneDescuento, arrDescuento);
    
    emiteReporte("PlatosOfrecidos.txt", "ReporteDePagoPorAlumno.txt",
            cantidadPlatos, 
            arrCodigosPlatos, arrPrecio, arrNumPlatosVendidos, 
            arrIngresoBruto, arrTotal, 
            arrTieneDescuento, arrDescuento);
    
    return 0;
}


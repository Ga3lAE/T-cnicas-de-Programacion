/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 17 de abril de 2025, 01:57 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

/*
 * 
 */
int main(int argc, char** argv) {
          
    ifstream archivoInfracciones("InfraccionesDeTransito.txt", ios::in);
    if(not archivoInfracciones.is_open()){
        cout<<"ERROR: No se pudo abrir InfraccionesDeTransito.txt"<<endl;
        exit(1);
    }
    ofstream archivoReporte("Reporte.txt", ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir Reporte.txt"<<endl;
        exit(1);
    }
    
    int dniMayorPago, dniMenorPago;
    double mayorPago, menorPago;
    
    procesaArchivos(archivoInfracciones, archivoReporte, 
            dniMayorPago, dniMenorPago, mayorPago, menorPago);
    
    imprimeEstadisticas(archivoReporte, 
            dniMayorPago, dniMenorPago, mayorPago, menorPago);
    

    return 0;
}


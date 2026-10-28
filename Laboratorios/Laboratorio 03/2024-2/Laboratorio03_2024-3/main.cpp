/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 15 de abril de 2025, 09:12 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {

    leeProcesaArchivos("RepartosRealizados.txt", "PlatosOfrecidos.txt", "Reporte.txt");
    
    return 0;
}


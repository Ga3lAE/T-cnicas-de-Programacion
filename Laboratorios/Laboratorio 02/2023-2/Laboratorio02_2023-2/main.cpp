/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 13 de abril de 2025, 12:14 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

/*
 * 
 */
int main(int argc, char** argv) {

    leeProcesaDatos("RegistroDeTelevidentes.txt", "Reporte.txt");
    
    return 0;
}


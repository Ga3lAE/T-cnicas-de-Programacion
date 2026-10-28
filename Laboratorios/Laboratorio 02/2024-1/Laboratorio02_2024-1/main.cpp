/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 12 de abril de 2025, 11:02 PM
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
    
    leeProcesaDatos("CitasMedicas.txt", "Reporte.txt");
    
    return 0;
}


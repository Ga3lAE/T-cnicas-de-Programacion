/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 4 de mayo de 2025, 04:11 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "FuncionesAuxiliares.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    leeProcesaArchivos("Medicos.txt", "CitasMedicas.txt", "Medicinas.txt", 
            "Reporte.txt");

    return 0;
}


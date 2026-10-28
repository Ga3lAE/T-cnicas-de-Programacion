/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 18 de mayo de 2025, 05:07 PM
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
    
    leeProcesaArchivos("Pacientes.txt", "CitasMedicas.txt", 
            "Medicos.txt", "Medicinas.txt", "Reporte.txt");

    return 0;
}


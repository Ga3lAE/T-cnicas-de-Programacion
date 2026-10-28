/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 15 de mayo de 2025, 06:18 PM
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
    
    leeProcesaArchivos("Tiktoks.txt", 
            "Comentarios.txt",  "Usuarios.txt", "Paises.txt",
            "Reporte.txt");

    return 0;
}


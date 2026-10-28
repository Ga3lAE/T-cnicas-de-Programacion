/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 25 de noviembre de 2024, 11:57 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Libro.h"
#include "UsuariosConElLibro.h"
#include "Usuario.h"
#include "UsuariosConElLibro.h"
#include "funciones.h"


#define MAX_LIBROS 50
#define MAX_USUARIOS 100


/*
 * 
 */
int main(int argc, char** argv) {

    leeLibros("Libros.csv", "Libros.bin");
    verificaLibros("ReporteInicialLibros.txt", "Libros.bin");
    
    leeUsuarios("Usuarios.csv", "Usuarios.bin");
    verificaUsuarios("ReporteIniciaUsuarios.txt", "Usuarios.bin");
    
    leeDevoluciones("DevolucionDeLibros.txt", "Libros.bin", "Usuarios.bin");
    
    verificaUsuarios("ReporteFinalUsuarios.txt", "Usuarios.bin");
    verificaLibros("ReporteFinalLibros.txt", "Libros.bin");
    
    return 0;
}


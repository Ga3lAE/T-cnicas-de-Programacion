/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 09:54 PM
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

    struct Libro libros[MAX_LIBROS]{};
    int cantidadLibros=0;
    leeLibros("Libros.csv", libros, cantidadLibros);
    
    verificaLibros("ArregloInicialLibros.txt", libros, cantidadLibros);
    
    struct Usuario usuarios[MAX_USUARIOS];
    int cantidadUsuarios=0;
    leeUsuarios("Usuarios.csv", usuarios, cantidadUsuarios);
    
    verificaUsuarios("ArregloInicialUsuarios.txt", usuarios, cantidadUsuarios);
    
    leeDevoluciones("DevolucionDeLibros.txt", usuarios, cantidadUsuarios, 
            libros, cantidadLibros);
    
    verificaLibros("ArregloFinalLibros.txt", libros, cantidadLibros);
    verificaUsuarios("ArregloFinalUsuarios.txt", usuarios, cantidadUsuarios);
    
    return 0;
}


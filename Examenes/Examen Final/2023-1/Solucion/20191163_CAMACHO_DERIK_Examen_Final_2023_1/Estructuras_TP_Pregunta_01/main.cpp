/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 *
 * Created on 3 de julio de 2023, 06:32 PM
 */
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_LIBROS 50
#define MAX_USUARIOS 100
#include "Usuario.h"
#include "Libro.h"
#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Libro libros [MAX_LIBROS];
    int numLibros;  
    
    struct Usuario usuarios [MAX_USUARIOS];
    int numUsuarios;
    
    /*Abre el archivo de libros.csv para la lectura y almacenamiento de datos
     en el arreglo de estrcuturas libros*/
    cargarDatosLibros(libros,numLibros);
    /*impresion de datos del arreglo de libros*/
    verificarDatosLibros(libros,numLibros);
    /*Abre el archivo de usuarios.csv para la lectura y almacenamiento de 
     datos en el arreglo de estructuras usuarios*/
    cargarDatosUsuarios(usuarios,numUsuarios);
    /*impresion de datos del arreglo de usuarios*/
    verificarDatosUsuarios(usuarios,numUsuarios);
    /*modificacion de arreglos usando el archivo de texto de DevolucionDeLibros*/
    modificarArreglos(libros,numLibros,usuarios,numUsuarios);
    mostrarDatosFinalesLibros(libros,numLibros);
    mostrarDatosFinalesUsuarios(usuarios,numUsuarios);
    return 0;
}


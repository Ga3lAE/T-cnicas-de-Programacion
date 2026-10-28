/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 *
 * Created on 3 de julio de 2023, 08:03 PM
 */

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    /*Crear achivo binario de libros con sus respectivos datos leidos*/
    crearLibrosBin("Libros.csv","Libros.bin");
    /*emite un reporte con los datos iniciales ya cargados en el archivo*/
    mostrarLibrosBin("Libros.bin","PruebaInicialDeLibros.txt");
    /*Crear archivo binario de usuarios con sus respectivos datos leidos*/
    crearUsuariosBin("Usuarios.csv","Usuarios.bin");
    /*emite un reporte con los datos inciales ya cargados en el achivo*/
    mostrarUsuariosBin("Usuarios.bin","PruebaInicialDeUsuarios.txt");
    
    modificarArchivosLibrosyUsuariosBin("Libros.bin","Usuarios.bin",
            "DevolucionDeLibros.txt");
    emiteReporteLibrosBin("Libros.bin","PruebaFinalDeLibros.txt");
    emiteReporteUsuariosBin("Usuarios.bin","PruebaFinalDeUsuarios.txt");
    return 0;
}


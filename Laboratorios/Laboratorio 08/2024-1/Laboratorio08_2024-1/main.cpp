/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 14 de junio de 2025, 08:29 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Facultad.h"
#include "Alumno.h"

#define MAX_CANT_ALUMNOS 100

/*
 * 
 */

int main(int argc, char** argv) {

    int cantidadAlumnos=0;
    struct Alumno arrAlumnos[MAX_CANT_ALUMNOS]{};
    leeNotas("Calificaciones.txt", 
            arrAlumnos, cantidadAlumnos);
    leeAlumnos("Alumnos.csv", 
            arrAlumnos, cantidadAlumnos);
    leeFacultades("Facultades.txt", 
            arrAlumnos, cantidadAlumnos);
    ordenaAlumnos(arrAlumnos, cantidadAlumnos);
    
    preocesaReporte("Reporte.txt", arrAlumnos, cantidadAlumnos);   
    
    return 0;
}


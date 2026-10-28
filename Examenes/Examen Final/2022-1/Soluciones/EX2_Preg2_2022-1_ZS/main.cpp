

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 27 de junio de 2023, 02:50 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    crearCursosBin("Cursos.csv","Cursos.bin");
    mostrarCursosBin("Cursos.bin","reporteCursos.txt");
    crearAlumnosBin("alumnos.csv","Alumnos.bin");
    actualizarAlumnosBin("Alumnos.bin","Cursos.bin","Notas.txt");
    ordearAlumnosBin("Alumnos.bin");
    emiteReporte("Alumnos.bin","ReportePorAlumno.txt");
    return 0;
}


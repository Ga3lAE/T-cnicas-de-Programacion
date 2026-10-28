

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 29 de junio de 2023, 01:24 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

#include "StructAlumno.h"
#include "StructCurso.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Curso cursos[50];
    int numCursos;
    
    struct Alumno alumnos[100];
    int numAlumnos;
    leerCursos(cursos,numCursos);
    leerAlumnos(alumnos,numAlumnos);
    emiteReporteSimpleAlumnos(alumnos,numAlumnos);
    leerProcesarNotas(alumnos,numAlumnos,cursos,numCursos);
    emiteReporte(alumnos,numAlumnos,cursos,numCursos);
    return 0;
}


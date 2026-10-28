/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:26 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Curso.h"
#include "CursoMatriculado.h"
#include "Alumno.h"
#include "funciones.h"
                    
#define MAX_CURSOS 50
#define MAX_ALUMNOS 100

/*
 * 
 */
int main(int argc, char** argv) {

    struct Curso* cursos;
    int cantidadCursos=0;
    cursos = new struct Curso[MAX_CURSOS]{};
    
    leeCursos("Cursos.csv", cursos, cantidadCursos);
    
    struct Alumno* alumnos;
    int cantidadAlumnos=0;
    alumnos = new struct Alumno[MAX_ALUMNOS]{};
    
    leeAlumnos("Alumnos.csv", alumnos, cantidadAlumnos);    
    confirmaAlumnos("ConfirmaAlumnos.txt", alumnos, cantidadAlumnos);
    
    leeNotas("Notas.txt", 
            alumnos, cantidadAlumnos, 
            cursos, cantidadCursos);
    
    ordenaAlumnos(alumnos, cantidadAlumnos);
    
    emiteReporte("Reporte.txt", alumnos, cantidadAlumnos);
    
    return 0;
}


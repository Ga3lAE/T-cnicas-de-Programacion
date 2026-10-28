/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 11:11 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

#include "Alumno.h"
#include "Curso.h"
#include "CursoMatriculado.h"
#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {

    leeCursos("Cursos.csv", "Cursos.bin");
    confirmaCursos("ConfirmacionCursos.txt", "Cursos.bin");
    
    leeAlumnos("Alumnos.csv", "Alumnos.bin");
    confirmaAlumnos("ConfirmaAlumnos.txt", "Alumnos.bin");
    
//    leeNotas("Notas.txt", "Alumnos.bin", "Cursos.bin");
    return 0;
}


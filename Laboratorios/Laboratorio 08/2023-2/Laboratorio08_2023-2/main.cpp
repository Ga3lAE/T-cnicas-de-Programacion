/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 10 de noviembre de 2024, 04:26 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int cicloValido;
    solicitaCiclo(cicloValido);
//    cicloValido = 20231;
    
    struct Alumno alumnos[100];
    int cantidadAlumnos=0;
    
    leeAlumnos("Alumnos.csv", alumnos, cantidadAlumnos);

    struct Curso cursos[100];
    int cantidadCursos =0;
    leeCursos("Cursos.csv", cursos, cantidadCursos);
    
    struct Escala escalas[100];
    int cantidadEscalas=0;
    leeEscalas("Escalas.csv", escalas, cantidadEscalas);
        
    leeMatricula("Matricula.csv", cicloValido,
            cursos, cantidadCursos, 
            alumnos, cantidadAlumnos, 
            escalas, cantidadEscalas);
    
    
    ordenaCursos(cursos, cantidadCursos);
    imprimeReporte("ReportePagosAlumnos.txt", cicloValido, 
        cursos, cantidadCursos);

    
    return 0;
}


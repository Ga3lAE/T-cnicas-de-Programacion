/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 5 de julio de 2025, 04:57 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "NodoCurso.h"
#include "NodoEscala.h"
#include "NodoAlumno.h"

/*
 * 
 */

int main(int argc, char** argv) {

    bool inicial = true;
    int anioAnalisis=0, cicloAnalisis=0;
    
    struct NodoCurso *listaCursos = NULL;
    leeCursos("Cursos.csv", listaCursos);        
    
    struct NodoEscala *listaEscalas = NULL;
    leeEscalas("Escalas.csv", listaEscalas);
    
    struct NodoAlumno *listaAlumnos = NULL;
    leeAlumnos("Alumnos.csv", listaAlumnos);       
    
    imprimeReporte("ReporteInicial.txt", listaAlumnos, 
            inicial, anioAnalisis, cicloAnalisis);    
    
    pideCiclo(inicial, anioAnalisis, cicloAnalisis);
    
    leeMatricula("Matricula.txt", 
            listaEscalas, 
            listaAlumnos, 
            listaCursos,
            anioAnalisis, cicloAnalisis);
    eliminaNoMatriculados(listaAlumnos);
    imprimeReporte("ReporteFin.txt", listaAlumnos, 
            inicial, anioAnalisis, cicloAnalisis);
    
    
    
    
    return 0;
}


/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 6 de julio de 2025, 12:09 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"

#define MAX_CANT_CURSOS 50
#define MAX_CANT_ESCALAS 35
#define MAX_CANT_ALUMNOS 100

/*
 * 
 */

int main(int argc, char** argv) {
    
    struct Curso *arrCursos;
    int cantidadCursos=0;
    arrCursos = new struct Curso[MAX_CANT_CURSOS]{};
    leeCursos("Cursos.csv", arrCursos, cantidadCursos);
    
    struct Escala *arrEscalas;
    int cantidadEscalas=0;
    arrEscalas = new struct Escala[MAX_CANT_ESCALAS]{};
    leeEscalas("Escalas.csv", arrEscalas, cantidadEscalas);
    
    struct Alumno *arrAlumnos;
    int cantidadAlumnos=0;
    arrAlumnos = new struct Alumno[MAX_CANT_ALUMNOS]{};
    leeAlumnos("Alumnos.csv", arrAlumnos, cantidadAlumnos);        
    
    int anio=0, ciclo=0;
    //emiteReporte(arrAlumnos, cantidadAlumnos, anio, ciclo);
    
    anio=2023; 
    ciclo=1;
    leeMatricula("Matricula.txt", 
            arrCursos,cantidadCursos,  
            arrEscalas, cantidadEscalas, 
            arrAlumnos, cantidadAlumnos, 
            anio, ciclo);
    
    ordenaAlumnos(arrAlumnos, cantidadAlumnos);
    
    //emiteReporte(arrAlumnos, cantidadAlumnos, anio, ciclo);

    
    return 0;
}


/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 11 de mayo de 2025, 12:51 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_ALUMNOS 100
#define MAX_CANT_CURSOS 50
#define MAX_CANT_ESCALAS 10

/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadAlumnos=0;
    int codigosAlumnos[MAX_CANT_ALUMNOS]{}, 
            escalasPagosAlumnos[MAX_CANT_ALUMNOS]{};
    
    leeAlumnos("Alumnos.txt", cantidadAlumnos, 
            codigosAlumnos, escalasPagosAlumnos);
    
   

    
    int cantidadCursos = 0;
    int codigosCursos[MAX_CANT_CURSOS]{};
    double creditosCursos[MAX_CANT_CURSOS]{};
    
    leeCursos("Cursos.txt", cantidadCursos, 
            codigosCursos, creditosCursos);
    
    int cantidadEscalas = 0;
    double pagosEscalas[MAX_CANT_ESCALAS]{};
    
    leeEscalas("Escalas.txt", cantidadEscalas, pagosEscalas);
    
    //definimos los arreglos que usaremos para las estadisticas
        //para los alumnos
    double totalesCreditosAlumnos[MAX_CANT_ALUMNOS]{}, 
            totalesPagosAlumnos[MAX_CANT_ALUMNOS]{};
    int totalesCursosAlumnos[MAX_CANT_ALUMNOS]{};
        //para los cursos
    int alumnosMatriculadosCursos[MAX_CANT_CURSOS]{};
    double totalesIngresosCursos[MAX_CANT_CURSOS]{};
    
    procesaMatricula("Matricula.txt", 
            cantidadAlumnos, codigosAlumnos, escalasPagosAlumnos, 
            cantidadCursos, codigosCursos, creditosCursos, 
            cantidadEscalas, pagosEscalas, 
            totalesCreditosAlumnos, totalesCursosAlumnos, totalesPagosAlumnos, 
            alumnosMatriculadosCursos, totalesIngresosCursos);
    
    ordenaAlumnos(cantidadAlumnos,codigosAlumnos, escalasPagosAlumnos,
            totalesCreditosAlumnos, totalesCursosAlumnos, totalesPagosAlumnos);
    
    
    ordenaCursos(cantidadCursos, codigosCursos, creditosCursos, 
            alumnosMatriculadosCursos, totalesIngresosCursos);
    
    imprimeReporte("Reporte.txt", 
            cantidadAlumnos, codigosAlumnos, 
            escalasPagosAlumnos, totalesCreditosAlumnos, 
            totalesCursosAlumnos, totalesPagosAlumnos, 
            cantidadCursos,codigosCursos, creditosCursos, 
            alumnosMatriculadosCursos, totalesIngresosCursos);
    
    
    
    
    
    

    return 0;
}


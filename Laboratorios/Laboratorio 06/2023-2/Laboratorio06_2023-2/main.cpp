/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 31 de mayo de 2025, 05:23 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_ALUMNOS 100
#define MAX_CANT_CURSOS 50
#define MAX_CANT_ESCALAS 30

/*
 * 
 */

int main(int argc, char** argv) {
    
    int anio=2022, ciclo=2;
    char descC;
//    cout<<"Ingrese el ciclo del que desea verificar (20xx-x): "<<endl;
//    cin>>anio>>descC>>ciclo;
    int periodo = anio*10+ciclo;
    
    int cantidadAlumnos=0;
    int arrCodigoAlumno[MAX_CANT_ALUMNOS]{};
    char arrEscalaAlumno[MAX_CANT_ALUMNOS]{};
    leeAlumnos("Alumnos.txt", cantidadAlumnos, 
            arrCodigoAlumno, arrEscalaAlumno);
    
    int cantidadCursos=0;
    int arrCodigoCurso[MAX_CANT_CURSOS]{};
    double arrCreditosCurso[MAX_CANT_CURSOS]{};
    leeCursos("Cursos.txt", cantidadCursos, 
            arrCodigoCurso, arrCreditosCurso);
    
    int cantidadEscalas=0;
    int arrPeriodoEscala[MAX_CANT_ESCALAS]{};
    char arrCodigoEscala[MAX_CANT_ESCALAS]{};
    double arrPagoEscala[MAX_CANT_ESCALAS]{};
    leeEscalas("Escalas.txt", cantidadEscalas, 
            arrPeriodoEscala, arrCodigoEscala, arrPagoEscala);
    
    int arrCantidadCursosAlumno[MAX_CANT_ALUMNOS]{};
    double arrTotalCreditosAlumno[MAX_CANT_ALUMNOS]{}, 
            arrMontoPagadoAlumno[MAX_CANT_ALUMNOS]{};
    leeMatricula("Matricula.txt", periodo, 
            cantidadAlumnos, arrCodigoAlumno, arrEscalaAlumno, 
            cantidadCursos, arrCodigoCurso, arrCreditosCurso, 
            cantidadEscalas, arrPeriodoEscala, arrCodigoEscala, arrPagoEscala, 
            arrCantidadCursosAlumno, arrTotalCreditosAlumno, arrMontoPagadoAlumno);
    
    emitirReporte("Reporte.txt", periodo, 
            "AlumnosNombres.txt", "AlumnosApellidos.txt", 
            cantidadAlumnos, arrCodigoAlumno, arrCantidadCursosAlumno, 
            arrTotalCreditosAlumno, arrEscalaAlumno, arrMontoPagadoAlumno);
    
    return 0;
}


/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 9 de junio de 2025, 05:10 PM
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
    
    int anio, ciclo, periodoElegido;
    
    int cantidadAlumnos=0;
    int arrCodigoAlumnos[MAX_CANT_ALUMNOS]{};
    char *arrNombreAlumnos[MAX_CANT_ALUMNOS]{},
            arrEscalaAlumnos[MAX_CANT_ALUMNOS]{};
    leeAlumnos("Alumnos.txt", cantidadAlumnos, 
            arrCodigoAlumnos, arrNombreAlumnos, arrEscalaAlumnos);
    
    int cantidadCursos=0;
    int arrCodigoCursos[MAX_CANT_CURSOS]{};
    char *arrNombresCursos[MAX_CANT_CURSOS]{};
    double arrCreditoCursos[MAX_CANT_CURSOS]{};
    leeCursos("Cursos.txt", cantidadCursos,
            arrCodigoCursos, arrNombresCursos, arrCreditoCursos);
    
    int cantidadEscalas=0;
    int arrPeriodoEscalas[MAX_CANT_ESCALAS]{};
    char arrCodigoEscalas[MAX_CANT_ESCALAS]{};
    double arrPrecioEscalas[MAX_CANT_ESCALAS]{};
    leeEscalas("Escalas.txt", cantidadEscalas, 
            arrPeriodoEscalas, arrCodigoEscalas, arrPrecioEscalas);
    
    
    //para el reporte necesitamos
    int arrCantidadCursosAlumnos[MAX_CANT_ALUMNOS]{};
    double arrCreditosCursosAlumnos[MAX_CANT_ALUMNOS]{};
    double arrMontoPagadoAlumnos[MAX_CANT_ALUMNOS]{};
    leeMatricula("Matricula.txt", periodoElegido,
            cantidadEscalas, 
            arrPeriodoEscalas, arrCodigoEscalas, arrPrecioEscalas, 
            cantidadAlumnos, 
            arrCodigoAlumnos, arrEscalaAlumnos, 
            cantidadCursos,
            arrCodigoCursos, arrCreditoCursos, 
            arrCantidadCursosAlumnos, arrCreditosCursosAlumnos, arrMontoPagadoAlumnos);
    
    
    
    return 0;
}


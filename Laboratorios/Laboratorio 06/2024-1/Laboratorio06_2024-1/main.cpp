/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 31 de mayo de 2025, 02:21 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_ALUMNOS 100

/*
 * 
 */

int main(int argc, char** argv) {
    
    int codigoFacultasUsuario;
    cout<<"INGRESE EL CODIGO DE UNA DE LAS FACULTADES: "<<endl;
    cin>>codigoFacultasUsuario;
    
    
    int cantidadAlumnos=0;
    int arrCodigoAlumno[MAX_CANT_ALUMNOS]{}, 
            arrNumCursos[MAX_CANT_ALUMNOS]{};
    double arrSumaPonderada[MAX_CANT_ALUMNOS]{}, 
            arrNumCreditos[MAX_CANT_ALUMNOS]{};
    leeCalificaciones("Calificaciones.txt", cantidadAlumnos, 
            arrCodigoAlumno, arrNumCursos, 
            arrSumaPonderada, arrNumCreditos);
    
    emiteReporte("Alumnos.txt", "Facultades.txt", "Reporte.txt", 
            codigoFacultasUsuario, 
            cantidadAlumnos, 
            arrCodigoAlumno, arrNumCursos, 
            arrSumaPonderada, arrNumCreditos);

    return 0;
}


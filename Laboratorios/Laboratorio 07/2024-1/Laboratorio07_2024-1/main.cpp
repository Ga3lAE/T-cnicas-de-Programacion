/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 6 de junio de 2025, 05:36 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_ALUMNOS 200
#define MAX_CANT_FACULTADES 50
#define MAX_CAR_FACULTAD_CODIGO 10

/*
 * 
 */

int main(int argc, char** argv) {
    
    char codigoFacultad1[MAX_CAR_FACULTAD_CODIGO] = "EEGGCC", 
            codigoFacultad2[MAX_CAR_FACULTAD_CODIGO] = "FDD";
//    cout<<"Ingrese el codigo de una facultad: "<<endl;
//    cin>>codigoFacultad1;
//    codigoFacultad1 = "EEGGCC";
//    cout<<"Ingrese el codigo de una facultad: "<<endl;
//    codigoFacultad2 = "FAD";
//    cin>>codigoFacultad2;
    
    int cantidadAlumnos=0;
    int arrCodigoAlumnos[MAX_CANT_ALUMNOS]{},
            arrNumCursos[MAX_CANT_ALUMNOS]{};
    double arrSumaPonderada[MAX_CANT_ALUMNOS]{}, 
            arrNumCreditos[MAX_CANT_ALUMNOS]{};
    leeCalificaciones("Calificaciones.txt", cantidadAlumnos, 
            arrCodigoAlumnos, arrNumCursos, 
            arrSumaPonderada, arrNumCreditos);
    
    char *arrNombreAlumnos[MAX_CANT_ALUMNOS]{}, 
            *arrCodigoFacultadAlumnos[MAX_CANT_ALUMNOS]{};
    
    leeAlumnos("Alumnos.csv", cantidadAlumnos, 
            arrCodigoAlumnos, arrNombreAlumnos, arrCodigoFacultadAlumnos);
    
    ordenaAlumnos(cantidadAlumnos, 
            arrCodigoAlumnos, arrNombreAlumnos, arrNumCursos,
            arrSumaPonderada, arrNumCreditos, 
            arrCodigoFacultadAlumnos);
    
    emiteReporte("Facultades.txt","Reporte.txt", cantidadAlumnos, 
            arrCodigoAlumnos, arrNombreAlumnos, arrNumCursos, 
            arrSumaPonderada, arrNumCreditos, 
            arrCodigoFacultadAlumnos, 
            codigoFacultad1, codigoFacultad2);

    return 0;
}


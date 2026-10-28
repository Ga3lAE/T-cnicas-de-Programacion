/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 9 de junio de 2025, 05:11 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

//LECTURA
int leePeriodo(ifstream &archivo){
    int anio, ciclo;
    char sep;

    archivo>>anio>>sep>>ciclo;
    return anio*10 + ciclo;
}
char *leeCadenaExacta(ifstream &archivo){
    char aux[100], *cad;
    
    archivo>>aux;
    if(archivo.eof()) return NULL;
    
    cad = new char[strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}
void leeAlumnos(const char *nombreArchivo, int &cantidad, 
        int *arrCodigoAlumnos, char **arrNombreAlumnos, char *arrEscalaAlumnos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //20216298      Cruz_Fuentes_Johana_Ydali      E
        archivo>>arrCodigoAlumnos[cantidad];
        if(archivo.eof()) break;
        arrNombreAlumnos[cantidad] = leeCadenaExacta(archivo);
        archivo>>arrEscalaAlumnos[cantidad];
        
        cantidad++;        
    }
}
void leeCursos(const char *nombreArchivo, int &cantidad, 
        int *arrCodigos, char **arrNombres, double *arrCreditos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //231209  Mecanica_De_Fluidos    3.75
        archivo>>arrCodigos[cantidad];
        if(archivo.eof()) break;
        arrNombres[cantidad] = leeCadenaExacta(archivo);
        archivo>>arrCreditos[cantidad];
        
        cantidad++;        
    }
}
void leeEscalas(const char *nombreArchivo, int &cantidad, 
        int *arrPeriodos, char *arrCodigos, double *arrPrecios){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //2021-1    A    175.29
        arrPeriodos[cantidad] = leePeriodo(archivo);
        if(archivo.eof()) break;
        archivo>>arrCodigos[cantidad]>>arrPrecios[cantidad];
        
        cantidad++;
    }
}
void leeMatricula(const char *nombreArchivo, int periodoElegido,  
        //Escalas
        int cantidadEscalas,
        int *arrPeriodoEscalas, char *arrCodigoEscalas, double *arrPrecioEscalas,
        //Alumnos
        int cantidadAlumnos,
        int *arrCodigoAlumnos, char *arrEscalaAlumnos,
        //Cursos
        int cantidadCursos,
        int *arrCodigoCursos, double *arrCreditoCursos,
        int *arrCantidadCursosAlumnos, double *arrCreditosCursosAlumnos, double *arrMontoPagadoAlumnos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    int periodoActual;
    int codigoAlumnoActual, codigoCursoActual;
    while(true){
        //2022-1    20212697    481203    109239
        periodoActual = leePeriodo(archivo);
        if(archivo.eof()) break;
        if(periodoActual != periodoElegido) //Saltamos y pasamos a la siguiente linea
            while(archivo.get()!='\n');
        else{            
            archivo>>codigoAlumnoActual;
            int posAlumno = buscaInt(arrCodigoAlumnos, cantidadAlumnos, codigoAlumnoActual);
            if(posAlumno == NO_ENCONTRADO){
                int posEscala = buscaIntChar(arrPeriodoEscalas, arrCodigoEscalas, cantidadEscalas, 
                        periodoElegido, arrEscalaAlumnos[posAlumno]);
                
                if(posEscala != NO_ENCONTRADO){
                    while(true){
                        if(archivo.get()=='\n') break;
                        archivo>>codigoCursoActual;
                    }
                }
            }
        }
    }
}

//BUSQUEDA
int buscaInt(int *arr, int cantidad, int el){ //Busca un entero generico en un arreglo de enteross
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i] == el) return i;
    }
    return NO_ENCONTRADO;
}
int buscaIntChar(int *arrI, char *arrC, int cantidad, 
        int elI, char elC){ //Busca un entero y un caracter en arreglos paralelos de enteros y caracteres
    for (int i = 0; i < cantidad; i++) {        
        if(arrI[i] == elI and arrC[i] == elC) return i;
    }
    return NO_ENCONTRADO;
}
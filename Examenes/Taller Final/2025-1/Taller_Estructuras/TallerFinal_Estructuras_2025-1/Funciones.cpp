/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 6 de julio de 2025, 12:10 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "Curso.h"
#include "Escala.h"
#include "Alumno.h"

#define NO_ENCONTRADO -1

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char buff[100], *cad;
    archivo.getline(buff, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(buff)+1]{};
    strcpy(cad, buff);
    return cad;
}
void leeCursos(const char *nombreArchivo, struct Curso *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }    
    while(true){
        //375241,Metodos Numericos En Ingenieria,5.75        
        archivo>>arr[cantidad].codigo;
        if(archivo.eof()) break;
        archivo.get();
        arr[cantidad].nombre = leeCadenaExacta(archivo, ',');
        archivo>>arr[cantidad].creditos;
        
        cantidad++;
    }
}
void leeEscalas(const char *nombreArchivo, struct Escala *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }    
    char descC;
    while(true){
        //2021-1,B,214.83
        archivo>>arr[cantidad].anio;
        if(archivo.eof()) break;
        archivo>>descC>>arr[cantidad].ciclo
                >>descC>>arr[cantidad].escala
                >>descC>>arr[cantidad].valorCredito;
        
        cantidad++;
    }
}
void leeAlumnos(const char *nombreArchivo, struct Alumno *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }    
    while(true){
        //20197374,Vilcara Correa Victor,D
        arr[cantidad] = {};
        archivo>>arr[cantidad].codigo;
        if(archivo.eof()) break;
        archivo.get();
        arr[cantidad].nombre = leeCadenaExacta(archivo, ',');
        archivo>>arr[cantidad].escala.escala;
        
        arr[cantidad].cursos = new Curso [MAX_CANT_ALUMNO_CURSOS]{};
        
        cantidad++;
    }
}
void leeMatricula(const char *nombreArchivo, 
        struct Curso *arrCursos, int cantidadCursos, 
        struct Escala *arrEscalas, int cantidadEscalas, 
        struct Alumno *arrAlumnos, int cantidadAlumnos, 
        int anio, int ciclo){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int aniomAtr, cicloMatr, alumnoMatr, cursoMatr;
    int posAlumno, posEscala, posCurso;
    while(true){
        //2023-2    20217328    109250    109220    481208
        archivo>>aniomAtr;
        if(archivo.eof()) break;
        archivo.get();
        archivo>>cicloMatr;
        if(anio != aniomAtr or ciclo != cicloMatr) // si es de otro ciclo
            while(archivo.get()!='\n');
        else{
            archivo>>alumnoMatr;
            posAlumno = buscaAlumno(arrAlumnos, cantidadAlumnos, alumnoMatr);
            if(posAlumno == NO_ENCONTRADO){
                while(archivo.get()!='\n');
            }
            else{
                posEscala = buscaEscala(arrEscalas, cantidadEscalas, 
                        anio, ciclo, arrAlumnos[posAlumno].escala.escala);
                while(true){
                    if(archivo.get()=='\n') break;
                    archivo>>cursoMatr;
                    posCurso = buscaCurso(arrCursos, cantidadCursos, cursoMatr);
                    if(posCurso!=NO_ENCONTRADO)
                        procesaCursoMatriculado(arrAlumnos[posAlumno], 
                                arrEscalas[posEscala], 
                                arrCursos[posCurso]);
                }
            }
            
        }

    }
}

//PREOCESAMIENTO
char *copiaCadena(const char *cad){
    char *nuev;
    nuev = new char [strlen(cad)+1]{};
    strcpy(nuev, cad);
    return nuev;
}
void procesaCursoMatriculado(struct Alumno &alumno, 
        struct Escala escala, 
        struct Curso curso){
    
    alumno.escala = escala;
    
    struct Curso &cursoMatr = alumno.cursos[alumno.cantidadCursos];
    cursoMatr.codigo = curso.codigo;
    cursoMatr.creditos = curso.creditos;
    cursoMatr.nombre = copiaCadena(curso.nombre);
    
    alumno.totalCreditos+=curso.creditos;
    alumno.totalPago+=curso.creditos*escala.valorCredito;
    
    alumno.cantidadCursos++;            
}

//BUSQUEDA
int buscaAlumno(struct Alumno *arr, int cantidad, int cod){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i].codigo == cod) return i;
    }
    return NO_ENCONTRADO;
}
int buscaEscala(struct Escala *arr, int cantidad, 
        int anio, int ciclo, char escala){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i].anio == anio and arr[i].ciclo == ciclo and arr[i].escala == escala) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCurso(struct Curso *arr, int cantidad, int cod){
    for (int i = 0; i < cantidad; i++) {
        if(arr[i].codigo == cod) return i;
    }
    return NO_ENCONTRADO;
}

//ORDENAMIENTO 
void ordenaAlumnos(struct Alumno *arr, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(arr[i].escala.escala>arr[j].escala.escala
                    or
                (arr[i].escala.escala==arr[j].escala.escala
                    and
                arr[i].totalCreditos<arr[j].totalCreditos)){
                cambiaAlumno(arr[i], arr[j]);
            }
        }

    }

}
void cambiaAlumno(struct Alumno &al1,struct Alumno &al2){
    struct Alumno aux;
    aux = al1;
    al1 = al2;
    al2 = aux;
}
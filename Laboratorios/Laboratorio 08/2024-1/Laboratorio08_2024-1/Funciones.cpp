/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 14 de junio de 2025, 08:30 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "Alumno.h"
#include "Facultad.h"

#define NO_ENCONTRADO -1

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOMBRE 50
#define MAX_TAM_CANT 12
#define MAX_TAM_NOTA 14
#define MAX_TAM_FAC 20

//LECTURA
char *leeCadenaEscata(ifstream &archivo, char del){
    char aux[100], *cad;
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return nullptr;
    for (int i = 0; aux[i]; i++) {        
        if(aux[i] == '_') aux[i] = ' ';
    }

    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}
void leeNotas(const char *nombreArchivo,
        struct Alumno *arr, int &cantidad){
    ifstream archivo(nombreArchivo,ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    char *codigoCurso;
    double creditos;
    int codigoAlumno, nota;
    while(true){
        //ARQ848   3.75   20213075   6   20236102   6   20226455   11   20208971   13   20227724   11   20202687   17   20197155   8   20193373   7   20198608   17
        codigoCurso = leeCadenaEscata(archivo, ' ');
        if(archivo.eof()) break;
        archivo>>creditos;
        
        while(true){
            if(archivo.get() == '\n') break;            
            archivo>>codigoAlumno>>nota;
                    
            int posAlumno = buscaAlumno(arr, cantidad, codigoAlumno);
            if(posAlumno== NO_ENCONTRADO)
                posAlumno = agregaAlumno(arr, cantidad, codigoAlumno);
            arr[posAlumno].numeroCreditos+=creditos;
            arr[posAlumno].numeroCursos++;
            arr[posAlumno].sumaPonderada+=nota*creditos;
            arr[posAlumno].promedioPonderado=arr[posAlumno].sumaPonderada/arr[posAlumno].numeroCreditos;
        }
                
    }
}
void leeAlumnos(const char *nombreArchivo,
        struct Alumno *arr, int cantidad){
    ifstream archivo(nombreArchivo,ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigo;
    while(true){
        //20218255,MEJIA DIAZ BLANCA MILAGROS,FARTE
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo.get();
        int posAlumno = buscaAlumno(arr, cantidad, codigo);
        if(posAlumno == NO_ENCONTRADO) while(archivo.get()!='\n');
        else{
            arr[posAlumno].nombre = leeCadenaEscata(archivo, ',');
            arr[posAlumno].facultad.codigo = leeCadenaEscata(archivo, '\n');
        }
    }
}
void leeFacultades(const char *nombreArchivo,
        struct Alumno *arr, int cantidad){
    ifstream archivo(nombreArchivo,ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    char *codigoFacultad, *nombreFacultad;
    while(true){
        //ESTUDIOS_GENERALES_CIENCIAS   EEGGCC
        nombreFacultad = leeCadenaEscata(archivo, ' ');
        if(archivo.eof()) break;
        archivo>>ws;
        codigoFacultad = leeCadenaEscata(archivo, '\n');
        
        for (int i = 0; i < cantidad; i++) {            
            if(strcmp(arr[i].facultad.codigo, codigoFacultad) == 0)
                arr[i].facultad.nombre = nombreFacultad;
        }
    }
}

//BUSQUEDA
int buscaAlumno(struct Alumno *arr, int cantidad, int el){
    for (int i = 0; i < cantidad; i++) {
        if(arr[i].codigo == el) return i;
    }
    return NO_ENCONTRADO;

}
//AGREGA
int agregaAlumno(struct Alumno *arr, int &cantidad, int codigo){
    arr[cantidad].codigo = codigo;
    arr[cantidad].numeroCreditos=0;
    arr[cantidad].numeroCursos=0;
    arr[cantidad].promedioPonderado=0;
    arr[cantidad].sumaPonderada=0;
    arr[cantidad].nombre=NULL;
    arr[cantidad].facultad.codigo=NULL;
    arr[cantidad].facultad.nombre=NULL;
    
    cantidad++;
    return cantidad-1;
}

//ORDENAMIENTO
void ordenaAlumnos(struct Alumno *arr, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int k = i+1; k < cantidad; k++) {            
            if(strcmp(arr[i].facultad.nombre, arr[k].facultad.nombre)>0
                    or 
                    (strcmp(arr[i].facultad.nombre, arr[k].facultad.nombre)==0)
                    and 
                    arr[i].promedioPonderado<arr[k].promedioPonderado)
                cambiaAlumno(arr[i], arr[k]);
        }

    }

}
void cambiaAlumno(struct Alumno &al1, struct Alumno &al2){
    struct Alumno aux;
    aux = al1;
    al1=al2;
    al2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {
        archivo<<c;
    }
    archivo<<endl;
}
void preocesaReporte(const char *nombreArchivo,
        struct Alumno *arr, int cantidad){
    ofstream archivo(nombreArchivo,ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_TAM_COD)<<arr[i].codigo
                <<setw(MAX_TAM_NOMBRE)<<arr[i].nombre
                <<setw(MAX_TAM_CANT)<<arr[i].numeroCursos
                <<setw(MAX_TAM_NOTA)<<arr[i].sumaPonderada
                <<setw(MAX_TAM_CANT)<<arr[i].numeroCreditos
                <<setw(MAX_TAM_NOTA)<<arr[i].promedioPonderado
                <<setw(MAX_TAM_FAC)<<arr[i].facultad.nombre
                <<endl;
    }

}
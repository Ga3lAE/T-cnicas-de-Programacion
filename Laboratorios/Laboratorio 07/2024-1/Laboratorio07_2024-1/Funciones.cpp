/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 6 de junio de 2025, 05:37 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_CURSO_CODIGO 10
#define MAX_CAR_FACULTAD_CODIGO 15
#define MAX_CAR_ALUMNO_NOMBRE 50
#define MAX_CAR_FACULTAD_NOMBRE 30

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOTA 14
#define MAX_TAM_CANT 12

//BUSQUEDA
int buscaInt(int *arr, int cant, int el){
    for (int i = 0; i < cant; i++) {        
        if(arr[i] == el) return i;
    }    
    return NO_ENCONTRADO ;
}
//LECTURA
char *leeCadena(ifstream &archivo, char del){
    char aux[100]{}, *cad;
    
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    return cad;
}
void leeCalificaciones(const char *nombreArchivo, int &cantidad,
        int *arrCodigoAlumnos, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);        
    }
    
    char codigoCurso[MAX_CAR_CURSO_CODIGO]{};
    double creditos;
    int codigoAlumno, notaAlumno;
    int posAlumno;
    while(true){
        //INF231   5.25   20209968   8   20193490   8   20218679   5   20198922   19   20193012   13   20207053   8   20202031   19   20239652   13   20197378   5   20198608   6   20205844   15   20217328   13   20219566   17   20221873   5
        archivo>>codigoCurso;
        if(archivo.eof()) break;
        archivo>>creditos;
        
        while(true){
            if(archivo.get() == '\n') break;
            archivo>>codigoAlumno>>notaAlumno;
            
            posAlumno = buscaInt(arrCodigoAlumnos, cantidad, codigoAlumno);
            if(posAlumno == NO_ENCONTRADO){
                arrCodigoAlumnos[cantidad] = codigoAlumno;
                posAlumno = cantidad;
                
                cantidad++;
            }
            
            arrNumCursos[posAlumno]++;
            arrNumCreditos[posAlumno]+=creditos;
            arrSumaPonderada[posAlumno]+=creditos*notaAlumno;
            
            
        }
    }
    
}
void leeAlumnos(const char *nombreArchivo, int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, char **arrNombreFacultadAlumnos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);        
    }
    
    int codigoAlumno;
    int posAlumno;
    while(true){
        //20205830,FERNANDEZ ORTEGA ELIZABETH ELIZABETH,FARQUITURB
        archivo>>codigoAlumno;
        if(archivo.eof()) break;       
        
        posAlumno= buscaInt(arrCodigoAlumnos, cantidad, codigoAlumno);
        if(posAlumno== NO_ENCONTRADO)
            while(archivo.get()!='\n');
        else{
            archivo.get();
            arrNombreAlumnos[posAlumno] = leeCadena(archivo, ',');
            arrNombreFacultadAlumnos[posAlumno] = leeCadena(archivo, '\n');
        }
    }
}
void leeFacultades(const char *nombreArchivo, int &cantidad,
        char **arrCodigoFacultades, char **arrNombreFacultades){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);        
    }
        
    while(true){
        //FACULTAD_DE_ARQUITECTURA_Y_URBANISMO   FARQUITURB
        arrNombreFacultades[cantidad] = leeCadena(archivo, ' ');
        if(archivo.eof()) break;       
        archivo>>ws;
        arrCodigoFacultades[cantidad] = leeCadena(archivo, '\n');
        
        cantidad++;
    }
}

//ORDENAMIENTO
void ordenaAlumnos(int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos, 
        char **arrCodigoFacultadAlumnos){    
    for (int i = 0; i < cantidad-1; i++) {       
        for (int k = i+1; k < cantidad; k++) {            
            if(strcmp(arrCodigoFacultadAlumnos[i], arrCodigoFacultadAlumnos[k])>0
                    or
                    (strcmp(arrCodigoFacultadAlumnos[i], arrCodigoFacultadAlumnos[k])==0
                        and 
                    arrSumaPonderada[i]/arrNumCreditos[i] < arrSumaPonderada[k]/arrNumCreditos[k])){
                cambiaInt(arrCodigoAlumnos[i], arrCodigoAlumnos[k]);
                cambiaCad(arrNombreAlumnos[i], arrNombreAlumnos[k]);
                cambiaInt(arrNumCursos[i], arrNumCursos[k]);
                cambiaDouble(arrSumaPonderada[i], arrSumaPonderada[k]);
                cambiaDouble(arrNumCreditos[i], arrNumCreditos[k]);                
                cambiaCad(arrCodigoFacultadAlumnos[i], arrCodigoFacultadAlumnos[k]);
                
                
            }
        }
    }        
}
void cambiaInt(int &d1, int &d2){
    int aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}
void cambiaDouble(double &d1, double &d2){
    double aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}
void cambiaCad(char *&d1, char *&d2){
    char *aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &arch, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        arch<<c;
    }
    arch<<endl;
}
void emiteReporte(const char *nombreArchivoFacultades, const char *nombreArchivoReporte, int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, int *arrNumCursos, 
        double *arrSumaPonderada, double *arrNumCreditos,
        char **arrCodigoFacultadAlumnos, 
        const char *codigoFacultad1, const char *codigoFacultad2){
    ifstream archivoFacultades(nombreArchivoFacultades, ios::out);
    if(not archivoFacultades.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoFacultades;
        exit(1);        
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);        
    }
    archivoReporte<<fixed<<setprecision(2);
    
    archivoReporte<<setw(MAX_TAM_LIN/2-5)<<"INSITUCION EDUCATIA VENUS S.A."<<endl
            <<setw(MAX_TAM_LIN/2)<<"PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS"<<endl
            <<setw(MAX_TAM_LIN/2-15)<<"CICLO 2024-1"<<endl;
    imprimeFacultades(archivoFacultades, archivoReporte, 
            codigoFacultad1, codigoFacultad2);
    imprimeLinea(archivoReporte, '=');
    
    archivoReporte<<left
            <<setw(MAX_TAM_COD+MAX_CAR_ALUMNO_NOMBRE)<<"ALUMNO"            
            <<setw(MAX_TAM_CANT)<<"No. CURSOS"
            <<setw(MAX_TAM_NOTA)<<"SUMA"
            <<setw(MAX_TAM_CANT)<<"CREDITOS"
            <<setw(MAX_TAM_NOTA)<<"PROMEDIO"
            <<setw(MAX_CAR_FACULTAD_CODIGO)<<"FACU"
            <<endl;
    imprimeLinea(archivoReporte, '=');
    
    char *nombreAlumnoMayor;
    int codigoAlumnoMayor;
    double creditosAlumnoMayor=0;    
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigoFacultad1, arrCodigoFacultadAlumnos[i])==0 
            or 
            strcmp(codigoFacultad2, arrCodigoFacultadAlumnos[i])==0){
            archivoReporte<<left
                    <<setw(MAX_TAM_COD)<<arrCodigoAlumnos[i]
                    <<setw(MAX_CAR_ALUMNO_NOMBRE)<<arrNombreAlumnos[i]
                    <<setw(MAX_TAM_CANT)<<arrNumCursos[i]
                    <<setw(MAX_TAM_NOTA)<<arrSumaPonderada[i]
                    <<setw(MAX_TAM_CANT)<<arrNumCreditos[i]
                    <<setw(MAX_TAM_NOTA)<<arrSumaPonderada[i]/(double)arrNumCreditos[i]
                    <<setw(MAX_CAR_FACULTAD_CODIGO)<<arrCodigoFacultadAlumnos[i]
                    <<endl;
            
            if(creditosAlumnoMayor<arrNumCreditos[i]){
                nombreAlumnoMayor = arrNombreAlumnos[i];
                codigoAlumnoMayor = arrCodigoAlumnos[i];
                creditosAlumnoMayor = arrNumCreditos[i];
            }
        }
    }
    
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<"ALUMNO CON MAYOR NUMERO DE CREDITOS MATRICULADOS: "
            <<nombreAlumnoMayor<<" ("<<codigoAlumnoMayor<<") con "
            <<creditosAlumnoMayor<<" CREDITOS"<<endl;
    
    
}
void imprimeFacultades(ifstream &archivoFacultades, ofstream &archivoReporte,
        const char *codigoFacultad1, const char *codigoFacultad2){
    char *nombre, *codigo;
    bool primera = true;
    while(true){
        //FACULTAD_DE_DERECHO   FDD   
        nombre = leeCadena(archivoFacultades, ' ');
        if(archivoFacultades.eof()) break;
        for (int i = 0; nombre[i]; i++) {            
            if(nombre[i] == '_') nombre[i] = ' ';
        }

        archivoFacultades>>ws;
        codigo = leeCadena(archivoFacultades, '\n');
                
        if(strcmp(codigo,codigoFacultad1) == 0 
            or 
            strcmp(codigo,codigoFacultad2) == 0){
            archivoReporte<<setw(MAX_TAM_LIN/2-15)<<nombre<<endl;
            if(primera){
                archivoReporte<<setw(MAX_TAM_LIN/3)<<"Y"<<endl;
                primera = false;
            }
        }            
    }
}

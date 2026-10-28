/* 
 * File:   Funciones.cpp
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

#define NO_ENCONTRADO -1

#define MAX_CAR_CURSO_COD 7
#define MAX_CAR_FACULTAD_NOMBRE 30
#define MAX_CAR_ALUMNO_NOMBRE 30

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOMBRE 50
#define MAX_TAM_CANT 20
#define MAX_TAM_NOTA 18

//LECTURA
void leeCalificaciones(const char* nombreArchivo, int &cantidad,
        int *arrCodigoAlumno, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }

    char codigoCurso[MAX_CAR_CURSO_COD]{};
    double numeroCreditos;
    while(true){
        //DER614   5.75   20238549   16   20205830   17   20205844   14   20193373   10   20198922   12   20209968   15   20193769   7   20226271   19   20239652   5   20194050   6   20195340   13   20236102   12
        archivo>>codigoCurso;
        if(archivo.eof()) break;
        archivo>>numeroCreditos;
                
        int codigoAlumno, notaAlumno;
        while(true){
            if(archivo.get()=='\n') break;            
            archivo>>codigoAlumno>>notaAlumno;
            
            int posAlumno = buscaIntBinAsc(arrCodigoAlumno, cantidad, codigoAlumno);
            
            if(posAlumno== NO_ENCONTRADO){
                posAlumno = agregaAlumno(cantidad, arrCodigoAlumno, arrNumCursos, 
                        arrSumaPonderada, arrNumCreditos, codigoAlumno);               
            }
            else{
                acumulaAlumno(arrNumCursos[posAlumno], arrSumaPonderada[posAlumno], 
                        arrNumCreditos[posAlumno], notaAlumno, numeroCreditos);
            }
        }
    }
}
int agregaAlumno(int &cantidad, int *arrCod, int *arrNumCursos, 
        double *arrSumPondera, double *arrNumCred, int codigo){
    
    int i = cantidad-1;
    for (i;i>=0 and arrCod[i]>codigo ; i--) {        
        arrCod[i+1] = arrCod[i];
        arrNumCursos[i+1] = arrNumCursos[i];
        arrSumPondera[i+1] = arrSumPondera[i];
        arrNumCred[i+1] = arrNumCred[i];
    }
    
    arrCod[i+1] = codigo;
    arrNumCursos[i+1] = 0;
    arrSumPondera[i+1] = 0;
    arrNumCred[i+1] = 0;
    
    cantidad++;
    
    return i+1;
}
void acumulaAlumno(int &numeroCursoa, double &sumaPonderada, 
        double &numeroCreditos, int nota, double creditos){
    numeroCursoa++;
    sumaPonderada+=nota*creditos;
    numeroCreditos+=creditos;
}

//BUSQUEDA
int buscaIntBinAsc(int *arr, int cantidad, int elemento){
    int posFin = cantidad-1, posInicio = 0, posMedio;
    
    while(true){
        posMedio = (posFin+posInicio)/2;
        
        if(posInicio>posFin) return NO_ENCONTRADO;
        
        if(arr[posMedio] == elemento) return posMedio;
        else if(arr[posMedio]>elemento) posFin = posMedio-1;
        else if(arr[posMedio]<elemento) posInicio = posMedio+1;
    }
}

//REPORTE
void emiteReporte(const char* nombreArchivoAlumnos, const char* nombreArchivoFacultades, const char* nombreArchivoReporte,
        int codigoFacultad, 
        int cantidadAlumnos,
        int *arrCodigoAlumno, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos){
    ifstream archivoAlumnos(nombreArchivoAlumnos, ios::in);
    if(not archivoAlumnos.is_open()){
        cout<<"ERROR: No se pudo abrir  "<<nombreArchivoAlumnos;
        exit(1);
    }
    ifstream archivoFacultades(nombreArchivoFacultades, ios::in);
    if(not archivoFacultades.is_open()){
        cout<<"ERROR: No se pudo abrir  "<<nombreArchivoFacultades;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir  "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    char nombreFacultad[MAX_CAR_FACULTAD_NOMBRE]{};
    int codigoFacultadActual;    
    while(true){
        archivoFacultades>>nombreFacultad;
        if(archivoFacultades.eof()) break;
        archivoFacultades>>codigoFacultadActual;
        
        if(codigoFacultad == codigoFacultadActual){
            imprimeEncabezado(archivoReporte, nombreFacultad);
            
            char nombreAlumno[MAX_CAR_ALUMNO_NOMBRE]{};
            int codigoAlumno, codigoFacultadAlumno;
            while(true){
                //20238549      JUSTINO/FORZANI/ERICKA-VICTORIA     500017
                archivoAlumnos>>codigoAlumno;
                if(archivoAlumnos.eof()) break;
                archivoAlumnos>>nombreAlumno>>codigoFacultadAlumno;
                
                if(codigoFacultad == codigoFacultadAlumno){
                    //este alumno pertenece por lo que debo imprimirlo en el reporte
                    int posAlumno = buscaIntBinAsc(arrCodigoAlumno, cantidadAlumnos, codigoAlumno);
                    if(posAlumno != NO_ENCONTRADO){
                        imprimeAlumno(archivoReporte, 
                                arrCodigoAlumno[posAlumno], nombreAlumno, 
                                arrNumCursos[posAlumno], arrSumaPonderada[posAlumno], 
                                arrNumCreditos[posAlumno]);
                    }
                }
            }
            imprimeLinea(archivoReporte, '=');
            break;
        }        
    }
}
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void imprimeEncabezado(ofstream &archivo, char *nombreFacultad){
    //modificamos la cadena
    for (int i = 0; nombreFacultad[i]; i++) {        
        if(nombreFacultad[i] == '_') nombreFacultad[i] = ' ';
    }
    
    archivo<<setw(MAX_TAM_LIN/2-10)<<"INSTITUCION EDUCATIVA VENUS"<<endl
            <<setw(MAX_TAM_LIN/2)<<"PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADO"<<endl
            <<setw(MAX_TAM_LIN/2-12)<<nombreFacultad<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"ALUMNO"
            <<setw(MAX_TAM_NOMBRE+3)<<" "
            <<setw(MAX_TAM_CANT)<<"No. CURSOS"
            <<setw(MAX_TAM_NOTA)<<"SUMA PONDERADA"
            <<setw(MAX_TAM_CANT)<<"No. CREDITOS"
            <<setw(MAX_TAM_NOTA)<<"PROMEDIO PONDERADO"
            <<endl            ;
    imprimeLinea(archivo, '=');

}
void imprimeAlumno(ofstream &archivo, 
        int codigoAlumno, char *nombreAlumno,
        int numCursos, double sumaPonderada,
        double numCreditos){
    procesaNombre(nombreAlumno);
    archivo<<left
            <<setw(MAX_TAM_COD)<<codigoAlumno
            <<setw(3)<<" - "
            <<setw(MAX_TAM_NOMBRE)<<nombreAlumno
            <<right<<setw(MAX_TAM_CANT/2)<<numCursos<<setw(MAX_TAM_CANT/2)<<' '
            <<setw(MAX_TAM_NOTA/2)<<sumaPonderada<<setw(MAX_TAM_NOTA/2)<<' '
            <<setw(MAX_TAM_CANT/2)<<numCreditos<<setw(MAX_TAM_CANT/2)<<' '
            <<setw(MAX_TAM_NOTA/2)<<sumaPonderada/numCreditos<<setw(MAX_TAM_NOTA/2)<<' '
            <<endl;   
}
void procesaNombre(char *nombre){
    bool esMayus=true;
    
    for (int i = 0; nombre[i]; i++) {        
        if(not esMayus)
            if(nombre[i]>='A' and nombre[i]<='Z') 
                nombre[i]-='A'-'a';
        
        if(nombre[i] == '/' or nombre[i]=='-'){
            nombre[i] = ' ';
            esMayus = true;
        }
        else 
            esMayus = false;
    }

}
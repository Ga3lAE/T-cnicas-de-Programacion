/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 11 de mayo de 2025, 12:52 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_CAR_CONT 3
#define MAX_CAR_COD 10
#define MAX_CAR_ESC 8
#define MAX_CAR_CRED 10
#define MAX_CAR_CANT 8
#define MAX_CAR_DIN 16

//BUSQUEDA
int buscaInt(int *arreglo, int cantidad, int elemento){
    for (int i = 0; i < cantidad; i++)    
        if(arreglo[i] == elemento) return i;    
    return NO_ENCONTRADO;
}

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        archivo<<c;
    }
    archivo<<endl;
}

//LECTURAS
void leeAlumnos(const char *nombreArchivo, int &cantidad,
        int *codigos, int *escalas){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //20227341    Diaz_Antezano_Magali_Silvana  3
        archivo>>codigos[cantidad];
        if(archivo.eof()) break;
        archivo>>ws;
        while(archivo.get()!=' ');
        archivo>>escalas[cantidad];
    
        cantidad++;
    }
        
    
}
void leeCursos(const char *nombreArchivo, int &cantidad,
        int *codigos, double *creditos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //20227341    Diaz_Antezano_Magali_Silvana  3
        archivo>>codigos[cantidad];
        if(archivo.eof()) break;
        archivo>>ws;
        while(archivo.get()!=' ');
        archivo>>creditos[cantidad];
    
        cantidad++;
    }

}
void leeEscalas(const char *nombreArchivo, int &cantidad, 
        double *pagos){
    ifstream archivo(nombreArchivo, ios::in);
    if (not archivo.is_open()) {
        cout << "ERROR: No se puede abrir " << nombreArchivo;
        exit(1);
    }

    int codigo;
    while (true) {
        //1   282.30
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo>>pagos[codigo-1];
        
        cantidad++;
    }
}

//PROCESAMOS
void procesaMatricula(const char *nombreArchivo,
        int cantidadAlumnos, int *codigosAlumnos, int *escalasPagosdAlumnos,
        int cantidadCursos, int *codigosCursos, double *creditosCursos,
        int cantidadEscalas, double *pagosEscalas,
        double *totalesCreditosAlumnos, int *totalesCursosAlumnos, double *totalesPagosAlumnos,
        int *alumnosMatriculadosCursos, double *totalesIngresosCursos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoAlumnoActual, codigoCursoActual;
    int posAlumno, posCurso, posEscala;
    
    while(true){
        //20227341   231270
        archivo>>codigoAlumnoActual;
        if(archivo.eof()) break;
        posAlumno = buscaInt(codigosAlumnos, cantidadAlumnos, codigoAlumnoActual);
        if(posAlumno == NO_ENCONTRADO)
            while(archivo.get()!='\n');
        else{
            archivo>>codigoCursoActual;
            posCurso = buscaInt(codigosCursos, cantidadCursos, codigoCursoActual);
            if(posCurso != NO_ENCONTRADO){
                // se encontraron toddos los datos por lo que debemos de procesarlo                
                if(escalasPagosdAlumnos[posAlumno]<cantidadEscalas){
                    posEscala = escalasPagosdAlumnos[posAlumno]-1;

                    totalesCreditosAlumnos[posAlumno]+=creditosCursos[posCurso];
                    totalesCursosAlumnos[posAlumno]++;
                    totalesPagosAlumnos[posAlumno]+=
                            creditosCursos[posCurso]*pagosEscalas[posEscala];

                    alumnosMatriculadosCursos[posCurso]++;
                    totalesIngresosCursos[posCurso]+=
                            creditosCursos[posCurso]*pagosEscalas[posEscala];                                                    
                }
            }
            
        }
                
        
    }
}

//ORDENAMOS
void ordenaAlumnos(int cantidad, int *codigos, int *escalas,
        double *totalesCreditos, int *totalesCursos, double *totalesPagos){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(totalesPagos[i]<totalesPagos[j]){
                cambiarInt(codigos[i], codigos[j]);
                cambiarInt(escalas[i], escalas[j]);
                cambiarDouble(totalesCreditos[i], totalesCreditos[j]);
                cambiarInt(totalesCursos[i], totalesCursos[j]);
                cambiarDouble(totalesPagos[i], totalesPagos[j]);
            }
        }

    }

}
void ordenaCursos(int cantidad, int *codigos, double *creditos,
        int *alumnosMatriculados, double *totalesPagos){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(alumnosMatriculados[i]>alumnosMatriculados[j]){
                cambiarInt(codigos[i], codigos[j]);
                cambiarDouble(creditos[i], creditos[j]);
                cambiarInt(alumnosMatriculados[i], alumnosMatriculados[j]);                
                cambiarDouble(totalesPagos[i], totalesPagos[j]);
            }
        }

    }

}

void cambiarInt(int &dato1, int &dato2){
    int aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}
void cambiarDouble(double &dato1, double &dato2){
    double aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}

//IMPRESION
void imprimeReporte(const char *nombreArchivo,
        int cantidadAlumnos, int *codigosAlumnos, 
        int *escalasPagosAlumnos, double *totalesCreditosAlumnos, 
        int *totalesCursosAlumnos,double *totalesPagosAlumnos,
        int cantidadCursos, int *codigosCursos, double *creditosCursos, 
        int *alumnosMatriculadosCursos, double *totalesIngresosCursos){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    imprimeEncaebzadoAlumnos(archivo);
    for (int i = 0; i < cantidadAlumnos; i++) {            
        archivo<<left
                <<setw(MAX_CAR_CONT)<<i+1
                <<setw(MAX_CAR_COD)<<codigosAlumnos[i]
                <<setw(MAX_CAR_ESC)<<escalasPagosAlumnos[i]
                <<right<<setw(MAX_CAR_CRED/2)<<totalesCreditosAlumnos[i]<<setw(MAX_CAR_CRED/2)<<' '
                <<setw(MAX_CAR_CANT/2)<<totalesCursosAlumnos[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<setw(MAX_CAR_DIN/2)<<totalesPagosAlumnos[i]<<setw(MAX_CAR_DIN/2)<<' '
                <<left<<endl;

    }   
    
    imprimeEncaebzadoCursos(archivo);
    for (int i = 0; i < cantidadCursos; i++) {            
        archivo<<left
                <<setw(MAX_CAR_CONT)<<i+1
                <<setw(MAX_CAR_COD)<<codigosCursos[i]
                <<right<<setw(MAX_CAR_ESC/2)<<creditosCursos[i]<<setw(MAX_CAR_ESC/2)<<' '
                <<setw(MAX_CAR_CANT/2)<<alumnosMatriculadosCursos[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<setw(MAX_CAR_DIN/2)<<totalesIngresosCursos[i]<<setw(MAX_CAR_DIN/2)<<' '                
                <<left<<endl;

    }   
}
void imprimeEncaebzadoAlumnos(ofstream &archivo){
    archivo<<right<<setw(MAX_CAR_LIN/2)<<"RELACION DE PAGOS DE ALUMNOS"<<endl;
    
    imprimeLinea(archivo, '=');
    archivo<<left
                <<setw(MAX_CAR_CONT)<<"No."
                <<setw(MAX_CAR_COD)<<"CODIGO"
                <<setw(MAX_CAR_ESC)<<"ESCALAS"
                <<setw(MAX_CAR_CRED)<<"CREDITOS"
                <<setw(MAX_CAR_CANT)<<"CURSOS"
                <<setw(MAX_CAR_DIN)<<"PAGO"
                <<endl;
    imprimeLinea(archivo, '=');
}
void imprimeEncaebzadoCursos(ofstream &archivo){
    archivo<<right<<setw(MAX_CAR_LIN/2)<<"RELACION DE PAGOS DE ALUMNOS"<<endl;
    
    imprimeLinea(archivo, '=');
    archivo<<left
                <<setw(MAX_CAR_CONT)<<"No."
                <<setw(MAX_CAR_COD)<<"CODIGO"
                <<setw(MAX_CAR_CRED)<<"CREDITOS"                
                <<setw(MAX_CAR_CANT)<<"ALUMNOS"
                <<setw(MAX_CAR_DIN)<<"PAGO"
                <<endl;
    imprimeLinea(archivo, '=');
}
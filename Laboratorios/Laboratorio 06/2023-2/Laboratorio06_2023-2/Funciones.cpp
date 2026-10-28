/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 31 de mayo de 2025, 06:01 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_CURSO_NOMBRE 50
#define MAX_CAR_ALUMNO_NOMBRE 45
#define MAX_CAR_ALUMNO_APELLIDO 15

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOMBRE 50
#define MAX_TAM_CANT 14
#define MAX_TAM_CRDT 16
#define MAX_TAM_ESCALA 10
#define MAX_TAM_DIN 16

//LECTURA
void leeAlumnos(const char* nombreArchivo, int &cantidad,
        int *arrCodigo, char *arrEscala){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigo;
    char escala;
    while(true){
        //20205830   A
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo>>escala;
        
        int posAlumno = buscaIntBinAsc(arrCodigo, cantidad, codigo);
        if(posAlumno == NO_ENCONTRADO)
            agregaAlumno(cantidad, 
                    arrCodigo, arrEscala, 
                    codigo, escala);
        
    }
}

void leeCursos(const char* nombreArchivo, int &cantidad,
        int *arrCodigoCurso,double *arrCreditosCurso){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigo;
    double creditos;
    char nombre[MAX_CAR_CURSO_NOMBRE]{};
    while(true){
        //109246    Bases_De_Datos    4.75
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo>>nombre>>creditos;
        
        int posCurso = buscaIntBinAsc(arrCodigoCurso, cantidad, codigo);
        if(posCurso == NO_ENCONTRADO)
            agregaCurso(cantidad, 
                    arrCodigoCurso, arrCreditosCurso, 
                    codigo, creditos);
    }
    
}

void leeEscalas(const char* nombreArchivo, int &cantidad,
        int *arrPeriodoEscala, char *arrCodigoEscala, double *arrPagoEscala){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int anio, ciclo;
    char descC;    
    while(true){
        //2023-2    D   556.70
        archivo>>anio;
        if(archivo.eof()) break;
        archivo>>descC>>ciclo
                >>arrCodigoEscala[cantidad]
                >>arrPagoEscala[cantidad];
        
        arrPeriodoEscala[cantidad] = anio*10+ciclo;
        
        cantidad++;                
    }
}

void leeMatricula(const char* nombreArchivo, int periodo,
        int cantidadAlumnos, int *arrCodigoAlumno, char *arrEscalaAlumno,
        int cantidadCursos, int *arrCodigoCurso, double *arrCreditosCurso,
        int cantidadEscalas, int *arrPeriodoEscala, char *arrCodigoEscala, double *arrPagoEscala,
        int *arrCantidadCursosAlumno, double *arrTotalCreditosAlumno, double *arrMontoPagadoAlumno){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int periodoActual, anio, ciclo, codigoAlumno, codigoCurso;
    char descC;
    while(true){
        archivo>>anio;
        if(archivo.eof()) break;
        archivo>>descC>>ciclo;
        
        periodoActual = anio*10+ciclo;        
        
        if(periodo != periodoActual) while(archivo.get()!='\n');
        else{
            archivo>>codigoAlumno;
            int posAlumno = buscaIntBinAsc(arrCodigoAlumno, cantidadAlumnos, codigoAlumno);
            if(posAlumno == NO_ENCONTRADO) 
                while(archivo.get()!='\n');
            else{
                int posEscala = buscaIntChar(arrPeriodoEscala, arrCodigoEscala, cantidadEscalas,
                        periodoActual, arrEscalaAlumno[posAlumno]);
                while(true){
                    if(archivo.get()=='\n') break;
                    archivo>>codigoCurso;
                    int posCurso = buscaIntBinAsc(arrCodigoCurso, cantidadCursos, codigoCurso);
                    if(posCurso != NO_ENCONTRADO){
                        procesaDatos(arrCantidadCursosAlumno[posAlumno], arrTotalCreditosAlumno[posAlumno], arrMontoPagadoAlumno[posAlumno], 
                                arrCreditosCurso[posCurso], arrPagoEscala[posEscala]);
                    }
                }
            }
        }
        
    }
}
void  procesaDatos(int &cantidadCursos, double &totalCreditos, double &montoPagadoAlumno,
        double creditosCurso, double pagoEscala){
    cantidadCursos++;
    totalCreditos+=creditosCurso;
    montoPagadoAlumno+=creditosCurso*pagoEscala;
}
//BUSQUEDA
int buscaIntBinAsc(int *arr, int cantidad, int elemento){
    int posFin=cantidad-1, posInicio=0, posMedio=0;
    
    while(true){
        posMedio = (posInicio+posFin)/2;
        
        if(posInicio>posFin) return NO_ENCONTRADO;
        
        if(arr[posMedio] == elemento) return posMedio;
        else if(arr[posMedio]>elemento) posFin = posMedio-1;
        else if(arr[posMedio]<elemento) posInicio = posMedio+1;
    }
}
int buscaIntChar(int *arrInt, char *arrChar, int cantidad, 
        int elementoInt, char elementoChar){
    for (int i = 0; i < cantidad; i++) {        
        if(arrInt[i] == elementoInt and arrChar[i] == elementoChar) return i;
    }
    return NO_ENCONTRADO;
}
//AGREGAR
void agregaAlumno(int &cantidad,
        int *arrCodigo, char *arrEscala,
        int codigo, char escala){
    int i = cantidad-1;
    for (i; i>=0 and arrCodigo[i]>codigo; i--) {        
        arrCodigo[i+1] = arrCodigo[i];
        arrEscala[i+1] = arrEscala[i];                
    }
    
    arrCodigo[i+1] = codigo;
    arrEscala[i+1] = escala;

    cantidad++;
}

void agregaCurso(int &cantidad,
        int *arrCodigo, double *arrCreditos,
        int codigo, double creditos){
    int i = cantidad-1;
    for (i; i>=0 and arrCodigo[i]>codigo; i--) {        
        arrCodigo[i+1] = arrCodigo[i];
        arrCreditos[i+1] = arrCreditos[i];                
    }
    
    arrCodigo[i+1] = codigo;
    arrCreditos[i+1] = creditos;

    cantidad++;
}

//TEXTO
void modificaTexto(char *apellidoNombre, char *apellidoMaterno){
    char apellidoPaterno[MAX_CAR_ALUMNO_APELLIDO]{}, 
            nombre[MAX_CAR_ALUMNO_NOMBRE]{};
    
    //separamos los apellidos de los nombres, cada uno en una cadena
    int posApellidoNombre=0;
    int i = 0;
    for (i = 0; apellidoNombre[posApellidoNombre]!='_'; i++, posApellidoNombre++) {
        apellidoPaterno[i] = apellidoNombre[posApellidoNombre];
    }
    posApellidoNombre++;//para saltarnos el '_'
    apellidoPaterno[i] = 0;
    
    for (i = 0; apellidoNombre[posApellidoNombre]; i++, posApellidoNombre++) {
        if(apellidoNombre[posApellidoNombre]=='_') apellidoNombre[posApellidoNombre] = ' ';
        nombre[i] = apellidoNombre[posApellidoNombre];
    }
    nombre[i] = 0;
    
    //copiamos las tres cadenas a la final
    int posFinal = 0;
    int j = 0;
    for (j = 0; apellidoPaterno[j]; j++, posFinal++) {        
        apellidoNombre[posFinal] = apellidoPaterno[j];
    }
    apellidoNombre[posFinal] = ' ';
    posFinal++;
        
    for (j = 0;apellidoMaterno[j] ; j++, posFinal++) {        
        apellidoNombre[posFinal] = apellidoMaterno[j];
    }
    apellidoNombre[posFinal] = ' ';
    posFinal++;
    
    for (j = 0; nombre[j]; j++, posFinal++) {        
        apellidoNombre[posFinal] = nombre[j];    
    }
    apellidoNombre[posFinal] = 0;       
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void emitirReporte(const char* nombreArchivoReporte, int periodo,  
        const char* nombreArchivoAlumnosNombres, 
        const char* nombreArchivoAlumnosApellidos,
        int cantidadAlumnos, int *arrCodigoAlumno, int *arrCantidadCursosAlumno,
        double *arrTotalCreditosAlumno, char *arrEscalaAlumno, double *arrMontoPagadoAlumno){
    
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);    
    }
    archivoReporte<<fixed<<setprecision(2);
    ifstream archivoNombres(nombreArchivoAlumnosNombres, ios::in);
    if(not archivoNombres.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoAlumnosNombres;
        exit(1);
    }
    ifstream archivoApellidos(nombreArchivoAlumnosApellidos, ios::in);
    if(not archivoApellidos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoAlumnosApellidos;
        exit(1);
    }
    
    imprimeEncabezado(archivoReporte, periodo);
    
    char nombreApellidoP[MAX_CAR_ALUMNO_NOMBRE+MAX_CAR_ALUMNO_APELLIDO]{}, 
            apellidoM[MAX_CAR_ALUMNO_NOMBRE]{};
    int codigoAlumno;
    while(true){
        //20202031  Aquino_Valentina_Rocio
        //Cortez
        archivoNombres>>codigoAlumno;
        if(archivoNombres.eof()) break;
        archivoNombres>>nombreApellidoP;
        archivoApellidos>>apellidoM;
        
        int posAlumno = buscaIntBinAsc(arrCodigoAlumno, cantidadAlumnos, codigoAlumno);
        if(posAlumno != NO_ENCONTRADO){
            modificaTexto(nombreApellidoP, apellidoM);
            archivoReporte<<left
                <<setw(MAX_TAM_COD)<<arrCodigoAlumno[posAlumno]
                <<setw(3)<<'-'
                <<setw(MAX_TAM_NOMBRE)<<nombreApellidoP
                <<right<<setw(MAX_TAM_CANT/2)<<arrCantidadCursosAlumno[posAlumno]<<setw(MAX_TAM_CANT/2)<<' '
                <<setw(MAX_TAM_CRDT/2)<<arrTotalCreditosAlumno[posAlumno]<<setw(MAX_TAM_CRDT/2)<<' '
                <<setw(MAX_TAM_ESCALA/2)<<arrEscalaAlumno[posAlumno] << setw(MAX_TAM_ESCALA / 2)<<' '
                <<setw(MAX_TAM_DIN/2)<<arrMontoPagadoAlumno[posAlumno]<<setw(MAX_TAM_DIN/2)<<' '
                <<left<<endl;
        }
    }
    imprimeLinea(archivoReporte, '-');
    archivoReporte<<setw(MAX_TAM_COD+MAX_TAM_NOMBRE+3+MAX_TAM_CANT+MAX_TAM_CRDT+MAX_TAM_ESCALA)<<"MONTO TOTAL PAGADO"
            <<sumaArrDouble(arrMontoPagadoAlumno, cantidadAlumnos)<<endl;
    imprimeLinea(archivoReporte, '=');
}
void imprimeEncabezado(ofstream &archivo, int periodo){
    archivo<<setw(MAX_TAM_LIN/2-5)<<"INSTITUCION EDUCATIVA VENUS"<<endl
            <<setw(MAX_TAM_LIN/2)<<"DETALLE DE PAGOS REALIZADO POR CICLOS"<<endl
            <<setw(MAX_TAM_LIN/2-16)<<periodo/10<<'-'<<periodo%10<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_TAM_COD+MAX_TAM_NOMBRE+3)<<"ALUMNO"
            <<setw(MAX_TAM_CANT)<<"No. CURSOS"
            <<setw(MAX_TAM_CRDT)<<"CREDITOS"
            <<setw(MAX_TAM_ESCALA)<<"ESCALA"
            <<setw(MAX_TAM_DIN)<<"MONTO PAGADO"
            <<endl;
            
    imprimeLinea(archivo, '-');
}
double sumaArrDouble(double *arr, int cantidad){
    double total;
    for (int i = 0; i < cantidad; i++) {        
        total += arr[i];
    }
    return total;
}
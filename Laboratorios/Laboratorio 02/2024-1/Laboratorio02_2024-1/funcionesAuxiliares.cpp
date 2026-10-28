#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

#define DURACION_MINIMA 1*3600+15*60+30
#define DURACION_MAXIMA 2*3600+30*60+25

#define MAX_CAR_LIN 150
#define MAX_CAR_HORA 16
#define MAX_CAR_FECHA 12
#define MAX_CAR_DNI 10
#define MAX_CAR_DESC 15
#define MAX_CAR_PAGO 16


void imprimeLinea(ofstream& archivo, char car){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<car;
    }
    archivo<<endl;
}

void leeProcesaDatos(const char* nombreArchivoCitas, 
        const char* nombreArchivoReporte){
    ifstream archivoCitas(nombreArchivoCitas, ios::in);
    if(not archivoCitas.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoCitas<<endl;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoReporte<<endl;
        exit(1);
    }
    
    int cantidadRegistrosTotal=0, 
            cantidadRegistrosProcesados=0;
    double porcentajeRegistrosProcesados=0;
    
    procesaArchivos(archivoCitas, archivoReporte, 
            cantidadRegistrosTotal, cantidadRegistrosProcesados);
    
    porcentajeRegistrosProcesados = cantidadRegistrosProcesados*100.0/cantidadRegistrosTotal;
    imprimeEstadisticas(archivoReporte, 
            cantidadRegistrosTotal, cantidadRegistrosProcesados, 
            porcentajeRegistrosProcesados);
}
void procesaArchivos(ifstream &archivoCitas, ofstream &archivoReporte, 
            int &cantidadRegistrosTotal, int &cantidadRegistrosProcesados){
    imprimeEncabezado(archivoReporte, DURACION_MINIMA, DURACION_MAXIMA);
    
    //9/09/2023   94683380   2.60   11:17:52   12:48:30   124.34   C   S   317.86
    int fecha, dniPaciente, horaInicio, horaFin;
    double porcentajeDescuento, tarifaMedico, pagoMedicamentos, totalIngresos=0;
    char especialidad, recetado;
    while(true){
        leeFecha(archivoCitas, fecha);
        if(archivoCitas.eof()) break;
        cantidadRegistrosTotal++;
        archivoCitas>>dniPaciente>>porcentajeDescuento;
        leeHora(archivoCitas, horaInicio);
        leeHora(archivoCitas, horaFin);
        archivoCitas>>tarifaMedico>>especialidad>>recetado;
        if(recetado == 'S')
            archivoCitas>>pagoMedicamentos;
        else pagoMedicamentos = 0;
        
        double duracion= horaFin-horaInicio;
        if(especialidad == 'P' 
                and 
            DURACION_MINIMA<=duracion and duracion<=DURACION_MAXIMA){
            cantidadRegistrosProcesados++;
            procesaImprimeDatos(archivoReporte, 
                    fecha, dniPaciente, horaInicio, horaFin, 
                    porcentajeDescuento, tarifaMedico, pagoMedicamentos,
                    totalIngresos);
        }
    }
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<fixed<<setprecision(2)<<"TOTAL DE INGRESOS: "<<totalIngresos<<endl;
    imprimeLinea(archivoReporte, '=');
}
void leeFecha(ifstream& archivoLectura, int &fecha){
    int dd, mm, aa;
    char sep;
    archivoLectura>>dd;
    if(archivoLectura.eof()) return;
    archivoLectura>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000+mm*100+dd;
}
void leeHora(ifstream &archivoLectura, int &hora){
    int hh, mm, ss;
    char sep;
    archivoLectura>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;
}
void procesaImprimeDatos(ofstream &archivoReporte, 
        int fecha, int dni, int horaInicio, int horaFin, 
        double descuento, double tarifaMedico, double pagoMedicinas, 
        double &totalIngresos){
    
    int duracionHMS;
    double duracionH, pagoCita;
    duracionHMS=horaFin-horaInicio;
    duracionH=duracionHMS/3600.0;
    
    pagoCita=tarifaMedico*duracionH*(1-descuento/100.0)+pagoMedicinas*(1-(descuento/100.0)/2);
    
    totalIngresos+=pagoCita;
    
    archivoReporte<<left<<fixed<<setprecision(2);
    imprimeFecha(archivoReporte, fecha);
    archivoReporte<<setw(MAX_CAR_DNI)<<dni;
    imprimeHora(archivoReporte, horaInicio);
    imprimeHora(archivoReporte, horaFin);
    imprimeHora(archivoReporte, duracionHMS);

    archivoReporte<<setw(MAX_CAR_HORA)<<setprecision(4)<<duracionH<<setprecision(2)
            <<right<<setw(6)<<descuento<<'%'<<setw(MAX_CAR_DESC-7)<<' '
            <<setw(MAX_CAR_PAGO)<<pagoCita<<endl<<left;
        
    
    
}

void imprimeEncabezado(ofstream &archivoReporte, 
        int duracionMinima, int duracionMaxima){
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<left<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS DE PEDIATRIA"<<endl
          <<"ENTRE UNA DURACION DE ";
    imprimeHora(archivoReporte, duracionMinima);
    archivoReporte<<"- ";
    imprimeHora(archivoReporte, duracionMaxima);
    archivoReporte<<endl;
    imprimeLinea(archivoReporte, '=');
    imprimeCategorias(archivoReporte);
    imprimeLinea(archivoReporte, '=');
}
void imprimeCategorias(ofstream &archivoReporte){
    archivoReporte<<left
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_DNI)<<"PACIENTE"
            <<setw(MAX_CAR_HORA)<<"INICIO"
            <<setw(MAX_CAR_HORA)<<"FIN"
            <<setw(MAX_CAR_HORA)<<"DURACION(H:M:S)"
            <<setw(MAX_CAR_HORA)<<"DURACION(H)"
            <<setw(MAX_CAR_DESC)<<"% DESCUENTO"
            <<setw(MAX_CAR_PAGO)<<"PAGO (CITA+MEDs)"<<endl;
}
void imprimeHora(ofstream &archivoReporte, int hora){
    int hh, mm, ss;
    char sep=':';
   
    hh=hora/3600;
    hora%=3600;
    mm=hora/60;
    ss=hora%60;
    
    archivoReporte<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<left<<setfill(' ')
            <<setw(MAX_CAR_HORA-8)<<' ';
}
void imprimeFecha(ofstream &archivoReporte, int fecha){
    int dd, mm, aa;
    char sep='/';
   
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    archivoReporte<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')
            <<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeEstadisticas(ofstream &archivoReporte, 
            int cantidadRegistrosTotal, int cantidadRegistrosProcesados, 
            double porcentajeRegistrosProcesados){
    archivoReporte<<fixed<<setprecision(2)
            <<"ESTADISTICAS OBTENIDAS: "<<endl
            <<"CANTIDAD DE REGISTROS DEL ARCHIVO: "<<cantidadRegistrosTotal<<endl
            <<"CANTIDAD DE REGISTROS PROCESADOS: "<<cantidadRegistrosProcesados<<endl
            <<"PORCENTAJE DE REGISTROS PROCESADOS: "<<porcentajeRegistrosProcesados<<'%'<<endl;
    imprimeLinea(archivoReporte, '=');
    
}


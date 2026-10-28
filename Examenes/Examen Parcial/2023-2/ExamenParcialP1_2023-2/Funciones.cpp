/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 18 de mayo de 2025, 06:29 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_COD 10
#define MAX_CAR_ANIO 12
//#define MAX_CAR_DESC 14
#define MAX_CAR_DIN 14
#define MAX_CAR_CANT 14
//#define MAX_CAR_CLAS 16
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_FECHA 12
#define MAX_CAR_HORA 10
#define MAX_CAR_DESCR 30
#define MAX_CAR_CONT 5

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

//LECTURA
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    archivo>>dd;
    if(archivo.eof())return;
    archivo>>sep>>mm>>sep>>aa;
    
    fecha = dd + mm*100 + aa*10000;
}
void leeHora(ifstream &archivo, int &hora){
    int hh, mm, ss;
    char sep;
    archivo>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;
}

//PROCESAMIENTO
void leeProcesaArchivos(const char *nombreArchivoPacientes, 
        const char *nombreArchivoCitas,
        const char *nombreArchivoMedicos, 
        const char *nombreArchivoMedicinas, 
        const char *nombreArchivoReporte){
    ifstream archivoPacientes(nombreArchivoPacientes, ios::in);
    if(not archivoPacientes.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPacientes;
    }
    ifstream archivoCitas(nombreArchivoCitas, ios::in);
    if(not archivoCitas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCitas;
    }
    ifstream archivoMedicos(nombreArchivoMedicos, ios::in);
    if(not archivoMedicos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoMedicos;
    }
    ifstream archivoMedicinas(nombreArchivoMedicinas, ios::in);
    if(not archivoMedicinas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoMedicinas;
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
    }
    archivoReporte<<fixed<<setprecision(2);
    
    leeArchivos(archivoPacientes, archivoCitas, 
            archivoMedicos, archivoMedicinas, 
            archivoReporte);
    
}
void leeArchivos(ifstream &archivoPacientes, ifstream &archivoCitas, 
            ifstream &archivoMedicos, ifstream &archivoMedicinas, 
            ofstream &archivoReporte){
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"DETALLE DE LAS CITAS MEDICAS DE LOS PACIENTES"<<endl;
    
    int dniPaciente, anioPaciente;
    double descuentoPaciente;
    while(true){
        //61061535   [ROCIO YOLANDA ACUNA YINO]   15055   2015   2.60
        archivoPacientes>>dniPaciente;
        if(archivoPacientes.eof()) break;
        leeImprimePaciente(archivoPacientes, archivoReporte, 
                dniPaciente, anioPaciente, descuentoPaciente);
                
        imprimeLinea(archivoReporte, '-');
        archivoReporte<<"CITAS:"<<endl;
        imprimeLinea(archivoReporte, '-');
        
        double pagoTotalPaciente=0;
        procesaCitas(archivoCitas, archivoMedicos, archivoMedicinas, 
                archivoReporte, 
                dniPaciente, descuentoPaciente, 
                pagoTotalPaciente);
        
        imprimeLinea(archivoReporte, '-');
        archivoReporte<<"PAGO TOTAL DEL PACIENTE: "<<pagoTotalPaciente<<endl;
    }
    
}
void leeImprimePaciente(ifstream &archivoPacientes, ofstream &archivoReporte,
        int dni, int& anio, double& descuento){
    int dist;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<left
            <<"PACIENTE: "<<setw(MAX_CAR_COD)<<dni;
    imprimeNombre(archivoPacientes, archivoReporte, ']');
    archivoPacientes>>dist>>anio>>descuento;
    archivoReporte<<"ANIO DE MACIMIENTO: "<<setw(MAX_CAR_ANIO)<<anio
            <<"%DESCUENTO: "<<descuento<<'%'<<endl;
}
void imprimeNombre(ifstream &archLec, ofstream &archRep, char del){
    int cantL=0;
    char letra;
    archLec>>ws;
    
    archLec.get();
    while(true){
        letra = archLec.get();
        if(letra == del) break;
        cantL++;
        archRep<<letra;
    }
    
    archRep<<setw(MAX_CAR_NOMBRE-cantL)<<' ';
}
void procesaCitas(ifstream &archivoCitas, ifstream &archivoMedicos, ifstream &archivoMedicinas, 
                ofstream &archivoReporte, 
                int dniPaciente, double descuentoPaciente, 
                double &pagoTotalPaciente){
    
    int fecha, horaInicio, horaFin, duracion, dniActual, codigoMedico;
    
    archivoCitas.clear();
    archivoCitas.seekg(0, ios::beg);
    while(true){
        //4/10/2023   63640178   15:16:39   17:6:38   80138   85325   8
        leeFecha(archivoCitas, fecha);
        if(archivoCitas.eof()) break;
        archivoCitas>>dniActual;
        if(dniActual!= dniPaciente) while(archivoCitas.get()!='\n');
        else{
            double pagoCitaPaciente = 0;
            leeHora(archivoCitas, horaInicio);
            leeHora(archivoCitas, horaFin);
            duracion = horaFin-horaInicio;
            archivoCitas>>codigoMedico;
            
            archivoReporte<<left
                    <<setw(MAX_CAR_FECHA)<<"FECHA"
                    <<setw(MAX_CAR_HORA)<<"DURACION"
                    <<setw(MAX_CAR_NOMBRE)<<"MEDICO"
                    <<setw(MAX_CAR_DESCR)<<"ESPECIALIDAD"
                    <<setw(MAX_CAR_DIN)<<"PAGO POR CITA"
                    <<endl;
            imprimeFecha(archivoReporte, fecha);
            imprimeHora(archivoReporte, duracion);
            imprimeMedico(archivoMedicos, archivoReporte, codigoMedico, 
                    pagoCitaPaciente, duracion, descuentoPaciente);
            pagoTotalPaciente += pagoCitaPaciente;
            
            int codigoMedicina, cantidadRecetada, contadorMedicinas = 0;
            double pagoMedicinas=0;
            while(true){
                if(archivoCitas.get()=='\n') break;
                archivoCitas>>codigoMedicina>>cantidadRecetada;
                contadorMedicinas++;
                procesaMedicinas(archivoMedicinas, archivoReporte, 
                        codigoMedicina, cantidadRecetada, contadorMedicinas, 
                        pagoMedicinas, descuentoPaciente);
            }
            pagoTotalPaciente+=pagoMedicinas;
            archivoReporte<<"PAGO TOTAL DE LAS MEDICINAS: "<<pagoMedicinas<<endl
                    <<"PAGO TOTAL: "<<pagoMedicinas+pagoCitaPaciente<<endl;
            imprimeLinea(archivoReporte, '-');
        }
    }
    
}
void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep = '/';
    
    aa = fecha / 10000;
    fecha %=10000;
    mm = fecha /100;
    dd = fecha %100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')<<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeHora(ofstream &archivo, int hora){
    int hh, mm, ss;
    char sep = ':';
    
    hh = hora / 3600;
    hora %=3600;
    mm = hora /60;
    ss = hora %60;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<left<<setfill(' ')<<setw(MAX_CAR_HORA-8)<<' ';
}
void imprimeMedico(ifstream &archivoMedico, ofstream &archivoReporte, 
        int codigoMedico, 
        double &pagoCita, int duracion, double descuento){
    
    int medicoActual;
    double tarifa;
    
    archivoMedico.clear();
    archivoMedico.seekg(0, ios::beg);
    while(true){
        //50611     /EDGAR MUNOZ VERGEL/   Urologia   337.03
        archivoMedico>>medicoActual;
        if(archivoMedico.eof()) break;
        if(medicoActual != codigoMedico) while(archivoMedico.get()!='\n');
        else{
            imprimeNombre(archivoMedico, archivoReporte, '/');
            imprimeDescripcion(archivoMedico, archivoReporte);
            
            archivoMedico>>tarifa;
            
            pagoCita = tarifa*duracion/3600.0*(1-descuento/100.0);
            
            archivoReporte<<setw(MAX_CAR_DIN)<<pagoCita<<endl;
        }
    }
    
    
}
void imprimeDescripcion(ifstream &archivoMedico, ofstream &archivoReporte){
    int cantL=0;
    char letra;
    archivoMedico>>ws;
    
    while(true){
        letra = archivoMedico.get();
        if(letra == ' ') break;
        cantL++;
        if(letra == '_') letra = ' ';
        archivoReporte<<letra;
    }
    
    archivoReporte<<setw(MAX_CAR_DESCR-cantL)<<' ';
}
void procesaMedicinas(ifstream &archivoMedicinas, ofstream &archivoReporte,
        int codigoMedicina, int cantidadRecetada, int contadorMedicinas, 
        double &pagoMedicinas, double descuento){
    int codigoActual;
    double precioMedicina, pagoMedicina;
    
    if(contadorMedicinas==1)
        imprimeEncabezadoMedicinas(archivoReporte);
    
    archivoMedicinas.clear();
    archivoMedicinas.seekg(0, ios::beg);
    while(true){
        //94429  TIAMAZOL_5MG_20T   52.7
        archivoMedicinas>>codigoActual;
        if(archivoMedicinas.eof()) break;
        if(codigoActual != codigoMedicina) while(archivoMedicinas.get()!='\n');
        else{
            archivoReporte<<left<<setw(MAX_CAR_LIN/3)<<' '
                <<setw(MAX_CAR_CONT)<<contadorMedicinas
                <<setw(MAX_CAR_COD)<<codigoActual;
            imprimeDescripcion(archivoMedicinas, archivoReporte);
            archivoMedicinas>>precioMedicina;
            pagoMedicina = cantidadRecetada*precioMedicina*(1-descuento/200.0);
            archivoReporte
                    <<right<<setw(MAX_CAR_CANT/2)<<cantidadRecetada<<setw(MAX_CAR_CANT/2)<<' '
                    <<setw(MAX_CAR_DIN/2)<<precioMedicina<<setw(MAX_CAR_DIN/2)<<' '
                    <<setw(MAX_CAR_DIN/2)<<pagoMedicina<<setw(MAX_CAR_DIN/2)<<' '
                    <<left<<endl;
            pagoMedicinas+=pagoMedicina;
        }

    }
    
}
void imprimeEncabezadoMedicinas(ofstream &archivo){
    archivo<<"MEDICINAS RECETADAS: "<<endl;
    
    archivo<<left<<setw(MAX_CAR_LIN/3)<<' '
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DESCR)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_DIN)<<"PAGO"
            <<endl;
}
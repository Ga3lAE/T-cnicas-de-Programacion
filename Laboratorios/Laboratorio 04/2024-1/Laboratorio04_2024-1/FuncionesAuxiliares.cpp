/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: arias
 * 
 * Created on 4 de mayo de 2025, 04:57 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "FuncionesAuxiliares.h"

#define MAX_DURACION_CITA 2*3600+31*60+25

#define MAX_CAR_LIN 150
#define MAX_CAR_ESP 20
#define MAX_CAR_FECHA 12
#define MAX_CAR_COD 10
#define MAX_CAR_HORA 10
#define MAX_CAR_DESC 35
#define MAX_CAR_DIN 14
#define MAX_CAR_TAB_MED 20
#define MAX_CAR_CONT 5
#define MAX_CAR_CANT 10

//lectura generica
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    
    archivo>>dd;
    if(archivo.eof()) return;
    archivo>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000+mm*100+dd;    
}
void leeHora(ifstream &archivo, int &hora){
    int hh, mm, ss;
    char sep;
    
    archivo>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;  
}

//Impresion generica
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void imprimeTexto(ifstream &archivoLectura, ofstream &archivoReporte, int tam, char del){
    char letra;
    int cantidadLetras=0;
    
    archivoLectura>>ws;    
    while(true){
        letra = archivoLectura.get();
        if(letra == del) break;
        cantidadLetras++;
        
        if(letra == '_') letra = ' ';
        archivoReporte.put(letra);
    }
    archivoReporte<<setw(tam-cantidadLetras)<<' ';
}
void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep = '/';
    
    aa= fecha /10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')
            <<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeHora(ofstream &archivo, int hora){
    int hh, mm, ss;
    char sep = ':';
    
    hh= hora/3600;
    hora%=3600;
    mm=hora/60;
    ss=hora%60;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<left<<setfill(' ')
            <<setw(MAX_CAR_HORA-8)<<' ';
}

//impresion exacta
void imprimeEncabezadoCitas(ofstream &archivoReporte){
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    imprimeLinea(archivoReporte, '=');
}
void imprimeNombreMedico(ifstream &archivoMedicos, ofstream &archivoReporte, 
        char del){
    char letra;
    int cantidadLetras=0;
    
    archivoMedicos>>ws;
    archivoMedicos.get();
    while(true){
        letra = archivoMedicos.get();
        if(letra == del) break;
        cantidadLetras++;
        archivoReporte.put(letra);
    }
    archivoReporte<<endl;
}
void imprimeEncabezadoPacientes(ofstream &archivo){
    archivo<<"PACIENTES ATENDIDOS"<<endl;
    imprimeLinea(archivo, '-');
    archivo<<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_COD)<<"PACIENTE"
            <<setw(MAX_CAR_HORA)<<"INICIO"
            <<setw(MAX_CAR_HORA)<<"FIN"
            <<setw(MAX_CAR_HORA)<<"DURACION"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO"
            <<setw(MAX_CAR_DIN)<<"PAGO"
            <<endl;    
}
void imprimeDatosCitaPaciente(ofstream &archivoReporte,
        int fechaCita, int dniPaciente, 
        int horaInicioCita, int horaFinCita, int duracionCita,
        double porcentajeDescuentoPaciente, double pagoCita){
    imprimeEncabezadoPacientes(archivoReporte);

    imprimeFecha(archivoReporte, fechaCita);
    archivoReporte<<setw(MAX_CAR_COD)<<dniPaciente;
    imprimeHora(archivoReporte, horaInicioCita);
    imprimeHora(archivoReporte, horaFinCita);
    imprimeHora(archivoReporte, duracionCita);
    archivoReporte<<right<<setw(MAX_CAR_DESC-3)<<porcentajeDescuentoPaciente
            <<left<<setw(3)<<'%'
            <<right<<setw(MAX_CAR_DIN-3)<<pagoCita<<setw(3)<<' '<<left
            <<endl;
    
}
void imprimeEncabezadoMedicinas(ofstream &archivo){
    archivo<<setw(MAX_CAR_TAB_MED)<<' '
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_DESC)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_DIN)<<"PAGO"
            <<endl;
}
void imprimeEstadisticasMedicinas(ofstream &archivoReporte, 
        double pagoTotalMedicinas, double pagoTotal){
    archivoReporte<<"PAGO TOTAL POR MEDICINAS: "<<pagoTotalMedicinas<<endl
            <<"PAGP TOTAL: "<<pagoTotal<<endl;
    imprimeLinea(archivoReporte, '_');
}

//Lectura y procesamiento de archivos
void leeProcesaArchivos(const char *nombreArchivoMedicos, 
        const char *nombreArchivoCitasMedicas,
        const char *nombreArchivoMedicinas,
        const char *nombreArchivoReporte){
    ifstream archivoCitasMedicas(nombreArchivoCitasMedicas, ios::in);
    if(not archivoCitasMedicas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCitasMedicas<<endl;
        exit(1);
    }
    ifstream archivoMedicos(nombreArchivoMedicos, ios::in);
    if(not archivoMedicos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoMedicos<<endl;
        exit(1);
    }
    ifstream archivoMedicinas(nombreArchivoMedicinas, ios::in);
    if(not archivoMedicinas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoMedicinas<<endl;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte<<endl;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    //definimos las estadisticas finales
    int codigoMedicoMayorAporte;
    double ingresoMedicoMayorAporte=0;
    
    //procesamos los archivos
    procesaArchivos(archivoMedicos, archivoCitasMedicas, archivoMedicinas, 
            archivoReporte, 
            codigoMedicoMayorAporte, ingresoMedicoMayorAporte);
    
//    imprimeEstadisticasFinales(archivoReporte, archivoMedicos, 
//            codigoMedicoMayorAporte, ingresoMedicoMayorAporte);
    
}
void procesaArchivos(ifstream &archivoMedicos, 
        ifstream &archivoCitasMedicas, 
        ifstream &archivoMedicinas,
        ofstream &archivoReporte,
        int &codigoMedicoMayorAporte, double &ingresoMedicoMayorAporte){
    imprimeEncabezadoCitas(archivoReporte);
    
    int codigoMedico;
    double tarifaMedico;
    while(true){
        //50611     /EDGAR MUNOZ VERGEL/   Urologia   337.03
        archivoMedicos>>codigoMedico;
        if(archivoMedicos.eof()) break;       
        archivoReporte<<left<<"CODIGO DEL MEDICO: "<<codigoMedico<<endl
                <<"NOMBRE DEL MEDICO: ";
        imprimeNombreMedico(archivoMedicos, archivoReporte, '/');
        archivoReporte<<"ESPECIALIDAD: ";
        imprimeTexto(archivoMedicos, archivoReporte, MAX_CAR_ESP, ' ');
        archivoReporte<<endl;
        archivoMedicos>>tarifaMedico;
        archivoReporte<<left<<"TARIFA: "<<tarifaMedico<<endl;                                
        
        procesaCitas(archivoCitasMedicas, archivoMedicinas, 
                archivoReporte, 
                codigoMedico, tarifaMedico, 
                codigoMedicoMayorAporte, ingresoMedicoMayorAporte);
    }        
}
void procesaCitas(ifstream &archivoCitasMedicas, ifstream &archivoMedicinas, 
        ofstream &archivoReporte, 
        int codigoMedico, double tarifa,
        int &codigoMedicoMayorAporte, double &ingresoMedicoMayorAporte){
    int fechaCita, dniPaciente, horaInicioCita, horaFinCita, duracionCita,
            codigoMedicoCita;
    double porcentajeDescuentoPaciente, pagoCita=0;
    
    archivoCitasMedicas.clear();
    archivoCitasMedicas.seekg(0, ios::beg);
    while(true){
        //9/9/2023   94683380   2.60   11:17:52   12:48:30   40414   28409   5
        leeFecha(archivoCitasMedicas, fechaCita);
        if(archivoCitasMedicas.eof()) break;
        archivoCitasMedicas>>dniPaciente>>porcentajeDescuentoPaciente;
        leeHora(archivoCitasMedicas, horaInicioCita);
        leeHora(archivoCitasMedicas, horaFinCita);
        duracionCita = horaFinCita-horaInicioCita;
        pagoCita = duracionCita/3600.0 * tarifa;
        archivoCitasMedicas>>codigoMedicoCita;
        
        if(codigoMedicoCita != codigoMedico or duracionCita>=MAX_DURACION_CITA)
            while(archivoCitasMedicas.get()!='\n');
        else{
            imprimeDatosCitaPaciente(archivoReporte, 
                    fechaCita, dniPaciente,
                    horaInicioCita, horaFinCita, duracionCita,
                    porcentajeDescuentoPaciente, pagoCita); 
            archivoReporte<<"MEDICINAS RECETADAS:"<<endl;
            imprimeEncabezadoMedicinas(archivoReporte);
            int cantidadMedicinasRecetada, codigoMedicinaRecetada, contadorMedicinas=0;
            double pagoTotalMedicinas=0, pagoTotal;
            while(true){                
                if(archivoCitasMedicas.get()=='\n') break;
                archivoCitasMedicas>>codigoMedicinaRecetada>>cantidadMedicinasRecetada;
                procesaMedicinas(archivoMedicinas, archivoReporte, 
                        cantidadMedicinasRecetada, codigoMedicinaRecetada, 
                        pagoTotalMedicinas, contadorMedicinas);               
            }
            imprimeLinea(archivoReporte, '.');
            pagoTotal = pagoTotalMedicinas+pagoCita;
            imprimeEstadisticasMedicinas(archivoReporte, pagoTotalMedicinas, pagoTotal);
            
//            asignaMayorIngresoDoctor(pagoTotal, ingresoMedicoMayorAporte,
//                    codigoMedico, codigoMedicoMayorAporte);
        }
    }
}
void procesaMedicinas(ifstream &archivoMedicinas,ofstream &archivoReporte, 
        int cantidadMedicinasRecetada, int codigoMedicinaRecetada,
        double &pagoTotalMedicinas, int &contadorMedicinas){
    
    int codigoMedicinaActual;
    double precioMedicinaActual;
        
    archivoMedicinas.clear();
    archivoMedicinas.seekg(0, ios::beg);
    while(true){
        //60509 AMPICILINA_125MG_SUSP_90ML   58.65
        archivoMedicinas>>codigoMedicinaActual;
        if(archivoMedicinas.eof()) break;
        if(codigoMedicinaActual != codigoMedicinaRecetada)
            while(archivoMedicinas.get()!='\n');
        else{
            contadorMedicinas++;
            archivoReporte<< setw(MAX_CAR_TAB_MED) << ' '
                    << setw(MAX_CAR_CONT) << contadorMedicinas;
            imprimeTexto(archivoMedicinas, archivoReporte, MAX_CAR_DESC, ' ');            
            archivoMedicinas>>precioMedicinaActual;
            double pago = precioMedicinaActual*cantidadMedicinasRecetada;
            archivoReporte<< setw(MAX_CAR_CANT) <<cantidadMedicinasRecetada
                    << setw(MAX_CAR_DIN) <<precioMedicinaActual
                    << setw(MAX_CAR_DIN) << pago
                    << endl;
            pagoTotalMedicinas+=pago;
        }
    }        
}
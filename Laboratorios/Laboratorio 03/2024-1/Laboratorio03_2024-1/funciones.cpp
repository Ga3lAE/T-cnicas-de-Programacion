#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_FECHA 12
#define MAX_CAR_DNI 10
#define MAX_CAR_HORA 10
#define MAX_CAR_DESC 15
#define MAX_CAR_NOMBRE 40
#define MAX_CAR_ESP 24
#define MAX_CAR_DIN 14

void imprimeLinea(ofstream &archivo, char car){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<car;
    }
    archivo<<endl;
}

void leeProcesaArchivos(const char *nombreArchivoCitas, const char *nombreArchivoMedicos,
        const char *nombreArchivoReporte){
    ifstream archivoCitas(nombreArchivoCitas, ios::in);
    if(not archivoCitas.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivoCitas<<endl;
        exit(1);
    }
    ifstream archivoMedicos(nombreArchivoMedicos, ios::in);
    if(not archivoMedicos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivoMedicos<<endl;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivoReporte<<endl;
        exit(1);
    }
    
    double totalIngresos=0;
    int dniPacienteMayorGasto;
    double mayorGastoPaciente;
    
    leeProcesaDatos(archivoCitas, archivoMedicos, archivoReporte, 
            totalIngresos, dniPacienteMayorGasto, mayorGastoPaciente);
    
    imprimeEstadisticas(archivoReporte, 
            totalIngresos, dniPacienteMayorGasto, mayorGastoPaciente);
}

void leeProcesaDatos(ifstream &archivoCitas, ifstream &archivoMedicos, 
        ofstream &archivoReporte, 
        double &totalIngresos, int &dniMayorGasto, double &mayorGasto){
    
    imprimeEncabezado(archivoReporte);
    
    //9/09/2023   94683380   2.60   11:17:52   12:48:30   40414   S   317.86
    int fecha, dniPaciente, horaInicio, horaFin, codigoMedico;
    double porcentajeDescuentoPaciente, pagoMedicina;
    char recibeMedicina;
    bool primerPaciente=true;
    
    while(true){
        leeFecha(archivoCitas, fecha);
        if(archivoCitas.eof()) break;
        archivoCitas>>dniPaciente>>porcentajeDescuentoPaciente;
        leeHora(archivoCitas, horaInicio);
        leeHora(archivoCitas, horaFin);
        archivoCitas>>codigoMedico>>recibeMedicina;
        if(recibeMedicina=='S')
            archivoCitas>>pagoMedicina;
        
        imprimeDatosPaciente(archivoReporte, 
                fecha, dniPaciente, horaInicio, horaFin, porcentajeDescuentoPaciente);
        
        double duracion = horaFin-horaInicio;
        procesaImprimeDatosMedico(archivoMedicos, archivoReporte, 
                codigoMedico, 
                duracion, porcentajeDescuentoPaciente, pagoMedicina, 
                totalIngresos, 
                dniMayorGasto, mayorGasto, 
                primerPaciente, dniPaciente);
        
    }
}
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    archivo>>dd;
    if(archivo.eof()) return;
    archivo>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000+mm*100+dd;
}
12:30:25
void leeHora(ifstream &archivo, int &hora){
    int hh, mm, ss;
    char sep;
    archivo>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;
}

void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep='/';
    aa=fecha/10000;
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
    char sep=':';
    hh=hora/3600;
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
void imprimeEncabezado(ofstream &archivoReporte){
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    imprimeLinea(archivoReporte, '=');
    imprimeCategorias(archivoReporte);
}
void imprimeCategorias(ofstream &archivo){
    archivo<<left
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_DNI)<<"PACIENTE"
            <<setw(MAX_CAR_HORA)<<"INICIO"
            <<setw(MAX_CAR_HORA)<<"FIN"
            <<setw(MAX_CAR_DESC)<<"% POR SEGURO"
            <<setw(MAX_CAR_NOMBRE)<<"MEDICO"
            <<setw(MAX_CAR_ESP)<<"ESPECIALIDAD"
            <<setw(MAX_CAR_DIN)<<"PAGO (CITA+MEDICINA)"
            <<endl;
}
void imprimeDatosPaciente(ofstream &archivo, 
        int fecha, int dni, int horaInicio, int horaFin, double porcentajeDescuento){
    imprimeFecha(archivo, fecha);
    archivo<<left
            <<setw(MAX_CAR_DNI)<<dni;
    imprimeHora(archivo, horaInicio);
    imprimeHora(archivo, horaFin);
    archivo<<fixed<<setprecision(2)
            <<right<<setw(2*MAX_CAR_DESC/3)<<porcentajeDescuento
            <<left<<setw(MAX_CAR_DESC/3)<<' ';
}
void procesaImprimeDatosMedico(ifstream &archivoMedicos, ofstream &archivoReporte, 
        int codigoMedico, 
        int duracion, double porcentajeDescuento, double pagoMedicina, 
        double &totalIngresos, 
        int &dniMayorGasto, double &mayorGasto, bool& primerPaciente, int dniPaciente){
    archivoMedicos.clear();
    archivoMedicos.seekg(0, ios::beg);
    
    int codigoMedicoActual;
    double tarifaMedico, pagoPaciente;
    while(true){
        archivoMedicos>>codigoMedicoActual;
        if(archivoMedicos.eof()) return;
        
        if(codigoMedico==codigoMedicoActual){
            leeImprimeNombre(archivoMedicos, archivoReporte);
            leeImprimeEspecialidad(archivoMedicos, archivoReporte);
            archivoMedicos>>tarifaMedico;

            pagoPaciente=duracion/3600.0*tarifaMedico*(1-porcentajeDescuento/100.0);
            procesaMayor(dniMayorGasto, mayorGasto, primerPaciente, 
                    dniPaciente, pagoPaciente);
            pagoPaciente+=pagoMedicina*(1-porcentajeDescuento/200.0);
            archivoReporte<<fixed<<setprecision(2)
                    <<pagoPaciente<<endl;
            
            totalIngresos+=pagoPaciente;
        }
        else while(archivoMedicos.get()!='\n');
    }
}
void procesaMayor(int &dniMayor, double &mayorGasto, 
        bool &primerPaciente, int dniPaciente, double pagoPaciente){
    if(primerPaciente){
        dniMayor=dniPaciente;
        mayorGasto=pagoPaciente;
        primerPaciente=false;
    }
    if(pagoPaciente>mayorGasto){
        mayorGasto=pagoPaciente;
        dniMayor=dniPaciente;
    }
}
void leeImprimeNombre(ifstream &archivoLectura ,ofstream &archivoImpresion){
    char letra;
    int cantidadLetras=0;    
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == ' ') break;
        cantidadLetras++;
        
        if(cantidadLetras==1){
            archivoImpresion<<letra;
        }
        else if(letra =='_'){
            letra=' ';
            archivoImpresion<<letra;
            letra = archivoLectura.get();
            cantidadLetras++;            
            archivoImpresion<<letra;
        }
        
        else if(letra>='A' and letra <='Z'){
            letra-='A'-'a';
            archivoImpresion<<letra;
        }
        
        
        
    }
    archivoImpresion<<setw(MAX_CAR_NOMBRE-cantidadLetras)<<' ';
}
void leeImprimeEspecialidad(ifstream &archivoLectura ,ofstream &archivoImpresion){
    char letra;
    int cantidadLetras=0;    
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == ' ') break;
        cantidadLetras++;                
        
        archivoImpresion<<letra;                
    }
    archivoImpresion<<setw(MAX_CAR_ESP-cantidadLetras)<<' ';
}
void imprimeEstadisticas(ofstream &archivoReporte, 
            double totalIngresos, int dniPacienteMayorGasto, double mayorGastoPaciente){
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<"TOTAL DE INGRESOS: "<<totalIngresos<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<"PACIENTE QUE MAS GASTO EN UNA CITA MEDICA: "<<dniPacienteMayorGasto<<endl
            <<"MONTO GASTADO: "<<mayorGastoPaciente<<endl;
    imprimeLinea(archivoReporte, '=');
}

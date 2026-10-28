#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_HORA 9
#define MAX_CAR_DNI 10
#define MAX_CAR_NOMBRE 40
#define MAX_CAR_SEXO 14
#define MAX_CAR_CTG 12
#define MAX_CAR_COMP 14
#define MAX_CAR_CHN 14

void imprimeLinea(ofstream &archivoReporte, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        archivoReporte<<c;
    }
    archivoReporte<<endl;
}

void leeProcesaDatos(const char *nombreArchivoRegistro, 
        const char *nombreArchivoReporte){
    ifstream archivoRegistro(nombreArchivoRegistro, ios::in);
    if(not archivoRegistro.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivoRegistro;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivoReporte;
        exit(1);
    }
    
    int cantidadTelevidentes=0, 
            tiempoTotalVistoMenoresYAdultos=0, cantidadMenoresYADultos=0, 
            cantidadMujeres=0, cantidadMujeresVenTvpucp=0;
    double promedioTiempoVistoMenoresYAdultos, porcentajeMujeresVenTvpucp;
    
    procesaArchivos(archivoRegistro, archivoReporte, 
            cantidadTelevidentes, 
            tiempoTotalVistoMenoresYAdultos, cantidadMenoresYADultos, 
            cantidadMujeres, cantidadMujeresVenTvpucp);
    
    promedioTiempoVistoMenoresYAdultos=tiempoTotalVistoMenoresYAdultos*1.0/cantidadMenoresYADultos;
    porcentajeMujeresVenTvpucp=cantidadMujeresVenTvpucp*100.0/cantidadMujeres;
    
    imprimeEstadisticas(archivoReporte, 
            cantidadTelevidentes, promedioTiempoVistoMenoresYAdultos, 
            porcentajeMujeresVenTvpucp);
}

void procesaArchivos(ifstream &archivoRegistro, ofstream &archivoReporte, 
            int &cantidadTelevidentes, 
            int &tiempoTotalVistoMenoresYAdultos, int &cantidadMenoresYADultos, 
            int &cantidadMujeres, int &cantidadMujeresVenTvpucp){
    
    imprimeEncabezado(archivoReporte);
    
    //69323674  M  ROSARIO_MENDOZA_EGUSQUIZA   B   
    //31/03/2013    556     13:54:27   16:12:37
    int dni, fechaNacimiento;
    char sexo, compania;
    while(true){
        imprimeLinea(archivoReporte, '-');
        archivoRegistro>>dni;
        if(archivoRegistro.eof()) break;
        cantidadTelevidentes++;
        archivoReporte<<left<<setw(MAX_CAR_DNI)<<dni;
        archivoRegistro>>sexo;
        leeImprimeNombre(archivoRegistro, archivoReporte, ' ');
        imprimeSexo(archivoReporte, sexo);
        archivoRegistro>>compania;
        leeFecha(archivoRegistro, fechaNacimiento);
        imprimeCategoria(archivoReporte, fechaNacimiento);
        imprimeCompania(archivoReporte, compania);
        archivoReporte<<endl;

        int canal, horaInicio, horaFin, tiempoTotal=0;
        
        while(true){            
            if(archivoRegistro.get() =='\n') break;
            archivoRegistro>>canal;
            leeHora(archivoRegistro, horaInicio);
            leeHora(archivoRegistro, horaFin);
            int duracion;
            duracion = horaFin-horaInicio;
            tiempoTotal+=duracion;
            if(fechaNacimiento/10000>=2009 or fechaNacimiento<1988){
                tiempoTotalVistoMenoresYAdultos+=duracion;
                cantidadMenoresYADultos++;
            }
            
            if(sexo == 'F'){
                cantidadMujeres++;
                if(compania=='A')
                    cantidadMujeresVenTvpucp++;
            }
            
            
            archivoReporte
                    <<setw(MAX_CAR_DNI+MAX_CAR_NOMBRE+MAX_CAR_SEXO+
                    MAX_CAR_CTG+MAX_CAR_COMP)<<' '
                    <<setw(MAX_CAR_CHN)<<canal;
            imprimeHora(archivoReporte, horaInicio);
            archivoReporte<<'-';
            imprimeHora(archivoReporte, horaFin);
            imprimeHora(archivoReporte, duracion);
            archivoReporte<<endl;
            
        }
        archivoReporte<<right
                <<setw(MAX_CAR_DNI+MAX_CAR_NOMBRE+MAX_CAR_SEXO+
                MAX_CAR_CTG+MAX_CAR_COMP+MAX_CAR_CHN+MAX_CAR_HORA*2+1)<<"TIEMPO TOTAL: "
                <<left;
        imprimeHora(archivoReporte, tiempoTotal);
        archivoReporte<<endl;
    }
}


void leeImprimeNombre(ifstream &archivoEntrada, ofstream &archivoSalida, char del){
    char letra;
    int cantidadLetras=0;
    archivoEntrada>>ws;
    while(true){        
        letra=archivoEntrada.get();
        if(letra == del) break;
        cantidadLetras++;
        if(cantidadLetras==1)
            archivoSalida<<letra;
        else{
            if(letra=='_'){
                letra=' ';
                archivoSalida<<letra;
                letra = archivoEntrada.get();
                cantidadLetras++;
                archivoSalida<<letra;
                letra = archivoEntrada.get();
                cantidadLetras++;
            }
            if(letra<='Z' and letra >='A')
                letra-='A'-'a';           
            archivoSalida<<letra;            
        }                    
    }
    archivoSalida<<setw(MAX_CAR_NOMBRE-cantidadLetras)<<' ';
}
void leeFecha(ifstream &archivoEntrada, int &fecha){
    int dd, mm, aa;
    char sep;
    archivoEntrada>>dd>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000+mm*100+dd;
}
void leeHora(ifstream &archivoEntrada, int &hora){
    int hh, mm, ss;
    char sep;
    archivoEntrada>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;
}
void imprimeEncabezado(ofstream &archivoReporte){
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE OPINION VENUS S.A."<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES"<<endl;
    imprimeLinea(archivoReporte, '=');
    imprimeCategorias(archivoReporte);
}
void imprimeCategorias(ofstream &archivoReporte){
    archivoReporte<<left
            <<setw(MAX_CAR_DNI)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_SEXO)<<"SEXO"
            <<setw(MAX_CAR_CTG)<<"CATEGORIA"
            <<setw(MAX_CAR_COMP)<<"COMPANIA"
            <<setw(MAX_CAR_CHN)<<"CANAL"
            <<setw(MAX_CAR_HORA*2+1)<<"RANGO"            
            <<setw(MAX_CAR_HORA)<<"DURACION"<<endl;
}
void imprimeEstadisticas(ofstream& archivoReporte, 
        int cantidadTelevidentes, double promedioTiempoVistoMenoresYAdultos, 
        double porcentajeMujeresVenTvpucp){
    archivoReporte<<fixed<<setprecision(2)
            <<"ESTADISTICAS OBTENIDAS:"<<endl
            <<"CANTIDAD DE TELEVIDENTES REGISTRADOS: "<<cantidadTelevidentes<<endl
            <<"TIEMPO PROMEDIO QUE VEN LOS MENORES Y ADULTOS: ";
    imprimeHora(archivoReporte, promedioTiempoVistoMenoresYAdultos);
    archivoReporte<<endl
            <<"PORCENTAJE DE MUJERES QUE VEN TVPUCP: "<<porcentajeMujeresVenTvpucp<<'%'<<endl;
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
            <<left<<setfill(' ')<<setw(MAX_CAR_HORA-8)<<' ';
}
void imprimeSexo(ofstream &archivoReporte, char sexo){
    if(sexo=='M')
        archivoReporte<<setw(MAX_CAR_SEXO)<<"MASCULINO";
    else if(sexo == 'F')
        archivoReporte<<setw(MAX_CAR_SEXO)<<"FEMENINO";
}
void imprimeCategoria(ofstream &archivoReporte, int fecha){    
    fecha/=10000;
    
    if(fecha>=2009)
        archivoReporte<<setw(MAX_CAR_CTG)<<"MENOR";
    else if(fecha>=1988)
        archivoReporte<<setw(MAX_CAR_CTG)<<"JOVEN";
    else
        archivoReporte<<setw(MAX_CAR_CTG)<<"ADULTO";
}
void imprimeCompania(ofstream &archivoReporte, char empresa){
    if(empresa == 'A')
        archivoReporte<<setw(MAX_CAR_COMP)<<"TVPUCP";
    else if(empresa == 'B')
        archivoReporte<<setw(MAX_CAR_COMP)<<"CABLEMAS";
    else if(empresa == 'C')
        archivoReporte<<setw(MAX_CAR_COMP)<<"TPVISION";
}
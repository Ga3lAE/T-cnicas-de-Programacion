#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_FECHA 12
#define MAX_CAR_TIPO 14
#define MAX_CAR_PLACA 8
#define MAX_CAR_HORA 10
#define MAX_CAR_GRAV 14
#define MAX_CAR_INCR 15
#define MAX_CAR_DIN 10

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

void procesaArchivos(ifstream &archivoInfracciones, ofstream &archivoReporte,        
        int &dniMayorPago, int &dniMenorPago, 
        double &mayorPago, double &menorPago){
    int fecha1, fecha2;
    leeFecha(archivoInfracciones, fecha1);
    leeFecha(archivoInfracciones, fecha2);
    
    imprimeEncabezado(archivoReporte, fecha1, fecha2);
    
    int dni;
    int cantidadCompanias=0;
    bool primeraLectura=true;
    double totalRecaudado=0;
    while(true){
        // 88167677      Prado/Vera/Juan
        leeImprimeDatos(archivoInfracciones, archivoReporte, 
                dni, cantidadCompanias);
        if(archivoInfracciones.eof()) break;
        
        double pagoTotal=0;
        procesaMultas(archivoInfracciones, archivoReporte, 
                pagoTotal, fecha1, fecha2);
        totalRecaudado+=pagoTotal;
        
        imprimeLinea(archivoReporte, '-');
        archivoReporte<<"PAGO TOTAL: "
                <<fixed<<setprecision(2)<<pagoTotal<<endl;
        imprimeLinea(archivoReporte, '=');
        asignaMayorMenor(dniMayorPago, dniMenorPago, 
                mayorPago, menorPago, primeraLectura, 
                dni, pagoTotal);
    }
    archivoReporte<<"TOTAL RECAUDADO: "<<totalRecaudado<<endl;
}
void procesaMultas(ifstream &archivoInfracciones, ofstream &archivoReporte, 
                double &pagoTotal, int fecha1, int fecha2){
    char tipoCarro, tipoInfraccion, descC;
    int placaCarro, placaCarro1, placaCarro2, fechaInfraccion, horaInfraccion;
    double multa, incrementoTipo, incrementoFecha, incrementoHora;
    imprimeCategoriasMulta(archivoReporte);
    while(true){
        //C264-957      13/08/2023    04:32:00        M  
        //M366-914        12/09/2024    03:08:38    L
        if(archivoInfracciones.get()=='\n') return;
        archivoInfracciones>>tipoCarro>>placaCarro1>>descC>>placaCarro2;
        leeFecha(archivoInfracciones, fechaInfraccion);
        leeHora(archivoInfracciones, horaInfraccion);
        archivoInfracciones>>tipoInfraccion;
        
        placaCarro = placaCarro1*1000+placaCarro2;
        imprimeTipoCarro(archivoReporte, tipoCarro);
        archivoReporte<<setw(MAX_CAR_PLACA)<<placaCarro;
        imprimeFecha(archivoReporte, fechaInfraccion);
        imprimeHora(archivoReporte, horaInfraccion);
        imprimeGravedad(archivoReporte, tipoInfraccion);
        asignaMulta(multa, tipoInfraccion);
        archivoReporte<<fixed<<setprecision(2)
                <<setw(MAX_CAR_DIN)<<multa;
        asingaIncrementos(multa, 
                incrementoFecha, incrementoHora, incrementoTipo, 
                fecha1, fecha2, fechaInfraccion, horaInfraccion, tipoCarro);
        pagoTotal += multa +incrementoFecha+incrementoHora+incrementoTipo;
        archivoReporte<<fixed<<setprecision(2)
                <<setw(MAX_CAR_INCR)<<incrementoTipo
                <<setw(MAX_CAR_INCR)<<incrementoFecha
                <<setw(MAX_CAR_INCR)<<incrementoHora
                <<setw(MAX_CAR_DIN)<<multa +incrementoFecha+incrementoHora+incrementoTipo
                <<endl;                        
    }
}

void asignaMayorMenor(int &dniMayorPago, int &dniMenorPago, 
        double &mayorPago, double &menorPago, bool &primerLectura, 
        int dni, double pagoTotal){
    
    if(primerLectura){
        dniMayorPago = dni;
        dniMenorPago = dni;        
        mayorPago=pagoTotal; 
        menorPago=pagoTotal;
        primerLectura=false;
    }
    
    if(pagoTotal>mayorPago){
        mayorPago=pagoTotal;
        dniMayorPago=dni;
    }
    if(pagoTotal<menorPago){
        menorPago=pagoTotal;
        dniMenorPago=dni;
    }
}
void asignaMulta(double& multa, char tipo){
    if(tipo =='L')
        multa=158.33;
    if(tipo =='M')
        multa=516.75;
    if(tipo =='G')
        multa=3920.25;
}
void asingaIncrementos(double multa, 
         double &incrementoFecha, double &incrementoHora, double &incrementoTipo,
         int fecha1, int fecha2, int fechaInfraccion, 
        int horaInfraccion, 
        char tipoCarro){
    if(fechaInfraccion<fecha1)
        incrementoFecha = multa/100.0*10.75;   
    else if(fechaInfraccion<fecha2)
        incrementoFecha = multa/100.0*7.25;   
    else 
        incrementoFecha = multa/100.0*0.00;   
    
    if(tipoCarro == 'P')
        incrementoTipo = multa/100.0*2.7;   
    else if(tipoCarro == 'M')
        incrementoTipo = multa/100.0*11.7;
    else if(tipoCarro == 'C')
        incrementoTipo = multa/100.0*15.3;
    
    if(horaInfraccion>4*3600+30*60 and horaInfraccion<11*3600+25*60)
        incrementoHora = multa/100.0*8.5;
    else if(horaInfraccion>=11*3600+25*60 and horaInfraccion<20*3600+40*60)
        incrementoHora = multa/100.0*5.8;
    else
        incrementoHora = multa/100.0*3.7;
}

void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    
    archivo>>dd>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000 +mm*100 +dd;
                
}
void leeHora(ifstream &archivo, int &hora){
    int hh, mm ,ss;
    char sep;
    
    archivo>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60 +ss;
                
}
void leeImprimeDatos(ifstream &archivoInfracciones, ofstream &archivoReporte, 
        int &dni, int &cantidadCompanias){
    archivoInfracciones>>dni;
    if(archivoInfracciones.eof()) return;
    cantidadCompanias++;
    archivoReporte<<left<<"COMPANIA No. "<<cantidadCompanias<<endl;
    archivoReporte<<"REPRESENTANTE: ";
    leeImprimeNombre(archivoInfracciones, archivoReporte);
    archivoReporte<<"DNI: "<<dni<<endl;
    imprimeLinea(archivoReporte, '-');
    
}
void leeImprimeNombre(ifstream &archivoLectura, ofstream &archivoImpresion){
    char letra;
    int cantidadLetras=0;
    
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == ' ') break;
        cantidadLetras++;
        
        if(letra =='-' or letra =='/') letra=' ';
        //convertir todo a mayusculas
        if(letra<='z' and letra >='a') letra+='A'-'a';
            
        archivoImpresion<<letra;
    }
    archivoImpresion<<setw(MAX_CAR_NOMBRE-cantidadLetras)<<' ';
}

void imprimeEncabezado(ofstream &archivo, int fecha1, int fecha2){
    archivo<<setw(MAX_CAR_LIN/2)<<"MIUANISTERIO DE TRANSPORTES"<<endl
            <<setw(MAX_CAR_LIN/2)<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl
            <<setw(MAX_CAR_LIN/2)<<"RANGO DE FECHAS A CONSIDERAR: ";
    imprimeFecha(archivo, fecha1);
    imprimeFecha(archivo, fecha2);
    archivo<<endl;
    imprimeLinea(archivo, '=');
    
}
void imprimeCategoriasMulta(ofstream &archivoReporte){
    archivoReporte<<right
            <<setw(MAX_CAR_TIPO+MAX_CAR_PLACA+MAX_CAR_FECHA+MAX_CAR_HORA+MAX_CAR_GRAV +MAX_CAR_DIN+3*MAX_CAR_INCR/2)<<"INCREMENTOS:"
            <<endl<<left
            <<setw(MAX_CAR_TIPO)<<"TIPO"
            <<setw(MAX_CAR_PLACA)<<"PLACA"
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_HORA)<<"HORA"
            <<setw(MAX_CAR_GRAV)<<"GRAVEDAD"
            <<setw(MAX_CAR_DIN)<<"MULTA"
            <<setw(MAX_CAR_INCR)<<"POR TIPO"
            <<setw(MAX_CAR_INCR)<<"POR FECHA"
            <<setw(MAX_CAR_INCR)<<"POR HORA"
            <<setw(MAX_CAR_DIN)<<"PAGO TOTAL"
            <<endl;
}
void imprimeFecha(ofstream& archivo, int fecha){
    int dd, mm, aa;
    char sep ='/';
    
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')<<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeHora(ofstream& archivo, int hora){
    int hh, mm, ss;
    char sep =':';
    
    hh=hora/3600;
    hora%=3600;
    mm=hora/60;
    ss=hora%60;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<left<<setfill(' ')<<setw(MAX_CAR_HORA-8)<<' ';
    
}
void imprimeTipoCarro(ofstream &archivo, char tipo){
    if(tipo == 'P')
        archivo<<setw(MAX_CAR_TIPO)<<"PEQUENO";
    if(tipo == 'M')
        archivo<<setw(MAX_CAR_TIPO)<<"MEDIANO";
    if(tipo == 'C')
        archivo<<setw(MAX_CAR_TIPO)<<"GRANDE";    
}
void imprimeGravedad(ofstream &archivo, char tipo){
    if(tipo == 'L')
        archivo<<setw(MAX_CAR_TIPO)<<"LEVE";
    if(tipo == 'G')
        archivo<<setw(MAX_CAR_TIPO)<<"GRAVE";
    if(tipo == 'M')
        archivo<<setw(MAX_CAR_TIPO)<<"MUY GRAVE";    
}
void imprimeEstadisticas(ofstream&archivoReporte,
        int dniMayorPago, int dniMenorPago, 
        double mayorPago, double menorPago){
    imprimeLinea(archivoReporte, '/');
    archivoReporte<<fixed<<setprecision(2)
            <<"//COMPANIA CON MAYOR PAGO POR INFRACCIONES:"<<endl
            <<"//DNI: "<<dniMayorPago<<endl
            <<"//TOTAL PAGADO: "<<mayorPago<<endl
            <<"//COMPANIA CON MENOR PAGO POR INFRACCIONES:"<<endl
            <<"//DNI: "<<dniMenorPago<<endl
            <<"//TOTAL PAGADO: "<<menorPago<<endl;
    imprimeLinea(archivoReporte, '/');
}
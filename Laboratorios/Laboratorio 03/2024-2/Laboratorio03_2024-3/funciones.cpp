#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_COD 15
#define MAX_CAR_DIN 15
#define MAX_CAR_DESC_PLATO 50
#define MAX_CAR_TIPO_PLATO 20
#define MAX_CAR_HORA 18
#define MAX_CAR_CANT 15

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

void leeProcesaArchivos(const char *nombreArchivoPedidos, 
        const char *nombreArchivoPlatos, 
        const char *nombreArchivoReporte){

    ifstream archivoPedidos(nombreArchivoPedidos, ios::in);
    if(not archivoPedidos.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoPedidos;
        exit(1);
    }
    ifstream archivoPlatos(nombreArchivoPlatos, ios::in);
    if(not archivoPlatos.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoPlatos;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoReporte;
        exit(1);
    }
    
    double totalRecaudado=0;
    
    procesaDatos(archivoPedidos, archivoPlatos, archivoReporte, 
            totalRecaudado);
}

void procesaDatos(ifstream &archivoPedidos, ifstream &archivoPlatos,
        ofstream &archivoReporte, 
        double &totalRecaudado){
    
    imprimeEncabezado(archivoReporte);
    
    //31796 ANTICUCHO_DE_CORAZON_AL_PLATO   31.90   ESPECIALES
    int codigoPlato;
    double precioPlato;
    while(true){
        archivoPlatos>>codigoPlato;
        if(archivoPlatos.eof()) break;
        imprimeDatosPlato(archivoPlatos, archivoReporte, 
                codigoPlato, precioPlato);
        // hasta acá ya tenemos el codigo del plato y su precio
        imprimeEncabezadoRepartos(archivoReporte);
        // lee el archivo de rapartos, entonces le paso el codigo del plato y su precio
        procesaRepartos(archivoPedidos, archivoReporte, 
                codigoPlato, precioPlato, totalRecaudado);
        

    }
    imprimeLinea(archivoReporte, '-');
    archivoReporte<<fixed<<setprecision(2)<<"TOTAL RECAUDADO: "<<totalRecaudado<<endl;
}
void procesaRepartos(ifstream &archivoRepartos, ofstream &archivoReporte, 
        int codigoPlato, double precioPlato, 
        double &totalRecaudado){
    int cantidadAtendia=0;
    double pagoEnvios=0;
    
    // LINEAS CLAVE
    archivoRepartos.clear();
    archivoRepartos.seekg(0, ios::beg);
    //45601937  JUSTINO/NORABUENA/VIRGINIA-KARINA   18:49:08   
    // 8   11471   7   77572   4   15724   2   15921   5   11171  
    int codigoRepartidor, horaPartida;
    //empieza la busqueda
    while(true){
        archivoRepartos>>codigoRepartidor;
        if(archivoRepartos.eof()) break;
        //salta nombre
        archivoRepartos>>ws;
        while(archivoRepartos.get()!=' ');
        leeHora(archivoRepartos, horaPartida);        
        
        int cantidadPedida, codigoPlatoPedido;
        while(true){
            if(archivoRepartos.get()=='\n') break;
            archivoRepartos>>cantidadPedida>>codigoPlatoPedido;
            if(codigoPlato==codigoPlatoPedido){
                imprimePlato(archivoReporte, 
                        codigoRepartidor, horaPartida, 
                        cantidadPedida, cantidadAtendia, 
                        pagoEnvios, precioPlato, 
                        totalRecaudado);
            }
        }
    }
    imprimeLinea(archivoReporte, '-');
        archivoReporte<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD+MAX_CAR_HORA)<<"TOTAL: "
                <<setw(MAX_CAR_CANT)<<cantidadAtendia
                <<setw(MAX_CAR_DIN)<<pagoEnvios<<endl;
    imprimeLinea(archivoReporte, '=');
}
void leeHora(ifstream &archivo, int &hora){
    int hh, mm, ss;
    char sep;
    
    //hora en segundos desde que inicio el dia
    archivo>>hh>>sep>>mm>>sep>>ss;
    hora = hh*3600+mm*60+ss;
}

void imprimeEncabezado(ofstream& archivo){
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE REPARTOS A DOMICILIO TP"<<endl;
    imprimeLinea(archivo, '=');
}
void imprimeDatosPlato(ifstream &archivoPlatos, 
        ofstream &archivoReporte, 
        int codigoPlato, double &precioPlato){
    archivoReporte<<left
            <<"CODIGO: "<<setw(MAX_CAR_COD)<<codigoPlato;
    imprimeDescripcionPlato(archivoPlatos, archivoReporte);
    archivoPlatos>>precioPlato;
    archivoReporte<<fixed<<setprecision(2)
            <<"PRECIO: "<<setw(MAX_CAR_DIN)<<precioPlato;
    imprimeTipoPlato(archivoPlatos, archivoReporte);    
}
void imprimeEncabezadoRepartos(ofstream &archivoReporte){
    archivoReporte<<"REPARTOS REALIZADOS: "<<endl;
    imprimeLinea(archivoReporte, '-');
    imprimeCategorias(archivoReporte);
}
void imprimeCategorias(ofstream &archivoReportes){
    archivoReportes<<left
            <<setw(MAX_CAR_COD)<<"REPARTIDOR"
            <<setw(MAX_CAR_HORA)<<"HORA PARTIDA"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"TOTAL PAGADO"
            <<endl;
}
void imprimeDescripcionPlato(ifstream &archivoPlatos, ofstream &archivoReporte){
    char letra;
    int cantidadLetras=0;
    archivoPlatos>>ws;
    
    while(true){
        letra = archivoPlatos.get();
        if(letra ==' ') break;
        cantidadLetras++;
        archivoReporte<<letra;
    }
    archivoReporte<<setw(MAX_CAR_DESC_PLATO-cantidadLetras)<<' ';
}
void imprimeTipoPlato(ifstream &archivoPlatos, ofstream &archivoReporte){
    char letra;
    archivoPlatos>>ws;
    
    while(true){
        letra = archivoPlatos.get();
        if(letra =='\n') break;
        archivoReporte<<letra;
    }
    archivoReporte<<endl;;
}
void imprimePlato(ofstream &archivoReporte,
        int codigoRepartidor, int horaPartida, 
        int cantidadPedida, int& cantidadAtendia, 
        double &pagoEnvios, double precio,
        double &totalRecaudado){
    
    double pago;
    pago = cantidadPedida*precio;
            
    archivoReporte<<left
            <<setw(MAX_CAR_COD)<<codigoRepartidor;
    imprimeHora(archivoReporte, horaPartida);
    archivoReporte<<setw(MAX_CAR_CANT)<<cantidadPedida
            <<setw(MAX_CAR_DIN)<<pago<<endl;
    
    pagoEnvios+=pago;
    totalRecaudado+=pago;
    cantidadAtendia+=cantidadPedida;                            
}
void imprimeHora(ofstream &archivo, int hora){
    int hh, mm ,ss;
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
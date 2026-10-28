/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 13 de mayo de 2025, 10:36 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_CONT 4
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_PORC 15            
#define MAX_CAR_CUOT 20            
#define MAX_CAR_CANT 14
#define MAX_CAR_DIN 12
#define MAX_CAR_FECHA 10

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

void procesaArchivos(const char *nombreArchivoVendedores, 
        const char *nombreArchivoArticulos,
        const char *nombreArchivoVentas, 
        const char *nombreArchivoReporte){
    
    ifstream archivoVendedores(nombreArchivoVendedores, ios::in);
    if(not archivoVendedores.is_open()){
        cout<<"ERROR : No se pudo abrir "<<nombreArchivoVendedores;
        exit(1);
    }
    ifstream archivoArticulos(nombreArchivoArticulos, ios::in);
    if(not archivoArticulos.is_open()){
        cout<<"ERROR : No se pudo abrir "<<nombreArchivoArticulos;
        exit(1);
    }
    ifstream archivoVentas(nombreArchivoVentas, ios::in);
    if(not archivoVentas.is_open()){
        cout<<"ERROR : No se pudo abrir "<<nombreArchivoVentas;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR : No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    double ventasTotales=0, porcentajeComisionTotal=0, 
            montoMayorVenta, montoMenorVenta;
    
    int cantidadVendedoresCumplenCuotaMinima=0, 
            cantidadVendedoresNoCumplenCuotaMinima=0, 
            dniVendedorMayorVenta, dniVendedorMenorVenta;
    
    procesaDatos(archivoVendedores, archivoArticulos, 
            archivoVentas, archivoReporte, 
            ventasTotales, 
            cantidadVendedoresCumplenCuotaMinima, cantidadVendedoresNoCumplenCuotaMinima, 
            porcentajeComisionTotal, 
            dniVendedorMayorVenta, montoMayorVenta, 
            dniVendedorMenorVenta, montoMenorVenta);
    
//    imprimeResumen(archivoReporte, );
    
}
void procesaDatos(ifstream &archivoVendedores, ifstream &archivoArticulos, 
        ifstream &archivoVentas, ofstream &archivoReporte, 
        double &ventasTotales,
        int &cantidadVendedoresCuotaMinima, int &cantidadVendedoresNoCuotaMinima, 
        double &porcentajeComisionTotal, 
        int &dniVendedorMayorVenta, double &montoMayorVenta, 
        int &dniVendedorMenorVenta, double &montoMenorVenta){
    
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"LISTADO DE VENDEDORES"<<endl;
    
    int dniVendedor, cantidadVendedores = 0;
    double porcentajeComisionVendedor, cuotaMinimaVendedor;
    while(true){
        //11602775	HIJAR ARCA ADOLFO/	    13.84	    67000
        imprimeLinea(archivoReporte, '=');
        leeImprimeVendedor(archivoVendedores, archivoReporte, 
                dniVendedor, porcentajeComisionVendedor, cuotaMinimaVendedor, 
                cantidadVendedores);
        if(archivoVendedores.eof()) break;                
        
        procesaVentas(archivoVentas, archivoArticulos,
                archivoReporte, 
                ventasTotales,
                cantidadVendedoresCuotaMinima, cantidadVendedoresNoCuotaMinima,
                porcentajeComisionTotal,
                dniVendedorMayorVenta, montoMayorVenta,
                dniVendedorMenorVenta, montoMenorVenta, 
                dniVendedor, porcentajeComisionVendedor, cuotaMinimaVendedor);
    }
}
void leeImprimeVendedor(ifstream &archivoLectura, ofstream &archivoReporte, 
        int &dni, double &porcentaje, double &cuotaMinima, int &cantidad){
    
    archivoLectura>>dni;
    if(archivoLectura.eof()) return;
    cantidad++;
    
    archivoReporte<<left
            <<setw(MAX_CAR_CONT)<<"No. "
            <<setw(MAX_CAR_NOMBRE)<<"VENDEDOR"
            <<setw(MAX_CAR_PORC)<<"% VENTAS"
            <<setw(MAX_CAR_CUOT)<<"CUOTA MINIMA"
            <<endl;
    imprimeLinea(archivoReporte, '-');
    archivoReporte<<left
            <<setw(MAX_CAR_CONT)<<cantidad;
    imprimeNombreVendedor(archivoLectura, archivoReporte);
    
    archivoLectura>>porcentaje>>cuotaMinima;
    archivoReporte<<setw(MAX_CAR_PORC)<<porcentaje
            <<setw(MAX_CAR_CUOT)<<cuotaMinima
            <<endl;            
}
void imprimeNombreVendedor(ifstream &archivoLectura, ofstream &archivoReporte){
    char letra;
    int cantidad=0;
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == '/') break;
        cantidad++;
        archivoReporte<<letra;
    }
    archivoReporte<<setw(MAX_CAR_NOMBRE-cantidad)<<' ';
}

void procesaVentas(ifstream &archivoVentas, ifstream &archivoArticulos,
        ofstream &archivoReporte, 
        double &ventasTotales,
        int &cantidadVendedoresCuotaMinima, int &cantidadVendedoresNoCuotaMinima,
        double &porcentajeComisionTotal,
        int &dniVendedorMayorVenta, double &montoMayorVenta,
        int &dniVendedorMenorVenta, double &montoMenorVenta,
        int dniVendedor, double porcentajeComisionVendedor, double cuotaMinimaVendedor){
        
    
    archivoReporte<<setw(MAX_CAR_CONT)<<' '
            <<"ARTICULOS VENDIDOS"<<endl;
    
    archivoReporte<<setw(MAX_CAR_CONT)<<' '
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_NOMBRE)<<"ARTICULO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_DIN)<<"MONTO"
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<endl;
    imprimeLinea(archivoReporte, '-');
    
    double totalVentasVendedor=0;
    int cantidadArticulos=0;
    
    
    char cod1, cod2, cod3;
    int codNum, dniComprador, cantidadComprada, fecha;
    double precioArticulo;
    
    archivoVentas.clear();
    archivoVentas.seekg(0, ios::beg);
    while(true){
        //JCW-489    13245501     5    2/09/2023
        leeCodigoArticulo(archivoVentas, cod1, cod2, cod3, codNum);
        if(archivoVentas.eof()) break;
        
        archivoVentas>>dniComprador>>cantidadComprada;
        leeFecha(archivoVentas, fecha);
        
        if(dniComprador == dniVendedor){
            buscaArticulo(archivoArticulos, archivoReporte, 
                    cod1, cod2, cod3, codNum, precioArticulo, 
                    cantidadArticulos, cantidadComprada, fecha);            
            
        }
    }
    imprimeLinea(archivoReporte, '.');
}
void leeCodigoArticulo(ifstream &archivo, 
        char &cod1, char &cod2, char &cod3, int &codNum){
    char descC;
    archivo>>cod1;
    if(archivo.eof()) return;
    archivo>>cod2>>cod3>>descC>>codNum;    
}
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    
    archivo>>dd>>sep>>mm>>sep>>aa;
    
    fecha = dd +mm*100 +aa*10000;
}

void buscaArticulo(ifstream &archivoArticulos, ofstream &archivoReporte,
        char cod1, char cod2, char cod3, int codNum, double &precioArticulo, 
        int &cantidadArticulos, 
        int cantidadComprada, int fecha){
    char c1,c2,c3;
    int cNum;
    
    archivoArticulos.clear();
    archivoArticulos.seekg(0, ios::beg);
    
    while(true){
        leeCodigoArticulo(archivoArticulos, c1,c2,c3, cNum);
        if(archivoArticulos.eof()) break;
        
        if(c1 == cod1 and c2 == cod2 and c3 == cod3 and cNum == codNum){
            cantidadArticulos++;
            archivoReporte << setw(MAX_CAR_CONT) << ' '
                    << setw(MAX_CAR_CONT) <<cantidadArticulos
                    <<cod1<<cod2<<cod3<<'-'
                    <<right<<setw(3)<<setfill('0')<<codNum<<' '<<left<<setfill(' ');
            
            imprimeArticulo(archivoArticulos, archivoReporte);
            archivoArticulos>>precioArticulo;

            archivoReporte << setw(MAX_CAR_CANT) << cantidadComprada
                    << setw(MAX_CAR_DIN) << precioArticulo
                    << setw(MAX_CAR_DIN) << precioArticulo*cantidadComprada;
            imprimeFecha(archivoReporte, fecha);
            archivoReporte<<endl;
            break; // dejo de buscar porque ya encontre el articulo
        }
        else
            while(archivoArticulos.get()!='\n');
        
    }        
}
void imprimeArticulo(ifstream &archivoLectura, ofstream &archivoReporte){
    char letra;
    int cantidad=0;
    archivoLectura>>ws;
    archivoLectura.get();
    while(true){
        letra = archivoLectura.get();
        if(letra == '}') break;
        cantidad++;
        archivoReporte<<letra;
    }
    archivoReporte<<setw(MAX_CAR_NOMBRE-cantidad-8)<<' ';
}
void imprimeFecha(ofstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep = '/';
    
    aa= fecha /10000;
    fecha%=10000;
    mm=fecha/100;
    dd = fecha%10;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')<<setw(MAX_CAR_FECHA-10)<<' ';
}
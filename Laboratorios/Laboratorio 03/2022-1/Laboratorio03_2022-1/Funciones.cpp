/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 12 de mayo de 2025, 11:11 AM
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
#define MAX_CAR_TEL 14
#define MAX_CAR_DIN 14
#define MAX_CAR_CANT 12

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

//LECTURA
void leeClientes(const char *nombreArchivo, int &cantidad,
        int  *dnis, int *telefonos){
    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 71984468   [IPARRAGUIRRE VILLEGAS NICOLAS EDILBERTO]   935441620
        archivo>>dnis[cantidad];
        if(archivo.eof()) break;
        while(archivo.get()!=']');
        archivo>>telefonos[cantidad];
        
        cantidad++;
    }        
}
void leePedidos(const char *nombreArchivo, int &cantidadProductos,
        int *codigosProductos, double *preciosProductos,
        double *cantidadesProductos, double *totalesProductos,
        int cantidadClientes, int *dnisClientes, double *gastosClientes) {
    ifstream archivo(nombreArchivo, ios::in);
    if (not archivo.is_open()) {
        cout << "ERROR: No se pudo abrir " << nombreArchivo;
        exit(1);
    }
    
    int codigoProductoActual;
    double precioProductoActual, cantidadPedidaProductoActual;
    int dniCliente;
    while(true){
        archivo>>codigoProductoActual;
        if(archivo.eof()) break;
        archivo>>ws;
        archivo.get(); 
        while(archivo.get()!='*');
        archivo>>cantidadPedidaProductoActual>>precioProductoActual;
        archivo>>dniCliente;
        while(archivo.get()!='\n');
        
        int posProducto = buscaInt(codigosProductos, cantidadProductos, codigoProductoActual);
        if(posProducto == NO_ENCONTRADO){ //No lo encontramos y lo añadimos
            codigosProductos[cantidadProductos] = codigoProductoActual;
            preciosProductos[cantidadProductos] = precioProductoActual;
            
            //como lo añadimos al final, la posicion será la ultima
            posProducto = cantidadProductos;
            
            //añadimos en uno porque lo añadimos satisfactoriamente
            cantidadProductos++;
            
        }        
        cantidadesProductos[posProducto]+=cantidadPedidaProductoActual;
        totalesProductos[posProducto] += cantidadPedidaProductoActual*precioProductoActual;
        
        int posCliente = buscaInt(dnisClientes, cantidadClientes, dniCliente);
        if(posCliente != NO_ENCONTRADO){
            gastosClientes[posCliente] += cantidadPedidaProductoActual*precioProductoActual;
        }
            
    }
}

int buscaInt(int *arr, int cantidad, int elemento){
    for (int i = 0; i < cantidad; i++)
        if(elemento == arr[i])
            return i;
    return NO_ENCONTRADO;
    

}
//ORDENAMIENTO
void ordenaClientes(int cantidad,
        int *dnis, int *telefonos){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(dnis[i]>dnis[j]){
                cambiarInt(dnis[i], dnis[j]);
                cambiarInt(telefonos[i], telefonos[j]);
            }
        }

    }
}

void cambiarInt(int &dato1, int &dato2){
    int aux;
    aux = dato1;
    dato1 = dato2;
    dato2=aux;
}

void imprimeReporte(const char *nombreArchivo,
        int cantidadClientes, 
        int *dnisClientes, int *telefonosClientes, double *gastosClientes,
        int cantidadProductos, 
        int* codigosProductos, double *preciosProductos, double *cantidadesProductos, double *totalesProductos){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA COMERCIALIZADORA VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"REPORTE DE VENTAS"<<endl;

    imprimeEncabezadoProductos(archivo);
    for (int i = 0; i < cantidadProductos; i++) {
        archivo<<left<<setw(MAX_CAR_CONT)<<i+1
                <<left<<setw(MAX_CAR_COD)<<codigosProductos[i]
                <<right<<setw(MAX_CAR_DIN/2)<<preciosProductos[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<cantidadesProductos[i]<<left<<setw(MAX_CAR_CANT/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalesProductos[i]<<left<<setw(MAX_CAR_DIN/2)<< ' '
                <<endl; 
    }
    
    imprimeEncabezadoClientes(archivo);
    for (int i = 0; i < cantidadClientes; i++) {        
        archivo<<left
                <<setw(MAX_CAR_CONT)<<i+1
                <<left<<setw(MAX_CAR_COD)<<dnisClientes[i]
                <<setw(MAX_CAR_TEL)<<telefonosClientes[i]
                <<right<<setw(MAX_CAR_DIN/2)<<gastosClientes[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
                <<endl;        
    }
}
void imprimeEncabezadoProductos(ofstream &archivo){
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"TOTAL"
            <<endl;        
    imprimeLinea(archivo, '=');
}
void imprimeEncabezadoClientes(ofstream &archivo){
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_TEL)<<"TELEFONO"
            <<setw(MAX_CAR_DIN)<<"TOTAL GASTADO"
            <<endl;        
    imprimeLinea(archivo, '=');
}



        
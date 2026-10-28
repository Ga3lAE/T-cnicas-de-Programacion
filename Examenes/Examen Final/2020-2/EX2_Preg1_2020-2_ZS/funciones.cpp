

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:23 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX_LINE 150
#define NO_ENCONTRADO -1
#include "StructFarmacias.h"
#include "StructProductos.h"
#include "StructProductosNoProcesados.h"
#include "funciones.h"



void crearFarmaciasBin(const char *nombArchCsv,const char *nombArchBin){
    
    ifstream archFarmacias(nombArchCsv,ios::in);
    if(not archFarmacias.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }  
    ofstream archFarmaciasBin(nombArchBin,ios::out | ios::binary);
    if(not archFarmaciasBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    int codigo;
    char distrito[30];
    struct Farmacia farmacia;
    while(true){
        archFarmacias>>codigo;
        if(archFarmacias.eof())break;
        archFarmacias.get();
        archFarmacias.getline(distrito,30);
        
        farmacia.codigo = codigo;
        strcpy(farmacia.distrito,distrito);
        farmacia.cantidadProductos=0;
        
        archFarmaciasBin.write(reinterpret_cast<const char*>(&farmacia),
                sizeof(struct Farmacia));
    }
}

void mostrarFarmaciasBin(const char *nombArchBin,const char *nombArchTxt){
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    ifstream archFarmaciaBin(nombArchBin,ios::in | ios::binary);
    if(not archFarmaciaBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    struct Farmacia farmacia;
    while(true){
        archFarmaciaBin.read(reinterpret_cast<char *>(&farmacia),
                sizeof(struct Farmacia));
        if(archFarmaciaBin.eof())break;
        archReporte<<farmacia.codigo<<' '<<farmacia.distrito<<' '<<
                farmacia.cantidadProductos<<endl;
    }
}

void actualizarFarmaciasBin(const char *nombArchBin,const char *nombArchProdBin,
        const char *nombArchCsv){    
    ifstream archVentas(nombArchCsv,ios::in);
    if(not archVentas.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    ofstream archProdBin(nombArchProdBin,ios::out | ios::binary);
    if(not archProdBin.is_open()){
        cout<<"ERROR al abrir l archivo de "<<nombArchProdBin<<endl;
        exit(1);
    }
    fstream archFarmaciasBin(nombArchBin,ios::in | ios::out | ios::binary);
    if(not archFarmaciasBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }  
    int codigoFarmacia,cantidadVendida,tamReg,tamArch,numReg;  
    double precio;
    char codigoProducto[8],nombreProducto[50];
    struct Farmacia farmacia;
    struct ProductoNoProcesado producto;
    tamReg = sizeof(struct Farmacia);
    datosArchivo(archFarmaciasBin,tamReg,tamArch,numReg);
    while(true){
        archVentas>>codigoFarmacia;
        if(archVentas.eof())break;
        archVentas.get();
        archVentas.getline(codigoProducto,8,',');
        archVentas.getline(nombreProducto,50,',');
        archVentas>>cantidadVendida;
        archVentas.get();
        archVentas>>precio;
        asignaModificaArchivoBin(producto,farmacia,codigoFarmacia,codigoProducto,
                nombreProducto,cantidadVendida,precio,tamReg,numReg,
                archFarmaciasBin,archProdBin);
    }
}

void asignaModificaArchivoBin(struct ProductoNoProcesado &producto,
        struct Farmacia &farmacia,int codigoFarmacia,
        char *codigoProducto,char *nombreProducto,int cantidadVendida,
        double precio,int tamReg,int numReg,fstream &archFarmaciasBin,
        ofstream &archProdBin){
    int posFarmacia;
    
    posFarmacia = buscarFarmmacia(archFarmaciasBin,codigoFarmacia,numReg);
    if(posFarmacia!=NO_ENCONTRADO){
        archFarmaciasBin.seekg(posFarmacia*tamReg,ios::beg);
        archFarmaciasBin.read(reinterpret_cast<char *>(&farmacia),tamReg);
        registrarProductos(producto,farmacia,codigoFarmacia,codigoProducto,
                nombreProducto,cantidadVendida,precio,archProdBin);
        archFarmaciasBin.seekg(posFarmacia*tamReg,ios::beg);
        archFarmaciasBin.write(reinterpret_cast<const char *>(&farmacia),tamReg);
        archFarmaciasBin.flush();  
    }
}

void registrarProductos(struct ProductoNoProcesado &producto,
        struct Farmacia &farmacia,int codigoFarmacia,
        char *codigoProducto,char *nombreProducto,int cantidadVendida,
        double precio,ofstream &archProdBin){
    int posProducto;
    posProducto = buscarProducto(farmacia.productosVendidos,codigoProducto,
            farmacia.cantidadProductos);       
    if(posProducto!=NO_ENCONTRADO){/*Si es repetido*/
        farmacia.productosVendidos[posProducto].
                cantidadVendida+=cantidadVendida;
        farmacia.productosVendidos[posProducto].recaudacion=
                farmacia.productosVendidos[posProducto].
                cantidadVendida*precio;
    }else {        
        if(farmacia.cantidadProductos<10){/*Si es nuevo Producto*/
            strcpy(farmacia.productosVendidos[farmacia.cantidadProductos].nombre,
                    nombreProducto);
            strcpy(farmacia.productosVendidos[farmacia.cantidadProductos].codigo,
                    codigoProducto);
            farmacia.productosVendidos[farmacia.cantidadProductos].
                    cantidadVendida=cantidadVendida;
            farmacia.productosVendidos[farmacia.cantidadProductos].recaudacion=
                    cantidadVendida*precio;
            farmacia.cantidadProductos++;
        }else{
            producto.codigoFarmacia = codigoFarmacia;
            strcpy(producto.codigoProducto,codigoProducto);
            strcpy(producto.nombreProducto,nombreProducto);
            producto.cantidadVendida = cantidadVendida;
            producto.precio = precio;
            archProdBin.write(reinterpret_cast<const char *>(&producto),
                    sizeof(struct ProductoNoProcesado));
        }
    }
}

void emiteReporte(const char *nombArchBin,const char *nombArchProdBin,
        const char *nombArchTxt){    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }    
    ifstream archFarmaciaBin(nombArchBin,ios::in | ios::binary);
    if(not archFarmaciaBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    ifstream archProdNoProcBin(nombArchProdBin,ios::in | ios::binary);
    if(not archProdNoProcBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchProdBin<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimeFarmaciasYproductos(archFarmaciaBin,archReporte);
    imprimeProductosNoProcesados(archProdNoProcBin,archReporte);
}

void imprimeProductosNoProcesados(ifstream &archProdNoProcBin,
        ofstream &archReporte){
    struct ProductoNoProcesado producto;
    archReporte<<endl<<"PRODUCTOS NO PROCESADOS"<<endl;
    imprimeLinea('-',MAX_LINE,archReporte);
    archReporte<<"FARMACIA"<<setw(10)<<' '<<"CODIGO"<<setw(10)<<' '
            <<"DESCRIPCION"<<setw(40)<<' '<<"CANTIDAD"<<setw(10)<<' '
            <<"PRECIO"<<endl;
    while(true){
        archProdNoProcBin.read(reinterpret_cast<char *>(&producto),
                sizeof(struct ProductoNoProcesado));
        if(archProdNoProcBin.eof())break;
        archReporte<<producto.codigoFarmacia<<setw(12)<<' '
                <<producto.codigoProducto<<setw(9)<<' '<<left<<setw(40)
                <<producto.nombreProducto<<right<<setw(16)
                <<producto.cantidadVendida<<setw(19)<<producto.precio<<endl;
    }
}

void imprimeFarmaciasYproductos(ifstream &archFarmaciaBin,ofstream &archReporte){
    struct Farmacia farmacia;
    archReporte<<setw(50)<<' '<<"CADENA DE FARMACIAS TP"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"LISTADO DE FARMACIAS"<<endl;
    while(true){
        archFarmaciaBin.read(reinterpret_cast<char *>(&farmacia),
                sizeof(struct Farmacia));
        if(archFarmaciaBin.eof())break;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"CODIGO: "<<farmacia.codigo<<setw(10)<<' '<<"DISTRITO: "
                <<farmacia.distrito<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"CODIGO"<<setw(10)<<' '<<"DESCRIPCION"<<setw(40)<<' '
                <<"CANTIDAD"<<setw(10)<<' '<<"MONTO TOTAL"<<endl;
        for(int i=0;i<farmacia.cantidadProductos;i++){
            archReporte<<farmacia.productosVendidos[i].codigo<<setw(9)<<' '
                    <<left<<setw(50)<<farmacia.productosVendidos[i].nombre
                    <<right<<setw(6)<<farmacia.productosVendidos[i].cantidadVendida
                    <<setw(22)<<farmacia.productosVendidos[i].recaudacion<<endl;
        }
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

int buscarProducto(struct Producto *producto, char *codigo, int numDatos){
    for(int i=0;i<numDatos;i++)
        if(strcmp(producto[i].codigo,codigo)==0) return i;
    return NO_ENCONTRADO;
}

int buscarFarmmacia(fstream &archFarmaciasBin,int codigoFarmacia,int numReg){
    struct Farmacia farmacia;
    archFarmaciasBin.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        archFarmaciasBin.read(reinterpret_cast<char *>(&farmacia),
                sizeof(struct Farmacia));
        if(farmacia.codigo == codigoFarmacia)return i;
    }
    
    return NO_ENCONTRADO;
}

void imprimeLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

void datosArchivo(fstream &archBin,int tamReg,int &tamArch,int &numReg){
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}
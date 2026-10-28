

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 23 de junio de 2023, 01:14 AM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX_LINE 150
#define NO_ENCONTRADO -1
#include "ProductoSolicitado.h"
#include "StockProduco.h"
#include "funciones.h"
#include "Pedidos.h"



void crearStocksProdBin(const char *nombArchCsv,const char *nombArchBin){
    
    ifstream archStock(nombArchCsv,ios::in);
    if(not archStock.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archStockBin(nombArchBin,ios::out | ios::binary);
    if(not archStockBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    int stock;
    char codProd[7],descripcion[60];
    double precio;
    struct StockProd stockProd;
    
    while(true){
        archStock.getline(codProd,7,',');
        if(archStock.eof())break;
        archStock.getline(descripcion,60,',');
        archStock>>stock;
        archStock.get();
        archStock>>precio;
        archStock.get();
        
        strcpy(stockProd.codigo,codProd);
        strcpy(stockProd.descrpcion,descripcion);
        stockProd.stock = stock;
        stockProd.precio = precio;
        
        archStockBin.write(reinterpret_cast<const char *>(&stockProd),sizeof(stockProd));
    }
}

void mostrarStocksProdBin(const char *nombArchBin,const char *nombArchTxt){
    ifstream archBin(nombArchBin,ios::in| ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    struct StockProd stockProd;
    while(true){
        archBin.read(reinterpret_cast<char *>(&stockProd),sizeof(StockProd));
        if(archBin.eof())break;
        archReporte<<stockProd.codigo<<' '<<stockProd.descrpcion<<' '
                <<stockProd.stock<<' '<<stockProd.precio<<endl;
    }
}

void crearPedidosBin(const char *nombArchTxt, const char *nombArchBin){   
    ofstream archPedidosBin(nombArchBin,ios::out | ios::binary);
    if(not archPedidosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }    
    ifstream archPedidos(nombArchTxt,ios::in);
    if(not archPedidos.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }   
    int dia,mes,anio,hora,min,seg,codPedido,dni,fecha,tiempo;
    char c;    
    struct Pedido pedido;
    while(true){
        archPedidos>>dia;
        if(archPedidos.eof())break;
        archPedidos>>c>>mes>>c>>anio;
        archPedidos>>hora>>c>>min>>c>>seg;
        archPedidos>>codPedido;
        archPedidos>>dni;
        fecha = anio*10000+mes*100+dia;
        tiempo = hora*10000 + min*100 + seg;
        pedido.numero = codPedido;
        pedido.fecha = fecha;
        pedido.hora = tiempo;
        pedido.cliente = dni;
        pedido.cantProdPed=0;
        
        archPedidosBin.write(reinterpret_cast<const char*>(&pedido),sizeof(Pedido));
    }
}

void mostrarPedidosBin(const char *nombArchBin, const char *nombArchTxt){
    
    ifstream archPedidoBin(nombArchBin,ios::in | ios::binary);
    if(not archPedidoBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    struct Pedido pedido;
    while(true){
        archPedidoBin.read(reinterpret_cast<char *>(&pedido),sizeof(Pedido));
        if(archPedidoBin.eof())break;
        archReporte<<pedido.fecha<<' '<<pedido.hora<<' '<<pedido.numero<<' '
                <<pedido.cliente<<' '<<pedido.cantProdPed<<endl;
    }
}

void actualizarPedidos(const char *nomArchStockBin, const char *nomArchPedidosBin,
        const char *nombArchTxt){
    
    fstream archStock(nomArchStockBin,ios::in | ios::out | ios::binary);
    if(not archStock.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nomArchStockBin<<endl;
        exit(1);
    }
    
    fstream archPedidos(nomArchPedidosBin,ios::in | ios::out | ios::binary);
    if(not archPedidos.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nomArchPedidosBin<<endl;
        exit(1);
    }
    
    ifstream archDetalles(nombArchTxt,ios::in);
    if(not archDetalles.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    struct StockProd producto;
    int tamRegProd = sizeof(struct StockProd);
    int tamArchProd,numRegProd;
    
    struct Pedido pedido;
    int tamRegPedido = sizeof(struct Pedido);
    int tamArchPedido,numRegPed;

    datosArchivo(archStock,tamRegProd,tamArchProd,numRegProd);
    datosArchivo(archPedidos,tamRegPedido,tamArchPedido,numRegPed);
    
    modificarArchivos(producto,tamRegProd,tamArchProd,numRegProd,pedido,
            tamRegPedido,tamArchPedido,numRegPed,archStock,archPedidos,archDetalles);
    
}

void modificarArchivos(struct StockProd &producto, int tamRegProd,int tamArchProd,
        int numRegProd,struct Pedido &pedido,int tamRegPedido,int tamArchPedido,
        int numRegPed,fstream &archStock, fstream &archPedidos, ifstream &archDetalles){  
    int posProducto,posPedido;
    int numPedido,cantidadSolicitada;
    char codProd[7];
    while(true){
        archDetalles>>numPedido;
        if(archDetalles.eof())break;
        archDetalles>>codProd;
        archDetalles>>cantidadSolicitada;
        posPedido = buscarPedido(archPedidos,numPedido,numRegPed);
        if(posPedido!=NO_ENCONTRADO){
            archPedidos.seekg(posPedido*tamRegPedido,ios::beg);
            archPedidos.read(reinterpret_cast<char *>(&pedido),tamRegPedido);           
            posProducto = buscarProducto(archStock,codProd,numRegProd);
            if(posProducto!=NO_ENCONTRADO){
                archStock.seekg(posProducto*tamRegProd,ios::beg);/*Posicionar el registro*/
                archStock.read(reinterpret_cast<char *>(&producto),tamRegProd);/*Lee el registro*/
                if(producto.stock>0){
                    asignarDatos(producto,pedido,cantidadSolicitada,posProducto,
                            posPedido,tamRegProd,tamRegPedido,archStock,archPedidos);
                }
            }           
        }
    }
}

void asignarDatos(struct StockProd &producto,struct Pedido &pedido,
        int cantidadSolicitada,int posProducto,int posPedido,int tamRegProd,
        int tamRegPedido,fstream &archStock,fstream &archPedidos){
    if(producto.stock>=cantidadSolicitada){
        pedido.productosPedidos[pedido.cantProdPed].cantidad=cantidadSolicitada;
        strcpy(pedido.productosPedidos[pedido.cantProdPed].codigo,
                producto.codigo);
        strcpy(pedido.productosPedidos[pedido.cantProdPed].descrpcion,
                producto.descrpcion);
        pedido.productosPedidos[pedido.cantProdPed].precioUnitario=producto.precio;
        pedido.productosPedidos[pedido.cantProdPed].subTotal=cantidadSolicitada*producto.precio;
        producto.stock-=cantidadSolicitada;
        pedido.cantProdPed++;                        
    }else if(producto.stock<cantidadSolicitada){
        pedido.productosPedidos[pedido.cantProdPed].cantidad=producto.stock;
        strcpy(pedido.productosPedidos[pedido.cantProdPed].codigo,
                producto.codigo);
        strcpy(pedido.productosPedidos[pedido.cantProdPed].descrpcion,
                producto.descrpcion);
        pedido.productosPedidos[pedido.cantProdPed].precioUnitario=producto.precio;
        pedido.productosPedidos[pedido.cantProdPed].subTotal=cantidadSolicitada*producto.precio;
        producto.stock-=producto.stock;
        pedido.cantProdPed++;
    }
    /*Reposicionamos para realizar la escritura o modificacion*/
    archPedidos.seekg(posPedido*tamRegPedido,ios::beg);
    archPedidos.write(reinterpret_cast<const char *>(&pedido),tamRegPedido);
    archStock.seekg(posProducto*tamRegProd,ios::beg);
    archStock.write(reinterpret_cast<const char *>(&producto),tamRegProd);
    archPedidos.flush();
    archStock.flush();
}

void emiteReporte(const char *nombArchBin,const char *nombArchTxt){
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    ifstream archPedidosBin(nombArchBin,ios::in | ios::binary);
    if(not archPedidosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    struct Pedido pedido;
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimLinea('=',MAX_LINE,archReporte);
    archReporte<<setw(50)<<' '<<"TIENDA VIRTUAL LA MAGNIFICA"<<endl;
    archReporte<<setw(53)<<' '<<"ATENCION DE PEDIDOS"<<endl;
    imprimLinea('=',MAX_LINE,archReporte);
    while(true){
        archPedidosBin.read(reinterpret_cast<char *>(&pedido),sizeof(struct Pedido));
        if(archPedidosBin.eof())break;
        archReporte<<"Pedido No. "<<pedido.numero<<setw(10)<<' '<<"Fecha: "
                <<pedido.fecha<<setw(10)<<' '<<"Hora: "<<pedido.hora<<endl;
        archReporte<<"Cliente: "<<endl;
        archReporte<<"DNI: "<<pedido.cliente<<endl;
        archReporte<<"Productos: "<<endl;
        archReporte<<"Codigo"<<setw(10)<<' '<<"Descripcion"<<setw(10)<<' '
                <<"Cantidad"<<setw(10)<<' '<<"Precio Unitario"<<setw(10)<<' '
                <<"Subtotal"<<endl;
        for(int i=0;i<pedido.cantProdPed;i++){
            archReporte<<pedido.productosPedidos[i].codigo<<setw(10)<<' '
                    <<left<<setw(50)<<pedido.productosPedidos[i].descrpcion
                    <<right<<setw(10)<<' '<<pedido.productosPedidos[i].cantidad
                    <<setw(10)<<' '<<pedido.productosPedidos[i].precioUnitario
                    <<setw(10)<<' '<<pedido.productosPedidos[i].subTotal<<endl;
        }
        imprimLinea('=',MAX_LINE,archReporte);
    }
}

void imprimLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

int buscarPedido(fstream &archPedidos,int numPedido, int numReg){
    
    struct Pedido pedido;
    archPedidos.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        archPedidos.read(reinterpret_cast<char*>(&pedido),sizeof(Pedido));
        
        if(pedido.numero ==numPedido)return i;
    }
    
    return NO_ENCONTRADO;
}

int buscarProducto(fstream &archStock,char *codProd,int numReg){
    
    struct StockProd producto;
    archStock.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        archStock.read(reinterpret_cast<char*>(&producto),sizeof(StockProd));
        if(strcmp(producto.codigo,codProd)==0)return i;
    }
    return NO_ENCONTRADO;
}

void datosArchivo(fstream &archBin, int tamReg,int &tamArch, int &numReg){
    archBin.seekg(0,ios::end);
    tamArch=archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}
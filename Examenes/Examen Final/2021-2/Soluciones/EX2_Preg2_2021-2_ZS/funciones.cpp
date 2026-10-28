

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 15 de junio de 2023, 12:38 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ratio>

using namespace std;


#include "NoEntregado.h"
#include "Entregado.h"
#include "stPedidos.h"
#include "StockProd.h"
#include "funciones.h"


void leerStockProductos(struct StockProd *productos,int &numProductos){
    
    
    ifstream archProductos("StockDeProductos.csv",ios::in);
    if(not archProductos.is_open()){
        cout<<"ERROR al abrir el archivo de StockDeProductos"<<endl;
        exit(1);
    }
    char *ptr_codProd,*ptr_nombre;
    int stock;
    double precio;
    numProductos=0;
    while(true){
        ptr_codProd=leerCadenaExacta(archProductos);
        if(archProductos.eof())break;
        ptr_nombre=leerCadenaExacta(archProductos);
        archProductos>>stock;
        archProductos.get();
        archProductos>>precio;
        archProductos.get();
        
        productos[numProductos].codigo=ptr_codProd;
        productos[numProductos].descripcion=ptr_nombre;
        productos[numProductos].stock=stock;
        productos[numProductos].precio=precio;
        numProductos++;
    }
   
}

void emiteProductos(struct StockProd *productos,int numProductos){
    
    ofstream archReporte("Datos Productos.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo Productos.txt"<<endl;
        exit(1);
    }
    
     for(int i=0;i<numProductos;i++)
        archReporte<<productos[i].codigo<<' '<<productos[i].descripcion<<' '
                <<productos[i].stock<<' '<<productos[i].precio<<endl;
}

void leerPedidos(struct stPedidos *pedidos,int &numPedidos){
    
    ifstream archPedidos("Pedidos.txt",ios::in);
    if(not archPedidos.is_open()){
        cout<<"ERROR al abrir el archivo de Pedidos"<<endl;
        exit(1);
    }
    
    int dia,mes,anio,hora,min,segundo,cod_pedido,dni,fechaAux,horaAux;
    char c;
    
    numPedidos=0;
    while(true){
        archPedidos>>dia;
        if(archPedidos.eof())break;
        archPedidos>>c>>mes>>c>>anio;
        archPedidos>>hora>>c>>min>>c>>segundo;
        archPedidos>>cod_pedido>>dni;
        fechaAux = anio*10000+mes*100+dia;
        horaAux = hora*10000+min*100+segundo;
        
        pedidos[numPedidos].numero = cod_pedido;
        pedidos[numPedidos].fecha = fechaAux;
        pedidos[numPedidos].hora = horaAux;
        pedidos[numPedidos].cliente =dni;
        pedidos[numPedidos].productosEntregados = new struct Entregado[20];
        pedidos[numPedidos].cantProdEnt =0;
        pedidos[numPedidos].productosNoEntregados = new struct NoEntregado[20];
        pedidos[numPedidos].cantProdNoEnt =0;
        numPedidos++;
    }
    
}

void emitePedidos(struct stPedidos *pedidos,int numPedidos){
    
    ofstream archReporte("Datos Pedidos.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de Datos Pedidos"<<endl;
        exit(1);
    }
    for(int i=0;i<numPedidos;i++)
        archReporte<<pedidos[i].numero<<' '<<pedidos[i].fecha<<' '
                <<pedidos[i].hora<<' '<<pedidos[i].cliente<<endl;
}

void leerDetallesPedidos(struct StockProd *productos,int numProductos,
        struct stPedidos *pedidos,int numPedidos){
    
    ifstream archDetallesPedidos("DetalleDeLosPedidos.txt",ios::in);
    if(not archDetallesPedidos.is_open()){
        cout<<"ERROR al abrir el archivo de DetalleDeLosPedidos"<<endl;
        exit(1);
    }
    int codPedido_evaluar,cantidad_solicitada,posProducto,posPedido;
    char codProducto[7];
    
    while(true){
        archDetallesPedidos>>codPedido_evaluar;
        if(archDetallesPedidos.eof())break;
        archDetallesPedidos>>codProducto;
        archDetallesPedidos>>cantidad_solicitada;
        posPedido = buscarPedido(pedidos,codPedido_evaluar,numPedidos);
        posProducto = buscarProducto(productos,codProducto,numProductos);
        if(posPedido!=-1){
            if(posProducto!=-1){
                if(productos[posProducto].stock>cantidad_solicitada){
                    productos[posProducto].stock-=cantidad_solicitada;
                    asignarProductosEntregados(pedidos[posPedido],
                            productos[posProducto],cantidad_solicitada);
                }else{
                    asignarProductosNoEntregados(pedidos[posPedido],
                            productos[posProducto],productos[posProducto].stock);             
                }
            }
        }       
    }   
}

void asignarProductosNoEntregados(struct stPedidos &pedidos,
        struct StockProd &productos,int cantidad){
    pedidos.productosNoEntregados[pedidos.cantProdNoEnt].codigo=
            productos.codigo;
    pedidos.productosNoEntregados[pedidos.cantProdNoEnt].descripcion=
            productos.descripcion;
    pedidos.productosNoEntregados[pedidos.cantProdNoEnt].cantNoEntregada=
            cantidad;
    pedidos.cantProdNoEnt++;
}

void asignarProductosEntregados(struct stPedidos &pedidos,
        struct StockProd &productos,int cantidad_solicitada){
    
    pedidos.productosEntregados[pedidos.cantProdEnt].codigo=productos.codigo;
    pedidos.productosEntregados[pedidos.cantProdEnt].descripcion=
            productos.descripcion;
    pedidos.productosEntregados[pedidos.cantProdEnt].precioUnitario=
            productos.precio;
    pedidos.productosEntregados[pedidos.cantProdEnt].subtotal=
            productos.precio*cantidad_solicitada;
    pedidos.productosEntregados[pedidos.cantProdEnt].cantEntregada = 
            cantidad_solicitada;
    pedidos.cantProdEnt++;
}

void emitirReporte(struct StockProd *productos,int numProductos,
        struct stPedidos *pedidos,int numPedidos){
    ofstream archReporte("ReporteDePedidos.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ReporteDePedidos"<<endl;
        exit(1);
    }
    int dia,mes,anio,hora,min,seg;
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimeLinea('=',150,archReporte);
    archReporte<<setw(50)<<' '<<"TIENDA VIRTUAL LA MAGNIFICA"<<endl;
    archReporte<<setw(53)<<' '<<"ATENCION DE PEDIDOS"<<endl;
    imprimeLinea('=',150,archReporte);
    for(int i=0;i<numPedidos;i++){
        archReporte<<"Pedido No. "<<pedidos[i].numero<<setw(10)<<' '<<"Fecha: ";
        separaFecha(dia,mes,anio,pedidos[i].fecha);
        separaHora(hora,min,seg,pedidos[i].hora);
        archReporte<<setfill('0')<<setw(2)<<dia<<'/'<<setw(2)<<mes<<'/'<<anio
                <<setfill(' ')<<setw(5)<<' '<<"Hora: "<<setfill('0')
                <<setw(2)<<hora<<':'<<setw(2)<<min<<':'<<setw(2)<<seg
                <<setfill(' ')<<endl;
        archReporte<<"Cliente:"<<endl;
        archReporte<<"DNI: "<<pedidos[i].cliente<<endl;
        imprimeProductosEntregados(pedidos[i],archReporte);
        imprimeProductosNoEntregados(pedidos[i],archReporte);
        imprimeLinea('=',150,archReporte);
    }
}

void imprimeProductosNoEntregados(struct stPedidos &pedidos,ofstream &archReporte){
    archReporte<<"Productos no entregados:"<<endl;
    if(pedidos.cantProdNoEnt>0){
        archReporte<<"Codigo"<<setw(10)<<' '<<"Descripcion"<<setw(40)<<' '
                    <<"Cantidad"<<endl;
        for(int j=0;j<pedidos.cantProdNoEnt;j++){
            archReporte<<left<<setw(6)<<pedidos.productosNoEntregados[j].codigo
                    <<setw(10)<<' '<<setw(55)
                    <<pedidos.productosNoEntregados[j].descripcion<<right<<setw(2)
                    <<pedidos.productosNoEntregados[j].cantNoEntregada<<endl;
        }
    }else archReporte<<"No hay productos que no han sido entregados"<<endl;
}

void imprimeProductosEntregados(struct stPedidos &pedidos,ofstream &archReporte){
    archReporte<<"Productos Entregados:"<<endl;
    if(pedidos.cantProdEnt>0){
        archReporte<<"Codigo"<<setw(10)<<' '<<"Descripcion"<<setw(40)<<' '
            <<"Cantidad"<<setw(10)<<' '<<"Precio Unitario"
            <<setw(10)<<' '<<"Subtotal"<<endl;
        for(int k=0;k<pedidos.cantProdEnt;k++){
            archReporte<<left<<setw(6)<<pedidos.productosEntregados[k].codigo
                    <<setw(10)<<' '<<setw(55)
                    <<pedidos.productosEntregados[k].descripcion<<right<<setw(2)
                    <<pedidos.productosEntregados[k].cantEntregada
                    <<setw(22)<<pedidos.productosEntregados[k].precioUnitario
                    <<setw(23)<<pedidos.productosEntregados[k].subtotal<<endl;
        }
    }else archReporte<<"Ningun producto fue entregado"<<endl;
}

void separaFecha(int &dia,int &mes,int &anio,int fecha){
    anio = fecha/10000;
    mes = (fecha%10000)/100;
    dia = (fecha%10000)%100;
}

void separaHora(int &hora, int &min, int &seg,int horaAux){
    hora = horaAux/10000;
    min = (horaAux%10000)/100;
    seg = (horaAux%10000)%100;
}

void imprimeLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

int buscarPedido(struct stPedidos *pedidos,int codPedido_evaluar,int numPedidos){
    for(int i=0;i<numPedidos;i++)
        if(pedidos[i].numero==codPedido_evaluar)return i;
    return -1;
}

int buscarProducto(struct StockProd *productos,char *codProducto,int numDatos){
    for(int i=0;i<numDatos;i++)
        if(strcmp(productos[i].codigo,codProducto)==0)return i;
    return -1;
}

char *leerCadenaExacta(ifstream &arch){
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    longitud = strlen(buffer);
    
    cadena = new char[longitud+1];
    
    strcpy(cadena,buffer);
    
    return cadena;
}
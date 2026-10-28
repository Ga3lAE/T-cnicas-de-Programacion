

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 30 de junio de 2023, 09:07 AM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <set>


using namespace std;

#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "StructProductoPedido.h"
#include "StructPedido.h"
#include "StructDireccion.h"
#include "funciones.h"

void leerDirecciones(struct Direccion *direcciones,int &numDirecciones){
    
    ifstream archDirecciones("direcciones.csv",ios::in);
    if(not archDirecciones.is_open()){
        cout<<"ERROR al abrir el archivo de direcciones"<<endl;
        exit(1);
    }
    
    char *ptr_codUsuario,*ptr_direccion,*ptr_distrito;
    numDirecciones=0;
    while(true){
        ptr_codUsuario = leerCadenaExacta(archDirecciones);
        if(archDirecciones.eof())break;
        ptr_direccion = leerCadenaExacta(archDirecciones);
        ptr_distrito = leerCadenaExacta(archDirecciones);
        while(archDirecciones.get()!='\n');
        
        direcciones[numDirecciones].codigoUsuario = ptr_codUsuario;
        direcciones[numDirecciones].direccion = ptr_direccion;
        direcciones[numDirecciones].distrito = ptr_distrito;
        
        numDirecciones++;
    }
}

void leerPedidos(struct Pedido *pedidos,int &numPedidos){
    
    ifstream archPedidos("pedidos.csv",ios::in);
    if(not archPedidos.is_open()){
        cout<<"ERROR al abrir el archivo de pedidos"<<endl;
        exit(1);
    }
    
    int codigo_pedido,posPedido;
    numPedidos=0;
    while(true){
        archPedidos>>codigo_pedido;
        if(archPedidos.eof())break;
        posPedido=buscarPedido(pedidos,codigo_pedido,numPedidos);
        archPedidos.get();
        if(posPedido==NO_ENCONTRADO){ /*Registra producto nuevo*/
            pedidos[numPedidos].montoTotal=0;
            pedidos[numPedidos].codigo = codigo_pedido;
            pedidos[numPedidos].cantidadProductos =0;
            pedidos[numPedidos].productos = new struct ProductoPedido[10];
            registrarNuevoPedido(pedidos[numPedidos],archPedidos);
            numPedidos++;
        }else if(posPedido!=NO_ENCONTRADO){ /*Acumular pedido ya registrado*/
            acumulaPedidoEncontrado(pedidos[posPedido],archPedidos);
        }
        
    }
}

void acumulaPedidoEncontrado(struct Pedido &pedido,ifstream &archPedidos){
    int cantidad;
    double precio;
    char *ptr_nombreProducto;
    
    while(true){
        ptr_nombreProducto = leerCadenaExacta(archPedidos);
        archPedidos>>cantidad;
        archPedidos.get();
        archPedidos>>precio;
        pedido.productos[pedido.cantidadProductos].cantidad=cantidad;
        pedido.productos[pedido.cantidadProductos].precioUnitario=precio;
        pedido.productos[pedido.cantidadProductos].nombre = ptr_nombreProducto;
        
        pedido.montoTotal += pedido.productos[pedido.cantidadProductos].cantidad*
                pedido.productos[pedido.cantidadProductos].precioUnitario;
        pedido.cantidadProductos++;
        
        if(archPedidos.get()=='\n')break;
    }
    
}

void registrarNuevoPedido(struct Pedido &pedido,ifstream &archPedidos){
    
    int cantidad;
    double precio;
    char *ptr_nombreProducto;
    
    while(true){
        ptr_nombreProducto = leerCadenaExacta(archPedidos);
        archPedidos>>cantidad;
        archPedidos.get();
        archPedidos>>precio;
        pedido.productos[pedido.cantidadProductos].cantidad = cantidad;
        pedido.productos[pedido.cantidadProductos].precioUnitario=precio;
        pedido.productos[pedido.cantidadProductos].nombre = ptr_nombreProducto;
        
        pedido.montoTotal +=pedido.productos[pedido.cantidadProductos].cantidad*
                pedido.productos[pedido.cantidadProductos].precioUnitario;
        pedido.cantidadProductos++;
        if(archPedidos.get()=='\n')break;
    }
    
}

void completarPedidos(struct Direccion *direcciones,int numDirecciones,
        struct Pedido *pedidos,int numPedidos){    
    ifstream archRappi("rappi.csv",ios::in);
    if(not archRappi.is_open()){
        cout<<"ERROR al abrir el archivo rappi "<<endl;
        exit(1);
    }
    int tiempo,hora,min,codPedido,posDireccion,posPedido;
    char *ptr_nombreRappi,*ptr_codUsuario,c;
    
    while(true){
        archRappi>>hora;
        if(archRappi.eof())break;
        archRappi>>c>>min>>c;
        tiempo = hora*100+min;
        ptr_nombreRappi = leerCadenaExacta(archRappi);
        ptr_codUsuario = leerCadenaExacta(archRappi);
        archRappi>>codPedido;
        posDireccion = buscarDireccion(direcciones,ptr_codUsuario,numDirecciones);
        if(posDireccion!=NO_ENCONTRADO){
            posPedido = buscarPedido(pedidos,codPedido,numPedidos);
            if(posPedido!=NO_ENCONTRADO){
                pedidos[posPedido].hora = tiempo;
                pedidos[posPedido].codigoUsuario = ptr_codUsuario;
                pedidos[posPedido].direccion = direcciones[posDireccion].direccion;
                pedidos[posPedido].distrito=direcciones[posDireccion].distrito;
                pedidos[posPedido].repartidorRappi = ptr_nombreRappi;
            }
        }else while(archRappi.get()!='\n');
    }
}

void emiteReporte(struct Direccion *direcciones,int numDirecciones,
        struct Pedido *pedidos,int numPedidos){
    
    ofstream archReporte("ReportePedidos.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ReportePedidos"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<"tp_Rappi"<<endl;
    archReporte<<"REPORTE DE PEDIDOS PARA EL DIA DE HOY"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numPedidos;i++){
        archReporte<<"Pedido: "<<pedidos[i].codigo<<"  Nombre Rappi: "
                <<left<<setw(45)<<pedidos[i].repartidorRappi<<right
                <<"Hora: "<<setfill('0')<<setw(2)<<pedidos[i].hora/100<<':'
                <<setw(2)<<pedidos[i].hora%100<<setfill(' ')<<endl;
        archReporte<<setw(13)<<' '<<"Destino: "<<pedidos[i].distrito<<','
                <<pedidos[i].direccion<<endl;
        archReporte<<setw(13)<<' '<<"Usuario: "<<pedidos[i].codigoUsuario<<endl;
        archReporte<<"Datos de la boleta"<<endl<<endl;
        archReporte<<"PRODUCTO"<<setw(45)<<"PRECIO UNITARIO"<<setw(18)<<"CANTIDAD"
                <<setw(20)<<"PREECIO TOTAL"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        imprimeProductos(pedidos[i],archReporte);
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void imprimeProductos(struct Pedido &pedido,ofstream &archReporte){
    int cantidad=0;
    for(int i=0;i<pedido.cantidadProductos;i++){
        archReporte<<left<<setw(40)<<pedido.productos[i].nombre<<right
                <<setw(7)<<pedido.productos[i].precioUnitario
                <<setw(20)<<pedido.productos[i].cantidad
                <<setw(16)<<pedido.productos[i].precioUnitario*
                pedido.productos[i].cantidad<<endl;
        cantidad+=pedido.productos[i].cantidad;
    }
    imprimeLinea('-',MAX_LINE,archReporte);
    archReporte<<"Resumen: "<<setw(55)<<cantidad<<" Items"
            <<setw(13)<<pedido.montoTotal<<endl;
}

void imprimeLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

int buscarDireccion(struct Direccion *direecciones, char *ptr_codUsuario,
        int numDirecciones){
    for(int i=0;i<numDirecciones;i++)
        if(strcmp(direecciones[i].codigoUsuario,ptr_codUsuario)==0)return i;
    return NO_ENCONTRADO;
}

int buscarPedido(struct Pedido *pedidos,int codigo_pedido,int numPedidos){
    for(int i=0;i<numPedidos;i++)
        if(pedidos[i].codigo == codigo_pedido)return i;
    
    return NO_ENCONTRADO;
}

char *leerCadenaExacta(ifstream &arch){
    
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    
    longitud = strlen(buffer)+1;
    
    cadena = new char[longitud+1];
    
    strcpy(cadena,buffer);
    
    return cadena;
}


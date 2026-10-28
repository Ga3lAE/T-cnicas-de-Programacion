/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
#include <cmath>
#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "StructDirecciones.h"
#include "funciones.h"
#include "StructPedidos.h"

void crearArchDireccionesBin(const char *nombArchCsv,const char *nombArchBin){   
    ifstream archDirecciones(nombArchCsv,ios::in);
    if(not archDirecciones.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }  
    ofstream archDireccionesBin(nombArchBin,ios::out | ios::binary);
    if(not archDireccionesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }   
    char codigoUsuario[7],distrito[50],direccion[20];
    double latitud,longitud;
    struct Direccion direccionEvaluar;
    while(true){
        archDirecciones.getline(codigoUsuario,7,',');
        if(archDirecciones.eof())break;
        archDirecciones.getline(direccion,50,',');
        archDirecciones.getline(distrito,20,',');
        archDirecciones>>latitud;
        archDirecciones.get();
        archDirecciones>>longitud;
        archDirecciones.get();    
        strcpy(direccionEvaluar.codigoUsuario,codigoUsuario);
        strcpy(direccionEvaluar.direccion,direccion);
        strcpy(direccionEvaluar.distrito,distrito);
        direccionEvaluar.latitud = latitud;
        direccionEvaluar.longitud = longitud;   
        archDireccionesBin.write(reinterpret_cast<const char*>(&direccionEvaluar),
                sizeof(struct Direccion));
    }
}

void crearArchPedidosBin(const char *nombArchCsv,const char *nombArchBin){   
    ifstream archCsv(nombArchCsv,ios::in);
    if(not archCsv.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    crearArchivo(nombArchBin);   
    fstream archBin(nombArchBin,ios::in | ios::out | ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    int codPedido,posPedido,tamArch,tamReg,numReg;
    struct Pedido pedido;
    tamReg = sizeof(struct Pedido);
    while(true){
        archCsv>>codPedido;
        if(archCsv.eof())break;
        archCsv.get();
        posPedido = buscarPedido(archBin,codPedido);
        if(posPedido!=NO_ENCONTRADO){/*Si es que ya fue registrado*/
            archBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
            archBin.read(reinterpret_cast<char*>(&pedido),sizeof(struct Pedido));
            asignarProductos(pedido,archCsv);
            archBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
        }else{ /*Si es un pedido nuevo*/            
            pedido.codigo = codPedido;
            pedido.cantProd =0;
            pedido.montoTotal=0;
            asignarProductos(pedido,archCsv);
            archBin.seekg(0,ios::end);
        }
        archBin.write(reinterpret_cast<const char*>(&pedido),sizeof(struct Pedido));
        archBin.flush();
    }
}

void asignarProductos(struct Pedido &pedido,ifstream &archCsv){
    char nombre[60];
    int cantidad;
    double precio;
    while(true){
        archCsv.getline(nombre,60,',');
        archCsv>>cantidad;
        archCsv.get();
        archCsv>>precio;
        pedido.productos[pedido.cantProd].cantidad = cantidad;
        strcpy(pedido.productos[pedido.cantProd].nombre,nombre);
        pedido.productos[pedido.cantProd].precio = precio;
        pedido.montoTotal += cantidad*precio;
        pedido.cantProd++;
        if(archCsv.get()=='\n')break;
    }
}

void actualizarPedidosBin(const char *nombPedidosBin,const char *nombDirecBin,
        const char *nombArchCsv){  
    fstream archPedidosBin(nombPedidosBin,ios::in | ios::out | ios::binary);
    if(not archPedidosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombPedidosBin<<endl;
        exit(1);
    }   
    ifstream archDireccionesBin(nombDirecBin,ios::in | ios::binary);
    if(not archDireccionesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombDirecBin<<endl;
        exit(1);
    }    
    ifstream archRappi(nombArchCsv,ios::in);
    if(not archRappi.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }   
    int hora,minuto,tiempo,codPedido,posDireccion,posPedido;
    char nombreRappi[60],codUsuario[7],c;
    while(true){
        archRappi>>hora;
        if(archRappi.eof())break;
        archRappi>>c>>minuto>>c;
        tiempo = hora * 100 + minuto;
        archRappi.getline(nombreRappi,60,',');
        archRappi.getline(codUsuario,7,',');
        archRappi>>codPedido;
        posDireccion = buscarDireccion(archDireccionesBin,codUsuario);
        if(posDireccion!=NO_ENCONTRADO){
            posPedido = buscarPedido(archPedidosBin,codPedido);
            if(posPedido!=NO_ENCONTRADO){
                asignarValores(tiempo,nombreRappi,codUsuario,posDireccion,
                        posPedido,archDireccionesBin,archPedidosBin);
            }
        }
    }
}

void asignarValores(int tiempo,char *nombreRappi,char *codUsuario,
        int posDireccion,int posPedido,ifstream &archDireccionesBin,
        fstream &archPedidosBin){
    struct Direccion direccion;
    struct Pedido pedido;
    archDireccionesBin.seekg(posDireccion*sizeof(struct Direccion),ios::beg);
    archDireccionesBin.read(reinterpret_cast<char *>(&direccion),
            sizeof(struct Direccion));
    archPedidosBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
    archPedidosBin.read(reinterpret_cast<char *>(&pedido),sizeof(struct Pedido));
    pedido.hora = tiempo;
    strcpy(pedido.repartidorRappi,nombreRappi);
    strcpy(pedido.codigoUs,codUsuario);
    //pedido.direccionRappi=direccion; otra forma valida
    strcpy(pedido.direccionRappi.codigoUsuario,codUsuario);
    strcpy(pedido.direccionRappi.direccion,direccion.direccion);
    strcpy(pedido.direccionRappi.distrito,direccion.distrito);
    pedido.distancia = sqrt(pow(fabs(-12.0766-direccion.latitud),2)+
                            pow(fabs(-77.0833-direccion.longitud),2));    
    archPedidosBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
    archPedidosBin.write(reinterpret_cast<const char *>(&pedido),sizeof(struct Pedido));
    archPedidosBin.flush();
}

void ordenarArchivos(const char *nombArchBin){
    
    fstream archBin(nombArchBin,ios::in | ios::out | ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    struct Pedido pedidoI,pedidoK;
    int tamReg,tamArch,numReg;
    tamReg = sizeof(struct Pedido);
    datosArchivo(archBin,tamArch,tamReg,numReg);
    for(int i=0;i<numReg-1;i++)
        for(int k=i+1;k<numReg;k++){
            archBin.seekg(i*tamReg,ios::beg);
            archBin.read(reinterpret_cast<char *>(&pedidoI),tamReg);
            archBin.seekg(k*tamReg,ios::beg);
            archBin.read(reinterpret_cast<char *>(&pedidoK),tamReg);
            if(pedidoI.hora>pedidoK.hora or pedidoI.hora==pedidoK.hora and
                    pedidoI.distancia<pedidoK.distancia){
                archBin.seekg(i*tamReg,ios::beg);
                archBin.write(reinterpret_cast<const char *>(&pedidoK),tamReg);
                archBin.seekg(k*tamReg,ios::beg);
                archBin.write(reinterpret_cast<const char *>(&pedidoI),tamReg);
                archBin.flush();
            }
        }
}

void imprimeReporte(const char *nombArchBin,const char *nombArchTxt){    
    ifstream archPedidosBin(nombArchBin,ios::in | ios::binary);
    if(not archPedidosBin.is_open()){
        cout<<"ERROR al abrir el achivo de "<<nombArchBin<<endl;
        exit(1);
    }  
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    struct Pedido pedido;
    int hora,min;
    archReporte<<"tp_rappi"<<endl;
    archReporte<<"REPORTE DE PEDIDOS"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"PEDIDO"<<setw(10)<<' '<<"Nombre Rappi"<<setw(40)<<' '
            <<"HORA"<<setw(10)<<' '<<"DISTANCIA EUCLIDIANA"<<setw(10)<<' '
            <<"PRECIO TOTAL"<<endl;
    imprimeLinea('-',MAX_LINE,archReporte);
    while(true){
        archPedidosBin.read(reinterpret_cast<char *>(&pedido),sizeof(struct Pedido));
        if(archPedidosBin.eof())break;
        archReporte<<setw(4)<<pedido.codigo<<setw(12)<<' '<<left<<setw(51)
                <<pedido.repartidorRappi;
        hora = pedido.hora/100;
        min = pedido.hora%100;
        archReporte<<right<<setfill('0')<<setw(2)<<hora<<':'<<setw(2)<<min
                <<setfill(' ')<<setw(25)<<setprecision(4)<<fixed<<pedido.distancia
                <<setw(25)<<setprecision(2)<<fixed<<pedido.montoTotal<<endl;
    }
    imprimeLinea('=',MAX_LINE,archReporte);
}

int buscarDireccion(ifstream &arch, char *codigo){
    int tamArch,tamReg,numReg;
    struct Direccion direccionAux;
    tamReg = sizeof(struct Direccion);
    datosArchivoDireccion(arch,tamArch,tamReg,numReg);
    for(int i=0;i<numReg;i++){
        arch.read(reinterpret_cast<char *>(&direccionAux),tamReg);
        if(strcmp(direccionAux.codigoUsuario,codigo)==0)return i;
    }
    return NO_ENCONTRADO;
}


int buscarPedido(fstream &archBin, int codigo){
    struct Pedido pedido;
    int tamArch,tamReg,numReg;
    tamReg = sizeof(struct Pedido);
    datosArchivo(archBin,tamArch,tamReg,numReg);
    for(int i=0;i<numReg;i++){
        archBin.read(reinterpret_cast<char *>(&pedido),sizeof(struct Pedido));
        if(pedido.codigo == codigo)return i;
    }
    return NO_ENCONTRADO;
}

void datosArchivoDireccion(ifstream &arch,int &tamArch,int tamReg,int &numReg){
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    arch.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

void datosArchivo(fstream &archBin,int &tamArch,int tamReg,int &numReg){
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

void crearArchivo(const char *nombArchBin){
    ofstream archBin(nombArchBin,ios::out | ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
}

void imprimeLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

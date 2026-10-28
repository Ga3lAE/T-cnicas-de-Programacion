/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;
#include "funcionesaux.h"
#include "Cliente.h"
#include "Libreria.h"
#include "Venta.h"
#include "Libro.h"
#define NOFOUND -1
#define CARMAX 180

//leyendo clientes
void leyendoClientes(const char*nomArch,const char*nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(!archBin){
        cout<<"NO SE APERTURO "<<nomArchBin<<endl;
        exit(1);
    }
    struct Cliente infoCliente;
    
    while(true){
        arch>>infoCliente.dni;
        if(arch.eof())break;
        arch.get();
        arch.getline(infoCliente.nombre,60,'\n');
        modificando(infoCliente.nombre);
        infoCliente.montoComprado=0;
        infoCliente.descuentoFuturo=0;
        //tras obtenr info grabamos en el bianriio
        archBin.write(reinterpret_cast<const char*>(&infoCliente),
                sizeof(struct Cliente));
    }
}
//funcion mayus nombres
void  modificando(char*nombre){
    for(int i=0;nombre[i];i++){
        if(nombre[i]>='a' and nombre[i]<='z')nombre[i]-='a'-'A';
    }
}
//funcion para corroborar clientes
void  corroborandoClientes(const char*nomArch,const char*nomArchBin){
    ofstream arch(nomArch,ios::out);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    ifstream archBin(nomArchBin,ios::in|ios::binary);
    if(!archBin){
        cout<<"NO SE APERTURO "<<nomArchBin<<endl;
        exit(1);
    }
    struct Cliente infoCliente;
    int tamReg,numReg,tamArch;
    tamReg=sizeof(struct Cliente);
    datosIfstream(tamReg,numReg,tamArch,archBin);
    arch<<setprecision(2)<<fixed;
    headerClientes(arch);
    for(int i=0;i<numReg;i++){
        //s buscar y se imprime
        archBin.seekg(i*tamReg,ios::beg);
        archBin.read(reinterpret_cast<char*>(&infoCliente),tamReg);
        arch<<infoCliente.dni<<"  "<<setw(60)<<left<<infoCliente.nombre<<
                setw(9)<<right<<infoCliente.montoComprado<<
                setw(21)<<infoCliente.descuentoFuturo<<endl;
    }
}
//cabezal
void headerClientes(ofstream&arch){
    arch<<left<<setw(10)<<"DNI"<<setw(60)<<"NOMBRE"<<setw(20)<<"MONTO COMPRADO"
            <<setw(20)<<"DESCUENTO FUTURO"<<endl;
}
//funcion para obtener datos ifstream
void datosIfstream(int tamReg,int&numReg,int&tamArch,ifstream&archBin){
    archBin.seekg(0,ios::end);
    tamArch=archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg=tamArch/tamReg;
}
//funcion de lectura de libros
void leyendoLibros(const char*nomArch,const char*nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(!archBin){
        cout<<"NO SE APERTURO "<<nomArchBin<<endl;
        exit(1);
    }
    struct Libro infoLibro;
    while(true){
        arch.getline(infoLibro.codigo,8,',');
        if(arch.eof())break;
        arch.getline(infoLibro.titulo,60,',');
        arch.getline(infoLibro.autor,60,',');
        arch>>infoLibro.precio;
        arch.get();
        infoLibro.cantidadBuenasCalificaciones=0;
        infoLibro.cantidadLibrerias=0;
        infoLibro.cantidadMalasCalificaciones=0;
        infoLibro.sumaBuenasCalificaciones=0;
        infoLibro.sumaMalasCalificaciones=0;
        infoLibro.totalVentas=0;
        infoLibro.unidadesVendidas=0;
        //almacenando en el archivo binario
         archBin.write(reinterpret_cast<const char*>(&infoLibro),
                sizeof(struct Libro));
    }
}
//funcion de emision de reporte
void emitiendoReporte(const char*nomArch,const char*nomArchBinClientes,
        const char*nomArchBinLibros){
    ofstream arch(nomArch,ios::out);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    ifstream archBinCli(nomArchBinClientes,ios::in|ios::binary);
    if(!archBinCli){
        cout<<"NO SE APERTURO "<<nomArchBinClientes<<endl;
        exit(1);
    }
    ifstream archBinLib(nomArchBinLibros,ios::in|ios::binary);
    if(!archBinLib){
        cout<<"NO SE APERTURO "<<nomArchBinLibros<<endl;
        exit(1);
    }
    //aperturando los archvios para su lectrua
    struct Cliente infoCliente;
    struct Libro infoLibro;
    int tamRegCli,numRegCli,tamArchCli,tamRegLib,numRegLib,tamArchLib;
    tamRegCli=sizeof(struct Cliente);
    tamRegLib=sizeof(struct Libro);
    datosIfstream(tamRegCli,numRegCli,tamArchCli,archBinCli);
    datosIfstream(tamRegLib,numRegLib,tamArchLib,archBinLib);
    arch<<setprecision(2)<<fixed;
    arch<<right<<setw(CARMAX/2+20)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS"
            <<endl;
    for(int i=0;i<numRegLib;i++){
        archBinLib.seekg(i*tamRegLib,ios::beg);
        archBinLib.read(reinterpret_cast<char*>(&infoLibro),tamRegLib);
        //tras leer ele libro nos llevamos la info para imprimir
        headerLibro(infoLibro,arch,i);
        //librerias imprimir
        imprimiendoLibreriasPerBook(infoLibro.librerias,
                infoLibro.cantidadLibrerias,arch);
    }
}
//funcion cabezal de la impremios
void headerLibro(struct Libro&arrLibros,ofstream&arch,int i){
    double promedioBuenasCalif,promedioMalasCalif,promedio;
    promedioBuenasCalif=(double)arrLibros.sumaBuenasCalificaciones/
            (double)arrLibros.cantidadBuenasCalificaciones;
    promedioMalasCalif=(double)arrLibros.sumaMalasCalificaciones/
            (double)arrLibros.cantidadMalasCalificaciones;
    promedio=(double)(arrLibros.sumaBuenasCalificaciones+
            arrLibros.sumaMalasCalificaciones)/(double)
            (arrLibros.cantidadBuenasCalificaciones+
            arrLibros.cantidadMalasCalificaciones);
    if(arrLibros.cantidadBuenasCalificaciones==0)promedioBuenasCalif=0.0;
    if(arrLibros.cantidadMalasCalificaciones==0)promedioMalasCalif=0.0;
    if(arrLibros.cantidadBuenasCalificaciones==0 and 
            arrLibros.cantidadMalasCalificaciones==0)promedio=0.0;
    arch<<setfill('=')<<setw(CARMAX)<<"="<<setfill(' ')<<endl;
    arch<<"LIBRO NO."<<right<<setw(8)<<i+1<<endl;
    arch<<"CODIGO    "<<left<<setw(40)<<"TITULO"<<setw(40)<<"AUTOR"<<setw(10)<<
            "PRECIO"<<setw(15)<<"VENDIDOS"<<"TOTAL.VENTAS  PROM.BUENAS.CALIF  "
            "PROM.MALAS.CALIF  PROM.CALIF"<<endl;
    arch<<setw(10)<<arrLibros.codigo<<setw(40)<<arrLibros.titulo<<setw(36)<<
            arrLibros.autor<<setw(10)<<right<<arrLibros.precio<<setw(10)<<
            arrLibros.unidadesVendidas<<setw(10)<<setw(18)<<
            arrLibros.totalVentas<<setw(15)<<
            promedioBuenasCalif<<setw(20)<<promedioMalasCalif<<setw(14)<<
            promedio<<endl;  
}
//imprimiendoLasLibrearias 
void imprimiendoLibreriasPerBook(struct Libreria*librerias,
                int cantidadLibrerias,ofstream&arch){
    for(int i=0;i<cantidadLibrerias;i++){
        arch<<setfill('-')<<setw(CARMAX)<<"-"<<setfill(' ')<<endl;
        arch<<"LIBRERIA: "<<left<<setw(10)<<librerias[i].codigo<<
                "TOTAL DE VENTAS: "<<right<<setw(10)<<librerias[i].totalVentas
                <<endl;
        arch<<setfill('-')<<setw(CARMAX)<<"-"<<setfill(' ')<<endl;
        //imprimiendo las ventas por librearia
        imprimiendoVentasLibreria(librerias[i].ventas,librerias[i].
                cantidadVentas,arch);  
    }  
}
//funcion impresion de ventas per libreria
void imprimiendoVentasLibreria(struct Venta*ventas,int cantidadVentas,
        ofstream&arch){
    arch<<"    VENTAS:"<<endl;
    arch<<"    No.  "<<left<<setw(10)<<"DNI"<<setw(60)<<"NOMBRE"<<setw(20)<<
            "CALIFICACION"<<"FECHA"<<endl;
    for(int i=0;i<cantidadVentas;i++){
        arch<<right<<setw(6)<<i+1<<"  "<<ventas[i].dniComprador<<"  "<<left<<
                setw(60)<<ventas[i].nombreComprador<<setw(8)<<right<<
                ventas[i].calificacion<<setw(19)<<ventas[i].fecha<<endl;
    }
            
}
//funcion actualizacion de ventas
void leyendoVentas(const char*nomArch,const char*nomArchBinClientes,
        const char*nomArchBinLibros){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    fstream archBinCli(nomArchBinClientes,ios::in|ios::out|ios::binary);
    if(!archBinCli){
        cout<<"NO SE APERTURO "<<nomArchBinClientes<<endl;
        exit(1);
    }
    fstream archBinLib(nomArchBinLibros,ios::in|ios::out|ios::binary);
    if(!archBinLib){
        cout<<"NO SE APERTURO "<<nomArchBinLibros<<endl;
        exit(1);
    }
    struct Cliente infoCliente;
    struct Libro infoLibro;
    int tamRegCli,numRegCli,tamArchCli,tamRegLib,numRegLib,tamArchLib,
            codeLibreriaVerif,dd,mm,aa,fecha,dniVerif,calificacion,posLibro,
        posCliente;
    tamRegCli=sizeof(struct Cliente);
    tamRegLib=sizeof(struct Libro);
    //obteniendodatos vitales
    datosFstream(tamRegCli,numRegCli,tamArchCli,archBinCli);
    datosFstream(tamRegLib,numRegLib,tamArchLib,archBinLib);
    char c,codeLibroVerif[8];
    while(true){
        arch>>codeLibreriaVerif;
        if(arch.eof())break;
        arch>>dd>>c>>mm>>c>>aa;
        fecha=aa*10000+mm*100+dd;
        while(true){
            if(arch.get()=='\n')break;
            arch>>ws;
            arch.getline(codeLibroVerif,8,' ');
            arch>>dniVerif>>calificacion;
            posLibro=buscandoLibro(codeLibroVerif,archBinLib,numRegLib);
            posCliente=buscandoCliente(dniVerif,archBinCli,numRegCli);
            //tras obtener la posicion procedemos a leer y actualizar
            if(posCliente!=NOFOUND and posLibro!=NOFOUND){
                archBinLib.seekg(posLibro*tamRegLib,ios::beg);
                archBinLib.read(reinterpret_cast<char*>(&infoLibro),
                        sizeof(struct Libro));
                archBinCli.seekg(posCliente*tamRegCli,ios::beg);
                archBinCli.read(reinterpret_cast<char*>(&infoCliente),
                        sizeof(struct Cliente));
                actualizandoInformacion(infoLibro,
                        infoCliente,fecha,codeLibreriaVerif,
                        calificacion);
                archBinLib.seekg(posLibro*tamRegLib,ios::beg);
                archBinLib.write(reinterpret_cast<const char*>(&infoLibro),
                        sizeof(struct Libro));
                archBinCli.seekg(posCliente*tamRegCli,ios::beg);
                archBinCli.write(reinterpret_cast<const char*>(&infoCliente),
                        sizeof(struct Cliente));
                archBinCli.flush();
                archBinLib.flush();
            }
        }   
    }
}
//funcion datos fstream
void datosFstream(int tamReg,int&numReg,int&tamArch,fstream&archBin){
    archBin.seekg(0,ios::end);
    tamArch=archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg=tamArch/tamReg;
}
//funcion busqueda book
int buscandoLibro(char*codeLibroVerif,fstream&archBinLib,int numRegLib){
    struct Libro infoLibro;
    archBinLib.seekg(0,ios::beg);
    for(int i=0;i<numRegLib;i++){
        archBinLib.read(reinterpret_cast<char*>(&infoLibro),
                sizeof(struct Libro));
        if(strcmp(codeLibroVerif,infoLibro.codigo)==0)return i;
    }return NOFOUND;
}
//funcion de busqueda cliente
int buscandoCliente(int dniVerif,fstream&archBinCli,int numRegCli){
    struct Cliente infoCliente;
    archBinCli.seekg(0,ios::beg);
    for(int i=0;i<numRegCli;i++){
        archBinCli.read(reinterpret_cast<char*>(&infoCliente),
                sizeof(struct Cliente));
        if(dniVerif==infoCliente.dni)return i;
    }return NOFOUND;
}
//funcion de actualizacion de info
void actualizandoInformacion(struct Libro&arrLibros,
                        struct Cliente&arrCliente,int fecha,
        int codeLibreriaVerif,int calificacion){
    int posLibreria,u,k;
    if(calificacion>50){
        arrLibros.cantidadBuenasCalificaciones++;
        arrLibros.sumaBuenasCalificaciones+=calificacion;
    }else{
        arrLibros.cantidadMalasCalificaciones++;
        arrLibros.sumaMalasCalificaciones+=calificacion;
    }
    //buscando la librearia
    posLibreria=buscandoLibreria(codeLibreriaVerif,arrLibros.librerias,
            arrLibros.cantidadLibrerias);
    u=arrLibros.cantidadLibrerias;
    //significa nueva librearia
    if(posLibreria==NOFOUND){
        arrLibros.librerias[u].cantidadVentas=0;
        arrLibros.librerias[u].totalVentas=0.0;
        ActualizandoLibrerias(arrLibros,u,arrCliente,codeLibreriaVerif,
                calificacion,fecha);
        u++;
        arrLibros.cantidadLibrerias=u;
    }else{
        //significa librearia repetida
        ActualizandoLibrerias(arrLibros,posLibreria,arrCliente,
                codeLibreriaVerif,
                calificacion,fecha);
    }
    //actualizando datos del cliente final
    arrCliente.montoComprado+=arrLibros.precio-arrLibros.precio*
            arrCliente.descuentoFuturo/100;
    arrLibros.totalVentas+=arrLibros.precio-arrLibros.precio*
            arrCliente.descuentoFuturo/100;
    if(arrCliente.montoComprado<3000)arrCliente.descuentoFuturo=10;
    else if(arrCliente.montoComprado<5000)arrCliente.descuentoFuturo=20;
    else if(arrCliente.montoComprado>=3000)arrCliente.descuentoFuturo=30;
    
}
//funcion de busqued libreria
int buscandoLibreria(int codeLibreriaVerif,struct Libreria*librerias,
            int cantidadLibrerias){
    for(int i=0;i<cantidadLibrerias;i++){
        if(codeLibreriaVerif==librerias[i].codigo)return i;
    }return NOFOUND;
}
//funcion actualizando librearia
void ActualizandoLibrerias(struct Libro&arrLibros,int u,
        struct Cliente&arrCliente,int codeLibreriaVerif,
                int calificacion,int fecha){
    int k;
    k=arrLibros.librerias[u].cantidadVentas;
    //aqui el codigo deberia de reempelazarse sin problema
        arrLibros.librerias[u].codigo = codeLibreriaVerif;
        arrLibros.librerias[u].totalVentas+=(double)(arrLibros.precio-
                arrLibros.precio*arrCliente.descuentoFuturo/100);
        //al parecer aqui hay un error
        arrLibros.librerias[u].ventas[k].calificacion=calificacion;
        arrLibros.librerias[u].ventas[k].dniComprador=arrCliente.dni;
        arrLibros.librerias[u].ventas[k].fecha=fecha;
        //posible origen de error
        strcpy(arrLibros.librerias[u].ventas[k].nombreComprador,
                arrCliente.nombre);
        k++;
        arrLibros.librerias[u].cantidadVentas=k;
        arrLibros.unidadesVendidas++;
        
}
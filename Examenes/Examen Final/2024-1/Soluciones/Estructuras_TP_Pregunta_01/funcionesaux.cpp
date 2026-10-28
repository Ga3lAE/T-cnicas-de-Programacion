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

//funciones leyendo cleintes
void leyendoClientes(const char*nomArch,struct Cliente*arrCliente,
        int&cantClientes){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    cantClientes=0;
    while(true){
        //alamcenadnodatos
        arch>>arrCliente[cantClientes].dni;
        if(arch.eof())break;
        arch.get();
        arrCliente[cantClientes].nombre=leyendoCadena(arch,'\n');
        modificando(arrCliente[cantClientes].nombre);
        arrCliente[cantClientes].montoComprado=0;
        arrCliente[cantClientes].descuentoFuturo=0;
        cantClientes++;
    }
    
}
//modificiando nombre
void  modificando(char*nombre){
    for(int i=0;nombre[i];i++){
        if(nombre[i]>='a' and nombre[i]<='z')nombre[i]-='a'-'A';
    }
}
//funcion leer cadena
char*leyendoCadena(ifstream&arch,char fin){
    char aux[100],*ptr;
    arch.getline(aux,100,fin);
    if(arch.eof())return nullptr;
    ptr=new char[strlen(aux)+1];
    strcpy(ptr,aux);
    return ptr;
}
//corroboradnoClientes
void corroborandoClientes(const char*nomArch,struct Cliente*arrCliente,
        int cantClientes){
    ofstream arch(nomArch,ios::out);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    arch<<setprecision(2)<<fixed;
    //facbezal y datos
    headerClientes(arch);
    for(int i=0;i<cantClientes;i++){
        arch<<arrCliente[i].dni<<"  "<<setw(60)<<left<<arrCliente[i].nombre<<
                setw(9)<<right<<arrCliente[i].montoComprado<<
                setw(21)<<arrCliente[i].descuentoFuturo<<endl;
    }
}
//cabezal de funcon clientes
void headerClientes(ofstream&arch){
    arch<<left<<setw(10)<<"DNI"<<setw(60)<<"NOMBRE"<<setw(20)<<"MONTO COMPRADO"
            <<setw(20)<<"DESCUENTO FUTURO"<<endl;
}
//leyendo libros
void leyendoLibros(const char*nomArch,struct Libro*arrLibros,
        int&cantLibros){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    cantLibros=0;
    while(true){
        //obteniendo datos e incializando
        arrLibros[cantLibros].codigo=leyendoCadena(arch,',');
        if(arch.eof())break;
        arrLibros[cantLibros].titulo=leyendoCadena(arch,',');
        arrLibros[cantLibros].autor=leyendoCadena(arch,',');
        arch>>arrLibros[cantLibros].precio;
        arch.get();
        arrLibros[cantLibros].cantidadBuenasCalificaciones=0;
        arrLibros[cantLibros].cantidadLibrerias=0;
        arrLibros[cantLibros].cantidadMalasCalificaciones=0;
        arrLibros[cantLibros].librerias=new struct Libreria[5]{};
        arrLibros[cantLibros].sumaBuenasCalificaciones=0;
        arrLibros[cantLibros].sumaMalasCalificaciones=0;
        arrLibros[cantLibros].totalVentas=0;
        arrLibros[cantLibros].unidadesVendidas=0;
        cantLibros++; 
    }
}
//emitiendo el reporte funcion
void emitiendoReporte(const char*nomArch,struct Cliente*arrCliente,
        struct Libro*arrLibros,int cantClientes,int cantLibros){
    ofstream arch(nomArch,ios::out);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    arch<<setprecision(2)<<fixed;
    arch<<right<<setw(CARMAX/2+20)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS"
            <<endl;
    for(int i=0;i<cantLibros;i++){
        //infolibros
        headerLibro(arrLibros[i],arch,i);
        //infolibreias de cada libro
        imprimiendoLibreriasPerBook(arrLibros[i].librerias,
                arrLibros[i].cantidadLibrerias,arch);
    }
}
//funcionde  infolibro
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
//funcion de impresionde librerias
void imprimiendoLibreriasPerBook(struct Libreria*librerias,
                int cantidadLibrerias,ofstream&arch){
    
    for(int i=0;i<cantidadLibrerias;i++){
        arch<<setfill('-')<<setw(CARMAX)<<"-"<<setfill(' ')<<endl;
        arch<<"LIBRERIA: "<<left<<setw(10)<<librerias[i].codigo<<
                "TOTAL DE VENTAS: "<<right<<setw(10)<<librerias[i].totalVentas
                <<endl;
        arch<<setfill('-')<<setw(CARMAX)<<"-"<<setfill(' ')<<endl;
        //imprimiendo el detalle de vetnas de cada librearia
        imprimiendoVentasLibreria(librerias[i].ventas,librerias[i].
                cantidadVentas,arch);
        
    }
    
}
//funcion detalle de vetnas
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
//funcion de lectura de ventas apra actualizar
void leyendoVentas(const char*nomArch,struct Libro*arrLibros,
        struct Cliente*arrCliente,
        int cantClientes,int cantLibros){
    ifstream arch(nomArch,ios::in);
    if(!arch){
        cout<<"NO SE APERTURO "<<nomArch<<endl;
        exit(1);
    }
    int codeLibreriaVerif,dd,mm,aa,fecha,dniVerif,calificacion,posLibro,
        posCliente;
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
            //tras obtener datos hacemos la busqeuda
            posLibro=buscandoLibro(codeLibroVerif,arrLibros, cantLibros);
            posCliente=buscandoCliente(dniVerif,arrCliente,cantClientes);
            if(posCliente!=NOFOUND and posLibro!=NOFOUND){
                //funcion actualizandoInformacion
                actualizandoInformacion(arrLibros[posLibro],
                        arrCliente[posCliente],fecha,codeLibreriaVerif,
                        calificacion);
            }
        }   
    }
}
//funcion de busqueda de libro
int buscandoLibro(char*codeLibroVerif,struct Libro*arrLibros,int cantLibros){
    for(int i=0;i<cantLibros;i++){
        if(strcmp(codeLibroVerif,arrLibros[i].codigo)==0)return i;
    }return NOFOUND;
}
//funcion de busqueda de cleinte
int buscandoCliente(int dniVerif,struct Cliente*arrCliente,int cantClientes){
    for(int i=0;i<cantClientes;i++){
        if(dniVerif==arrCliente[i].dni)return i;
    }return NOFOUND;
}
//funcion de actuzlizadno informe
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
    //buscando la libreria si es que se encuentra o no
    posLibreria=buscandoLibreria(codeLibreriaVerif,arrLibros.librerias,
            arrLibros.cantidadLibrerias);
    u=arrLibros.cantidadLibrerias;
    //significa nueva librearia
    if(posLibreria==NOFOUND){
        arrLibros.librerias[u].ventas=new struct Venta[10];
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
    //actullizando al cliente
    arrCliente.montoComprado+=arrLibros.precio-arrLibros.precio*
            arrCliente.descuentoFuturo/100;
    arrLibros.totalVentas+=arrLibros.precio-arrLibros.precio*
            arrCliente.descuentoFuturo/100;
    if(arrCliente.montoComprado<3000)arrCliente.descuentoFuturo=10;
    else if(arrCliente.montoComprado<5000)arrCliente.descuentoFuturo=20;
    else if(arrCliente.montoComprado>=3000)arrCliente.descuentoFuturo=30;
    
}
//buscandoLibreria
int buscandoLibreria(int codeLibreriaVerif,struct Libreria*librerias,
            int cantidadLibrerias){
    for(int i=0;i<cantidadLibrerias;i++){
        if(codeLibreriaVerif==librerias[i].codigo)return i;
    }return NOFOUND;
}
//funcion de actulizacion librearia para ambos casos
void ActualizandoLibrerias(struct Libro&arrLibros,int u,
        struct Cliente&arrCliente,int codeLibreriaVerif,
                int calificacion,int fecha){
    int k;
    k=arrLibros.librerias[u].cantidadVentas;
    //aqui el codigo deberia de reempelazarse sin problema
        arrLibros.librerias[u].codigo = codeLibreriaVerif;
        arrLibros.librerias[u].totalVentas+=(double)(arrLibros.precio-
                arrLibros.precio*arrCliente.descuentoFuturo/100);
        arrLibros.librerias[u].ventas[k].calificacion=calificacion;
        arrLibros.librerias[u].ventas[k].dniComprador=arrCliente.dni;
        arrLibros.librerias[u].ventas[k].fecha=fecha;
        //posible origen de error
        arrLibros.librerias[u].ventas[k].nombreComprador=arrCliente.nombre;
        k++;
        arrLibros.librerias[u].cantidadVentas=k;
        arrLibros.unidadesVendidas++;
        
}
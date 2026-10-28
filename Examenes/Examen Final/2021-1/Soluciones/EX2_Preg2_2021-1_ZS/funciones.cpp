

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 14 de junio de 2023, 11:56 AM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define NO_ENCONTRADO -1
#include "StructLibroPrestado.h"
#include "StructRegPrestamos.h"
#include "StructLibros.h"
#include "funciones.h"

void leerLibros(struct Libro *libros,int &numLibros){
    
    ifstream archLibro("Libros.csv",ios::in);
    if(not archLibro.is_open()){
        cout<<"ERROR al abrir el archivo de libros"<<endl;
        exit(1);
    }
    char *ptr_codLibro, *ptr_titulo, *ptr_autor;
    numLibros=0;
    int anioPublicacion,cantLibro,cantVecesPrestado;
    while(true){
        ptr_codLibro = leerCadenaExacta(archLibro);
        if(archLibro.eof())break;
        ptr_titulo = leerCadenaExacta(archLibro);
        ptr_autor = leerCadenaExacta(archLibro);
        archLibro>>anioPublicacion;
        archLibro.get();
        archLibro>>cantLibro;
        archLibro.get();
        archLibro>>cantVecesPrestado;
        archLibro.get();
        libros[numLibros].codigo = ptr_codLibro;
        libros[numLibros].titulo = ptr_titulo;
        libros[numLibros].autor = ptr_autor;
        libros[numLibros].aPublicacion=anioPublicacion;
        libros[numLibros].cantidad = cantLibro;
        libros[numLibros].prestamos = cantVecesPrestado;
        numLibros++;
    }
    
//    for(int i=0;i<numLibros;i++)
//        cout<<libros[i].codigo<<' '<<libros[i].titulo<<' '<<libros[i].autor
//                <<' '<<libros[i].aPublicacion<<' '<<libros[i].cantidad
//                <<' '<<libros[i].prestamos<<endl;
}

void imprimeLibros(struct Libro *libros, int numLibros){
    
    ofstream archReporte("DatosLibros.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de Libros"<<endl;
        exit(1);
    }
    
    for(int i=0;i<numLibros;i++)
        archReporte<<libros[i].codigo<<' '<<libros[i].titulo<<' '<<libros[i].autor
                <<' '<<libros[i].aPublicacion<<' '<<libros[i].cantidad
                <<' '<<libros[i].prestamos<<endl;
}

void leerRegistrosPrestamos(struct RegPrestamo *regPrestamos,int &numRegistros){
    
    ifstream archRegistros("RegistroDePrestamos.csv",ios::in);
    if(not archRegistros.is_open()){
        cout<<"ERROR al abrir el archivo de registros"<<endl;
        exit(1);
    }
    int codigo;
    char *ptr_nombreUsuario;
    numRegistros=0;
    while(true){
        archRegistros>>codigo;
        if(archRegistros.eof())break;
        archRegistros.get();
        ptr_nombreUsuario = leerCadenaExacta(archRegistros);
        regPrestamos[numRegistros].codigo = codigo;
        regPrestamos[numRegistros].nombre = ptr_nombreUsuario;
        regPrestamos[numRegistros].libro = new struct LibroPrestado[7];
        regPrestamos[numRegistros].cantidadDeLibros = 0;
        asignarLibros(regPrestamos[numRegistros],archRegistros);
        numRegistros++;
    }
}

void asignarLibros(struct RegPrestamo &regPrestamos,ifstream &archRegistros){
    char *ptr_libro,c;
    int dia,mes,anio;
    while(true){
        ptr_libro = leerCadenaExacta(archRegistros);
        archRegistros>>dia>>c>>mes>>c>>anio;
        regPrestamos.libro[regPrestamos.cantidadDeLibros].codigo=ptr_libro;
        regPrestamos.libro[regPrestamos.cantidadDeLibros].fecha=
                anio*10000+mes*100+dia;
        regPrestamos.cantidadDeLibros++;
        if(archRegistros.get()=='\n')break;
    }
}

void imprimeRegistrosPrestamos(struct RegPrestamo *regPrestamos,int &numRegistros){
    ofstream archReporte("DatosRegistros.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de DatosRegistros"<<endl;
        exit(1);
    }
    
    for(int i=0;i<numRegistros;i++){
        archReporte<<regPrestamos[i].codigo<<' '<<regPrestamos[i].nombre<<endl;
        for(int k=0;k<regPrestamos[i].cantidadDeLibros;k++)
            archReporte<<' '<<regPrestamos[i].libro[k].codigo<<' '
                    <<regPrestamos[i].libro[k].fecha<<endl;
    }
}

void emiteReporteAtencionPrestamos(struct Libro *libros,int numLibros,
        struct RegPrestamo *regPrestamos,int numRegistros){
    ifstream archSolicitudes("SolicitudesDePrestamos.csv",ios::in);
    if(not archSolicitudes.is_open()){
        cout<<"ERROR al abrir el archivo de solicitudes"<<endl;
        exit(1);
    }
    ofstream archReporte("ReporteSolicitudesAtendidas.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ReporteSolicitudesAtendidas"<<endl;
        exit(1);
    }
    int fechaProceso,fechaLimite,dia,mes,anio,codigo,posUsuario,posLibro;
    char c,*ptr_usuario,codLibro[8],*ptr_libro;
    archSolicitudes>>dia>>c>>mes>>c>>anio;
    fechaProceso = anio*10000+mes*100+dia;
    archSolicitudes>>dia>>c>>mes>>c>>anio;
    fechaLimite = anio*10000+mes*100+dia;
    archReporte<<setw(50)<<' '<<"BIBLIOTECA CENTRAL"<<endl;
    archReporte<<"CODIGO"<<setw(12)<<' '<<"NOMBRE"<<setw(44)<<' '<<"COD. "
            "DE LIBRO"<<setw(9)<<' '<<"TITULO"<<setw(50)<<' '<<"OBSERVACION"
            <<endl;
    while(true){
        archSolicitudes>>codigo;
        if(archSolicitudes.eof())break;
        archSolicitudes.get();
        ptr_usuario = leerCadenaExacta(archSolicitudes);
        archSolicitudes.getline(codLibro,8);
        ptr_libro = new char[strlen(codLibro)+1];
        strcpy(ptr_libro,codLibro);
        analizaSolicitudes(codigo,ptr_usuario,ptr_libro,fechaLimite,fechaProceso,libros,numLibros,
                regPrestamos,numRegistros,archReporte);
    }
}

void analizaSolicitudes(int codigo,char *ptr_usuario,char *ptr_libro,int fechaLimite,int fechaProceso,
        struct Libro *libros,int numLibros,struct RegPrestamo *regPrestamos,
        int numRegistros,ofstream &archReporte){
    int posUsuario,posLibro,cantLibros;
    posUsuario = buscarUsuario(regPrestamos,codigo,numRegistros);
    if(posUsuario!=NO_ENCONTRADO){
        archReporte<<regPrestamos[posUsuario].codigo<<setw(10)<<' '
                <<left<<setw(50)<<regPrestamos[posUsuario].nombre<<right;
        posLibro= buscarLibro(libros,ptr_libro,numLibros);
        if(posLibro!=NO_ENCONTRADO){
            archReporte<<libros[posLibro].codigo<<setw(15)<<' '
                    <<left<<setw(50)<<libros[posLibro].titulo<<right;
            if(libros[posLibro].cantidad>0){                   
                if(regPrestamos[posUsuario].cantidadDeLibros<7){
                    cantLibros = contarLibros(fechaLimite,regPrestamos[posUsuario]);
                    if(cantLibros!=-1){
                        libros[posLibro].cantidad--;
                        libros[posLibro].prestamos++;
                        regPrestamos[posUsuario].libro[regPrestamos[posUsuario]
                                .cantidadDeLibros].codigo=libros[posLibro].codigo;
                        regPrestamos[posUsuario].libro[regPrestamos[posUsuario].
                                cantidadDeLibros].fecha=fechaProceso;
                        regPrestamos[posUsuario].cantidadDeLibros++;
                        archReporte<<"Se entrego libro"<<endl;
                     }else archReporte<<"Supero fecha limite"<<endl;
                }else archReporte<<"Supero el limite de prestamos"<<endl;
            }else archReporte<<"No hay libro disponible"<<endl;
        }else{
            archReporte<<libros[posLibro].codigo<<setw(15)<<' '
                    <<left<<setw(50)<<libros[posLibro].titulo<<right
                    <<"No existe el libro"<<endl;
        }
    }else{
        archReporte<<codigo<<setw(10)<<' '<<left<<setw(50)<<ptr_usuario
                <<right<<ptr_libro<<setw(15)<<' ';
        posLibro=buscarLibro(libros,ptr_libro,numLibros);
        if(posLibro!=NO_ENCONTRADO){
            archReporte<<left<<setw(50)<<libros[posLibro].titulo
                    <<"Se entrego el libro"<<endl;
        }else archReporte<<"No existe libro"<<endl;
    }
}

int contarLibros(int fechaLimite, struct RegPrestamo &regPrestamos){
    int cantLibros=0;
    for(int i=0;i<regPrestamos.cantidadDeLibros;i++){
        if(regPrestamos.libro[i].fecha>=fechaLimite) cantLibros++;
        else return -1;  
    }
    return cantLibros;
}

int buscarLibro(struct Libro *libros,char *ptr_libro,int numLibros){
    for(int i=0;i<numLibros;i++)
        if(strcmp(libros[i].codigo,ptr_libro)==0)return i;
    return NO_ENCONTRADO;
}

int buscarUsuario(struct RegPrestamo *regPrestamos,int codigo,int numRegistros){
    for(int i=0;i<numRegistros;i++)
        if(regPrestamos[i].codigo==codigo)return i;
    return NO_ENCONTRADO;
}

char *leerCadenaExacta(ifstream &archivo){
    char buffer[500],*cadena;
    int longitud;
    
    archivo.getline(buffer,500,',');
    if(archivo.eof())return nullptr;
    
    longitud = strlen(buffer);
    cadena = new char[longitud+1];
    strcpy(cadena,buffer);
    
    return cadena;
}
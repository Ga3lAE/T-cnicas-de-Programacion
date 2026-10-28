/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#define NO_ENCONTRADO -1
#include "LibroPrestado.h"
#include "Libros.h"
#include "Registros.h"
#include "funciones.h"

void crearLibrosBin(const char *nombArchCsv, const char *nombArchBin){
    ifstream archLibros(nombArchCsv,ios::in);
    if(not archLibros.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archLibrosBin(nombArchBin,ios::out | ios::binary);
    if(not archLibrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    int anio,cantidad,prestamos;
    char codigo[8],titulo[60],autor[60];
    
    struct Libro libro;
    while(true){
        archLibros.getline(codigo,8,',');
        if(archLibros.eof())break;
        archLibros.getline(titulo,60,',');
        archLibros.getline(autor,60,',');
        archLibros>>anio;
        archLibros.get();
        archLibros>>cantidad;
        archLibros.get();
        archLibros>>prestamos;
        archLibros.get();
        strcpy(libro.codigo,codigo);
        strcpy(libro.titulo,titulo);
        strcpy(libro.autor,autor);
        libro.aPublicacion=anio;
        libro.cantidad=cantidad;
        libro.prestamos=prestamos;
        archLibrosBin.write(reinterpret_cast<const char*>(&libro),sizeof(Libro));
    }
}

void mostrarLibrosBin(const char *nombArchBin, const char *nombArchTxt){
    
    ifstream archLibrosBin(nombArchBin,ios::in | ios::binary);
    if(not archLibrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    struct Libro libro;
    while(true){
        archLibrosBin.read(reinterpret_cast<char *>(&libro),sizeof(Libro));
        if(archLibrosBin.eof())break;
        archReporte<<libro.codigo<<' '<<libro.titulo<<' '<<libro.autor
                <<' '<<libro.aPublicacion<<' '<<libro.cantidad<<' '
                <<libro.prestamos<<endl;
    }
}

void crearRegistrosBin(const char *nombArchCsv, const char *nombArchBin){
    
    ifstream archRegistros(nombArchCsv,ios::in);
    if(not archRegistros.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archRegistrosBin(nombArchBin,ios::out | ios::binary);
    if(not archRegistrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    int codigo,dia,mes,anio;
    char nombre[60],codLibro[8],c;
    struct Registros registro;
    while(true){
        archRegistros>>codigo;
        if(archRegistros.eof())break;
        archRegistros.get();
        archRegistros.getline(nombre,60,',');
        registro.codigo=codigo;
        strcpy(registro.nombre,nombre);
        registro.cantidadDeLibros=0;
        while(true){
            archRegistros.getline(codLibro,8,',');
            archRegistros>>dia>>c>>mes>>c>>anio;
            strcpy(registro.libro[registro.cantidadDeLibros].codigo,codLibro);
            registro.libro[registro.cantidadDeLibros].fecha=
                    anio*10000+mes*100+dia;
            registro.cantidadDeLibros++;
            if(archRegistros.get()=='\n')break;
        }
        archRegistrosBin.write(reinterpret_cast<const char*>(&registro),
                sizeof(Registros));
    }   
}

void mostrarRegistrosBin(const char *nombArchBin,const char *nombArchTxt){
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    ifstream archRegistrosBin(nombArchBin,ios::in | ios::binary);
    if(not archRegistrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    struct Registros registro;
    while(true){
        archRegistrosBin.read(reinterpret_cast<char *>(&registro),
                sizeof(Registros));
        if(archRegistrosBin.eof())break;
        archReporte<<registro.codigo<<' '<<registro.nombre<<endl;
        for(int i=0;i<registro.cantidadDeLibros;i++)
            archReporte<<registro.libro[i].codigo<<' '<<
                    registro.libro[i].fecha<<endl;
    }
}

void actualizarSolicitudes(const char *nombArchCsv,const char *nomLibrosBin,
        const char *nomRegiBin,const char *nombArchTxt){
    
    ifstream archSolicitudes(nombArchCsv,ios::in);
    if(not archSolicitudes.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    fstream archLibrosBin(nomLibrosBin,ios::in | ios::out | ios::binary);
    if(not archLibrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nomLibrosBin<<endl;
        exit(1);
    }
    
    fstream archRegistrosBin(nomRegiBin,ios::in | ios::out |ios::binary);
    if(not archRegistrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nomRegiBin<<endl;
        exit(1);
    }
    
    leeImprimeRegistrosActualizados(archSolicitudes,archLibrosBin,
            archRegistrosBin,archReporte);
}

void leeImprimeRegistrosActualizados(ifstream &archSolicitudes,
        fstream &archLibrosBin,fstream &archRegistrosBin,ofstream &archReporte){
    int fechaLimite,fechaProcesar,dni,posLibro,posUsuario,superaFecha;
    char nombre[60],codLibro[8];
    leeImprimeEncabezado(fechaProcesar,fechaLimite,archSolicitudes,archReporte);
    struct Libro libro;
    struct Registros registro;
    int tamRegLibros=sizeof(struct Libro);
    int tamRegPrestamos=sizeof(struct Registros);
    while(true){
        archSolicitudes>>dni;
        if(archSolicitudes.eof())break;
        archSolicitudes.get();
        archSolicitudes.getline(nombre,60,',');
        archSolicitudes.getline(codLibro,8);
        posLibro = buscarPosicion(archLibrosBin,codLibro);
        if(posLibro!=NO_ENCONTRADO){
            archLibrosBin.seekg(posLibro*tamRegLibros,ios::beg);
            archLibrosBin.read(reinterpret_cast<char*>(&libro),tamRegLibros);
            if(libro.cantidad>0){
                posUsuario = buscarUsuario(archRegistrosBin,dni);
                if(posUsuario!=NO_ENCONTRADO){
                    archRegistrosBin.seekg(posUsuario*tamRegPrestamos,ios::beg);
                    archRegistrosBin.read(reinterpret_cast<char*>(&registro),tamRegPrestamos);
                    if(registro.cantidadDeLibros<7){
                        superaFecha=verificaLibros(registro,registro.cantidadDeLibros,fechaLimite);
                        if(!superaFecha){
                            actualizarArchivos(registro,codLibro,fechaProcesar,
                                    posUsuario,libro,posLibro,tamRegLibros,tamRegPrestamos,
                                    archLibrosBin,archRegistrosBin,archReporte);
                        }else imprimeObservacion(dni,nombre,libro.titulo,codLibro,
                                4,archReporte);                          
                    }else imprimeObservacion(dni,nombre,libro.titulo,codLibro,3,
                            archReporte);
                }else //Si no se encuentra en los registros
                    asignarNuevoRegistro(registro,dni,nombre,codLibro,
                            fechaProcesar,libro,posLibro,tamRegLibros,tamRegPrestamos,
                            archRegistrosBin,archLibrosBin,archReporte);
            }else imprimeObservacion(dni,nombre,libro.titulo,codLibro,2,archReporte);
        }else imprimeObservacion(dni,nombre,"NN",codLibro,1,archReporte);
    }
}

void actualizarArchivos(struct Registros &registro,char *codLibro,int fechaProcesar,
        int posUsuario,struct Libro &libro,int posLibro,int tamRegLibros,
        int tamRegPrestamos,fstream &archLibrosBin,fstream &archRegistrosBin,
        ofstream &archReporte){
    strcpy(registro.libro[registro.cantidadDeLibros].codigo,
            codLibro);
    registro.libro[registro.cantidadDeLibros].fecha=fechaProcesar;
    registro.cantidadDeLibros++;
    libro.cantidad--;
    libro.prestamos++;
    archLibrosBin.seekg(posLibro*tamRegLibros,ios::beg);
    archLibrosBin.write(reinterpret_cast<const char*>
    (&libro),tamRegLibros);
    archRegistrosBin.seekg(posUsuario*tamRegPrestamos,ios::beg);
    archRegistrosBin.write(reinterpret_cast <const char*>
            (&registro),tamRegPrestamos);
    imprimeObservacion(registro.codigo,registro.nombre,libro.titulo,codLibro,
            5,archReporte);
}

void asignarNuevoRegistro(struct Registros &registro,int dni,char *nombre,
        char *codLibro,int fechaProcesar,struct Libro &libro,int posLibro,
        int tamRegLibros,int tamRegPrestamos,fstream &archRegistrosBin,
        fstream &archLibrosBin,ofstream &archReporte){
    archRegistrosBin.seekg(0,ios::end);
    registro.codigo = dni;
    strcpy(registro.nombre,nombre);
    registro.cantidadDeLibros=0;
    strcpy(registro.libro[registro.cantidadDeLibros].codigo,
            codLibro);
    registro.libro[registro.cantidadDeLibros].fecha = fechaProcesar;
    registro.cantidadDeLibros++;
    archReporte<<dni<<setw(8)<<' '<<left<<setw(46)<<nombre
        <<codLibro<<setw(16)<<' '<<setw(42)<<libro.titulo
            <<"Se le entrego el libro"<<endl;
    libro.cantidad--;
    libro.prestamos++;
    archLibrosBin.seekg(posLibro*tamRegLibros,ios::beg);
    archLibrosBin.write(reinterpret_cast<const char*>(&libro),tamRegLibros);
    archRegistrosBin.write(reinterpret_cast<const char*>(&registro),tamRegPrestamos);
}

int verificaLibros(struct Registros &registro, int cantidad, int fecha){
    
    for(int i=0;i<cantidad;i++)
        if(registro.libro[i].fecha>fecha) return 1;
    return 0;
}

void imprimeObservacion(int dni,char *nombre,const char *nomLibro,char *codLibro,
        int observacion,ofstream &archReporte){
    archReporte<<dni<<setw(8)<<' '<<left<<setw(46)<<nombre
                        <<codLibro<<setw(16)<<' '<<setw(42)<<nomLibro;
    if(observacion==1)archReporte<<"No existe el libro"<<endl;
    else if(observacion==2)archReporte<<"No hay libro disponible"<<endl;
    else if(observacion==3)archReporte<<"Supero el limite de prestamos"<<endl;
    else if(observacion==4)archReporte<<"Supero fecha limite"<<endl;
    else if(observacion==5)archReporte<<"Se entrego el libro"<<endl;
}

int buscarUsuario(fstream &archRegistrosBin,int dni){
    struct Registros registro;
    int tamReg = sizeof(struct Registros);
    int tamArch,numReg;
    datosArchivos(archRegistrosBin,tamReg,tamArch,numReg);
    for(int i=0;i<numReg;i++){
        archRegistrosBin.read(reinterpret_cast<char *>(&registro),tamReg);
        if(registro.codigo == dni) return i;
    }
    return NO_ENCONTRADO;
}

int buscarPosicion(fstream &archLibrosBin,char *codiLibro){
    
    struct Libro libroAux;
    int tamReg = sizeof(struct Libro);
    int tamArch,numReg;
    datosArchivos(archLibrosBin,tamReg,tamArch,numReg);
    for(int i=0;i<numReg;i++){
        archLibrosBin.read(reinterpret_cast<char *>(&libroAux),tamReg);
        if(strcmp(libroAux.codigo,codiLibro)==0) return i;
    }
    return NO_ENCONTRADO;
}

void leeImprimeEncabezado(int &fechaProcesar,int &fechaLimite,ifstream &archSolicitudes,
        ofstream &archReporte){
    int dia,mes,anio;
    char c;
    archSolicitudes>>dia>>c>>mes>>c>>anio;
    archReporte<<setw(50)<<' '<<"BIBLIOTECA CENTRAL"<<setw(10)<<' '
            <<setw(2)<<dia<<'/'<<setw(2)<<mes<<'/'<<setw(4)<<anio<<endl;
    fechaProcesar=anio*10000+mes*100+dia;
    archSolicitudes>>dia>>c>>mes>>c>>anio;
    fechaLimite=anio*10000+mes*100+dia;
    archReporte<<"CODIGO"<<setw(10)<<' '<<"NOMBRE"<<setw(40)<<' '
            <<"COD. DE LIBRO"<<setw(10)<<' '<<"TITULO"<<setw(40)<<' '
            <<"OBSERVACION"<<endl;
}

void datosArchivos(fstream &archLibrosBin,int tamReg,int &tamArch, int &numReg){
    
    archLibrosBin.seekg(0,ios::end);
    tamArch = archLibrosBin.tellg();
    archLibrosBin.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}
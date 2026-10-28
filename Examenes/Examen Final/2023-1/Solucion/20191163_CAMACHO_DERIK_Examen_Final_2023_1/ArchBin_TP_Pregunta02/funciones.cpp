/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/*
 * 
 * Nombre: Derik Camacho Pastor 
 * Codigo: 20191163 
 
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "StructLibrosEnSuPoder.h"
#include "StructUsuario.h"
#include "StructUsuariosConElLibro.h"
#include "StructLibro.h"
#include "funciones.h"

/*Creacion del archivo binario de libros*/
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
    
    /*Modulo encargado de leer los datos del archivo csv*/
    leerDatosArchivo(archLibrosBin,archLibros);
}

void leerDatosArchivo(ofstream &archLibrosBin, ifstream &archLibros){
    struct Libro libro;
    int tamReg = sizeof(struct Libro);
    char codLibro[8],titulo[60],autor[60],c;
    int cantidadVolumenes,dni,dia,mes,anio;
    double precio;
    while(true){
        archLibros.getline(codLibro,8,',');
        if(archLibros.eof())break;
        archLibros.getline(titulo,60,',');
        archLibros.getline(autor,60,',');
        archLibros>>cantidadVolumenes>>c;
        archLibros>>precio>>c;        
        strcpy(libro.codigo,codLibro);
        strcpy(libro.titulo,titulo);
        strcpy(libro.autor,autor);
        libro.cantidadDeLibros = cantidadVolumenes;
        libro.precio = precio;
        libro.cantUsuarios=0;       
        while(true){
            archLibros>>dni>>c;
            archLibros>>dia>>c>>mes>>c>>anio;
            libro.usuarios[libro.cantUsuarios].dni = dni;
            libro.usuarios[libro.cantUsuarios].fechaDeDevolucion=
                    anio*10000+mes*100+dia;
            libro.cantUsuarios++;
            if(archLibros.get()=='\n')break;
        }
        archLibrosBin.write(reinterpret_cast<const char*>(&libro),tamReg);
    }
}
/*Impresion de los datos del archivo binario libros.bin*/
void mostrarLibrosBin(const char *nombArchBin, const char *nombArchTxt){ 
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }   
    ifstream archLibrosBin(nombArchBin,ios::in | ios::binary);
    if(not archLibrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    } 
    struct Libro libro;
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimeEncabezadosLibros(archReporte);
    while(true){
        archLibrosBin.read(reinterpret_cast<char *>(&libro),sizeof(struct Libro));
        if(archLibrosBin.eof())break;
        archReporte<<libro.codigo<<setw(15)<<' '<<left<<setw(40)
                <<libro.titulo<<setw(30)<<libro.autor<<right<<setw(20)
                <<libro.cantidadDeLibros<<setw(25)<<libro.precio<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Usuarios con ejemplares: "<<libro.cantUsuarios<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"DNI Usuario"<<setw(10)<<' '<<"Fecha Maxima"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int i=0;i<libro.cantUsuarios;i++)
            archReporte<<libro.usuarios[i].dni<<setw(17)<<' '
                    <<libro.usuarios[i].fechaDeDevolucion<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}
/*creacion del archivo binario de usuarios*/
void crearUsuariosBin(const char *nombArchCsv,const char *nombArchBin){
    
    ifstream archUsuarios(nombArchCsv,ios::in);
    if(not archUsuarios.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archUsuariosBin(nombArchBin,ios::out | ios::binary);
    if(not archUsuariosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    /*Modulo encargado de leer los datos del archivo csv*/
    leerDatosUsuarios(archUsuariosBin,archUsuarios);
    
}

/*creacion del archivo binario de usuarios*/
void leerDatosUsuarios(ofstream &archUsuariosBin,ifstream &archUsuarios){   
    struct Usuario usuario;
    int dni;
    char nombreUsuario[60],codigoLibro[8],categoria,c;
    double calificacion;
    
    while(true){
        archUsuarios>>dni;
        if(archUsuarios.eof())break;
        archUsuarios>>c;
        archUsuarios.getline(nombreUsuario,60,',');
        archUsuarios>>categoria;
        archUsuarios>>c>>calificacion>>c;        
        usuario.dni = dni;
        strcpy(usuario.nombre,nombreUsuario);
        usuario.categoria = categoria;
        usuario.calificacion = calificacion;
        usuario.cantidadDeLibros =0;
        while(true){
            archUsuarios>>codigoLibro;
            strcpy(usuario.libros[usuario.cantidadDeLibros].codigoLibro,
                    codigoLibro);
            usuario.cantidadDeLibros++;
            if(archUsuarios.get()=='\n')break;
        }
        archUsuariosBin.write(reinterpret_cast<const char*>(&usuario),
                sizeof(struct Usuario));
    }
}

/*impresion del archivo binario de usuarios */
void mostrarUsuariosBin(const char *nombArchBin,const char *nombArchTxt){   
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }   
    ifstream archUsuariosBin(nombArchBin,ios::in | ios::binary);
    if(not archUsuariosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    struct Usuario usuario;  
    imprimeEncabezadoUsuarios(archReporte);
    while(true){
        archUsuariosBin.read(reinterpret_cast<char *>(&usuario),
                sizeof(struct Usuario));
        if(archUsuariosBin.eof())break;
        archReporte<<usuario.dni<<setw(10)<<' '<<left<<setw(50)
                <<usuario.nombre<<usuario.categoria<<right<<setw(25)
                <<usuario.calificacion<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Libros que han prestado: "<<usuario.cantidadDeLibros<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"Codigo de Libro"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<usuario.cantidadDeLibros;k++)
            archReporte<<usuario.libros[k].codigoLibro<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void modificarArchivosLibrosyUsuariosBin(const char *nombLibrosBin,
        const char *nombUsuariosBin,const char *nombArcTxt){
    fstream archLibros(nombLibrosBin,ios::in | ios::out | ios::binary);
    if(not archLibros.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombLibrosBin<<endl;
        exit(1);
    }
    fstream archUsuarios(nombUsuariosBin,ios::in | ios::out | ios::binary);
    if(not archUsuarios.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombUsuariosBin<<endl;
        exit(1);
    }
    ifstream archDevoluciones(nombArcTxt,ios::in);
    if(not archDevoluciones.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArcTxt<<endl;
        exit(1);
    }  
    int dni,dia,mes,anio;
    char codigoLibro[8],*ptr_codLibro,c;
    archDevoluciones>>dia>>c>>mes>>c>>anio;
    int fechaDevolucion = anio*10000+mes*100+dia;
    while(true){
        archDevoluciones>>dni;
        if(archDevoluciones.eof())break;
        archDevoluciones>>codigoLibro;
        ptr_codLibro = new char[strlen(codigoLibro)+1];
        strcpy(ptr_codLibro,codigoLibro);
        modificarArchivos(fechaDevolucion,dni,ptr_codLibro,archLibros,archUsuarios);
    }
}

void modificarArchivos(int fechaDevolucion,int dni,char *ptr_codLibro,
        fstream &archLibros,fstream &archUsuarios){
    struct Libro libro;
    struct Usuario usuario;
    int posLibro,posUsuario,posUsuarioEliminar,posLibroEliminar;
    int tamRegLibro = sizeof(struct Libro);
    int tamRegUsuario = sizeof(struct Usuario);
    posLibro = buscarLibro(ptr_codLibro,archLibros);
    posUsuario = buscarUsuario(dni,archUsuarios);
    if(posLibro!=NO_ENCONTRADO and posUsuario!=NO_ENCONTRADO){
        archLibros.seekg(posLibro*tamRegLibro,ios::beg);
        archLibros.read(reinterpret_cast<char *>(&libro),tamRegLibro);
        archUsuarios.seekg(posUsuario*tamRegUsuario,ios::beg);
        archUsuarios.read(reinterpret_cast<char *>(&usuario),tamRegUsuario);
        posLibroEliminar=buscarLibroDeUsuario(ptr_codLibro,usuario);
        posUsuarioEliminar=buscarUsuarioDeLibro(dni,libro);
        //posicionarnos 2 veces y leer 2 veces
        if(posUsuarioEliminar!=NO_ENCONTRADO and posLibroEliminar!=NO_ENCONTRADO){        
            if(fechaDevolucion>libro.usuarios[posUsuarioEliminar].fechaDeDevolucion){
                if(usuario.categoria == 'D'){
                    usuario.calificacion-=0.2*usuario.calificacion;
                }else if(usuario.categoria=='V'){
                    usuario.calificacion-=0.15*usuario.calificacion;
                }else if(usuario.categoria=='A'){
                    usuario.calificacion-=0.1*usuario.calificacion;
                }
                strcpy(usuario.libros[posLibroEliminar].codigoLibro,
                    usuario.libros[usuario.cantidadDeLibros-1].codigoLibro);
                usuario.cantidadDeLibros--;    
                libro.usuarios[posUsuarioEliminar].dni=
                    libro.usuarios[libro.cantUsuarios-1].dni;
                libro.usuarios[posUsuarioEliminar].fechaDeDevolucion=
                        libro.usuarios[libro.cantUsuarios-1].fechaDeDevolucion;
                libro.cantUsuarios--;
                archLibros.seekg(posLibro*tamRegLibro,ios::beg);
                archLibros.write(reinterpret_cast<const char*>(&libro),tamRegLibro);
                archUsuarios.seekg(posUsuario*tamRegUsuario,ios::beg);
                archUsuarios.write(reinterpret_cast<const char*>(&usuario),tamRegUsuario);
                archLibros.flush();
                archUsuarios.flush();
            }
        }
    } 
}


int buscarLibro(char *codigoLibro, fstream &archLibros){
    struct Libro libro;
    int tamReg =sizeof (struct Libro);
    int tamArch,numReg;
    datosArchivo(archLibros,tamReg,tamArch,numReg);
    for(int i=0;i<numReg;i++){
        archLibros.read(reinterpret_cast<char *>(&libro),tamReg);
        if(strcmp(libro.codigo,codigoLibro)==0)return i;
    }
    return NO_ENCONTRADO;
}

int buscarUsuarioDeLibro(int dni,struct Libro &libro){
    
    for(int i=0;i<libro.cantUsuarios;i++){
        
        if(libro.usuarios[i].dni==dni)return i;
    }
    return NO_ENCONTRADO;
}

int buscarUsuario(int dni,fstream &archUsuarios){
    struct Usuario usuario;
    int tamReg = sizeof(struct Usuario);
    int tamArch,numReg;
    datosArchivo(archUsuarios,tamReg,tamArch,numReg);
    for(int i=0;i<numReg;i++){
        archUsuarios.read(reinterpret_cast<char *>(&usuario),tamReg);
        if(usuario.dni==dni)return i;
    }
    return NO_ENCONTRADO;
}

int buscarLibroDeUsuario(char *codigLibro,struct Usuario &usuario){
    for(int i=0;i<usuario.cantidadDeLibros;i++){       
        if(strcmp(usuario.libros[i].codigoLibro,codigLibro)==0)return i;
    }
    return NO_ENCONTRADO;
}

void emiteReporteLibrosBin(const char *nombArchBin, const char *nombArchTxt){
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }   
    ifstream archLibrosBin(nombArchBin,ios::in | ios::binary);
    if(not archLibrosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    struct Libro libro;
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimeEncabezadosLibros(archReporte);
    while(true){
        archLibrosBin.read(reinterpret_cast<char *>(&libro),sizeof(struct Libro));
        if(archLibrosBin.eof())break;
        archReporte<<libro.codigo<<setw(15)<<' '<<left<<setw(40)
                <<libro.titulo<<setw(30)<<libro.autor<<right<<setw(20)
                <<libro.cantidadDeLibros<<setw(25)<<libro.precio<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Usuarios con ejemplares: "<<libro.cantUsuarios<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"DNI Usuario"<<setw(10)<<' '<<"Fecha Maxima"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int i=0;i<libro.cantUsuarios;i++)
            archReporte<<libro.usuarios[i].dni<<setw(17)<<' '
                    <<libro.usuarios[i].fechaDeDevolucion<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void emiteReporteUsuariosBin(const char *nombArchBin,const char *nombArchTxt){
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }   
    ifstream archUsuariosBin(nombArchBin,ios::in | ios::binary);
    if(not archUsuariosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    struct Usuario usuario;  
    imprimeEncabezadoUsuarios(archReporte);
    while(true){
        archUsuariosBin.read(reinterpret_cast<char *>(&usuario),
                sizeof(struct Usuario));
        if(archUsuariosBin.eof())break;
        archReporte<<usuario.dni<<setw(10)<<' '<<left<<setw(50)
                <<usuario.nombre<<usuario.categoria<<right<<setw(25)
                <<usuario.calificacion<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Libros que han prestado: "<<usuario.cantidadDeLibros<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"Codigo de Libro"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<usuario.cantidadDeLibros;k++)
            archReporte<<usuario.libros[k].codigoLibro<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void imprimeEncabezadoUsuarios(ofstream &archReporte){
    archReporte<<setw(50)<<' '<<"Datos Iniciales de Usuarios"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"DNI"<<setw(15)<<' '<<"Nombre"<<setw(40)<<' '<<"Categoria"
            <<setw(5)<<' '<<"Calificacion de Usuario"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}

void imprimeEncabezadosLibros(ofstream &archReporte){
    archReporte<<setw(50)<<' '<<"Datos Iniciales de Libros"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"CODIGO LIBRO"<<setw(10)<<' '<<"TITULO"<<setw(34)<<' '
            <<"AUTOR"<<setw(35)<<' '<<"CANTIDAD VOLUMENES"<<setw(11)<<' '
            <<"PRECIO"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}

void datosArchivo(fstream &arch,int tamReg, int &tamArch,int &numReg){
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    arch.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

void imprimeLinea(char caracter, int cantidad ,ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}
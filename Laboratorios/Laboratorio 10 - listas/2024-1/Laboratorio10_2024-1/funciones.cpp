#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Cliente.h"
#include "Fecha.h"
#include "Libro.h"
#include "Venta.h"
#include "funciones.h"

#define NO_ECNONTRADO -1

#define ALING 5
#define MAX_CAR_LIN 200
#define CAR_COD 10
#define MAX_VENTAS 10

#define MAX_CAR_COD 10
#define MAX_CAR_TITULO 60
#define MAX_CAR_NOMBRE 60
#define MAX_CAR_PRECIO 30
#define MAX_CAR_CANT 20
#define MAX_CAR_RANK 15
#define MAX_CAR_CONT 5
#define MAX_CAR_FECHA 15
#define MAX_CAR_DNI 10

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

void leeClientes(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    while(true){
        // 54393647,Reyes Tang Edward
        int nDNI;
        char nombre [MAX_NOMBRE_CLIENTE];
        archivoCsv>>nDNI;
        if(archivoCsv.eof()) break;
        archivoCsv.get();
        archivoCsv.getline(nombre, MAX_NOMBRE_CLIENTE, '\n');
        
        struct Cliente cliente;
        cliente.nDNI = nDNI;
        strcpy(cliente.nombre, nombre);
        
        archivoBin.write(reinterpret_cast<const char*>(&cliente), sizeof(cliente));
    }
}
void leeLibros(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    while(true){
        // YDK7687,El otonio del patriarca,Gabriel Garcia Marquez,368.04
        char codigo[MAX_CODIGO_LIBRO], titulo[MAX_TITULO_LIBRO], autor[MAX_AUTOR_LIBRO];        
        double precio;
        
        archivoCsv.getline(codigo, MAX_CODIGO_LIBRO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv.getline(titulo, MAX_TITULO_LIBRO, ',');
        archivoCsv.getline(autor, MAX_AUTOR_LIBRO, ',');
        archivoCsv>>precio;
        archivoCsv.get();
        
        struct Libro libro;
        
        strcpy(libro.codigo, codigo);
        strcpy(libro.titulo, titulo);
        strcpy(libro.autor, autor);
        libro.precio = precio;
        libro.ventas = new struct Venta[10]{};
        libro.librosVendidos=0;
        libro.fechaMasReciente.fecha= libro.fechaMasReciente.dd 
                = libro.fechaMasReciente.mm = libro.fechaMasReciente.aa = 0;
        libro.sumaCalificaciones = 0;
        libro.ranking = 0;
        
        archivoBin.write(reinterpret_cast<const char*>(&libro), sizeof(libro));                
    }
}

void leeVentas(const char* nombreArchivoCsv, const char* nombreArchivoLibros, 
        const char* nombreArchivoClientes){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoCsv;
        exit(1);
    }
    fstream archivoLibros(nombreArchivoLibros, ios::in|ios::out|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLibros;
        exit(1);
    }
    ifstream archivoClientes(nombreArchivoClientes, ios::in|ios::binary);
    if(not archivoClientes.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoClientes;
        exit(1);
    }
    
    while(true){
        //CRY6839,34460612,15/10/2023,93
        char codigo[MAX_CODIGO_LIBRO], descC;
        int nDNICompra, calificacionCompra;
        struct Fecha fechaCompra;
        
        archivoCsv.getline(codigo, MAX_CODIGO_LIBRO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv>>nDNICompra>>descC>>fechaCompra.dd>>descC>>fechaCompra.mm
                >>descC>>fechaCompra.aa>>descC>>calificacionCompra;
        fechaCompra.fecha = fechaCompra.dd 
                +100*fechaCompra.dd +10000*fechaCompra.dd;
        archivoCsv.get();
        
        int tamArchivo, tamLibro, cantidadLibros;
        tamLibro = sizeof(struct Libro);
        datosArchivoF(tamArchivo, tamLibro, cantidadLibros, archivoLibros);
        
        int posLibro;
        posLibro = buscaLibro(codigo, archivoLibros, cantidadLibros);
        if(posLibro != NO_ECNONTRADO){
            struct Libro libro;                                  
            archivoLibros.seekg(posLibro*tamLibro, ios::beg);
            archivoLibros.read(reinterpret_cast<char*>(&libro), sizeof(struct Libro));
            int posVenta = libro.librosVendidos;
            
            libro.sumaCalificaciones+=calificacionCompra;
            
            libro.ventas[posVenta].calificacion = calificacionCompra;
            libro.ventas[posVenta].fecha = fechaCompra;
            libro.ventas[posVenta].nDNI = nDNICompra;
            asignaNombreSegunDni(libro.ventas[posVenta].nombre, nDNICompra, archivoClientes);
            if(libro.ventas[posVenta].fecha.fecha > libro.fechaMasReciente.fecha)
                libro.fechaMasReciente = libro.ventas[posVenta].fecha;
            
            libro.librosVendidos++;
            
            archivoLibros.seekg(posLibro*tamLibro, ios::beg);
            archivoLibros.write(reinterpret_cast<const char*>(&libro), tamLibro);            
        }
        
    }
}
int buscaLibro(char* codigo, fstream& archivo, int cantidad){
    struct Libro libro;
    int tamDato = sizeof(struct Libro);
    for (int i = 0; i < cantidad; i++){
        archivo.seekg(i*tamDato, ios::beg);
        archivo.read(reinterpret_cast<char*>(&libro), sizeof(struct Libro));
        if(strcmp(codigo, libro.codigo)==0)  return i;
    }
    return NO_ECNONTRADO;
        

}
void asignaNombreSegunDni(char* nombre, int dni, ifstream& archivo){
    int posCliente;
    struct Cliente cliente;
    int tamArchivo, tamDato, cantidad;
    tamDato = sizeof(struct Cliente);
    datosArchivoIn(tamArchivo, tamDato, cantidad, archivo);
    posCliente = buscaCliente(dni, archivo, cantidad);
    
    archivo.seekg(posCliente*tamDato, ios::beg);
    archivo.read(reinterpret_cast<char*>(&cliente), sizeof(cliente));
    
    strcpy(nombre, cliente.nombre);

    
}
int buscaCliente(int nDNI, ifstream& archivo, int cantidad){
    struct Cliente cliente;
    int tamDato = sizeof(struct Cliente);
    for (int i = 0; i < cantidad; i++){
        archivo.seekg(i*tamDato, ios::beg);
        archivo.read(reinterpret_cast<char*>(&cliente), sizeof(struct Cliente));
        if(nDNI - cliente.nDNI==0)  return i;
    }
    return NO_ECNONTRADO;        
}

void asignaRankings(const char* nombreArchivoLibros){
    fstream archivoLibros(nombreArchivoLibros, ios::in|ios::out|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLibros;
        exit(1);
    }
    
    int tamArchivo, tamLibro, cantidadLibros;
    tamLibro = sizeof(struct Libro);
    datosArchivoF(tamArchivo, tamLibro, cantidadLibros, archivoLibros);
    
    for (int i = 0; i < cantidadLibros; i++) {      
        struct Libro libro;
        archivoLibros.seekg(i*tamLibro, ios::beg);
        archivoLibros.read(reinterpret_cast<char*>(&libro), sizeof(libro));
        
        if(libro.librosVendidos == 0) libro.ranking = 0;
        else{
            double promedio = libro.sumaCalificaciones/libro.librosVendidos;
            if(promedio <25) libro.ranking = 1;
            if(promedio <50) libro.ranking = 2;
            if(promedio <75) libro.ranking = 3;
            else libro.ranking = 4;
        }
        archivoLibros.seekg(i*tamLibro, ios::beg);
        archivoLibros.write(reinterpret_cast<const char*>(&libro), sizeof(libro));
    }

    
}
void oredenaLibros(const char* nombreArchivoLibros){
    fstream archivoLibros(nombreArchivoLibros, ios::in|ios::out|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLibros;
        exit(1);
    }
    
    int tamArchivo, tamLibro, cantidadLibros;
    tamLibro = sizeof(struct Libro);
    datosArchivoF(tamArchivo, tamLibro, cantidadLibros, archivoLibros);
    
    for (int i = 0; i < cantidadLibros-1; i++) {        
        for (int j = i+1; j < cantidadLibros-1; j++) {            
            struct Libro libroP, libroS;
            archivoLibros.seekg(i*tamLibro, ios::beg);
            archivoLibros.read(reinterpret_cast<char*>(&libroP), tamLibro);
            archivoLibros.seekg(j*tamLibro, ios::beg);
            archivoLibros.read(reinterpret_cast<char*>(&libroS), tamLibro);
            
            if(libroP.ranking < libroS.ranking
                    or
                libroP.ranking == libroS.ranking
                        and                     
                    libroP.fechaMasReciente.fecha > libroS.fechaMasReciente.fecha){
                archivoLibros.seekg(j*tamLibro, ios::beg);
                archivoLibros.write(reinterpret_cast<char*>(&libroP), tamLibro);
                archivoLibros.seekg(i*tamLibro, ios::beg);
                archivoLibros.write(reinterpret_cast<char*>(&libroS), tamLibro);
                
            }
        }
    }
    
    for (int i = 0; i < cantidadLibros; i++) {        
        
    }

}

void emiteReporte(const char* nombreArchivoReporte, const char* nombreArchivoLibros){
    ifstream archivoLibros(nombreArchivoLibros, ios::in|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLibros;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    
    int tamArchivo, tamLibro, cantidadLibros;
    tamLibro = sizeof(struct Libro);
    datosArchivoIn(tamArchivo, tamLibro, cantidadLibros, archivoLibros);
    
    archivoReporte<<right
            <<setw(MAX_CAR_LIN/2-5)<<"LIBRERIA VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"RESULTADO DE VENTAS REALIZADAS"<<endl
            <<left;
    for (int i = 0; i < cantidadLibros; i++) {
        struct Libro libro;
        archivoLibros.read(reinterpret_cast<char*>(&libro), tamLibro);
        
        
        imprimeLinea('=', archivoReporte);
        imprimeEncabezadoLibros(archivoReporte, i, libro);
        imprimeLinea('-', archivoReporte);
        
        archivoReporte<<setw(ALING)<<" "<<"VENTAS REALIZADAS:"<<endl;                
        if(libro.librosVendidos == 0)
            archivoReporte<<setw(ALING)<<" "<<"NO SE VENDIO ESTE LIBRO"<<endl;
        else{
            imprimeEncabezadoVentas(archivoReporte);
            for (int j = 0; j < libro.librosVendidos; j++) {
                archivoReporte<<setw(ALING)<<" "
                    <<setfill('0')<<right<<setw(2)<<j+1<<left<<setfill(' ')
                    <<setw(MAX_CAR_CONT-2)<<" "
                    <<setw(MAX_CAR_DNI)<<libro.ventas[j].nDNI
                    <<setw(MAX_NOMBRE_CLIENTE)<<libro.ventas[j].nombre
                    <<setw(MAX_CAR_RANK)<<libro.ventas[j].calificacion;
                imprimeFecha(libro.ventas[j].fecha, archivoReporte);
                archivoReporte<<endl;
            }
            imprimeLinea('-', archivoReporte);
            archivoReporte<<setw(ALING)<<" "
                    <<"FECHA MAS RECIENTE: ";
            imprimeFecha(libro.fechaMasReciente, archivoReporte);
            archivoReporte<<endl;
        }
    }    
}
void datosArchivoF(int& tamArchivo, int tamDato, int& cantidad, fstream& archivo){
    archivo.seekg(0, ios::end);
    tamArchivo = archivo.tellg();
    cantidad = tamArchivo/ tamDato;    
    archivo.seekg(0, ios::beg);    
}
void datosArchivoIn(int& tamArchivo, int tamDato, int& cantidad, ifstream& archivo){
    archivo.seekg(0, ios::end);
    tamArchivo = archivo.tellg();
    cantidad = tamArchivo/ tamDato;    
    archivo.seekg(0, ios::beg);
}
void imprimeEncabezadoLibros(ofstream& archivoReporte, int cont, struct Libro libro){
    archivoReporte<<"LIBRO No. "
            <<setfill('0')<<right
            <<setw(3)<<cont+1
            <<setfill(' ')<<left<<endl;
    archivoReporte<<setw(ALING)<<" "
            <<setw(MAX_CODIGO_LIBRO)<<"CODIGO"
            <<setw(MAX_TITULO_LIBRO)<<"TITULO"
            <<setw(MAX_AUTOR_LIBRO)<<"AUTOR"
            <<setw(MAX_CAR_PRECIO)<<"PRECIO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD VENDIDA"
            <<setw(MAX_CAR_RANK)<<"RANKING"
            <<endl;
    archivoReporte<<setw(ALING)<<" "<<fixed<<setprecision(2)
            <<setw(MAX_CODIGO_LIBRO)<<libro.codigo
            <<setw(MAX_TITULO_LIBRO)<<libro.titulo
            <<setw(MAX_AUTOR_LIBRO)<<libro.autor
            <<setw(MAX_CAR_PRECIO)<<libro.precio
            <<setw(MAX_CAR_CANT)<<libro.librosVendidos
            <<setw(MAX_CAR_RANK)<<libro.ranking
            <<endl;
}
void imprimeEncabezadoVentas(ofstream& archivoReporte){
    archivoReporte<<setw(ALING)<<" "
            <<setw(MAX_CAR_CONT)<<"NO."
            <<setw(MAX_CAR_DNI)<<"DNI"
            <<setw(MAX_NOMBRE_CLIENTE)<<"NOMBRE"
            <<setw(MAX_CAR_RANK)<<"CALIFICACION"
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<endl;            
}
void imprimeFecha(struct Fecha fecha, ofstream& archivo){
    archivo<<setfill('0')<<right
            <<setw(2)<<fecha.dd<<'/'
            <<setw(2)<<fecha.mm<<'/'
            <<setw(4)<<fecha.aa
            <<setfill(' ')<<left
            <<setw(MAX_CAR_FECHA-10)<<" ";
}
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <math.h>

using namespace std;

#include "Cliente.h"
#include "Libreria.h"
#include "Libro.h"
#include "Venta.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define ALING 5
#define MAX_CAR_LIN 200
#define MAX_CAR_COD 10
#define MAX_CAR_NOMBRE 60
#define MAX_CAR_AUTOR 30
#define MAX_CAR_DESC 10
#define MAX_CAR_DINERO 15
#define MAX_CAR_CANT 15
#define MAX_CAR_CALIFICA 20
#define MAX_CAR_CONT 10
#define MAX_CAR_FECHA 12

#define MINIMA_BUENA_CALIFICACION 50

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {       
        archivo<<c;
    }
    archivo<<endl;
}
int datosArchivoIf(int tamElem, ifstream& archivo){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch/tamElem;
}
int datosArchivoF(int tamElem, fstream& archivo){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch/tamElem;
}

void leeClientes(const char* nombreArchivoDatos,
        const char* nombreArchivoBin){
    ifstream archivoDatos(nombreArchivoDatos, ios::in);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoDatos;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    /*
    int dni;
    char* nombre;
    double montoComprado;
    double descuentoFuturo;
     */
    struct Cliente cliente;
    while(true){
        // 054393647,Reyes Tang Edward
        archivoDatos>>cliente.dni;
        if(archivoDatos.eof()) break;
        archivoDatos.get();
        archivoDatos.getline(cliente.nombre, MAX_CLIENTE_NOMBRE, '\n');
        cliente.montoComprado=0;
        cliente.descuentoFuturo=0;

        archivoBin.write(reinterpret_cast<const char*>(&cliente), 
                sizeof(struct Cliente));
    }    
}
void confirmaClientes(const char* nombreArchivoReporte,
        const char* nombreArchivoBin){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    int tamElemento, cantElementos;
    tamElemento = sizeof(struct Cliente);
    cantElementos = datosArchivoIf(tamElemento, archivoBin);
    
    struct Cliente cliente;
            
    /*
    int dni;
    char* nombre;
    double montoComprado;
    double descuentoFuturo;
     */
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE CLIENTES"<<endl;
    
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO"
            <<setw(MAX_CAR_DINERO)<<"COMPRADO"
            <<endl;
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantElementos; i++) {        
        archivoBin.read(reinterpret_cast<char*>(&cliente), tamElemento);
        archivoReporte<<left<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD)<<cliente.dni
                <<setw(MAX_CAR_NOMBRE)<<cliente.nombre
                <<setw(MAX_CAR_DESC)<<cliente.descuentoFuturo
                <<setw(MAX_CAR_DINERO)<<cliente.montoComprado
                <<endl;
    }

}

void leeLibros(const char* nombreArchivoDatos,
        const char* nombreArchivoBin){
    ifstream archivoDatos(nombreArchivoDatos, ios::in);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoDatos;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Libro libro;
    while(true){
        // IIM5175,Diamantes y pedernales,Jose Maria Arguedas,69.02
        archivoDatos.getline(libro.codigo, MAX_LIBRO_CODIGO, ',');
        if(archivoDatos.eof()) break;        
        archivoDatos.getline(libro.titulo, MAX_LIBRO_TITULO, ',');
        archivoDatos.getline(libro.autor, MAX_LIBRO_TITULO, ',');
        archivoDatos>>libro.precio;
        archivoDatos.get();
        
        
        libro.cantidadLibrerias = 0;
        libro.totalVentas = 0;
        libro.unidadsVendidas = 0;
        libro.cantidadBuenasCalificaciones = 0;
        libro.sumaBuenasCalificaciones = 0;
        libro.cantidadMalasCalificaciones = 0;
        libro.sumaMalasCalificaciones = 0;                
        archivoBin.write(reinterpret_cast<const char*>(&libro), 
                sizeof(struct Libro));
    }    
}

void emiteReporte(const char* nombreArchivoReporte,
        const char* nombreArchivoBin){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    int tamElemento, cantElementos;
    tamElemento = sizeof(struct Libro);
    cantElementos = datosArchivoIf(tamElemento, archivoBin);
    
    struct Libro libro;
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS VENUS"<<endl;    
    
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantElementos; i++) {
        archivoBin.read(reinterpret_cast<char*>(&libro), tamElemento);
        imprimeLibro(archivoReporte, libro, i);        
    }

}
void imprimeLibro(ofstream& archivo, const struct Libro& libro, int cont){
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<"LIBRO No. "<<cont+1<<endl
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_NOMBRE)<<"TITULO"
            <<setw(MAX_CAR_AUTOR)<<"AUTOR"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"
            <<setw(MAX_CAR_CANT)<<"VENDIDOS"
            <<setw(MAX_CAR_DINERO)<<"TOTAL VENTAS"
            <<setw(MAX_CAR_CALIFICA)<<"PROM. BUENAS CALIF"
            <<setw(MAX_CAR_CALIFICA)<<"PROM. MALAS CALIF"
            <<setw(MAX_CAR_CALIFICA)<<"PROM. CALIF"
            <<endl;
    double promedioBuenasCalifiaciones, promedioMalasCalifiaciones, 
            promedioCalifiaciones;
    promedioBuenasCalifiaciones = hallaPromedio(libro.sumaBuenasCalificaciones, 
            libro.cantidadBuenasCalificaciones);
    promedioMalasCalifiaciones = hallaPromedio(libro.sumaMalasCalificaciones, 
            libro.cantidadMalasCalificaciones);
    promedioCalifiaciones = hallaPromedio(
            libro.sumaMalasCalificaciones + libro.sumaBuenasCalificaciones,
            libro.cantidadMalasCalificaciones+libro.cantidadBuenasCalificaciones);
    archivo<<left<<fixed<<setprecision(2)            
            <<setw(MAX_CAR_COD)<<libro.codigo
            <<setw(MAX_CAR_NOMBRE)<<libro.titulo
            <<setw(MAX_CAR_AUTOR)<<libro.autor
            <<setw(MAX_CAR_DINERO)<<libro.precio
            <<setw(MAX_CAR_CANT)<<libro.unidadsVendidas
            <<setw(MAX_CAR_DINERO)<<libro.totalVentas
            <<setw(MAX_CAR_CALIFICA)<<promedioBuenasCalifiaciones
            <<setw(MAX_CAR_CALIFICA)<<promedioMalasCalifiaciones
            <<setw(MAX_CAR_CALIFICA)<<promedioCalifiaciones
            <<endl;
    
    for (int i = 0; i < libro.cantidadLibrerias; i++) {        
        imprimeLibreria(archivo, libro.librerias[i]);
    }

    
}
double hallaPromedio(double suma, int cantidad){
    if( cantidad == 0) return 0;
    return suma / cantidad;
}
void imprimeLibreria(ofstream& archivo, const struct Libreria & libreria){
    imprimeLinea('-', archivo);
    archivo<<"LIBRERIA: "<<setw(MAX_CAR_COD)<<libreria.codigo
            <<"TOTAL DWE VENTAS: "<<setw(MAX_CAR_DINERO)<<libreria.totalVentas
            <<endl;
    imprimeLinea('-', archivo);
    archivo<<setw(ALING)<<" "
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_CALIFICA)<<"CALIFICACION"
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<endl;
    
    for (int i = 0; i < libreria.cantidadVentas; i++) {        
        imprimeVenta(archivo, libreria.ventas[i], i);
    }
}
void imprimeVenta(ofstream& archivo, const struct Venta& venta, int cont){
    archivo<<setw(ALING)<<" "
            <<setw(MAX_CAR_CONT)<<cont+1
            <<setw(MAX_CAR_COD)<<venta.dniComprador 
            <<setw(MAX_CAR_NOMBRE)<<venta.nombreComprador
            <<setw(MAX_CAR_CALIFICA)<<venta.calificacion
            <<setw(MAX_CAR_FECHA)<<venta.fecha
            <<endl;
    
}

void leeVentas(const char* nombreArchivoVentas,
        const char* nombreArchivoLibros,
        const char* nombreArchivoClientes){
    ifstream archivoVentas(nombreArchivoVentas, ios::in);
    if(not archivoVentas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoVentas;
        exit(1);
    }
    fstream archivoLibros(nombreArchivoLibros, ios::in|ios::out|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoLibros;
        exit(1);
    }
    fstream archivoClientes(nombreArchivoClientes, ios::in|ios::out|ios::binary);
    if(not archivoClientes.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoClientes;
        exit(1);
    }
    
    int tamLibro, cantLibros;
    tamLibro = sizeof(struct Libro);
    cantLibros = datosArchivoF(tamLibro, archivoLibros);    
    struct Libro libro;
    
    int tamCliente, cantClientes;
    tamCliente = sizeof(struct Cliente);
    cantClientes = datosArchivoF(tamCliente, archivoClientes);
    
    struct Cliente cliente;
    
    while(true){
        // 99377   29/4/2024   
        //RZX8790   92240876   18   
        //RAO4129   15129661   21
        int codigoLibreria, fechaVenta, dd,mm,aa;
        char descC;
        archivoVentas>>codigoLibreria;
        if(archivoVentas.eof()) break;
        archivoVentas>>dd>>descC>>mm>>descC>>aa;
        fechaVenta=dd+mm*100+aa*10000;
                           
        leeCompras(archivoVentas, archivoClientes, archivoLibros, cliente, libro, 
                cantLibros, tamLibro, cantClientes, tamCliente, 
                codigoLibreria, fechaVenta);        
    }    
}
void leeCompras(ifstream& archivoVentas, 
        fstream& archivoClientes, fstream& archivoLibros, 
        struct Cliente& cliente, struct Libro& libro, 
        int cantLibros, int tamLibro, 
        int cantClientes, int tamCliente, 
        int codigoLibreria, int fechaVenta){
    while(true){
        if(archivoVentas.get()=='\n') break;
        char codigoLibro[10];
        int dniUsuario, calificacion;
        archivoVentas>>codigoLibro>>dniUsuario>>calificacion;

        int posLibro, posCliente;
        posLibro = buscaLibro(codigoLibro, archivoLibros, cantLibros, tamLibro);
        posCliente = buscaCliente(dniUsuario, archivoClientes, cantClientes, tamCliente);

        if(posLibro!= NO_ENCONTRADO and posCliente != NO_ENCONTRADO){
            archivoLibros.seekg(posLibro*tamLibro, ios::beg);
            archivoLibros.read(reinterpret_cast<char*>(&libro), tamLibro);
            archivoClientes.seekg(posCliente*tamCliente, ios::beg);
            archivoClientes.read(reinterpret_cast<char*>(&cliente), tamCliente);

            procesaVenta(libro, cliente,
                    calificacion, codigoLibreria, fechaVenta);

            archivoLibros.seekg(posLibro*tamLibro, ios::beg);
            archivoLibros.write(reinterpret_cast<const char*>(&libro), tamLibro);
            archivoLibros.flush();

            archivoClientes.seekg(posCliente*tamCliente, ios::beg);
            archivoClientes.write(reinterpret_cast<const char*>(&cliente), tamCliente);
            archivoClientes.flush();
        }
        
    }
    
}
int buscaLibro(char* codigo, fstream& archivo, int cantidad, int tamElem){
    archivo.seekg(0, ios::beg);
    struct Libro libro;
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&libro), tamElem);
        if(strcmp(codigo, libro.codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCliente(int dni, fstream& archivo, int cantidad, int tamElem){
    archivo.seekg(0, ios::beg);
    struct Cliente cliente;
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&cliente), tamElem);
        if(dni == cliente.dni) return i;
    }
    return NO_ENCONTRADO;
}

void procesaVenta(struct Libro& libro, struct Cliente& cliente, 
        int calificacion, int codigoLibreria, int fecha){
    
    cliente.montoComprado+=libro.precio;
    
    if(calificacion>MINIMA_BUENA_CALIFICACION){
        libro.cantidadBuenasCalificaciones++;
        libro.sumaBuenasCalificaciones+=calificacion;
    }
    else{
        libro.cantidadMalasCalificaciones++;
        libro.sumaMalasCalificaciones+=calificacion;        
    }
    
    int posLibreria;
    posLibreria = buscaLibreria(codigoLibreria, libro.librerias, libro.cantidadLibrerias);
    if(posLibreria == NO_ENCONTRADO){
        posLibreria = libro.cantidadLibrerias;
        libro.librerias[posLibreria].codigo=codigoLibreria;
        libro.librerias[posLibreria].cantidadVentas=0;
        libro.librerias[posLibreria].totalVentas=0;

        libro.cantidadLibrerias++;
    }
    int posVenta = libro.librerias[posLibreria].cantidadVentas;
    libro.librerias[posLibreria].totalVentas+=libro.precio;
    libro.librerias[posLibreria].ventas[posVenta].calificacion = calificacion;
    libro.librerias[posLibreria].ventas[posVenta].dniComprador= cliente.dni;
    libro.librerias[posLibreria].ventas[posVenta].fecha= fecha;
    strcpy(libro.librerias[posLibreria].ventas[posVenta].nombreComprador, 
            cliente.nombre);
    
    libro.librerias[posLibreria].cantidadVentas++;
    
    libro.totalVentas+=libro.precio;
    libro.unidadsVendidas++;
}
int buscaLibreria(int codigo, struct Libreria* librerias, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(codigo == librerias[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}
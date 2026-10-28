#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Cliente.h"
#include "Libreria.h"
#include "Libro.h"
#include "Venta.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define ALING 5
#define MAX_CAR_LIN 170
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
char* leeCadena(ifstream& archivo, char del){
    char buff[100], *aux;
    archivo.getline(buff, 100, del);
    if(archivo.eof()) return nullptr;
    aux = new char[strlen(buff)+1]{};
    strcpy(aux, buff);
    return aux;
}

void leeClientes(const char* nombreArchivo,
        struct Cliente* clientes, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    
    /*
    int dni;
    char* nombre;
    double montoComprado;
    double descuentoFuturo;
     */
    while(true){
        // 054393647,Reyes Tang Edward
        archivo>>clientes[cantidad].dni;
        if(archivo.eof()) break;
        archivo.get();
        clientes[cantidad].nombre = leeCadena(archivo, '\n');
        clientes[cantidad].montoComprado=0;
        clientes[cantidad].descuentoFuturo=0;
                
        cantidad++;
    }    
}
void confirmaClientes(const char* nombreArchivo,
        struct Cliente* clientes, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    
    /*
    int dni;
    char* nombre;
    double montoComprado;
    double descuentoFuturo;
     */
    archivo<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE CLIENTES"<<endl;
    
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO"
            <<setw(MAX_CAR_DINERO)<<"COMPRADO"
            <<endl;
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD)<<clientes[i].dni
                <<setw(MAX_CAR_NOMBRE)<<clientes[i].nombre
                <<setw(MAX_CAR_DESC)<<clientes[i].descuentoFuturo
                <<setw(MAX_CAR_DINERO)<<clientes[i].montoComprado
                <<endl;
    }

}

void leeLibros(const char* nombreArchivo,
        struct Libro* libros, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // IIM5175,Diamantes y pedernales,Jose Maria Arguedas,69.02
        libros[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;        
        libros[cantidad].titulo = leeCadena(archivo, ',');
        libros[cantidad].autor = leeCadena(archivo, ',');
        archivo>>libros[cantidad].precio;
        archivo.get();
        
        libros[cantidad].librerias = 
                new struct Libreria [MAX_LIBRO_LIBRERIAS]{};
        libros[cantidad].cantidadLibrerias = 0;
        libros[cantidad].totalVentas = 0;
        libros[cantidad].unidadsVendidas = 0;
        libros[cantidad].cantidadBuenasCalificaciones = 0;
        libros[cantidad].sumaBuenasCalificaciones = 0;
        libros[cantidad].cantidadMalasCalificaciones = 0;
        libros[cantidad].sumaMalasCalificaciones = 0;                
                
        cantidad++;
    }    
}

void emiteReporte(const char* nombreArchivo,
        struct Libro* libros, int cantidadLibros){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }            
    archivo<<setw(MAX_CAR_LIN/2)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS VENUS"<<endl;    
    
    for (int i = 0; i < cantidadLibros; i++) {
        imprimeLibro(archivo, libros[i], i);        
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
    promedioMalasCalifiaciones = hallaPromedio(
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
            <<setw(MAX_CAR_CALIFICA)<<promedioBuenasCalifiaciones
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

void leeVentas(const char* nombreArchivo,
        struct Libro* libros, int cantidadLibros, 
        struct Cliente* clientes, int cantidadClientes){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 99377   29/4/2024   
        //RZX8790   92240876   18   
        //RAO4129   15129661   21
        int codigoLibreria, fechaVenta, dd,mm,aa;
        char descC;
        archivo>>codigoLibreria;
        if(archivo.eof()) break;
        archivo>>dd>>descC>>mm>>descC>>aa;
        fechaVenta=dd+mm*100+aa*10000;
        
        while(true){
            if(archivo.get()=='\n') break;
            char codigoLibro[10];
            int dniUsuario, calificacion;
            archivo>>codigoLibro>>dniUsuario>>calificacion;
            
            int posLibro, posCliente;
            posLibro = buscaLibro(codigoLibro, libros, cantidadLibros);
            posCliente = buscaCliente(dniUsuario, clientes, cantidadClientes);
            
            if(posLibro!= NO_ENCONTRADO and posCliente != NO_ENCONTRADO){
                procesaVenta(libros[posLibro], clientes[posCliente], 
                        calificacion, codigoLibreria, fechaVenta);
            }
        }
    }    
}
int buscaLibro(char* codigo, struct Libro* libros, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, libros[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCliente(int dni, struct Cliente* clientes, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(dni == clientes[i].dni) return i;
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
        libro.librerias[posLibreria].totalVentas=0;        ;
        libro.librerias[posLibreria].ventas=
                new struct Venta[MAX_LIBRERIAS_VENTAS]{};
        libro.cantidadLibrerias++;
    }
    int posVenta = libro.librerias[posLibreria].cantidadVentas;
    libro.librerias[posLibreria].totalVentas+=libro.precio;
    libro.librerias[posLibreria].ventas[posVenta].calificacion = calificacion;
    libro.librerias[posLibreria].ventas[posVenta].dniComprador= cliente.dni;
    libro.librerias[posLibreria].ventas[posVenta].fecha= fecha;
    libro.librerias[posLibreria].ventas[posVenta].nombreComprador = 
            new char [strlen(cliente.nombre)+1];
    strcpy(libro.librerias[posLibreria].ventas[posVenta].nombreComprador, 
            cliente.nombre);
    
    libro.librerias[posLibreria].cantidadVentas++;
    
    libro.unidadsVendidas++;
}
int buscaLibreria(int codigo, struct Libreria* librerias, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(codigo == librerias[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}
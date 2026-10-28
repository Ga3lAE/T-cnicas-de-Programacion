/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 13 de junio de 2025, 10:39 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Cliente.h"
#include "Libreria.h"
#include "Libro.h"
#include "Venta.h"
#include "NodoCliente.h"
#include "NodoLibro.h"

#define MAX_CAR_LIBRO_COD 8

#define MAX_TAM_TAB 10
#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOM 50
#define MAX_TAM_TIT 40
#define MAX_TAM_AUT 30
#define MAX_TAM_DIN 14
#define MAX_TAM_CANT 12
#define MAX_TAM_CONT 5
#define MAX_TAM_CAL 14
#define MAX_TAM_FECHA 12

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char  aux[100], *cad;
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}
int leeFecha(ifstream &archivo){
    int dd, mm, aa;
    char sep;
    archivo>>dd>>sep
            >>mm>>sep
            >>aa;
    
    return dd+mm*100+aa*10000;
}
void leeClientes(const char *nombreArchivo, 
        struct NodoCliente *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Cliente cliente;
    while(true){
        //67066631,Arca Amezquita Edric Ronald
        archivo>>cliente.dni;
        if(archivo.eof()) break;
        archivo.get();
        cliente.nombre = leeCadenaExacta(archivo, '\n');
        cliente.descuentoFuturo=0;
        cliente.montoComprado=0;
        
        insertaClienteLista(cliente, lista);
    }
}
void leeLibros(const char *nombreArchivo, 
        struct NodoLibro *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Libro libro;
    while(true){
        //ETZ8565,Confesiones de una mascara,Yukio Mishima,339.31
        libro.codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;        
        libro.titulo = leeCadenaExacta(archivo, ',');
        libro.autor = leeCadenaExacta(archivo, ',');
        archivo>>libro.precio;
        archivo.get(); //salto de linea
        
        libro.cantidadBuenasCalificaciones=0;
        libro.cantidadMalasCalificaciones=0;
        libro.cantidadLibrerias=0;
        libro.sumaBuenasCalificaciones=0;
        libro.sumaMalasCalificaciones=0;
        libro.totalVentas=0;
        libro.unidadesVendidas=0;                
        
        insertaLibroLista(libro, lista);
    }
}
void leeVentas(const char *nombreArchivo, 
        struct NodoCliente *listaClientes, 
        struct NodoLibro *listaLibros){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoLibreria, fechaCompra, dniComprador, calificacion;
    char codigoLibro[MAX_CAR_LIBRO_COD]{};    
    while(true){
        //32198   30/4/2024   
            //BSX2922   54393647   97   
            //JZQ8143   57431952   81   
            //CRR5443   57431952   40
        archivo>>codigoLibreria;
        if(archivo.eof()) break;
        fechaCompra = leeFecha(archivo);
        
        while(true){
            if(archivo.get()=='\n') break;
            archivo>>codigoLibro>>dniComprador>>calificacion;
            struct NodoLibro *libroActual = buscaLibro(listaLibros, codigoLibro);                                                            
            struct NodoCliente *clienteActual = buscaCliente(listaClientes, dniComprador);
            if(clienteActual != NULL and libroActual != NULL){
                procesaCliente(clienteActual, libroActual);                               
                procesaLibro(codigoLibreria, fechaCompra, dniComprador, 
                        calificacion, 
                        clienteActual, libroActual);                   
                
                
            }                                                
        }        
    }   
}
void procesaCliente(struct NodoCliente* clienteActual, struct NodoLibro* libroActual){
    
    clienteActual->cliente.montoComprado+=libroActual->libro.precio;
    
    if(clienteActual->cliente.montoComprado>5000)
        clienteActual->cliente.descuentoFuturo = 30;
    else if(clienteActual->cliente.montoComprado>3000)
        clienteActual->cliente.descuentoFuturo = 20;
    else if(clienteActual->cliente.montoComprado>0)
        clienteActual->cliente.descuentoFuturo = 10;
}
int insertaLibreria(struct Libro &libro, int codigoLibreria){
    int i;
    for (i = 0; i < libro.cantidadLibrerias; i++) {        
        if(libro.librerias[i].codigo == codigoLibreria) return i;// ya existe la libreria
    }    
    libro.librerias[libro.cantidadLibrerias].codigo = codigoLibreria;
    libro.librerias[libro.cantidadLibrerias].cantidadVentas=0;
    libro.librerias[libro.cantidadLibrerias].totalVentas=0;
    
    libro.cantidadLibrerias++;
    return libro.cantidadLibrerias-1;
}
void procesaLibro(int codigoLibreria, int fechaCompra, 
        int dniComprador, int calificacion, 
        struct NodoCliente *clienteActual, 
        struct NodoLibro *libroActual){                    
    
    libroActual->libro.unidadesVendidas++;
    libroActual->libro.totalVentas+=libroActual->libro.precio;
    if(calificacion>50)
        asignaCalificacion(libroActual->libro.cantidadBuenasCalificaciones, 
                libroActual->libro.sumaBuenasCalificaciones, calificacion);
    else    
        asignaCalificacion(libroActual->libro.cantidadMalasCalificaciones, 
                libroActual->libro.sumaMalasCalificaciones, calificacion);
    int posLibreria = insertaLibreria(libroActual->libro, codigoLibreria);
    
    struct Libreria &libreriaActual = libroActual->libro.librerias[posLibreria];    
    libreriaActual.totalVentas += libroActual->libro.precio;
    libreriaActual.venta[libreriaActual.cantidadVentas].calificacion = calificacion;
    libreriaActual.venta[libreriaActual.cantidadVentas].dniComprador = dniComprador;
    libreriaActual.venta[libreriaActual.cantidadVentas].fecha = fechaCompra;
    libreriaActual.venta[libreriaActual.cantidadVentas].nombreComprador = new char[strlen(clienteActual->cliente.nombre)+1]{};
    strcpy(libreriaActual.venta[libreriaActual.cantidadVentas].nombreComprador, clienteActual->cliente.nombre);
    libreriaActual.cantidadVentas++;    
}
void asignaCalificacion(int &cantidad, double &suma, int calificacion){
    cantidad++;
    suma+=(double)calificacion;
}
//INSERCION
void insertaClienteLista(struct Cliente cliente, 
        struct NodoCliente *&listaCliente){
    struct NodoCliente *nuevo;
    nuevo = new struct NodoCliente;
    nuevo->cliente = cliente;
    nuevo->siguiente = listaCliente;
    
    listaCliente = nuevo;   
}
void insertaLibroLista(struct Libro libro, 
        struct NodoLibro *&lista){
    struct NodoLibro *nuevo;
    nuevo = new struct NodoLibro;
    nuevo->libro = libro;
    nuevo->siguiente = lista;
    
    lista = nuevo;   
}

//BUSQUEDA
struct NodoCliente *buscaCliente(struct NodoCliente *lista, int dato){
    struct NodoCliente *ptr;
    ptr = lista;
    
    while(ptr){
        if(ptr->cliente.dni == dato) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}
struct NodoLibro *buscaLibro(struct NodoLibro *lista, const char *dato){
    struct NodoLibro *ptr;
    ptr = lista;
    
    while(ptr){
        if(strcmp(ptr->libro.codigo, dato)==0) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {
        archivo<<c;
    }
    archivo<<endl;
}
void verificaClientes(const char *nombreArchivo, 
        struct NodoCliente *listaClientes){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<right<<setw(MAX_TAM_LIN/2)<<"VERIFIFACION DE CLIENTES"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"DNI"
            <<setw(MAX_TAM_NOM)<<"NOMBRE"
            <<setw(MAX_TAM_DIN)<<"COMPRADO"
            <<setw(MAX_TAM_DIN)<<"DESCUENTO"
            <<endl;
    imprimeLinea(archivo, '=');
    
    struct NodoCliente *ptr;
    ptr = listaClientes;

    while(ptr){
        archivo<<left
                <<setw(MAX_TAM_COD)<<ptr->cliente.dni
                <<setw(MAX_TAM_NOM)<<ptr->cliente.nombre
                <<setw(MAX_TAM_DIN)<<ptr->cliente.montoComprado
                <<setw(MAX_TAM_DIN)<<ptr->cliente.descuentoFuturo
                <<endl;
        
        ptr = ptr->siguiente;
    }
}
void verificaLibros(const char *nombreArchivo, 
        struct NodoLibro *lista){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<right<<setw(MAX_TAM_LIN/2)<<"VERIFICACION DE LIBROS"<<endl;    
    
    int totalLibros=0;
    double totalRecaudado=0;
    
    struct NodoLibro *ptr;
    ptr = lista;    
    
    for (int i = 0; ptr; i++) {
    imprimeLinea(archivo, '=');
    double promedioBueno, promedioMalo, promedioTotal;
    promedioBueno = ptr->libro.cantidadBuenasCalificaciones!=0?ptr->libro.sumaBuenasCalificaciones/ptr->libro.cantidadBuenasCalificaciones:0;
    promedioMalo = ptr->libro.cantidadMalasCalificaciones!=0?ptr->libro.sumaMalasCalificaciones/ptr->libro.cantidadMalasCalificaciones:0;
    promedioTotal = ptr->libro.unidadesVendidas!=0?(ptr->libro.sumaMalasCalificaciones+ptr->libro.sumaBuenasCalificaciones)/ptr->libro.unidadesVendidas:0;
    
        archivo<<left
                <<"LIBRO No. "<<i+1<<endl
                <<setw(MAX_TAM_COD)<<"CODIGO"
                <<setw(MAX_TAM_TIT)<<"TITULO"
                <<setw(MAX_TAM_AUT)<<"AUTOR"
                <<setw(MAX_TAM_DIN)<<"PRECIO"
                <<setw(MAX_TAM_CANT)<<"VENDIDOS"
                <<setw(MAX_TAM_DIN)<<"TOTAL VENTAS"
                <<setw(MAX_TAM_CAL)<<"PROM GOOD"
                <<setw(MAX_TAM_CAL)<<"PROM BAD"
                <<setw(MAX_TAM_CAL)<<"PROM CALI"
                <<endl
                <<setw(MAX_TAM_COD)<<ptr->libro.codigo
                <<setw(MAX_TAM_TIT)<<ptr->libro.titulo
                <<setw(MAX_TAM_AUT)<<ptr->libro.autor
                <<setw(MAX_TAM_DIN)<<ptr->libro.precio
                <<setw(MAX_TAM_CANT)<<ptr->libro.unidadesVendidas
                <<setw(MAX_TAM_DIN)<<ptr->libro.totalVentas
                <<setw(MAX_TAM_CAL)<<promedioBueno
                <<setw(MAX_TAM_CAL)<<promedioMalo
                <<setw(MAX_TAM_CAL)<<promedioTotal
                <<endl;
        totalLibros+=ptr->libro.totalVentas;
        totalRecaudado+=ptr->libro.totalVentas*ptr->libro.precio;
        imprimeLinea(archivo, '-');
        
        for (int i = 0; i<ptr->libro.cantidadLibrerias; i++) {            
            archivo
                    <<"LIBRERIA: "<<setw(MAX_TAM_COD)<<ptr->libro.librerias[i].codigo
                    <<"TOTAL DE VENTAS "<<setw(MAX_TAM_DIN)<<ptr->libro.librerias[i].totalVentas
                    <<endl;
            imprimeLinea(archivo, '-');
            
            archivo<<setw(MAX_TAM_TAB)<<" "
                    <<"VENTAS"<<endl
                    <<setw(MAX_TAM_TAB)<<" "
                    <<setw(MAX_TAM_CONT)<<"No."
                    <<setw(MAX_TAM_COD)<<"DNI"
                    <<setw(MAX_TAM_NOM)<<"NOMBRE"
                    <<setw(MAX_TAM_CAL)<<"CALIFICACION"
                    <<setw(MAX_TAM_FECHA)<<"FECHA"
                    <<endl;
            
            for (int k = 0; k < ptr->libro.librerias[i].cantidadVentas; k++) {
                archivo<<setw(MAX_TAM_TAB)<<" "
                        <<setw(MAX_TAM_CONT)<<k+1
                        <<setw(MAX_TAM_COD)<<ptr->libro.librerias[i].venta[k].dniComprador
                        <<setw(MAX_TAM_NOM)<<ptr->libro.librerias[i].venta[k].nombreComprador
                        <<setw(MAX_TAM_CAL)<<ptr->libro.librerias[i].venta[k].calificacion
                        <<setw(MAX_TAM_FECHA)<<ptr->libro.librerias[i].venta[k].fecha
                        <<endl;                
            }
            imprimeLinea(archivo, '-');
            
        }        
        ptr = ptr->siguiente;
    }     
    
    archivo<<"RESUMEN:"<<endl
            <<"TOTAL DE LIBROS VENDIDOS: "<<totalLibros<<endl
            <<"TOTAL RECAUDADO: "<<totalRecaudado<<endl;            
}

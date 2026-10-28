/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 23 de junio de 2025, 11:46 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "Cliente.h"
#include "NodoCliente.h"
#include "Plato.h"
#include "NodoPlato.h"

#define MAX_TAM_COD 10
#define MAX_TAM_DESC 50
#define MAX_TAM_CAT 25
#define MAX_TAM_DIN 14
#define MAX_TAM_CANT 12
#define MAX_TAM_NOM 50
#define MAX_TAM_DIST 25

//AOBRECARGA
void operator << (ofstream &archivo, struct Plato plato){
    archivo<<left
            <<setw(MAX_TAM_COD)<<plato.codigo
            <<setw(MAX_TAM_DESC)<<plato.descripcion
            <<setw(MAX_TAM_CAT)<<plato.categoria
            <<setw(MAX_TAM_CANT)<<plato.cantidad
            <<setw(MAX_TAM_DIN)<<plato.precio
            <<setw(MAX_TAM_DIN)<<plato.totalBruto
            <<setw(MAX_TAM_DIN)<<plato.totalNeto
            <<endl;
}
void operator << (ofstream &archivo, struct Cliente cliente){
     archivo<<left
            <<setw(MAX_TAM_COD)<<cliente.dni
            <<setw(MAX_TAM_NOM)<<cliente.nombre
            <<setw(MAX_TAM_DIST)<<cliente.distrito
            <<setw(MAX_TAM_CANT)<<cliente.cantidad
            <<setw(MAX_TAM_DIN)<<cliente.pagoBruto            
            <<setw(MAX_TAM_DIN)<<cliente.total
            <<endl; 
}

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[100], *cad;
    archivo.getline(aux, 100, del);
    
    if(archivo.eof()) return NULL;
    cad = new char[strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}

void leePlatos(const char *nombreArchivo, struct NodoPlato *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Plato plato;
    while(true){
        //AP-73428,TEQUEÑOS,19.50,APERITIVO
        plato.codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        plato.descripcion = leeCadenaExacta(archivo, ',');
        archivo>>plato.precio;
        archivo.get();
        plato.categoria = leeCadenaExacta(archivo, '\n');
        
        plato.totalBruto=0;
        plato.totalNeto=0;
        plato.cantidad=0;
        
        insertaPlatoLista(plato, lista);
    }
}
void leeClientes(const char *nombreArchivo, struct NodoCliente *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Cliente cliente;
    while(true){
        //99774549,HENRIQUEZ ESPINO BEATRIZ,San Borja
        archivo>>cliente.dni;
        if(archivo.eof()) break;
        archivo.get();
        cliente.nombre = leeCadenaExacta(archivo, ',');
        cliente.distrito = leeCadenaExacta(archivo, '\n');
        cliente.cantidad=0;
        cliente.pagoBruto=0;
        cliente.total=0;
        
        insertaClienteLista(cliente, lista);
    }
}
void leePedidos(const char *nombreArchivo, 
        struct NodoCliente *listaClientes,
        struct NodoPlato *listaPlatos, 
        double descuento, const char *categoriaDescuento){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoPedido, dniCliente, cantidadPedida;
    char codigoPlato[9]{};
    while(true){
        //593758       81539774    PA-11850    7
        archivo>>codigoPedido;
        if(archivo.eof()) break;
        archivo>>dniCliente>>codigoPlato>>cantidadPedida;                
        
        struct NodoPlato *nodoPlato = buscaPlato(listaPlatos, codigoPlato) ;
        struct NodoCliente *nodoCliente = buscaCliente(listaClientes, dniCliente);
        if(nodoPlato and nodoCliente){
            struct Cliente &cliente = nodoCliente->cliente;
            struct Plato &plato = nodoPlato->plato;
            
            double descuentoAplicado;
            if(strcmp(plato.categoria, categoriaDescuento) != 0)
                descuentoAplicado = 0;
            else
                descuentoAplicado = descuento;
            
            cliente.cantidad+=cantidadPedida;
            cliente.pagoBruto+=plato.precio*cantidadPedida;
            cliente.total+=(1-descuentoAplicado/100.0)*plato.precio*cantidadPedida;
            
            plato.cantidad+=cantidadPedida;
            plato.totalBruto+=cantidadPedida*plato.precio;
            plato.totalNeto+=(1-descuentoAplicado/100.0)*cantidadPedida*plato.precio;
        }
    }
}
//INSERCION
void insertaPlatoLista(struct Plato plato, struct NodoPlato *&lista){
    struct NodoPlato *nuevo;
    nuevo = new struct NodoPlato;
    nuevo->plato = plato;
    nuevo->siguiente = lista;
    lista = nuevo;
}
void insertaClienteLista(struct Cliente cliente, struct NodoCliente *&lista){
    struct NodoCliente *nuevo;
    nuevo = new struct NodoCliente;
    nuevo->cliente = cliente;
    nuevo->siguiente = lista;
    lista = nuevo;
}

//BUSQUEDA
struct NodoPlato *buscaPlato(struct NodoPlato *lista, const char *cod){
    struct NodoPlato *ptr = lista;
    while(ptr){
        if(strcmp(ptr->plato.codigo,cod) == 0) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}
struct NodoCliente *buscaCliente(struct NodoCliente *lista, int dni){
    struct NodoCliente *ptr = lista;
    while(ptr){
        if(ptr->cliente.dni == dni) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}

//IMPRESION
void emiteReporte(const char *nombreArchivo, 
        struct NodoCliente *listaClientes,
        struct NodoPlato *listaPlatos, 
        double descuento, const char *categoriaDescuento){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    struct NodoPlato *ptrPlato = listaPlatos;
    while(ptrPlato){                                
        archivo<<ptrPlato->plato;
        ptrPlato = ptrPlato->siguiente;
    }
    archivo<<'\n'<<endl;
    struct NodoCliente *ptrCliente = listaClientes;
    while(ptrCliente){              
        archivo<<ptrCliente->cliente;
        ptrCliente = ptrCliente->siguiente;
    }
}
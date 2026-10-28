/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 21 de junio de 2025, 11:47 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "NodoEmpresa.h"
#include "NodoInfraccion.h"

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[300], *cad;
    archivo.getline(aux, 300, del);
    if(archivo.eof()) return NULL;
    
    cad = new char[strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}
void leeFecha(ifstream &archivo, struct Fecha &fecha){    
    fecha.dd = 0;
    fecha.mm = 0;
    fecha.aa = 0;
    char sep;
    archivo>>fecha.dd;
    if(archivo.eof()) return;
    archivo>>sep>>fecha.mm
            >>sep>>fecha.aa;
    archivo.get();
    
    fecha.fecha = fecha.dd + fecha.mm*100 + fecha.aa*10000;
}
char *cadenaAMayusculas(char *cad){
    for (int i = 0; cad[i]; i++) {        
        if(cad[i]<='z' and cad[i]>='a') cad[i]+='A'-'a';        
    }
    return cad;
}
void leeEmpresas(const char *nombreArchivo, struct NodoEmpresa *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Empresa aux;
    while(true){
        //12858682,zarate perez alexander,Barranco
        archivo>>aux.dni;
        if(archivo.eof()) break;
        archivo.get();
        aux.nombre = cadenaAMayusculas(leeCadenaExacta(archivo, ','));
        aux.distrito = leeCadenaExacta(archivo, '\n');
        
        aux.cantidadFaltas=0;
        aux.cantidadPlacas=0;
        aux.totalAdeudado=0;
        aux.totalMultas=0;
        aux.totalPagado=0;

        agregaEmpresa(aux, lista);
    }
}
void leeInfracciones(const char *nombreArchivo, struct NodoInfraccion *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Infraccion aux;    
    while(true){
        //G2031,365.30,Circular transportando personas en la parte exterior de la carroceria o permitir que sobresalga parte del cuerpo de personas.
        aux.codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        archivo>>aux.multa;
        archivo.get();
        aux.descripcion = leeCadenaExacta(archivo, '\n');        
               
        agregaInfraccion(aux, lista);
    }
}
void leePlacas(const char *nombreArchivo, struct NodoEmpresa *lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int dni;
    char *placa;
    while(true){
        archivo>>dni;
        if(archivo.eof()) break;
        archivo>>ws;
        placa = leeCadenaExacta(archivo, '\n');
        
        struct NodoEmpresa *representante = buscaEmpresa(lista, dni);
        if(representante!=NULL){//existe
            representante->empresa.placas[representante->empresa.cantidadPlacas] = placa;
            representante->empresa.cantidadPlacas++;            
        }
    }
        
}
void leeInfraccionesCometidas(const char *nombreArchivo, 
        struct NodoEmpresa *listaEmpresas, 
        struct NodoInfraccion *listaInfracciones){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    struct Fecha fechaInfraccion, fechaPago;
    char *placaCome, *infraccionCome, pago;
    while(true){
        //5/10/2024,M907-605,M1002,P,24/10/2024
        leeFecha(archivo, fechaInfraccion);
        if(archivo.eof()) break;
        placaCome = leeCadenaExacta(archivo, ',');
        infraccionCome = leeCadenaExacta(archivo, ',');
        
        archivo>>pago;
        if(pago == 'P'){
            archivo.get();
            leeFecha(archivo, fechaPago);
        }
        
        struct NodoEmpresa *empresa;
        struct NodoInfraccion *infraccion;
        empresa = buscaPlaca(listaEmpresas, placaCome);
        infraccion = buscaInfraccion(listaInfracciones, infraccionCome);
        
        if(empresa and infraccion){
            struct Empresa &empresaAux = empresa->empresa;
            struct Infraccion infraccionAuz = infraccion->infraccion;
            
            empresaAux.cantidadFaltas++;
            
            if(empresaAux.totalMultas == 0)//primera falta
                empresaAux.fechaInfraccion = fechaInfraccion;            
            if(pago =='P' and empresaAux.totalPagado == 0)//primer pag
                empresaAux.fechaPago = fechaPago;
            empresaAux.cantidadFaltas++;     
            if(fechaInfraccion.fecha<empresaAux.fechaInfraccion.fecha)
                 empresaAux.fechaInfraccion = fechaInfraccion;
            if(fechaPago.fecha>empresaAux.fechaPago.fecha and pago == 'P')
                 empresaAux.fechaPago = fechaPago;
            
            empresaAux.totalMultas+=infraccionAuz.multa;
            
            if(pago =='N')
                empresaAux.totalAdeudado+=infraccionAuz.multa;
            else
                empresaAux.totalPagado+=infraccionAuz.multa;
            
        }
    }
}

//AGREGA
void agregaEmpresa(struct Empresa aux, struct NodoEmpresa *&lista){
    struct NodoEmpresa *nuevo;
    nuevo = new struct NodoEmpresa;
    nuevo->empresa = aux;
    nuevo->siguiente=lista;
    
    lista = nuevo;
}
void agregaInfraccion(struct Infraccion aux, struct NodoInfraccion *&lista){
    struct NodoInfraccion *nuevo;
    nuevo = new struct NodoInfraccion;
    nuevo->infraccion = aux;
    nuevo->siguiente=lista;
    
    lista = nuevo;
}

//BUSQUEDA
struct NodoEmpresa *buscaEmpresa(struct NodoEmpresa *lista, int dni){
    struct NodoEmpresa *aux = lista;
    
    while(aux){
        if(aux->empresa.dni == dni) return aux;
        aux = aux->siguiente;            
    }
    return NULL;
}
struct NodoEmpresa *buscaPlaca(struct NodoEmpresa *lista, const char *placa){
    struct NodoEmpresa *aux = lista;
    
    while(aux){
        for (int i = 0; i < aux->empresa.cantidadPlacas; i++) {            
            if(strcmp(aux->empresa.placas[i], placa) == 0) return aux;
        }        
        aux = aux->siguiente;            
    }
    return NULL;
}
struct NodoInfraccion *buscaInfraccion(struct NodoInfraccion *lista, const char *codigo){
    struct NodoInfraccion *aux = lista;
    
    while(aux){        
        if(strcmp(aux->infraccion.codigo, codigo) == 0) return aux;          
        
        aux = aux->siguiente;            
    }
    return NULL;
}

//ORDENA
void ordenaInfracciones(struct NodoInfraccion *lista){
            
    struct NodoInfraccion *i = lista;        
    
    while(i){
        struct NodoInfraccion *j = i->siguiente;
        while(j){
            if(strcmp(i->infraccion.codigo, j->infraccion.codigo)<0){
                struct Infraccion aux;
                aux = i->infraccion;
                i->infraccion = j->infraccion;
                j->infraccion = aux;
            }
            j = j->siguiente;
        }
        i = i->siguiente;        
    }            
}
void ordenaEmpresas(struct NodoEmpresa *lista){            
    struct NodoEmpresa *i = lista;        
    
    while(i){
        struct NodoEmpresa *j = i->siguiente;
        while(j){
            if(i->empresa.dni>j->empresa.dni){
                struct Empresa aux;
                aux = i->empresa;
                i->empresa = j->empresa;
                j->empresa = aux;
            }
            j = j->siguiente;
        }
        i = i->siguiente;        
    }            
}

void cambiaInfraccion(struct NodoInfraccion *&aux, struct NodoInfraccion *&auxAnt, 
        struct NodoInfraccion *&siguiente, struct NodoInfraccion *&siguienteAnt){
    struct NodoInfraccion *auxiliar, *siguienteSig;
    auxiliar = aux;
    auxAnt->siguiente = siguiente;
    
    
}


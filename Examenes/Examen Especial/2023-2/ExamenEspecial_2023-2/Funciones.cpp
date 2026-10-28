/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 27 de junio de 2025, 07:20 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "NodoArticulo.h"
#include "Vendedor.h"
#include "NodoVendedor.h"
#include "Vendedor.h"
#include "ArticuloPedido.h"


#define TAB 5
#define MAX_TAM_LIN 150
#define MAX_TAM_CONT 5
#define MAX_TAM_COD 10
#define MAX_TAM_DESCR 55
#define MAX_TAM_STOCK 12
#define MAX_TAM_DIN 16
#define MAX_TAM_PORC 16
#define MAX_TAM_NOMB 50
#define MAX_TAM_CANT 10
#define MAX_TAM_FECHA 16

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char buff[100], *cad;
    archivo.getline(buff, 100, del);
    
    if(archivo.eof()) return NULL;    
    cad = new char [strlen(buff)+1]{};
    strcpy(cad, buff);
    return cad;
}
int leeFecha(ifstream &archivo){
    int dd, mm ,aa;
    char sep;
    
    archivo>>dd>>sep>>mm>>sep>>aa;
    
    return dd + mm*100 + aa*10000;
}
char *copiaCadena(const char *cad){
    char *aux;
    aux = new char [strlen(cad)+1]{};
    strcpy(aux, cad);
    return aux;
}
void leeArticulos(const char *nombreArchivo, struct NodoArticulo *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Articulo articulo;
    while(true){
        //NMV-644,Lavadora Automatica,5,3272.48
        articulo.codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        articulo.descripcion = leeCadenaExacta(archivo, ',');
        archivo>>articulo.stock;
        archivo.get();
        archivo>>articulo.precio;
        archivo.get();
        
        articulo.cantidadVendida = 0;
        articulo.montoVendido = 0;
        articulo.cantidadNoVendida = 0;
        articulo.montoNoVendido = 0;        
        
        insertaArticuloOrdenado(articulo, lista);
    }
}
void leeVendedores(const char *nombreArchivo, struct NodoVendedor *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Vendedor vendedor;
    char descC;
    while(true){
        //26976877,TORO CUBA DIALY DIANA,23.14,38000.00
        archivo>>vendedor.codigo;
        if(archivo.eof()) break;
        archivo.get();
        vendedor.nombre = leeCadenaExacta(archivo, ',');
        archivo>>vendedor.porcentajeVentas>>descC
                >>vendedor.cuotaMinima;        
        vendedor.articulosVendidos = new struct ArticuloPedido[MAX_CANT_ARTICULOS_VENDEDOR]{};
        vendedor.cantidadArticulosVendidos = 0;
        vendedor.montoVendido = 0;
        vendedor.articulosNoVendidos = new struct ArticuloPedido[MAX_CANT_ARTICULOS_VENDEDOR]{};
        vendedor.cantidadArticulosNoVendidos = 0;
        vendedor.montoNoVendido = 0;        
        
        insertaVendedorOrdenado(vendedor, lista);
    }
}
void leeVentas(const char *nombreArchivo, 
        struct NodoArticulo *listaArticulos, 
        struct NodoVendedor *listaVendedores){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    char codigoArticulo[8]{};
    int dniVendedor, cantidad, fecha;
    while(true){
        //MMA-577     52097922  4    2/10/2023
        archivo>>codigoArticulo;
        if(archivo.eof()) break;
        archivo>>dniVendedor>>cantidad;
        fecha = leeFecha(archivo);
        
        struct NodoArticulo *nodoArticulo = buscaArticulo(listaArticulos, codigoArticulo);        
        struct NodoVendedor *nodoVendedor = buscaVendedor(listaVendedores, dniVendedor);        
        
        if(nodoArticulo != NULL and nodoVendedor != NULL){
            struct Vendedor &vendedor = nodoVendedor->vendedor;
            struct Articulo &articulo = nodoArticulo->articulo;
            
            if(cantidad>articulo.stock){
                articulo.cantidadNoVendida+=cantidad;
                articulo.montoNoVendido+=cantidad*articulo.precio;
                
                vendedor.montoNoVendido+=articulo.precio*cantidad;
                struct ArticuloPedido &articuloNoVendido=
                        vendedor.articulosNoVendidos[vendedor.cantidadArticulosNoVendidos];
                articuloNoVendido.cantidad+=cantidad;
                articuloNoVendido.codigo = copiaCadena(codigoArticulo);
                articuloNoVendido.fechaUltima = articuloNoVendido.fechaUltima<fecha?fecha:articuloNoVendido.fechaUltima;
                articuloNoVendido.total+=cantidad*articulo.precio;
                vendedor.cantidadArticulosNoVendidos++;
            }
            else{
                articulo.cantidadVendida+=cantidad;
                articulo.montoVendido+=cantidad*articulo.precio;                
                
                vendedor.montoVendido+=articulo.precio*cantidad;
                struct ArticuloPedido &articuloVendido=
                        vendedor.articulosVendidos[vendedor.cantidadArticulosVendidos];
                articuloVendido.cantidad+=cantidad;
                articuloVendido.codigo = copiaCadena(codigoArticulo);
                articuloVendido.fechaUltima = articuloVendido.fechaUltima<fecha?fecha:articuloVendido.fechaUltima;
                articuloVendido.total+=cantidad*articulo.precio;
                vendedor.cantidadArticulosVendidos++;
                
                articulo.stock-=cantidad;
            }
        }
    }
}

//INSERCION
void insertaArticuloOrdenado(struct Articulo articulo, struct NodoArticulo *&lista){
    struct NodoArticulo *nuevo, *ptr = lista, *ant = NULL;
    nuevo = new struct NodoArticulo;
    nuevo->articulo = articulo;
    
    while(ptr){
        if(strcmp(articulo.codigo, ptr->articulo.codigo)<0) break;
        ant = ptr;
        ptr = ptr->siguiente;
    }
    nuevo->siguiente = ptr;
    
    if(ant == NULL) lista = nuevo;
    else ant->siguiente = nuevo;    
}
void insertaVendedorOrdenado(struct Vendedor vendeddor, struct NodoVendedor *&lista){
    struct NodoVendedor *nuevo, *ptr = lista, *ant = NULL;
    nuevo = new struct NodoVendedor;
    nuevo->vendedor = vendeddor;
    
    while(ptr){
        if(vendeddor.codigo<ptr->vendedor.codigo) break;
        ant = ptr;
        ptr = ptr->siguiente;
    }
    nuevo->siguiente = ptr;
    if(ant == NULL) lista = nuevo;
    else ant->siguiente = nuevo;    
}

//BUSQUEDA
struct NodoArticulo *buscaArticulo(struct NodoArticulo *lista, const char *codigo){
    struct NodoArticulo *ptr = lista;
    while(ptr){
        if(strcmp(ptr->articulo.codigo, codigo) == 0) return ptr;
        else if(strcmp(ptr->articulo.codigo, codigo)>0) return NULL;
        ptr = ptr->siguiente;
    }
    return NULL;
}
struct NodoVendedor *buscaVendedor(struct NodoVendedor *lista, int dni){
    struct NodoVendedor *ptr = lista;
    while(ptr){
        if(dni == ptr->vendedor.codigo) return ptr;
        else if(dni<ptr->vendedor.codigo) return NULL;
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
void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep= '/';
    aa=fecha/10000;
    fecha %=10000;
    mm=fecha/100;
    dd =fecha % 100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<right<<setfill(' ')
            <<setw(MAX_TAM_FECHA-10)<<' ';
}
void imprimeArticulos(const char *nombreArchivo, struct NodoArticulo *lista){    
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_TAM_LIN/2)<<"DETALLE DE ENTAS POR ARTICULO"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_CONT)<<"No."
            <<setw(MAX_TAM_COD+MAX_TAM_DESCR)<<"ARTICULO"            
            <<setw(MAX_TAM_STOCK)<<"STOCK"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_STOCK)<<"CANT VEND"
            <<setw(MAX_TAM_DIN)<<"MONT VEND"
            <<setw(MAX_TAM_STOCK)<<"CANT NO VEND"
            <<setw(MAX_TAM_DIN)<<"MONT NO VEND"   
            <<endl;            
    imprimeLinea(archivo, '=');
    
    struct NodoArticulo *ptr = lista;
    struct Articulo articulo;
    int cont = 0;
    double ingresosVentas = 0, perdidoFalta = 0;
    while(ptr){
        articulo = ptr->articulo;
        archivo<<left
                <<setw(MAX_TAM_CONT)<<cont+1
                <<setw(MAX_TAM_COD)<<articulo.codigo
                <<setw(MAX_TAM_DESCR)<<articulo.descripcion
                <<right<<setw(MAX_TAM_STOCK/2)<<articulo.stock<<setw(MAX_TAM_STOCK/2)<<' '
                <<setw(MAX_TAM_DIN/2)<<articulo.precio<<setw(MAX_TAM_DIN/2)<<' '
                <<setw(MAX_TAM_STOCK/2)<<articulo.cantidadVendida<<setw(MAX_TAM_STOCK/2)<<' '
                <<setw(MAX_TAM_DIN/2)<<articulo.montoVendido<<setw(MAX_TAM_DIN/2)<<' '
                <<setw(MAX_TAM_STOCK/2)<<articulo.cantidadNoVendida<<setw(MAX_TAM_STOCK/2)<<' '
                <<setw(MAX_TAM_DIN/2)<<articulo.montoNoVendido<<setw(MAX_TAM_DIN/2)<<' '<<left
                <<endl;
        ingresosVentas += articulo.montoVendido;
        perdidoFalta += articulo.montoNoVendido;
        
        cont++;
        ptr = ptr->siguiente;
    }
    imprimeLinea(archivo, '=');
    archivo<<"TOTAL DE INGREOS POR VENTAS, DESCONTANDO PAGOS: "<<ingresosVentas<<endl
            <<"TOTAL PERDIDO POR FALTA DE STOCK: "<<perdidoFalta<<endl;
    imprimeLinea(archivo, '=');
}
void imprimeVendedores(const char *nombreArchivo, struct NodoVendedor *lista){    
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_TAM_LIN/2)<<"LISTADO DE VENDEDORES"<<endl;
    
    struct NodoVendedor *ptr = lista;
    struct Vendedor vendedor;
    int cont = 0;
    double ganado = 0, supuesto = 0, perdido = 0;
    while(ptr){
        imprimeLinea(archivo, '=');
        archivo<<left
                <<setw(MAX_TAM_CONT)<<"No."
                <<setw(MAX_TAM_COD+MAX_TAM_NOMB)<<"VENDEDOR"
                <<setw(MAX_TAM_PORC)<<"% VENTAS"
                <<setw(MAX_TAM_DIN)<<"CUOTA MIN"                
                <<setw(MAX_TAM_DIN)<<"TOTAL VEND"                
                <<setw(MAX_TAM_DIN)<<"TOTAL NO VEND"                
                <<endl;            
        imprimeLinea(archivo, '=');
        
        vendedor = ptr->vendedor;
        archivo<<left
                <<setw(MAX_TAM_CONT)<<cont+1
                <<setw(MAX_TAM_COD)<<vendedor.codigo
                <<setw(MAX_TAM_NOMB)<<vendedor.nombre
                <<setw(MAX_TAM_PORC)<<vendedor.porcentajeVentas
                <<setw(MAX_TAM_DIN)<< vendedor.cuotaMinima
                <<setw(MAX_TAM_DIN)<<vendedor.montoVendido       
                <<setw(MAX_TAM_DIN)<<vendedor.montoNoVendido       
                <<endl;
        imprimeLinea(archivo, '-');
        /*
         * HACER EL PAGO Y ESO COMO PIDE EL DOC
         * se puede modular int realizaPago(){}
         * y luego solo se muestra el pago
         */
        archivo<<setw(TAB)<<' '
                <<"ARTICULOS VENDIDOS"<<endl;
        imprimeArticulo(archivo, vendedor.articulosVendidos, vendedor.cantidadArticulosVendidos, 
                ganado);
        archivo<<setw(TAB)<<' '
                <<"ARTICULOS NO VENDIDOS"<<endl;
        imprimeArticulo(archivo, vendedor.articulosNoVendidos, vendedor.cantidadArticulosNoVendidos, 
                perdido);
        supuesto = ganado+perdido;
        
        archivo<<"TOTAL PAGADO AL VENDEDOR: "<<ganado<<endl
                <<"TOTAL PAGADO AL VENDEDOR SI SE HUBIERAN VENDIDO TODOS LOS PRODUCTOS: "<<supuesto<<endl
                <<"TOTAL PERDDIDO POR FALTA DE STOCK: "<<perdido<<endl;                
        cont++;
        ptr = ptr->siguiente;
    }            
}
void imprimeArticulo(ofstream &archivo, struct ArticuloPedido *articulos, int cantidad, 
        double &suma){    
    archivo<<left<<setw(TAB)<<' '
            <<setw(MAX_TAM_CONT)<<"No."
            <<setw(MAX_TAM_COD)<<"ARTICULO"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
            <<setw(MAX_TAM_DIN)<<"MONTO"
            <<setw(MAX_TAM_FECHA)<<"FECHA"
            <<endl;
    for (int i = 0; i < cantidad; i++) {
        archivo<<left<<setw(TAB)<<' '
                <<setw(MAX_TAM_CONT)<<i+1
                <<setw(MAX_TAM_COD)<<articulos[i].codigo
                <<right<<setw(MAX_TAM_CANT/2)<<articulos[i].cantidad<<setw(MAX_TAM_CANT/2)<<' '
                <<setw(MAX_TAM_DIN/2)<<articulos[i].total<<setw(MAX_TAM_DIN/2)<<' '<<left;
        imprimeFecha(archivo, articulos[i].fechaUltima);
        archivo<<endl;
        suma+=articulos[i].total;
    }
    imprimeLinea(archivo, '.');
}

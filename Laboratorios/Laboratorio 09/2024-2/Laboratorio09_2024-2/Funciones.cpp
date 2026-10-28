/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 15 de junio de 2025, 02:21 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Distrito.h"
#include "Plato.h"
#include "Cliente.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_PLATO_CODIGO 9

#define TAB 8
#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOMB 50
#define MAX_TAM_DIST 25
#define MAX_TAM_DIN 12
#define MAX_TAM_DESC 50
#define MAX_TAM_CANT 13

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[100], *cad;    
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char[strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
    
}
void leePlatos(const char *nombreArchivo, struct Plato *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //BE-39584,COCA COLA 1 LITRO,15.50,BEBIDAS
        arr[cantidad].codigo=leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        arr[cantidad].descripcion=leeCadenaExacta(archivo, ',');
        archivo>>arr[cantidad].precio;
        archivo.get();
        arr[cantidad].categoria=leeCadenaExacta(archivo, '\n');
        
        arr[cantidad].cantidad=0;
        
        cantidad++;

    }
}
void leeDistritos(const char *nombreArchivo, struct Distrito *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        arr[cantidad].codigo=leeCadenaExacta(archivo, ',');
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //LE3801,Cieneguilla,ESTE
        arr[cantidad].codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        arr[cantidad].nombre = leeCadenaExacta(archivo, ',');
        arr[cantidad].ubicacion = leeCadenaExacta(archivo, '\n');
        
        cantidad++;
    }
}
void leeClientes(const char *nombreArchivo, struct Cliente *arr, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //51465986,CAMACHO AGUERO ELIA ROSA,LE3716
        archivo>>arr[cantidad].dni;
        if(archivo.eof()) break;
        archivo.get();
        arr[cantidad].nombre=leeCadenaExacta(archivo, ',');
        arr[cantidad].distrito.codigo=leeCadenaExacta(archivo, '\n');
        
        arr[cantidad].cantidadDePedidos=0;
        arr[cantidad].montoTotal=0;
        arr[cantidad].distrito.nombre = NULL;
        arr[cantidad].distrito.ubicacion = NULL;                

        cantidad++;
    }
}

void leePedidos(const char *nombreArchivo,
            struct Plato *arrPlatos, int cantidadPlatos,
            struct Distrito *arrDistritos, int cantidadDistritos, 
            struct Cliente *arrClientes, int cantidadClientes){
     ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoPedido, dniCliente, cantidadPedida;
    char codigoPlato[MAX_CAR_PLATO_CODIGO]{};
    while(true){
        //261051        36471787      BR-15665        5
        archivo>>codigoPedido;
        if(archivo.eof()) break;
        archivo>>dniCliente>>codigoPlato>>cantidadPedida;
        
        int posPlato = buscaPlato(arrPlatos, cantidadPlatos, codigoPlato), 
                posCliente = buscaCliente(arrClientes, cantidadClientes, dniCliente);
        
        if(posPlato!=NO_ENCONTRADO and posCliente!=NO_ENCONTRADO){
            //primero con los pedidos del cliente
            struct Cliente &cliente = arrClientes[posCliente];
            struct Plato &plato = arrPlatos[posPlato];           
            int posPedido = buscaPedido(cliente.pedidos, cliente.cantidadDePedidos, 
                    codigoPedido, plato.codigo);
            if(posPedido == NO_ENCONTRADO)
                posPedido = agregapedido(cliente.pedidos, cliente.cantidadDePedidos, 
                        codigoPedido, plato);
            struct PlatoPedido &pedido = cliente.pedidos[posPedido];
            pedido.cantidad+=cantidadPedida;
            pedido.subtotal+=cantidadPedida*pedido.precio;                                   
            cliente.montoTotal+=cantidadPedida*pedido.precio;
            
            //ahora con el distrito del cliente
            int posDistrito = buscaDistrito(arrDistritos, cantidadDistritos, cliente.distrito.codigo);
            if(posDistrito!= NO_ENCONTRADO){
                cliente.distrito.nombre = copiaCadChar(arrDistritos[posDistrito].nombre);
                cliente.distrito.ubicacion = copiaCadChar(arrDistritos[posDistrito].ubicacion);                            
            }
        }
    }
}


//BUSQUEDA
int buscaPlato(struct Plato *arr, int cantidad, const char *codigo){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(arr[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCliente(struct Cliente *arr, int cantidad, int dni){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i].dni==dni) return i;
    }
    return NO_ENCONTRADO;
}
int buscaPedido(struct PlatoPedido *arr, int cantidad, 
        int codigo, const char *codigoPlato){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i].codigoPedido==codigo and strcmp(arr[i].codigoPlato, codigoPlato)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaDistrito(struct Distrito *arr, int cantidad, const char *codigo){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(arr[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;    
}
//AGREGAR
int agregapedido(struct PlatoPedido *pedidos, int &cantidad, 
        int codigo, struct Plato plato){
    pedidos[cantidad].codigoPedido=codigo;
    pedidos[cantidad].cantidad=0;
    pedidos[cantidad].subtotal=0;    
    pedidos[cantidad].codigoPlato=copiaCadChar(plato.codigo);
    pedidos[cantidad].descripcion=copiaCadChar(plato.descripcion);
    pedidos[cantidad].precio=plato.precio;
    
    cantidad++;
    return cantidad-1;
}
char *copiaCadChar(const char *cad){
    char *aux;
    aux = new char [strlen(cad)+1]{};
    strcpy(aux, cad);
    
    return aux;
}

//ORDENAMIENTO
void ordenaClientes(struct Cliente *arrClientes, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int k = i+1; k < cantidad; k++) {            
            if(strcmp(arrClientes[i].nombre, arrClientes[k].nombre)>0){
//            if(arrClientes[i].montoTotal < arrClientes[k].montoTotal){
                cambiaCliente(arrClientes[i], arrClientes[k]);
            }
        }
    }
    
    for (int i = 0; i < cantidad; i++) {        
        for (int j = 0; j < arrClientes[i].cantidadDePedidos-1; j++) {           
            for (int k = j+1; k < arrClientes[i].cantidadDePedidos; k++) {                
                if(arrClientes[i].pedidos[j].codigoPedido>arrClientes[i].pedidos[k].codigoPedido
                        or
                        (arrClientes[i].pedidos[j].codigoPedido==arrClientes[i].pedidos[k].codigoPedido
                            and 
                        strcmp(arrClientes[i].pedidos[j].codigoPlato, arrClientes[i].pedidos[k].codigoPlato)<0))
                    cambiaPedido(arrClientes[i].pedidos[j], arrClientes[i].pedidos[k]);
            }

        }

    }


}
void cambiaCliente(struct Cliente &cliente1, struct Cliente &cliente2){
    struct Cliente aux;
    aux = cliente1;
    cliente1 = cliente2;
    cliente2=aux;
}
void cambiaPedido(struct PlatoPedido &plato1, struct PlatoPedido &plato2){
    struct PlatoPedido aux;
    aux = plato1;
    plato1 = plato2;
    plato2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {
        archivo<<c;        
    }
    archivo<<endl;
}
void emiteReporte(const char *nombreArchivo, struct Cliente *arr, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    for (int i = 0; i < cantidad; i++) {        
        struct Cliente cliente = arr[i];
        if(cliente.cantidadDePedidos>0){
            imprimeLinea(archivo, '=');
            imprimeEncabezadoClientes(archivo);
            archivo<<left
                    <<setw(MAX_TAM_COD)<<cliente.dni
                    <<setw(MAX_TAM_NOMB)<<cliente.nombre
                    <<setw(MAX_TAM_COD)<<cliente.distrito.codigo
                    <<setw(MAX_TAM_DIST)<<cliente.distrito.nombre
                    <<setw(MAX_TAM_DIN)<<cliente.montoTotal                
                    <<endl;
            imprimeLinea(archivo, '-');                    
            imprimeEncabezadoPedidos(archivo);
            for (int j = 0; j < cliente.cantidadDePedidos; j++) {            
                struct PlatoPedido pedido = cliente.pedidos[j];
                archivo<<left<<setw(TAB)<<' '
                        <<setw(MAX_TAM_COD)<<pedido.codigoPedido
                        <<setw(MAX_TAM_COD)<<pedido.codigoPlato
                        <<setw(MAX_TAM_DESC)<<pedido.descripcion
                        <<setw(MAX_TAM_DIN)<<pedido.precio
                        <<setw(MAX_TAM_CANT)<<pedido.cantidad
                        <<setw(MAX_TAM_DIN)<<pedido.subtotal
                        <<endl;                        
            
        }
        }        
    }
}
void imprimeEncabezadoClientes(ofstream &archivo){
    archivo<<left
            <<setw(MAX_TAM_COD)<<"DNI"
            <<setw(MAX_TAM_NOMB)<<"NOMBRE"
            <<setw(MAX_TAM_COD+MAX_TAM_DIST)<<"DISTRITO"            
            <<setw(MAX_TAM_DIN)<<"TOTAL"           
            <<endl;
    
}
void imprimeEncabezadoPedidos(ofstream &archivo){
    archivo<<left<<setw(TAB)<<' '
            <<setw(MAX_TAM_COD)<<"PEDIDO"
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_DESC)<<"DESCRIPCION"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_CANT)<<"CANTIDA"
            <<setw(MAX_TAM_DIN)<<"SUBTOTAL"
            <<endl;                            
}
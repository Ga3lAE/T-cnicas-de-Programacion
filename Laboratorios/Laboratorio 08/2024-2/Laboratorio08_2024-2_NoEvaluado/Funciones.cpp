/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 14 de junio de 2025, 10:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_PLATO_COD 9

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_DIN 12
#define MAX_TAM_NOM 50
#define MAX_TAM_DIST 30
#define MAX_TAM_VEH 25
#define MAX_TAM_DESC 50
#define MAX_TAM_CAT 25
#define MAX_TAM_CANT 10

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[100], *cad;
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    
    return cad;
}

void leePlatos(const char *nombreArchivo, int &cantidad,
        char **arrCodigoPlatos, char **arrDescripcionPlatos,
        double *arrPrecioPlato, char **arrCategoriaPlato, 
        double *arrDescuentoPlatos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //PO-11283,2 BOLAS DE HELADO,14.90,POSTRES,17.72%
        arrCodigoPlatos[cantidad] = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        arrDescripcionPlatos[cantidad] = leeCadenaExacta(archivo, ',');
        archivo>>arrPrecioPlato[cantidad];
        archivo.get();
        arrCategoriaPlato[cantidad] = leeCadenaExacta(archivo, ',');
        if(archivo.get() != '\n'){ // hay descuento
            archivo>>arrDescuentoPlatos[cantidad];
            while(archivo.get()!='\n');
        }
        
        cantidad++;
    }
}

void leeDistritos(const char *nombreArchivo, int &cantidad,
        char **arrCodigo, char **arrNombre,
        char **arrUbicacion){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //LN7093,Independencia,Norte
        arrCodigo[cantidad] = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        arrNombre[cantidad] = leeCadenaExacta(archivo, ',');
        arrUbicacion[cantidad] = leeCadenaExacta(archivo, '\n');        
        
        cantidad++;
    }
}

void leeClientes(const char *nombreArchivo, int &cantidad,
        int *arrDniClientes, char **arrNombreClientes,
        char **arrDistritoClientes, char **arrVehiculoClientes,
        double *arrDescuentoClientes){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //66039166,LAURA WONG MELVIN HENRRY,LO3562,Bicicleta,
        archivo>>arrDniClientes[cantidad];      
        if(archivo.eof()) break;
        archivo.get();
        arrNombreClientes[cantidad] = leeCadenaExacta(archivo, ',');
        arrDistritoClientes[cantidad] = leeCadenaExacta(archivo, ',');
        arrVehiculoClientes[cantidad] = leeCadenaExacta(archivo, ',');                
        if(archivo.get() != '\n'){ // hay descuento
            archivo>>arrDescuentoClientes[cantidad];
            while(archivo.get()!='\n');
        }
                
        cantidad++;
    }
}

void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *arrCodigoReprtidores, char **arrNombreRepartidores,
        char **arrVehiculoRepartidores, char **arrDistritorepartidores){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //60685215,Sakaguchi Mori Carlos Ronal,Motocicleta,LN1439
        archivo>>arrCodigoReprtidores[cantidad];      
        if(archivo.eof()) break;
        archivo.get();
        arrNombreRepartidores[cantidad] = leeCadenaExacta(archivo, ',');
        arrVehiculoRepartidores[cantidad] = leeCadenaExacta(archivo, ',');
        arrDistritorepartidores[cantidad] = leeCadenaExacta(archivo, '\n');
        
        cantidad++;
    }
}

void leePedidos(const char *nombreArchivo, int &cantidad,
            int *arrCodigoPedidos, double *arrIngresoBrutoPedidos, 
            double *arrIngresoDescuentoPedidos, double *arrIngresoNetoPedidos, 
            int *arrClienteDniPedidos, char **arrClienteNombrePedidos, char **arrClienteDistritoPedidos,  
            int *arrRepartidorDniPedidos, char **arrRepartidorNombrePedidos, char **arrRepartidorVehiculoPedidos, 
            double *arrPagoRepartidorPedidos,
        int cantidadPlatos, char **arrCodigoPlatos,
            double *arrPrecioPlato, double *arrDescuentoPlatos,
            int *arrCantidadPlatos, double *arrMontoVendidoPlatos, double *arrDescuentoPlatoPlatos,
            double *arrDescuentoClientePlatos, double *arrTotalIngresadoPlatos,         
        int cantidadDistritos, char **arrCodigoDistritos, char **arrNombredistritos, 
        int cantidadClientes, int *arrDniClientes, char **arrNombreClientes, 
            char **arrDistritoClientes, char **arrVehiculoClientes,
            double *arrDescuentoClientes,
        int cantidadRepartidores, int *arrCodigoRepartidores,
            char **arrVehiculoRepartidores, char **arrDistritorepartidores, 
            char **arrNombreRepartidores){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    int codigoPedido, dniComprador, cantidadPedida;
    char codigoPlato[MAX_CAR_PLATO_COD]{};
    double porcentajeRepartidor=0;
        
    while(true){
        //798625        99774549         BE-39738         9
        archivo>>codigoPedido;    
        if(archivo.eof()) break;
        archivo>>dniComprador>>codigoPlato>>cantidadPedida;
        int posPedido, posCliente, posPlato, posDistrito, posRepartidor;
        posPedido = buscaInt(arrCodigoPedidos, cantidad, codigoPedido);
        posCliente = buscaInt(arrDniClientes, cantidadClientes, dniComprador);
        posPlato = buscaCadChar(arrCodigoPlatos, cantidadPlatos, codigoPlato);
        if(posCliente!=NO_ENCONTRADO and posPlato!=NO_ENCONTRADO){
            if(posPedido == NO_ENCONTRADO){
                posDistrito = buscaCadChar(arrCodigoDistritos, cantidadDistritos, arrDistritoClientes[posCliente]);
                if(posDistrito!=NO_ENCONTRADO){
                posRepartidor = buscaCadCharDoble(arrDistritorepartidores, arrVehiculoRepartidores, cantidadRepartidores, 
                                arrDistritoClientes[posCliente], arrVehiculoClientes[posCliente]);                
                    if(posPedido==NO_ENCONTRADO){
                        arrCodigoPedidos[cantidad] = codigoPedido;
                        arrClienteDniPedidos[cantidad] = arrDniClientes[posCliente];
                        arrClienteNombrePedidos[cantidad] = duplicaCadChar(arrNombreClientes[posCliente]);
                        arrClienteDistritoPedidos[cantidad] = duplicaCadChar(arrNombredistritos[posDistrito]);

                        arrRepartidorDniPedidos[cantidad] = arrCodigoRepartidores[posRepartidor];
                        arrRepartidorVehiculoPedidos[cantidad] = duplicaCadChar(arrVehiculoRepartidores[posRepartidor]);
                        arrRepartidorNombrePedidos[cantidad] = duplicaCadChar(arrNombreRepartidores[posRepartidor]);
                        cout<<cantidad<<"  "<<arrRepartidorNombrePedidos[cantidad]<<endl;
                        if(strcmp(arrVehiculoRepartidores[posRepartidor], "Bicicleta") == 0) porcentajeRepartidor = 5;
                        else porcentajeRepartidor = 10;

                        posPedido = cantidad;
                        cantidad++;                        
                    }
                }
            }
            //ya tenemos la posicion del pedido
            if(posCliente!=NO_ENCONTRADO and posPlato!=NO_ENCONTRADO){
                //primero con los pedidos
                arrIngresoBrutoPedidos[posPedido] +=cantidadPedida*arrPrecioPlato[posPlato];
                arrIngresoDescuentoPedidos[posPedido] += 
                        (arrDescuentoClientes[posCliente] + arrDescuentoPlatos[posPlato])/100.0*cantidadPedida*arrPrecioPlato[posPlato];
                arrIngresoNetoPedidos[posPedido] = arrIngresoBrutoPedidos[posPedido] - 
                        arrIngresoDescuentoPedidos[posPedido];
                arrPagoRepartidorPedidos[posPedido] = porcentajeRepartidor/100.0*arrIngresoNetoPedidos[posPedido];                                                
                //luego con los platos
                arrCantidadPlatos[posPlato] += cantidadPedida;
                arrMontoVendidoPlatos[posPlato] += cantidadPedida*arrPrecioPlato[posPlato];                
                arrDescuentoPlatoPlatos[posPlato] += arrDescuentoPlatos[posPlato]/100*cantidadPedida*arrPrecioPlato[posPlato];
                arrDescuentoClientePlatos[posPlato] += arrDescuentoClientes[posCliente]/100*cantidadPedida*arrPrecioPlato[posPlato];
                arrTotalIngresadoPlatos[posPlato] = arrMontoVendidoPlatos[posPlato] - (arrDescuentoClientePlatos[posPlato] + arrDescuentoPlatoPlatos[posPlato]);
            }            
        }        
    }
}
char *duplicaCadChar(const char *cad){
    char *aux;
    aux = new char[strlen(cad)+1]{};
    strcpy(aux, cad);
    return aux;
}
//BUSQUEDA
int buscaInt(int *arr, int cantidad, int el){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i] == el) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCadChar(char **arr, int cantidad, const char *el){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(arr[i], el)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCadCharDoble(char **arr1, char **arr2,  int cantidad, 
        const char *el1, const char *el2){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(arr1[i], el1)==0 and strcmp(arr2[i], el2)==0) return i;
    }
    return NO_ENCONTRADO;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void emiteReporte(const char *nombreArchivoPedidos, int cantidadPedidos,
            int *arrCodigoPedidos, double *arrIngresoBrutoPedidos,
            double *arrIngresoDescuentoPedidos, double *arrIngresoNetoPedidos,
            int *arrClienteDniPedidos, char **arrClienteNombrePedidos, char **arrClienteDistritoPedidos,
            int *arrRepartidorDniPedidos, char **arrRepartidorNombrePedidos, char **arrRepartidorVehiculoPedidos,
            double *arrPagoRepartidorPedidos, 
        const char *nombreArchivoPlatos, int cantidadPlatos,
            char **arrCodigoPlatos, char **arrDescripcionPlatos, char **arrCategoriaPlato,
            double *arrPrecioPlato, double *arrDescuentoPlatos,
            int *arrCantidadPlatos, double *arrMontoVendidoPlatos, double *arrDescuentoPlatoPlatos,
            double *arrDescuentoClientePlatos, double *arrTotalIngresadoPlatos){
    ofstream archivoPedidos(nombreArchivoPedidos, ios::out);
    if(not archivoPedidos.is_open()){
        cout<<"ERROR: No se puddo abrir "<<nombreArchivoPedidos;
        exit(1);
    }
    archivoPedidos<<fixed<<setprecision(2);
    ofstream archivoPlatos(nombreArchivoPlatos, ios::out);
    if(not archivoPlatos.is_open()){
        cout<<"ERROR: No se puddo abrir "<<nombreArchivoPlatos;
        exit(1);
    }
    archivoPlatos<<fixed<<setprecision(2);
    
    for (int i = 0; i < cantidadPedidos; i++) {        
        archivoPedidos<<left
                <<setw(MAX_TAM_COD)<<arrCodigoPedidos[i]
                <<setw(MAX_TAM_DIN)<<arrIngresoBrutoPedidos[i]
                <<setw(MAX_TAM_DIN)<<arrIngresoDescuentoPedidos[i]
                <<setw(MAX_TAM_DIN)<<arrIngresoNetoPedidos[i]
                <<setw(MAX_TAM_COD)<<arrClienteDniPedidos[i]
                <<setw(MAX_TAM_NOM)<<arrClienteNombrePedidos[i]
                <<setw(MAX_TAM_DIST)<<arrClienteDistritoPedidos[i]
                <<setw(MAX_TAM_COD)<<arrRepartidorDniPedidos[i]
                <<setw(MAX_TAM_NOM)<<arrRepartidorNombrePedidos[i]
                <<setw(MAX_TAM_VEH)<<arrRepartidorVehiculoPedidos[i]
                <<setw(MAX_TAM_DIN)<<arrPagoRepartidorPedidos[i]
                <<endl;
    }
    
    for (int i = 0; i < cantidadPlatos; i++) {        
        archivoPlatos<<left
                <<setw(MAX_TAM_COD)<<arrCodigoPlatos[i]
                <<setw(MAX_TAM_DESC)<<arrDescripcionPlatos[i]
                <<setw(MAX_TAM_CAT)<<arrCategoriaPlato[i]
                <<setw(MAX_TAM_DIN)<<arrPrecioPlato[i]
                <<setw(MAX_TAM_DIN)<<arrDescuentoPlatos[i]
                <<setw(MAX_TAM_CANT)<<arrCantidadPlatos[i]
                <<setw(MAX_TAM_DIN)<<arrMontoVendidoPlatos[i]
                <<setw(MAX_TAM_DIN)<<arrDescuentoPlatoPlatos[i]
                <<setw(MAX_TAM_DIN)<<arrDescuentoClientePlatos[i]                
                <<setw(MAX_TAM_DIN)<<arrTotalIngresadoPlatos[i]                
                <<endl;
    }


    
}
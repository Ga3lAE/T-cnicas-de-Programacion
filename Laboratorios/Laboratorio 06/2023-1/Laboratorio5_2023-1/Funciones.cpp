/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 31 de mayo de 2025, 09:55 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_CANT 8
//#define MAX_TAM_

//LECTURA
void leeStock(const char *nombreArchivo, int &cantidad,
        int *arrCodigoProductos, int *arrAlmacenProsducto, int *arrStockProductos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //74543    10007    263
        archivo>>arrCodigoProductos[cantidad];
        if(archivo.eof()) break;
        archivo>>arrAlmacenProsducto[cantidad]
                >>arrStockProductos[cantidad];
        
        cantidad++;
    }
    
}
void leeFecha(int &fecha){
    int dd, mm, aa;
    char sep;
    
    cin>>dd>>sep
            >>mm>>sep
            >>aa;
    
    fecha = aa*10000 + mm*100 + dd;
}
//VERIFICACION
void verificaStock(const char *nombreArchivo, int cantidad,
        int *arrCodigoProductos, int *arrAlmacenProsducto, int *arrStockProductos){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_TAM_LIN/2)<<"VERIFICACION DE STOCK"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_COD)<<"ALMACEN"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
            <<endl;
    
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_TAM_COD)<<arrCodigoProductos[i]
                <<setw(MAX_TAM_COD)<<arrAlmacenProsducto[i]
                <<setw(MAX_TAM_CANT)<<arrStockProductos[i]
                <<endl;

    }

}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

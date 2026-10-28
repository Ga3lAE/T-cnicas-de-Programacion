/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 27 de mayo de 2025, 05:24 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_DESC_PLATO 100
#define MAX_CAR_CATG_PLATO 40

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_DIN 16
#define MAX_TAM_CANT 20
#define MAX_TAM_CONT 5
#define MAX_TAM_DESC 60

//LECTURA
void leeRepartos(const char *nombreArchivo, int &cantidad,
        int *codigos, int *numeros){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    int dni, codigoPedido;   
    while(true){
        //961419   77324146   9   53764   4   90766   1   90758
        archivo>>dni;
        if(archivo.eof()) break;
        archivo>>codigoPedido;
        
        int codigoPlato, cantidadPedida;
        while(true){
            if(archivo.get()=='\n') break;
            archivo>>cantidadPedida>>codigoPlato;
            
            int posPlato = buscaIntBinDesc(codigos, cantidad, codigoPlato);
            if(posPlato==NO_ENCONTRADO){
                agregaPlato(codigos, numeros, cantidad, 
                        codigoPlato, cantidadPedida);
            }
            else{
                numeros[posPlato]+=cantidadPedida;
            }
        }
        
    }   
}
void leePlatos(const char *nombreArchivo, int cantidad, 
        int *codigos, int *numeros,
        double *precios, double *ingresos,
        bool *tienenDescuentos, double *descuentos, double *totales){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    int codigo;        
    while(true){
        //53546   CHOCLO     9.9   BEBIDAS      7.19%
        archivo>>codigo;
        if(archivo.eof()) break;
        
        int posPlato = buscaIntBinDesc(codigos, cantidad, codigo);
        if(posPlato == NO_ENCONTRADO)
            while(archivo.get()!='\n');
        else{
            char aux[100];
            archivo>>aux>>precios[posPlato]>>aux;                                    

            tienenDescuentos[posPlato] = archivo.get()!='\n';

            if(tienenDescuentos[posPlato]){
                archivo>>descuentos[posPlato];
                archivo.get();
            }
            else
                descuentos[posPlato] = 0;
            
            ingresos[posPlato] += numeros[posPlato]*precios[posPlato];
            totales[posPlato] += numeros[posPlato]*precios[posPlato]*(1-descuentos[posPlato]/100.0);
        }
    }
}
//BUSQUEDA
int buscaIntBinDesc(int *arr, int cantidad, int elemento){
    int inicio=0, fin=cantidad-1, medio;
    while(true){
        medio = (inicio+fin)/2;

        if(inicio>fin) return NO_ENCONTRADO;

        if(arr[medio]==elemento) return medio;
        else if(arr[medio]>elemento) inicio = medio+1;
        else if(arr[medio]<elemento) fin = medio-1;
    }
}
//INSERCION
void agregaPlato(int *codigos, int *numeros, int &cantidad, 
        int codigo, int numero){
    int i;
    for (i= cantidad-1; i>=0 and codigos[i]<codigo; i--) {
        //recorremos los elementos
        codigos[i+1] = codigos[i];
        numeros[i+1] = numeros[i];
    }
    codigos[i+1] = codigo;
    numeros[i+1] = numero;
    
    cantidad++;
}
//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void verificaArreglos(const char *nombreArchivo, int cantidad,
        int *codigos, double *precios, int *platosVendidos,
        double *ingresosBruto, double *totales,
        bool *tieneDescuento, double *descuentos){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivo<<endl;
        exit(1);
    }  
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_TAM_LIN/2)<<"VERIFICACION DE LECTURA DE PLATOS"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_CANT)<<"VENDIDOS"
            <<setw(MAX_TAM_DIN)<<"BRUTOS"
            <<setw(MAX_TAM_DIN)<<"TOTALES"
            <<setw(MAX_TAM_DIN)<<"DESCUENTO"
            <<endl;
    imprimeLinea(archivo, '=');
    
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
            <<setw(MAX_TAM_COD)<<codigos[i]
            <<right<<setw(MAX_TAM_DIN/2)<<precios[i]<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_CANT/2)<<platosVendidos[i]<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_DIN/2)<<ingresosBruto[i]<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_DIN/2)<<totales[i]<<setw(MAX_TAM_DIN/2)<<' '<<left;
        if(tieneDescuento[i])
            archivo<<setw(MAX_TAM_DIN/2)<<descuentos[i]<<setw(MAX_TAM_DIN/2)<<' '<<left;;
        archivo<<endl;
    }

}
void emiteReporte(const char *nombreArchivoPlatos, const char *nombreArchivoReporte,
        int cantidadPlatos,
        int *arrCodigosPlatos, double *arrPrecio, int *arrNumPlatosVendidos,
        double *arrIngresoBruto, double *arrTotal,
        bool *arrTieneDescuento, double *arrDescuento){
    
    ifstream archivoPlatos(nombreArchivoPlatos, ios::in);
    if(not archivoPlatos.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoPlatos<<endl;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoReporte<<endl;
        exit(1);
    }  
    archivoReporte<<fixed<<setprecision(2);
    
    imprimeEncabezado(archivoReporte);
    
    for (int i = 0; i < cantidadPlatos; i++) {        
         archivoReporte<<left
                <<setw(3)<<i+1<<setw(MAX_TAM_CONT-3)<<')'
                <<setw(MAX_TAM_COD)<<arrCodigosPlatos[i];                
        imprimeDescripcion(archivoPlatos, archivoReporte, 
                arrCodigosPlatos[i], arrTieneDescuento[i]);
        archivoReporte<<right<<setw(MAX_TAM_CANT/2)<<arrNumPlatosVendidos[i]<<setw(MAX_TAM_CANT/2)<<' '
                <<setw(MAX_TAM_DIN/2)<<arrPrecio[i]<<setw(MAX_TAM_DIN/2)<<' '                
                <<setw(MAX_TAM_DIN/2)<<arrIngresoBruto[i]<<setw(MAX_TAM_DIN/2)<<' ';
         imprimeDescuento(archivoReporte, arrTieneDescuento[i], arrDescuento[i]);
         archivoReporte<<setw(MAX_TAM_DIN/2)<<arrTotal[i]<<setw(MAX_TAM_DIN/2)<<' '
                <<endl;
    }

}
void imprimeEncabezado(ofstream &archivo){
    archivo<<setw(MAX_TAM_LIN/2)<<"EMPRESA DE REPATOS A DOMICILIO TP S.A."<<endl
            <<setw(MAX_TAM_LIN/2)<<"RELACION DE PLATOS ATENDIDOS"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_CONT)<<"No."
            <<setw(MAX_TAM_COD+MAX_TAM_DESC)<<"PLATO OFRECIDO"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD VENDIDA"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_DIN)<<"INGRESO BRUTO"
            <<setw(MAX_TAM_DIN)<<"DESCUENTO"
            <<setw(MAX_TAM_DIN)<<"TOTAL"
            <<endl            ;
    imprimeLinea(archivo, '=');
    
}
void imprimeDescripcion(ifstream &archivoPlatos, ofstream &archivoReporte, 
        int codigo, bool hayDescuento){
    
    archivoPlatos.clear();
    archivoPlatos.seekg(0, ios::beg);
    
    int codigoActual;
    double precio;
    char descripcion[MAX_CAR_DESC_PLATO]{}, 
            categoria[MAX_CAR_CATG_PLATO]{}, 
            descripcionCompleta[MAX_CAR_CATG_PLATO+MAX_CAR_DESC_PLATO]{}, 
            cadenaDescuento [] = "PROMOCIONADO", 
            separador = '-';
    while(true){
        //39199     LIMONADA_1_LITRO    10.5    POSTRES
        archivoPlatos>>codigoActual;
        if(archivoPlatos.eof()) break;
        if(codigoActual != codigo){
            while(archivoPlatos.get()!='\n');
        }
        else{
            archivoPlatos>>descripcion>>precio>>categoria;
            while(archivoPlatos.get()!='\n');
            
            procesaCadena(descripcionCompleta, descripcion, categoria, 
                    cadenaDescuento, separador, hayDescuento);
            
            archivoReporte<<setw(MAX_TAM_DESC)<<descripcionCompleta;
            
        }        
    }    
}
void procesaCadena(char *descripcionCompleta, char *descripcion, char *categoria,
        char *cadenaDescuento, char separador, bool hayDescuento){
    int posCadena=0;
    bool esMinus = false;
    
    for (int i = 0; i < descripcion[i]; i++, posCadena++) {
        if(esMinus){
            if(descripcion[i]<='Z' and descripcion[i]>='A')descripcion[i]-='A'-'a';
        }                
        if(descripcion[i] == '_') {            
            descripcion[i] = ' ';
            esMinus = false;
        }
        else esMinus = true;
        
        descripcionCompleta[posCadena] = descripcion[i];        
    }
    descripcionCompleta[posCadena] = 0;
    
    if(hayDescuento){
        descripcionCompleta[posCadena] = separador;
        posCadena++;
        for (int i =0; i < cadenaDescuento[i]; i++, posCadena++) {
            descripcionCompleta[posCadena] = cadenaDescuento[i];
        }
        descripcionCompleta[posCadena] = 0;
    }
    
    descripcionCompleta[posCadena] = separador;
    posCadena++;
    
    for (int i = 0; categoria[i]; i++, posCadena++) {
        descripcionCompleta[posCadena] = categoria[i];
    }
    descripcionCompleta[posCadena] = 0;
}
void imprimeDescuento(ofstream &archivo, bool hay, double descuento){
    if(hay)
        archivo<<setw(MAX_TAM_DIN/2)<<descuento<<setw(MAX_TAM_DIN/2)<<' ';
    else
        archivo<<setw(MAX_TAM_DIN/2)<<'-'<<setw(MAX_TAM_DIN/2)<<' ';
    
}


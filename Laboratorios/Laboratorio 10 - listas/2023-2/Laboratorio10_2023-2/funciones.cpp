#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "ArticuloVendido.h"
#include "Vendedor.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 200
#define ALING 5
#define MAX_CAR_CONT 5
#define MAX_CAR_CANT 10
#define MAX_CAR_NOMBRE TAM_ART_DESC
#define MAX_CAR_PORC 15
#define MAX_CAR_DINERO 20
#define MAX_CAR_OBSERVA 25


void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void datosArchivoIf(int& tamArch, int tamElemento, int& cantidad, 
        ifstream& archivo){
    archivo.seekg(0, ios::end);
    tamArch = archivo.tellg();
    cantidad = tamArch/tamElemento;
    archivo.seekg(0, ios::beg);
}
void datosArchivoF(int& tamArch, int tamElemento, int& cantidad, 
        fstream& archivo){
    archivo.seekg(0, ios::end);
    tamArch = archivo.tellg();
    cantidad = tamArch/tamElemento;
    archivo.seekg(0, ios::beg);
}


void leeArticulos(const char* nombreArchivoLec, const char* nombreArchivoBin){
    ifstream archivoLec(nombreArchivoLec, ios::in);
    if(not archivoLec.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLec<<endl;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin<<endl;
        exit(1);
    }
    
    struct Articulo articulo;
    while(true){
        //BIT-434,Campana Extractora modelo Glass,375.09
        char codigo[TAM_ART_COD];
        archivoLec.getline(codigo, TAM_ART_COD, ',');
        if(archivoLec.eof()) break;
        strcpy(articulo.codigo, codigo);
        archivoLec.getline(articulo.descripcion, TAM_ART_DESC, ',');
        archivoLec>>articulo.precio;
        archivoLec.get();
        
        articulo.cantidadVendidos=0;
        articulo.montoVendido=0;        
        
        archivoBin.write(reinterpret_cast<const char*>(&articulo), sizeof(struct Articulo));
        
    }
}

void leeVendedores(const char* nombreArchivoLec, const char* nombreArchivoBin){
    ifstream archivoLec(nombreArchivoLec, ios::in);
    if(not archivoLec.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLec<<endl;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin<<endl;
        exit(1);
    }
    
    struct Vendedor vendedor;
    while(true){
        //11602775,HIJAR/ARCA/ADOLFO,18.75,67000.00
        int codigo;
        archivoLec>>codigo;
        if(archivoLec.eof()) break;
        vendedor.codigo = codigo;
        archivoLec.get();
        archivoLec.getline(vendedor.nombre, TAM_VEND_NOMBRE, ',');
        quitaGuiones(vendedor.nombre);
        archivoLec>>vendedor.porcentajeVentas;
        archivoLec.get();
        archivoLec>>vendedor.cuotaMinima;
        
        vendedor.cantidadVendidos=0;
        vendedor.montoTotal=0;

        archivoBin.write(reinterpret_cast<const char*>(&vendedor), sizeof(struct Vendedor));

        
    }
}
void quitaGuiones(char* cad){
    for (int i = 0; cad[i]; i++) {        
        if(cad[i] == '/') cad[i] = ' ';
    }

}

void leeVentas(const char* nombreArchivoLec, const char* nombreArchivoVendedores, 
        const char* nombreArchivoArticulos){
    ifstream archivoLec(nombreArchivoLec, ios::in);
    if(not archivoLec.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoLec<<endl;
        exit(1);
    }
    fstream archivoVendedores(nombreArchivoVendedores, ios::in|ios::out|ios::binary);
    if(not archivoVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoVendedores<<endl;
        exit(1);
    }
    fstream archivoArticulos(nombreArchivoArticulos, ios::in|ios::out|ios::binary);
    if(not archivoArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoArticulos<<endl;
        exit(1);
    }
    
    struct Articulo articulo;
    int tamArchivoArticulos, tamArticulo, cantArticulos;
    tamArticulo = sizeof(struct Articulo);
    datosArchivoF(tamArchivoArticulos, tamArticulo, cantArticulos, archivoArticulos);
    
    struct Vendedor vendedor;
    int tamArchivoVendedores, tamVendedor, cantVendedores;
    tamVendedor = sizeof(struct Vendedor);
    datosArchivoF(tamArchivoVendedores, tamVendedor, cantVendedores, archivoVendedores);
        
    while(true){
        // JCW-489     13245501      5
        char codigo[TAM_ART_COD];
        int nDNI, cantidadPedida;
        archivoLec>>codigo;
        if(archivoLec.eof()) break;
        archivoLec>>nDNI>>cantidadPedida;
        
        int posArticulo;
        posArticulo = buscaArticulo(codigo, archivoArticulos, cantArticulos);
        archivoArticulos.seekg(posArticulo*tamArticulo, ios::beg);
        archivoArticulos.read(reinterpret_cast<char*>(&articulo), tamArticulo); 
        
        int posVendedor;
        posVendedor = buscaVendedor(nDNI, archivoVendedores, cantVendedores);
        archivoVendedores.seekg(posVendedor*tamVendedor, ios::beg);
        archivoVendedores.read(reinterpret_cast<char*>(&vendedor), tamVendedor);
               
        // procesamos y modificamos los datos y luego solo os reescribimos
        
        if(posVendedor!=NO_ENCONTRADO and posArticulo != NO_ENCONTRADO){
            int posVenta;
            posVenta = buscaVenta(codigo, vendedor.articulosVendidos, vendedor.cantidadVendidos);
            if(posVenta == NO_ENCONTRADO){            
                strcpy(vendedor.articulosVendidos[vendedor.cantidadVendidos].codigo, codigo);
                vendedor.cantidadVendidos++;
            }
            posVenta = buscaVenta(codigo, vendedor.articulosVendidos, vendedor.cantidadVendidos);

            vendedor.articulosVendidos[posVenta].cantidad = cantidadPedida;
            vendedor.articulosVendidos[posVenta].montoVendido = 
                    cantidadPedida*articulo.precio;
            vendedor.articulosVendidos[posVenta].pagoVendedor = 
                    cantidadPedida*articulo.precio*vendedor.porcentajeVentas/100;
            vendedor.montoTotal += cantidadPedida*articulo.precio*vendedor.porcentajeVentas/100;
            if(vendedor.montoTotal>=vendedor.cuotaMinima)
                vendedor.superaCuota = true;
            else 
                vendedor.superaCuota = false;

            articulo.cantidadVendidos += cantidadPedida;
            articulo.montoVendido += cantidadPedida*articulo.precio;                

            archivoVendedores.seekg(posVendedor*tamVendedor, ios::beg);
            archivoVendedores.write(reinterpret_cast<const char*>(&vendedor), sizeof(struct Vendedor));                  

            archivoArticulos.seekg(posArticulo*tamArticulo, ios::beg);
            archivoArticulos.write(reinterpret_cast<const char*>(&articulo), tamArticulo);
            
        }
    }    
}
int buscaArticulo(char* codigo, fstream& archivo, int cantidad){
    struct Articulo articulo;
    archivo.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++){
        archivo.read(reinterpret_cast<char*>(&articulo), sizeof(struct Articulo));
        if(strcmp(articulo.codigo, codigo) == 0) return i;
    }
    return NO_ENCONTRADO;


}
int buscaVendedor(int nDNI, fstream& archivo, int cantidad){
    struct Vendedor vendedor;
    archivo.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {
        archivo.read(reinterpret_cast<char*>(&vendedor), sizeof(struct Vendedor));
        if(nDNI == vendedor.codigo) return i;
    }
    return NO_ENCONTRADO;


}
int buscaVenta(char* codigo, struct ArticuloVendido* ventas, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, ventas[i].codigo) == 0) 
            return i;
    }
    return NO_ENCONTRADO;

}

void emiteReporte(const char* nombreArchivoReporte, const char* nombreArchivoVendedores, 
        const char* nombreArchivoArticulos){
    ifstream archivoVendedores(nombreArchivoVendedores, ios::in|ios::binary);
    if(not archivoVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoVendedores<<endl;
        exit(1);
    }
    ifstream archivoArticulos(nombreArchivoArticulos, ios::in|ios::binary);
    if(not archivoArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoArticulos<<endl;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte<<endl;
        exit(1);
    }
    
    int tamArchVendedors, tamVendedor, cantVendedores;
    tamVendedor = sizeof(struct Vendedor);
    datosArchivoIf(tamArchVendedors, tamVendedor, cantVendedores, archivoVendedores);
    
    int tamArchArticulo, tamArticulo, cantArticulos;
    tamArticulo = sizeof(struct Articulo);
    datosArchivoIf(tamArchArticulo, tamArticulo, cantArticulos, archivoArticulos);
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"TIENDA POR DEPARTAMENTOS VENUS S.A."<<endl
            <<endl
            <<setw(MAX_CAR_LIN/2)<<"DETALLE DE PAGO A LOS VENDEDORES"<<endl;
    
    
    struct Vendedor vendedor;
    archivoVendedores.seekg(0, ios::beg);
    for (int i = 0; i < cantVendedores; i++){
        archivoVendedores.read(reinterpret_cast<char*>(&vendedor), tamVendedor);
        imprimeEncabezadoVendedores(vendedor, i, archivoReporte);
        
        archivoReporte<<setw(ALING)<<" "<<"ARTICULOS VENDIDOS"<<endl;
        
        imprimeVentas(vendedor, archivoReporte, archivoArticulos);        
        
        imprimeLinea('-', archivoReporte);
        archivoReporte<<"TOTAL DE PAGO POR VENTAS: "<<vendedor.montoTotal<<endl;        
        
    }
    
    archivoReporte<<left<<setw(MAX_CAR_LIN/2)<<"DETALLE DE INGRESO POR ARTICULO"<<endl;
    
    struct Articulo articulo;
    imprimeEncabezadoArticulos(archivoReporte);
    archivoArticulos.seekg(0, ios::beg);
    double montoTotal=0;
    for (int i = 0; i < cantArticulos; i++) {
        archivoArticulos.read(reinterpret_cast<char*>(&articulo), tamArticulo); 
        imprimeArticulo(articulo, i, archivoReporte, montoTotal);
    }
    
    imprimeLinea('=', archivoReporte);
    archivoReporte<<"TOTAL DE INGRESO POR VENTAS, DESCONTANDO PAGOS: "<<montoTotal<<endl;
    imprimeLinea('=', archivoReporte);


}
void imprimeEncabezadoVendedores(const struct Vendedor& vendedor, int cont, 
        ofstream& archivo){
    imprimeLinea('=', archivo);
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No"
            <<setw(MAX_CAR_NOMBRE)<<"VENDEDOR"
            <<setw(MAX_CAR_PORC)<<"% POR VENTAS"
            <<setw(MAX_CAR_DINERO)<<"CUOTA MINIMA"
            <<setw(MAX_CAR_OBSERVA)<<"OBSERVACION"
            <<endl;
    imprimeLinea('-', archivo);
    
    archivo<<fixed<<setprecision(2)
            <<setw(3)<<right<<setfill('0')<<cont+1<<setfill(' ')
            <<setw(MAX_CAR_CONT-3)<<" "<<left
            <<setw(8)<<vendedor.codigo<<" - "
            <<setw(MAX_CAR_NOMBRE-11)<<vendedor.nombre
            <<setw(MAX_CAR_PORC)<<vendedor.porcentajeVentas
            <<setw(MAX_CAR_DINERO)<<vendedor.cuotaMinima;
    if(not vendedor.superaCuota)
        archivo<<setw(MAX_CAR_OBSERVA)<<"NO SUPERA LA CUOTA MINIMA";
    archivo<<endl;
}
void imprimeVentas(struct Vendedor vendedor, ofstream& archivo, 
        ifstream& archivoArticulos){
    archivo<<setw(ALING)<<" "
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_NOMBRE)<<"ARTICULO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DINERO)<<"TOTAL"
            <<setw(MAX_CAR_DINERO)<<"PAGO POR VENTAS"
            <<endl;
    
    
    char descripcionArticulo[TAM_ART_DESC];
    for (int i = 0; i < vendedor.cantidadVendidos; i++) {        
        nombraArticulo(vendedor.articulosVendidos[i].codigo, 
                archivoArticulos, descripcionArticulo);
        archivo<<setw(ALING)<<" "<<fixed<<setprecision(2)
                <<setw(2)<<right<<setfill('0')<<i+1<<setfill(' ')
                <<setw(MAX_CAR_CONT-2)<<" "<<left
                <<setw(6)<<vendedor.articulosVendidos[i].codigo<<" - "
                <<setw(MAX_CAR_NOMBRE-9)<<descripcionArticulo
                <<setw(MAX_CAR_CANT)<<vendedor.articulosVendidos[i].cantidad
                <<setw(MAX_CAR_DINERO)<<vendedor.articulosVendidos[i].montoVendido
                <<setw(MAX_CAR_DINERO)<<vendedor.articulosVendidos[i].pagoVendedor
                <<endl;
        
    }

}
void nombraArticulo(char* codigo, ifstream& archivo, char* descripcion){
    struct Articulo articulo;
    int tamArchivo, tamElemento, cantElementos;
    tamElemento = sizeof(struct Articulo);
    datosArchivoIf(tamArchivo, tamElemento, cantElementos, archivo);
    
    for (int i = 0; i < cantElementos; i++) {
        archivo.read(reinterpret_cast<char*>(&articulo), tamElemento);
        if(strcmp(codigo, articulo.codigo)==0) {
            strcpy(descripcion, articulo.descripcion);
            break;
        }
    }

}
void imprimeEncabezadoArticulos(ofstream& archivo){
    imprimeLinea('=',archivo);
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_NOMBRE)<<"ARTICULO"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD VENDIDA"
            <<setw(MAX_CAR_DINERO)<<"INGRESO POR VENTAS"
            <<endl;
    imprimeLinea('-',archivo);
}
void imprimeArticulo(struct Articulo articulo, int cont, ofstream& archivo, 
        double& montoTotal){    
    montoTotal+=articulo.montoVendido;
    archivo<<left
            <<setfill('0')<<right<<setw(3)<<cont+1
            <<setfill(' ')<<left<<setw(MAX_CAR_CONT-3)<<" "
            <<setw(7)<<articulo.codigo<<" - "
            <<setw(MAX_CAR_NOMBRE-7)<<articulo.descripcion
            <<setw(MAX_CAR_DINERO)<<articulo.precio
            <<setw(MAX_CAR_CANT)<<articulo.cantidadVendidos
            <<setw(MAX_CAR_DINERO)<<articulo.montoVendido
            <<endl;
    
}
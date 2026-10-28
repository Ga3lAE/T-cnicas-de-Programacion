#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "StockDeProductos.h"
#include "PedidoPorInternet.h"
#include "ProductoSolicitado.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 170
#define MAX_CAR_COD 10
#define MAX_CAR_DESC 70
#define MAX_CAR_DINERO 15
#define MAX_CAR_CANT 10
#define MAX_CAR_TIEMPO 12

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
int datosArchivoIf(int tamElem, ifstream& archivo){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch / tamElem;
    
}
int datosArchivoF(int tamElem, fstream& archivo){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch / tamElem;
    
}

void leeStock(const char* nombreArchivoDatos, const char* nombreArchivoBin){
    ifstream archivoDatos(nombreArchivoDatos,  ios::in);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin,  ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct StockDeProductos producto;
    
    while(true){
        // WM3524,EMPANIZADOR CONTADINA TRADICIONAL 283GR,40,16.50
        archivoDatos.getline(producto.codigo, MAX_PRODUCTO_CODIGO, ',');
        if(archivoDatos.eof()) break;
        archivoDatos.getline(producto.descripcion, MAX_PRODUCTO_DESCRIPCION, ',');
        archivoDatos>>producto.stock;
        archivoDatos.get();
        archivoDatos>>producto.precio;
        archivoDatos.get();
        
        archivoBin.write(reinterpret_cast<const char*>(&producto), 
                sizeof(struct StockDeProductos));
    }
}
void confirmaStock(const char* nombreArchivoReporte, const char* nombreArchivoBin){
    ofstream archivoReporte(nombreArchivoReporte,  ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin,  ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct StockDeProductos producto;
    
    int tamElemento = sizeof(struct StockDeProductos), 
            cantElementos = datosArchivoIf(tamElemento, archivoBin);
    
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantElementos; i++) {
        archivoBin.read(reinterpret_cast<char*>(&producto), tamElemento);
        archivoReporte<<left
                <<setw(MAX_CAR_COD)<<producto.codigo
                <<setw(MAX_CAR_DESC)<<producto.descripcion
                <<setw(MAX_CAR_DINERO)<<producto.precio
                <<setw(MAX_CAR_CANT)<<producto.stock
                <<endl;
    }

    
}

void leePedidos(const char* nombreArchivoDatos, const char* nombreArchivoBin){
    ifstream archivoDatos(nombreArchivoDatos,  ios::in);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin,  ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct PedidoPorInternet pedido;
    
    while(true){
        // 13/10/2021  18:20:25   829251  71984468
        int dd, mm,aa, hh,mn,ss;
        char descC;
        archivoDatos>>dd;
        if(archivoDatos.eof()) break;
        archivoDatos>>descC>>mm>>descC>>aa
                >>hh>>descC>>mn>>descC>>ss;
        
        pedido.fecha = dd+ mm*100+ aa*10000;
        pedido.hora = ss+ mn*60+ hh*3600;
        
        archivoDatos>>pedido.numero>>pedido.clienteDNI;                                       
        
        pedido.cantidadPedida=0;
        
        archivoBin.write(reinterpret_cast<const char*>(&pedido), 
                sizeof(struct PedidoPorInternet));
    }
}
void confirmaPedidos(const char* nombreArchivoReporte, const char* nombreArchivoBin){
    ofstream archivoReporte(nombreArchivoReporte,  ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin,  ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct PedidoPorInternet pedido;
    
    int tamElemento = sizeof(struct PedidoPorInternet), 
            cantElementos = datosArchivoIf(tamElemento, archivoBin);
    
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantElementos; i++) {
        archivoBin.read(reinterpret_cast<char*>(&pedido), tamElemento);
        archivoReporte<<left
                <<setw(MAX_CAR_COD)<<pedido.numero
                <<setw(MAX_CAR_COD)<<pedido.clienteDNI
                <<setw(MAX_CAR_TIEMPO)<<pedido.fecha
                <<setw(MAX_CAR_TIEMPO)<<pedido.hora
                <<setw(MAX_CAR_CANT)<<pedido.cantidadPedida                
                <<endl;
    }

    
}

void completaPedidos(const char* nombreArchivoDatos, 
        const char* nombreArchivoPedidos, 
        const char* nombreArchivoStock){
    ifstream archivoDatos(nombreArchivoDatos,  ios::in);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    fstream archivoPedidos(nombreArchivoPedidos,  ios::in|ios::out|ios::binary);
    if(not archivoPedidos.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoPedidos;
        exit(1);
    }
    fstream archivoStock(nombreArchivoStock,  ios::in|ios::out|ios::binary);
    if(not archivoStock.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoStock;
        exit(1);
    }
    
    
    struct PedidoPorInternet pedido;    
    int tamPedido = sizeof(struct PedidoPorInternet), 
            cantPedidos = datosArchivoF(tamPedido, archivoPedidos);
    
    struct StockDeProductos producto;    
    int tamProducto = sizeof(struct StockDeProductos), 
            cantProductos = datosArchivoF(tamProducto, archivoStock);            
    
    while(true){
        // 908402  WM3524  2
        int numeroPedido, cantidadPedida;
        char productoPedido[MAX_PRODUCTO_CODIGO]{};
        
        archivoDatos>>numeroPedido;
        if(archivoDatos.eof()) break;
        archivoDatos>>productoPedido>>cantidadPedida;
        
        
        int posProducto = buscaProducto(productoPedido, archivoStock, 
                cantProductos, tamProducto);
        
        int posPedido = buscaPedido(numeroPedido, archivoPedidos, 
                cantPedidos, tamPedido);
        if(posProducto != NO_ENCONTRADO and posPedido != NO_ENCONTRADO){
            archivoStock.seekg(posProducto*tamProducto, ios::beg);
            archivoStock.read(reinterpret_cast<char*>(&producto), tamProducto);
            
            archivoPedidos.seekg(posPedido*tamPedido, ios::beg);
            archivoPedidos.read(reinterpret_cast<char*>(&pedido), tamPedido);
            procesaPedido(pedido, producto, cantidadPedida);                        
            
            archivoPedidos.seekg(posPedido*tamPedido, ios::beg);
            archivoPedidos.write(reinterpret_cast<const char*>(&pedido), tamPedido);
            archivoPedidos.flush();
        }
        
    }
}
int buscaProducto(char* codigo, fstream& archivo, int cantidad, int tamElemento){
    struct StockDeProductos producto;
    archivo.seekg(0, ios::beg);
    
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&producto), tamElemento);
        if(strcmp(codigo, producto.codigo) == 0) return i;        
    }    
    return NO_ENCONTRADO;
}
int buscaPedido(int codigo, fstream& archivo, int cantidad, int tamElemento){
    struct PedidoPorInternet pedido;
    archivo.seekg(0, ios::beg);
    
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&pedido), tamElemento);
        if(codigo == pedido.numero) return i;        
    }    
    return NO_ENCONTRADO;
}
void procesaPedido(struct PedidoPorInternet& pedido, struct StockDeProductos& producto, 
        int cantidadPedida){
    int posPedido = pedido.cantidadPedida;
    pedido.productosPedidos[posPedido].cantidad=cantidadPedida;
    strcpy(pedido.productosPedidos[posPedido].codigo, producto.codigo);    
    strcpy(pedido.productosPedidos[posPedido].descripcion, producto.descripcion);    
    pedido.productosPedidos[posPedido].precioUnitario= producto.precio;
    pedido.productosPedidos[posPedido].subtotal= producto.precio*cantidadPedida;
    
    pedido.cantidadPedida++;
}

void emiteReporte(const char* nombreArchivoReporte, 
        const char* nombreArchivoPedidos){
            ofstream archivoReporte(nombreArchivoReporte,  ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoPedidos(nombreArchivoPedidos,  ios::in|ios::binary);
    if(not archivoPedidos.is_open()){
        cout<<"ERROR: No se puede abrir el archivo "<<nombreArchivoPedidos;
        exit(1);
    }
    
    struct PedidoPorInternet pedido;
    
    int tamPedido = sizeof(struct PedidoPorInternet), 
            cantPedidos = datosArchivoIf(tamPedido, archivoPedidos);
    
    archivoPedidos.seekg(0, ios::beg);
    
    imprimeLinea('=', archivoReporte);
    archivoReporte
            <<setw(MAX_CAR_LIN/2)<<"TIENDA VIRTUAL VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2-3)<<"ATENCION DE PEDIDOS"<<endl;            
    
    archivoPedidos.seekg(0, ios::beg);
    for (int i = 0; i < cantPedidos; i++) {   
        archivoPedidos.read(reinterpret_cast<char*>(&pedido), tamPedido);
        imprimePedido(archivoReporte, pedido);
    }
}
void imprimePedido(ofstream& archivo, const struct PedidoPorInternet& pedido){
    imprimeLinea('=', archivo);
    archivo<<left
            <<"PEDIDO No. "<<setw(MAX_CAR_COD)<<pedido.numero
            <<"FECHA: ";
    imprimeFechaHora(pedido.fecha, 'F', archivo);
    archivo<<"HORA: ";
    imprimeFechaHora(pedido.hora, 'H', archivo);
    archivo<<endl;
    imprimeLinea('-', archivo);
    archivo<<"CLIENTE:"<<endl
            <<"DNI: "<<pedido.clienteDNI<<endl;
    imprimeLinea('-', archivo);
    archivo<<"PRODUCTOS ENTREGADOS: "<<endl;
    
    archivo<<left
        <<setw(MAX_CAR_COD)<<"CODIGO"
        <<setw(MAX_CAR_DESC)<<"DESCRIPCION"
        <<setw(MAX_CAR_CANT)<<"CANTIDAD"
        <<setw(MAX_CAR_DINERO)<<"P/UNITARIO"
        <<setw(MAX_CAR_DINERO)<<"SUBTOTAL"
        <<endl;
    for (int i = 0; i < pedido.cantidadPedida; i++) {        
        imprimeProducto(archivo, pedido.productosPedidos[i]);
    }

    
    
    
}
void imprimeFechaHora(int dato, char tipo, ofstream& archivo){
    char sep;
    int d1,d2,d3;
    if(tipo=='F'){
        sep = '/';
        d1=dato/10000;
        dato%=10000;
        d2=dato/100;
        dato%=100;
        d3=dato;
        
        archivo<<right<<setfill('0')
                <<setw(2)<<d3<<sep
                <<setw(2)<<d2<<sep
                <<setw(4)<<d1
                <<setfill(' ')
                <<setw(MAX_CAR_TIEMPO-10)<<" ";
    }
    if(tipo=='H'){
        sep = ':';
        d1=dato/3600;
        dato%=3600;
        d2=dato/60;
        dato%=60;
        d3=dato;
        
        archivo<<right<<setfill('0')
                <<setw(2)<<d1<<sep
                <<setw(2)<<d2<<sep
                <<setw(2)<<d3
                <<setfill(' ')
                <<setw(MAX_CAR_TIEMPO-8)<<" ";
    }
    
}
void imprimeProducto(ofstream& archivo, const struct ProductoSolicitado producto){
    archivo<<left<<fixed<<setprecision(2)
        <<setw(MAX_CAR_COD)<<producto.codigo
        <<setw(MAX_CAR_DESC)<<producto.descripcion
        <<setw(MAX_CAR_CANT)<<producto.cantidad
        <<setw(MAX_CAR_DINERO)<<producto.precioUnitario
        <<setw(MAX_CAR_DINERO)<<producto.subtotal
        <<endl;
}
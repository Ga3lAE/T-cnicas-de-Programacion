#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "StockProducto.h"
#include "Pedido.h"
#include "Entregado.h"
#include "NoEntregado.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 170
#define MAX_CAR_COD 10
#define MAX_CAR_DESCR 50
#define MAX_CAR_CANT 15
#define MAX_CAR_DINERO 15
#define MAX_CAR_TIEMPO 12

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}

char* leeCadena(ifstream& archivo, char del){
    char buff[100], *aux;
    archivo.getline(buff, 100, del);
    if(archivo.eof()) return nullptr;
    aux = new char[strlen(buff)+1]{};
    strcpy(aux, buff);
    return aux;    
}

void leeStock(const char* nombreArchivo, struct StockProducto* productos, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //SB6549,AGUACATE REGIONAL KG.1.000 GR,22,26.65
        productos[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        productos[cantidad].descripcion = leeCadena(archivo, ',');
        archivo>>productos[cantidad].stock;
        archivo.get();
        archivo>>productos[cantidad].precio;
        archivo.get();
        
        cantidad++;
    }
}

void confirmaStock(const char* nombreArchivo, struct StockProducto* productos, 
        int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE PRODUCTOS"<<endl;
    
    
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DESCR)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"STOCK"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"
            <<endl;
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD)<<productos[i].codigo
                <<setw(MAX_CAR_DESCR)<<productos[i].descripcion
                <<setw(MAX_CAR_CANT)<<productos[i].stock
                <<setw(MAX_CAR_DINERO)<<productos[i].precio
                <<endl;

    }

}

void leePedidos(const char* nombreArchivo, struct Pedido* pedidos, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    
    /*
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct Entregado* productosEntregados;
    int cantidadEntregado;
    struct NoEntregado* productosNoEntregados;
    int cantidadNoEntregado;
     */
    while(true){
        //18/10/2021     22:4:20  942192   33397650
        int dd,mm,aa, hh,mn,ss;
        char descC;
        archivo>>dd;        
        if(archivo.eof()) break;
        archivo>>descC>>mm>>descC>>aa>>hh>>descC>>mn>>descC>>ss
                >>pedidos[cantidad].numero>>pedidos[cantidad].cliente;
        
        pedidos[cantidad].fecha = dd+mm*100+aa*10000;
        pedidos[cantidad].hora = ss+mn*60+hh*3600;
        
        pedidos[cantidad].productosEntregados = 
                new struct Entregado [MAX_PEDIDO_ENTREGADO]{};
        pedidos[cantidad].cantidadEntregado=0;
        pedidos[cantidad].productosNoEntregados = 
                new struct NoEntregado [MAX_PEDIDO_NO_ENTREGADO]{};
        pedidos[cantidad].cantidadNoEntregado=0;        
        
        cantidad++;
    }
}
void confirmaPedidos(const char* nombreArchivo, struct Pedido* pedidos, 
        int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE PEDIDOS"<<endl;
    
    /*
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct Entregado* productosEntregados;
    int cantidadEntregado;
    struct NoEntregado* productosNoEntregados;
    int cantidadNoEntregado;
     */
    
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"NUMERO"
            <<setw(MAX_CAR_COD)<<"CLIENTE"
            <<setw(MAX_CAR_TIEMPO)<<"FECHA"
            <<setw(MAX_CAR_TIEMPO)<<"HORA"
            <<setw(MAX_CAR_CANT)<<"ENTREGADOS"
            <<setw(MAX_CAR_CANT)<<"NO ENTREGADOS"
            <<endl;
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD)<<pedidos[i].numero
                <<setw(MAX_CAR_COD)<<pedidos[i].cliente
                <<setw(MAX_CAR_TIEMPO)<<pedidos[i].fecha
                <<setw(MAX_CAR_TIEMPO)<<pedidos[i].hora
                <<setw(MAX_CAR_CANT)<<pedidos[i].cantidadEntregado
                <<setw(MAX_CAR_CANT)<<pedidos[i].cantidadNoEntregado
                <<endl;

    }

}

void completaPedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos, 
        struct StockProducto* productos, int cantidadProductos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //908402  WM3524  2
        int numeroPedido, cantidadPedida;
        char productoPedido[10];
        
        archivo>>numeroPedido;
        if(archivo.eof()) break;
        archivo>>productoPedido>>cantidadPedida;
        
        int posPedido = buscaPedido(numeroPedido, pedidos, cantidadPedidos),
        posProducto = buscaProducto(productoPedido, productos, cantidadProductos);
        if(posProducto!= NO_ENCONTRADO){ // no podemos hacer nada si no encuentra el producto
            if(posPedido != NO_ENCONTRADO){// pero si no encuentra el producto, sabemos que es lo que se pidio
                if(posPedido == 0)
                    cout<<"here"<<endl;
                procesaPedido(pedidos[posPedido], productos[posProducto], cantidadPedida);
            }                            
            else // solo se reduce el stock, mas no se cuenta la venta
                if(productos[posProducto].stock>cantidadPedida)
                    productos[posProducto].stock-=cantidadPedida;                            
        }
    }
}
int buscaPedido(int numero, struct Pedido* pedidos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(numero == pedidos[i].numero) return i;
    }
    return NO_ENCONTRADO;
}
int buscaProducto(char* codigo, struct StockProducto* productos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, productos[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
void procesaPedido(struct Pedido& pedido, struct StockProducto& producto, int cantidad){
    if(cantidad<producto.stock){
        int posEntrega = pedido.cantidadEntregado;
        pedido.productosEntregados[posEntrega].cantidad=cantidad;
        pedido.productosEntregados[posEntrega].codigo = 
                new char[strlen(producto.codigo)+1]{};
        strcpy(pedido.productosEntregados[posEntrega].codigo, producto.codigo);
        pedido.productosEntregados[posEntrega].descripcion = 
                new char[strlen(producto.descripcion)+1]{};
        strcpy(pedido.productosEntregados[posEntrega].descripcion, producto.descripcion);
        pedido.productosEntregados[posEntrega].precio=producto.precio;
        pedido.productosEntregados[posEntrega].subtotal = cantidad*producto.precio;
        pedido.cantidadEntregado++;
        producto.stock-=cantidad;                
    }
    else{
        int posNoEntrega = pedido.cantidadNoEntregado;
        pedido.productosNoEntregados[posNoEntrega].cantidad=cantidad;        ;
        pedido.productosNoEntregados[posNoEntrega].codigo = 
                new char[strlen(producto.codigo)+1]{};
        strcpy(pedido.productosNoEntregados[posNoEntrega].codigo, producto.codigo);
        pedido.productosNoEntregados[posNoEntrega].descripcion = 
                new char[strlen(producto.descripcion)+1]{};
        strcpy(pedido.productosNoEntregados[posNoEntrega].descripcion, producto.descripcion);
        pedido.cantidadNoEntregado++;
    }
    
        
    
}

void emiteReporte(const char* nombreArchivo, struct Pedido* pedidos, 
        int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"TIENDA VIRTUAL VENUS S.A."<<endl
        <<setw(MAX_CAR_LIN/2)<<"ATENCION DE PEDIDOS"<<endl;
    for (int i = 0; i < cantidad; i++) {        
        imprimePedido(archivo, pedidos[i]);
    }
}
void imprimePedido(ofstream& archivo, const struct Pedido& pedido){
    imprimeLinea('=', archivo);
    int dd,mm,aa, hh,mn,ss;
    aa = pedido.fecha/10000;
    mm = (pedido.fecha%10000)/100;
    dd = pedido.fecha%100;
    
    hh=pedido.hora/3600;
    mn=(pedido.hora%3600)/60;
    ss=((pedido.hora/(3600))%60);
    archivo<<left
            <<"PEDIDO No: "<<setw(MAX_CAR_COD)<<pedido.numero
            <<"FECHA: "<<setfill('0')<<right
            <<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa
            <<setfill(' ')<<left<<setw(MAX_CAR_TIEMPO-10)<<" "
            <<"HORA: "<<setfill('0')<<right
            <<setw(2)<<hh<<':'<<setw(2)<<mn<<':'<<setw(2)<<ss
            <<setfill(' ')<<left<<setw(MAX_CAR_TIEMPO-8)<<" "
            <<endl;
    archivo<<"CLIENTE"<<endl
            <<"DNI: "<<pedido.cliente<<endl;
    archivo<<"PRODUCTOS ENTREGADOS:"<<endl;            
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DESCR)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"
            <<setw(MAX_CAR_DINERO)<<"SUBTOTAL"
            <<endl;                    
    for (int i = 0; i < pedido.cantidadEntregado; i++)  
        imprimeEntregas(archivo, pedido.productosEntregados[i]);
    
    imprimeLinea('-', archivo);
    
    archivo<<"PRODUCTOS NO ENTREGADOS:"<<endl;            
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DESCR)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"                        
            <<endl;
    for (int i = 0; i < pedido.cantidadNoEntregado; i++) 
        imprimeNoEntregas(archivo, pedido.productosNoEntregados[i]);

}
void imprimeEntregas(ofstream& archivo, const struct Entregado& entrega){
    archivo<<left
            <<setw(MAX_CAR_COD)<<entrega.codigo
            <<setw(MAX_CAR_DESCR)<<entrega.descripcion
            <<setw(MAX_CAR_CANT)<<entrega.cantidad
            <<setw(MAX_CAR_DINERO)<<entrega.precio
            <<setw(MAX_CAR_DINERO)<<entrega.subtotal
            <<endl;  
}
void imprimeNoEntregas(ofstream& archivo, const struct NoEntregado& entrega){
    archivo<<left
            <<setw(MAX_CAR_COD)<<entrega.codigo
            <<setw(MAX_CAR_DESCR)<<entrega.descripcion
            <<setw(MAX_CAR_CANT)<<entrega.cantidad                        
            <<endl;  
}
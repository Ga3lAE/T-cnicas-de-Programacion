#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include"Direccion.h"
#include"Pedido.h"
#include"ProductoPedido.h"
#include"funciones.h"

#define MAX_PRODUCTOS 20

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_TAM_NOMBRE 50
#define MAX_TAM_PRODUCTO 40
#define MAX_TAM_DINERO 20
#define MAX_TAM_CANT 15

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
char* leeCadena(ifstream& archivo, char del){
    char buff[200]{}, *aux;
    archivo.getline(buff, 200, del);
    if(archivo.eof()) return nullptr;
    aux = new char[strlen(buff)+1];
    strcpy(aux, buff);
    return aux;
}

void cargarDirecciones(const char* nombreArchivo, struct Direccion* direcciones, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if( not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // USR123,Jr. Pando 234,Surco, -12.1122, -76.9796
        direcciones[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        direcciones[cantidad].direccion = leeCadena(archivo, ',');
        while(archivo.get()!='\n');
        
        cantidad++;
        
    }
}

void cargarPedidos(const char* nombreArchivo, struct Pedido* pedidos, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if( not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 234,
        //Coca Cola 1L Sabor Original,2,4.5,
        //Galletas Margarita 125g,3,3.1,
        //Mantequilla De Mani Union 410g,1,24.0
        int codigoPedido;
        archivo>>codigoPedido;
        if(archivo.eof()) break;
        
        int posPedido;
        posPedido = buscaPedido(codigoPedido, pedidos, cantidad);
        
        if(posPedido == NO_ENCONTRADO){
            pedidos[cantidad].codigo = codigoPedido;
            pedidos[cantidad].productos = new struct ProductoPedido[MAX_PRODUCTOS]{};
            pedidos[cantidad].cantidadProductosPedidos = 0;
            pedidos[cantidad].hora = 0;
            pedidos[cantidad].montoTotal = 0;
            cantidad++;
        }
        posPedido = buscaPedido(codigoPedido, pedidos, cantidad);            
        
        while(true){ 
            if(archivo.get()=='\n') break;
            int posProducto = pedidos[posPedido].cantidadProductosPedidos;                        
                       
            pedidos[posPedido].productos[posProducto].nombre = leeCadena(archivo, ',');                        
            archivo>>pedidos[posPedido].productos[posProducto].cantidad;
            archivo.get();
            archivo>>pedidos[posPedido].productos[posProducto].precioUnitario;
            
            pedidos[posPedido].cantidadProductosPedidos++;                        
        }                                
    }
}
int buscaPedido(int codigo, struct Pedido* pedidos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(codigo == pedidos[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}

void completaPedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos, 
        struct Direccion* direcciones, int cantidadDirecciones){
    ifstream archivo(nombreArchivo, ios::in);
    if( not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 14:45,Erasmo Gomez,USR123,234
        int hh,mm, hora;
        archivo>>hh;
        if(archivo.eof()) break;
        hora = hh*100+mm;
        archivo.get();
        archivo>>mm;
        archivo.get();
        
        char *nombre, *usuario;
        int codigoPedido;
        nombre = leeCadena(archivo, ',');
        usuario = leeCadena(archivo, ',');        
        archivo>>codigoPedido;
        
        int posPedido, posUsuario;
        posPedido = buscaPedido(codigoPedido, pedidos, cantidadPedidos); 
        posUsuario = buscaUsuario(usuario, direcciones, cantidadDirecciones);
        
        pedidos[posPedido].hora = hh*100+mm;
        
        pedidos[posPedido].repartidorRappi = new char[strlen(nombre)+1]{};
        strcpy(pedidos[posPedido].repartidorRappi, nombre);
        
        pedidos[posPedido].direccion = new char[strlen(direcciones[posUsuario].direccion)+1]{};
        strcpy(pedidos[posPedido].direccion, direcciones[posUsuario].direccion);
        pedidos[posPedido].codigoUsuario = new char[strlen(usuario)+1]{};
        strcpy(pedidos[posPedido].codigoUsuario, usuario);
        
    }
}
int buscaUsuario(char* codigo, struct Direccion* direcciones, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, direcciones[i].codigo) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void emiteReporte(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos){
    
    ofstream archivo(nombreArchivo, ios::out);
    if( not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
            
    imprimeTitulo(archivo);
    for (int i = 0; i < cantidadPedidos; i++) {                
        imprimePedidos(archivo, pedidos[i]);
    }

}
void imprimeTitulo(ofstream& archivo){
    
    archivo<<right
            <<setw(MAX_CAR_LIN/2-10)<<"VENUS DELIVERY's S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"REPORTE DE PEDIDOS PARA EL DIA DE HOY"<<endl
            <<left;
}
void imprimePedidos(ofstream& archivo, struct Pedido pedido){
    imprimeLinea('=', archivo);
    archivo<<left
            <<"PEDIDO: "<<pedido.codigo<<endl
            <<"NOMBRE: "<<setw(MAX_TAM_NOMBRE)<<pedido.repartidorRappi
            <<"HORA: "<<pedido.hora/100<<':'<<pedido.hora%100<<endl
            <<"DESTINO: "<<pedido.direccion<<endl
            <<"USUARIO: "<<pedido.codigoUsuario<<endl;
    
    archivo<<"DATOS DE LA BOLETA:"<<endl;
    imprimeProductos(archivo, pedido.productos, pedido.cantidadProductosPedidos);
    
}
void imprimeProductos(ofstream& archivo, struct ProductoPedido* productos, int cantidad){
    archivo<<left
            <<setw(MAX_TAM_PRODUCTO)<<"PRODUCTO"
            <<setw(MAX_TAM_DINERO)<<"PRECIO"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
            <<setw(MAX_TAM_DINERO)<<"PRECIO TOTAL"
            <<endl;
    imprimeLinea('=', archivo);
    
    double totalPagos=0;
    int totalCantidad=0;
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_TAM_PRODUCTO)<<productos[i].nombre
            <<setw(MAX_TAM_DINERO)<<productos[i].precioUnitario
            <<setw(MAX_TAM_CANT)<<productos[i].cantidad
            <<setw(MAX_TAM_DINERO)<<productos[i].precioUnitario*productos[i].cantidad
            <<endl;
        
        totalPagos += productos[i].precioUnitario*productos[i].cantidad;
        totalCantidad+=productos[i].cantidad;
    }
    imprimeLinea('-', archivo);
    archivo<<setw(MAX_TAM_PRODUCTO+MAX_TAM_DINERO)<<"RESUMEN: "
            <<setw(MAX_TAM_CANT)<<totalCantidad
            <<setw(MAX_TAM_DINERO)<<totalPagos
            <<endl;

}
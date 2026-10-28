#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include"funciones.h"
#include"Direccion.h"
#include"Pedido.h"
#include"ProductoPedido.h"

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

void cargarDirecciones(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if( not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if( not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    
    struct Direccion direccion;
    while(true){
        // USR123,Jr. Pando 234,Surco, -12.1122, -76.9796
        archivoCsv.getline(direccion.codigoUsuario, TAM_USUARIO_CODIGO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv.getline(direccion.direccion, TAM_DISTRITO, ',');
        archivoCsv.getline(direccion.distrito, TAM_DISTRITO, ',');
        archivoCsv>>direccion.latitud;
        archivoCsv.get();
        archivoCsv>>direccion.longitud;
        archivoCsv.get();

        archivoBin.write(reinterpret_cast<const char*>(&direccion), 
                sizeof(struct Direccion));
        
    }
}

void cargarPedidos(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if( not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if( not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Pedido pedido;
    while(true){
        // 234,
        //Coca Cola 1L Sabor Original,2,4.5,
        //Galletas Margarita 125g,3,3.1,
        //Mantequilla De Mani Union 410g,1,24.0
        int codigoPedido;
        archivoCsv>>pedido.codigo;
        if(archivoCsv.eof()) break;            
        
        pedido.codigo = codigoPedido;       
        pedido.cantidad = 0;
        pedido.hora = 0;
        pedido.montoTotal = 0;                        
        
        while(true){ 
            if(archivoCsv.get()=='\n') break;
            int posProducto = pedido.cantidad;                        
                       
            archivoCsv.getline(pedido.productos[posProducto].nombre, TAM_PRODUCTO_NOMBRE, ',');
            archivoCsv>>pedido.productos[posProducto].cantidad;
            archivoCsv.get();
            archivoCsv>>pedido.productos[posProducto].precio;
            
            pedido.cantidad++;                        
        }
        
        archivoBin.write(reinterpret_cast<const char*>(&pedido), 
                sizeof(struct Pedido));
    }
}
//int buscaPedido(int codigo, struct Pedido* pedidos, int cantidad){
//    for (int i = 0; i < cantidad; i++) {        
//        if(codigo == pedidos[i].codigo) return i;
//    }
//    return NO_ENCONTRADO;
//}
//
void completaPedidos(const char* nombreArchivoPedidos, 
        const char* nombreArchivoDirecciones,
        const char* nombreArchivoRappis){
    ifstream archivoRappis(nombreArchivoRappis, ios::in);
    if( not archivoRappis.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoRappis;
        exit(1);
    }
    fstream archivoDirecciones(nombreArchivoDirecciones, ios::in|ios::out||ios::binary);
    if( not archivoDirecciones.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoDirecciones;
        exit(1);
    }
    fstream archivoPedidos(nombreArchivoPedidos, ios::in|ios::out||ios::binary);
    if( not archivoPedidos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPedidos;
        exit(1);
    }
    
    
    int ;
    struct Direccion direccion;
    struct Pedido pedido;
    
    while(true){
        // 14:45,Erasmo Gomez,USR123,234
        int hh,mm, hora;
        archivoRappis>>hh;
        if(archivoRappis.eof()) break;
        hora = hh*100+mm;
        archivoRappis.get();
        archivoRappis>>mm;
        archivoRappis.get();
        
        
        int codigoPedido;
        char nombreRappi[TAM_REPARTIDOR_NOMBRE], codigoUsuario[TAM_USUARIO_CODIGO];        
        archivoRappis.getline(nombreRappi, TAM_REPARTIDOR_NOMBRE, ',');
        archivoRappis.getline(codigoUsuario, TAM_USUARIO_CODIGO, ',');        
        archivoRappis>>codigoPedido;
        
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
//int buscaUsuario(char* codigo, struct Direccion* direcciones, int cantidad){
//    for (int i = 0; i < cantidad; i++) {        
//        if(strcmp(codigo, direcciones[i].codigo) == 0) return i;
//    }
//    return NO_ENCONTRADO;
//}
//
//void emiteReporte(const char* nombreArchivo, 
//        struct Pedido* pedidos, int cantidadPedidos){
//    
//    ofstream archivo(nombreArchivo, ios::out);
//    if( not archivo.is_open()){
//        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
//        exit(1);
//    }
//            
//    imprimeTitulo(archivo);
//    for (int i = 0; i < cantidadPedidos; i++) {                
//        imprimePedidos(archivo, pedidos[i]);
//    }
//
//}
//void imprimeTitulo(ofstream& archivo){
//    
//    archivo<<right
//            <<setw(MAX_CAR_LIN/2-10)<<"VENUS DELIVERY's S.A."<<endl
//            <<setw(MAX_CAR_LIN/2)<<"REPORTE DE PEDIDOS PARA EL DIA DE HOY"<<endl
//            <<left;
//}
//void imprimePedidos(ofstream& archivo, struct Pedido pedido){
//    imprimeLinea('=', archivo);
//    archivo<<left
//            <<"PEDIDO: "<<pedido.codigo<<endl
//            <<"NOMBRE: "<<setw(MAX_TAM_NOMBRE)<<pedido.repartidorRappi
//            <<"HORA: "<<pedido.hora/100<<':'<<pedido.hora%100<<endl
//            <<"DESTINO: "<<pedido.direccion<<endl
//            <<"USUARIO: "<<pedido.codigoUsuario<<endl;
//    
//    archivo<<"DATOS DE LA BOLETA:"<<endl;
//    imprimeProductos(archivo, pedido.productos, pedido.cantidadProductosPedidos);
//    
//}
//void imprimeProductos(ofstream& archivo, struct ProductoPedido* productos, int cantidad){
//    archivo<<left
//            <<setw(MAX_TAM_PRODUCTO)<<"PRODUCTO"
//            <<setw(MAX_TAM_DINERO)<<"PRECIO"
//            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
//            <<setw(MAX_TAM_DINERO)<<"PRECIO TOTAL"
//            <<endl;
//    imprimeLinea('=', archivo);
//    
//    double totalPagos=0;
//    int totalCantidad=0;
//    for (int i = 0; i < cantidad; i++) {        
//        archivo<<left<<fixed<<setprecision(2)
//            <<setw(MAX_TAM_PRODUCTO)<<productos[i].nombre
//            <<setw(MAX_TAM_DINERO)<<productos[i].precioUnitario
//            <<setw(MAX_TAM_CANT)<<productos[i].cantidad
//            <<setw(MAX_TAM_DINERO)<<productos[i].precioUnitario*productos[i].cantidad
//            <<endl;
//        
//        totalPagos += productos[i].precioUnitario*productos[i].cantidad;
//        totalCantidad+=productos[i].cantidad;
//    }
//    imprimeLinea('-', archivo);
//    archivo<<setw(MAX_TAM_PRODUCTO+MAX_TAM_DINERO)<<"RESUMEN: "
//            <<setw(MAX_TAM_CANT)<<totalCantidad
//            <<setw(MAX_TAM_DINERO)<<totalPagos
//            <<endl;
//
//}
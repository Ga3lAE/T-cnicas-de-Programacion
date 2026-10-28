#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "ArticuloPedido.h"
#include "Vendedor.h"
#include "funciones.h"


#define NO_ENCONTRADO -1

#define ALING 7
#define MAX_CAR_LIN 170
#define MAX_CAR_COD 10
#define MAX_CAR_DESCR 50
#define MAX_CAR_CANT 10
#define MAX_CAR_DINERO 15
#define MAX_CAR_CONT 5
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_PORC 15
#define MAX_CAR_FECHA 15

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

void leeArticulos(const char* nombreArchivo, 
        struct Articulo* articulos, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // BIT-434,Campana Extractora modelo Glass,11,375.09
        articulos[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        articulos[cantidad].descripcion = leeCadena(archivo, ',');
        archivo>>articulos[cantidad].stock;
        archivo.get();
        archivo>>articulos[cantidad].precio;
        archivo.get();
        
        articulos[cantidad].cantVendidos=0;
        articulos[cantidad].montoVendido=0;
        articulos[cantidad].cantPerdidos=0;
        articulos[cantidad].montoPerdido=0;        
        
        cantidad++;
    }
}
void pruebaArticulos(const char* nombreArchivo, 
        struct Articulo* articulos, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw( MAX_CAR_LIN/2)<<"ARTICULOS LEIDOS"<<endl;
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DESCR)<<"DESCRIPCION"
            <<setw(MAX_CAR_CANT)<<"STOCK"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"
            <<setw(MAX_CAR_CANT)<<"VENDIDOS"
            <<setw(MAX_CAR_DINERO)<<"MONTO GANADO"
            <<setw(MAX_CAR_CANT)<<"NO VENDIDOS"
            <<setw(MAX_CAR_DINERO)<<"MONTO PERDIDO"
            <<endl;                    
    
    for (int i = 0; i < cantidad; i++) {
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<articulos[i].codigo
            <<setw(MAX_CAR_DESCR)<<articulos[i].descripcion
            <<setw(MAX_CAR_CANT)<<articulos[i].stock
            <<setw(MAX_CAR_DINERO)<<articulos[i].precio
            <<setw(MAX_CAR_CANT)<<articulos[i].cantVendidos
            <<setw(MAX_CAR_DINERO)<<articulos[i].montoVendido
            <<setw(MAX_CAR_CANT)<<articulos[i].cantPerdidos
            <<setw(MAX_CAR_DINERO)<<articulos[i].montoPerdido
            <<endl;                    
        

    }

//    while(true){
//        // BIT-434,Campana Extractora modelo Glass,11,375.09
//        articulos[cantidad].codigo = leeCadena(archivo, ',');
//        if(archivo.eof()) break;
//        articulos[cantidad].descripcion = leeCadena(archivo, ',');
//        archivo>>articulos[cantidad].stock;
//        archivo.get();
//        archivo>>articulos[cantidad].precio;
//        archivo.get();
//        
//        cantidad++;
//    }
}

void leeVendedores(const char* nombreArchivo, 
        struct Vendedor* vendedores, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 11602775,HIJAR/ARCA/ADOLFO,5.61,67000.00
        archivo>>vendedores[cantidad].codigo;
        if(archivo.eof()) break;
        archivo.get();
        vendedores[cantidad].nombre = leeCadena(archivo, ',');
        quitaEspacios(vendedores[cantidad].nombre);
        archivo>>vendedores[cantidad].porcVentas;
        archivo.get();
        archivo>>vendedores[cantidad].cuotaMin;
        
        vendedores[cantidad].articulosVendidos = 
                new struct ArticuloPedido[MAX_VENDEDOR_VENDIDOS]{};
        vendedores[cantidad].articulosPerdidos = 
                new struct ArticuloPedido[MAX_VENDEDOR_PERDIDOS]{};
        vendedores[cantidad].cantArtVendidos=0; 
        vendedores[cantidad].cantArtPerdidos=0; 
        vendedores[cantidad].montoTotalVendido=0; 
        vendedores[cantidad].montoTotalPerdido=0;                  
        
        cantidad++;
    }
}
void quitaEspacios(char* nombre){
    for (int i = 0; nombre[i]; i++) {        
        if(nombre[i] == '/') nombre[i] = ' ';
    }

}

void emiteReporte(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidad){    
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw( MAX_CAR_LIN/2)<<"LISTADO DE VENDEDORES"<<endl;
    
    for (int i = 0; i < cantidad; i++) {        
        imprimeVendedor(archivo, vendedores[i], i);        
    }    
}
void imprimeVendedor(ofstream& archivo, const struct Vendedor& vendedor, int cont){
    imprimeLinea('=', archivo);
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_COD + MAX_CAR_NOMBRE)<<"VENDEDOR"
            <<setw(MAX_CAR_PORC)<<"% VENTAS"
            <<setw(MAX_CAR_DINERO)<<"CUOTA MIN"
            <<setw(MAX_CAR_DINERO)<<"TOTAL VENDIDO"
            <<setw(MAX_CAR_DINERO)<<"TOTAL NO VENDIDO"
            <<endl;
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_CONT)<<cont+1
            <<setw(MAX_CAR_COD)<<vendedor.codigo
            <<setw(MAX_CAR_NOMBRE)<<vendedor.nombre
            <<setw(MAX_CAR_PORC)<<vendedor.porcVentas
            <<setw(MAX_CAR_DINERO)<<vendedor.cuotaMin
            <<setw(MAX_CAR_DINERO)<<vendedor.montoTotalVendido
            <<setw(MAX_CAR_DINERO)<<vendedor.montoTotalPerdido
            <<endl;
    
    double totalVendidos=0, totalPerdidos=0;
    
    archivo<<setw(ALING)<<"ARTICULOS VENDIDOS"<<endl;
    imprimeLinea('-', archivo);
    for (int i = 0; i < vendedor.cantArtVendidos; i++) {        
        imprimeVentas(archivo, vendedor.articulosVendidos[i], i, 
                totalVendidos);
    }
    archivo<<setw(ALING)<<"ARTICULOS NO VENDIDOS"<<endl;
    imprimeLinea('-', archivo);
    for (int i = 0; i < vendedor.cantArtPerdidos; i++) {        
        imprimeVentas(archivo, vendedor.articulosPerdidos[i], i, 
                totalPerdidos);
    }
    
    archivo<<left<<fixed<<setprecision(2)
            <<"TOTAL PAGO AL VENDEDOR: "<<totalVendidos<<endl
            <<"TOTAL PAGO AL VENDEDOR SI SE HUBIERAN VENDISO TODOS LOS PRODUCTOS: "
            <<totalVendidos+totalPerdidos<<endl
            <<"TOTAL PERDIDOS POR FALTA DE STOCK: "
            <<totalPerdidos<<endl;
}
void imprimeVentas(ofstream& archivo, const struct ArticuloPedido& venta, int cont, 
        double& total){
    if(cont == 0){
        archivo<<setw(ALING)<<" "
                <<setw(MAX_CAR_CONT)<<"No."
                <<setw(MAX_CAR_COD)<<"ARTICULO"
                <<setw(MAX_CAR_CANT)<<"CANTIDAD"
                <<setw(MAX_CAR_DINERO)<<"MONTO"
                <<setw(MAX_CAR_FECHA)<<"FECHA MAS RECIENTE"
                <<endl;
    }
    total+=venta.montoTotal;
    archivo<<setw(ALING)<<" "
        <<setw(MAX_CAR_CONT)<<cont+1
        <<setw(MAX_CAR_COD)<<venta.codigo
        <<setw(MAX_CAR_CANT)<<venta.cantidad
        <<setw(MAX_CAR_DINERO)<<venta.montoTotal
        <<setw(MAX_CAR_FECHA)<<venta.fechaUltPedido
        <<endl;
}

void leeVentas(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidadVendedores, 
        struct Articulo* articulos, int cantidadAritculos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // JCW-489    13245501     5    2/09/2023
        char codigoArticulo[10], descC;
        int codigoVendedor, cantidadPedida, fecha, dd,mm,aa;
        
        archivo>>codigoArticulo;
        if(archivo.eof()) break;
        archivo>>codigoVendedor>>cantidadPedida
                >>dd>>descC>>mm>>descC>>aa;
        fecha = dd+mm*100+aa*10000;
        
        int posArticulo, posVendedor;
        posArticulo = buscaArticulo(codigoArticulo, articulos, cantidadAritculos);
        posVendedor = buscaVendedor(codigoVendedor, vendedores, cantidadVendedores);
        
        if(posArticulo != NO_ENCONTRADO and posVendedor!= NO_ENCONTRADO){
            procesaVenta(articulos[posArticulo], vendedores[posVendedor], 
                    cantidadPedida, fecha);
        }
    }
}
int buscaArticulo(char* codigo, struct Articulo* articulos, int cantidad){
    
    for (int i = 0; i < cantidad; i++) {
        if(strcmp(codigo, articulos[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaVendedor(int codigo, struct Vendedor* vendedores, int cantidad){
    
    for (int i = 0; i < cantidad; i++) {
        if(codigo == vendedores[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}
void procesaVenta(struct Articulo& articulo, struct Vendedor& vendedor, 
        int cantidadPedida, int fecha){
    if(cantidadPedida<articulo.stock){
        int posVenta = vendedor.cantArtVendidos; 
        procesaArticulo(articulo, vendedor.articulosVendidos[posVenta], 
                vendedor.montoTotalVendido, vendedor.cantArtVendidos, 
                articulo.montoVendido, articulo.cantVendidos,
                cantidadPedida, fecha);
        
        articulo.stock-=cantidadPedida;
    }
    else{        
        int posPerdida = vendedor.cantArtPerdidos; 
        procesaArticulo(articulo, vendedor.articulosPerdidos[posPerdida], 
                vendedor.montoTotalPerdido, vendedor.cantArtPerdidos, 
                articulo.montoPerdido, articulo.cantPerdidos,
                cantidadPedida, fecha);               
    }
}
void procesaArticulo(struct Articulo& articulo, 
        struct ArticuloPedido& articuloPedido,
        double& montoTotal, int& cantArtTotal, 
        double& montoTotalArticulo, int& cantTotalArticulo, 
        int cantidadPedida, int fecha){
    
    articuloPedido.cantidad=cantidadPedida;
    if(fecha > articuloPedido.fechaUltPedido)
        articuloPedido.fechaUltPedido= fecha;
    articuloPedido.codigo= new char[strlen(articulo.codigo)+1];
    strcpy(articuloPedido.codigo, articulo.codigo);    
    articuloPedido.montoTotal=
            cantidadPedida*articulo.precio;

    montoTotalArticulo+=cantidadPedida*articulo.precio;    
    cantTotalArticulo+=cantidadPedida;    
    montoTotal+=cantidadPedida*articulo.precio;    
    cantArtTotal++;
}
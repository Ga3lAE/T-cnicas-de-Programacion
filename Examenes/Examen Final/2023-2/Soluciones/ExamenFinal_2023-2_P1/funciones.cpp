#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Articulo.h"
#include "ArticuloPedido.h"
#include "Vendedor.h"
#include "funciones.h"

#define MAX_ART_VENDIDOS 50
#define MAX_ART_PERDIDOS 50
#define MAX_COD 10

#define NO_ENCONTRADO -1

#define ALING 5
#define ALING_TOTAL 100
#define MAX_CAR_LIN 200
#define MAX_CAR_CONT 5
#define MAX_CAR_NOMBRE 60
#define MAX_CAR_PORCENT 15
#define MAX_CAR_DINERO 20
#define MAX_CAR_CODIGO 10
#define MAX_CAR_CANTIDAD 10
#define MAX_CAR_FECHA 12           

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

void leeArticulos(const char* nombreArchivo, struct Articulo* articulos, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    /*
    char* codigo;
    char* descripcion;
    int stock;
    double precio;

    int cantVendidos;
    double montoVendido;
    int cantPerdidos;
    double montoPerdido;
     */
    
    while(true){
        // BIT-434,Campana Extractora modelo Glass,11,375.09
        char* codigo;
        codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        articulos[cantidad].codigo = new char[strlen(codigo)+1]{};
        strcpy(articulos[cantidad].codigo, codigo);
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
void confirmaArticulos(const char* nombreArchivo, struct Articulo* articulos, 
        int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<left<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE LECTURA DE ARTICULOS"<<endl;
    imprimeLinea('=', archivo);
    archivo
            <<setw(10)<<"CODIGO"
            <<setw(60)<<"DESCRIPCION"
            <<setw(10)<<"STOCK"
            <<setw(10)<<"PRECIO"
            <<setw(20)<<"CANTIDAD VENDIDA"
            <<setw(20)<<"MONTO VENDIDO"
            <<setw(20)<<"CANTIDAD NO VENDIDA"
            <<setw(20)<<"MONTO NO VENDIDO"
            <<endl;
       
    imprimeLinea('=', archivo);
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(10)<<articulos[i].codigo
                <<setw(60)<<articulos[i].descripcion
                <<setw(10)<<articulos[i].stock
                <<setw(10)<<articulos[i].precio
                <<setw(20)<<articulos[i].cantVendidos
                <<setw(20)<<articulos[i].montoVendido
                <<setw(20)<<articulos[i].cantPerdidos
                <<setw(20)<<articulos[i].montoPerdido
                <<endl;
    }

}

void leeVendedores(const char* nombreArchivo, struct Vendedor* vendedores, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    /*
    int codigo;
    char* nombre;
    double porcVentas;
    double cuotaMin;
    
    struct ArticuloPedido* articulosVendidos;
    int cantArtVendidos;
    struct ArticuloPedido* articulosPerdidos;
    int cantArtPerdidos;
    double montoTotalVendido;
    double montoTotalPerdido;
     */
    
    while(true){
        // 11602775,HIJAR/ARCA/ADOLFO,5.61,67000.00
        int codigo;
        char* nombre;
        double porcentaje, cuotaMinima;
        
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo.get();
        nombre = leeCadena(archivo, ',');
        archivo>>porcentaje;
        porcentaje +=0.01;
        archivo.get();
        archivo>>cuotaMinima;
        
        vendedores[cantidad].codigo = codigo;
        vendedores[cantidad].nombre = new char[strlen(nombre)+1];
        strcpy(vendedores[cantidad].nombre, nombre);
        quitaGuiones(vendedores[cantidad].nombre);
        vendedores[cantidad].porcVentas = porcentaje;
        vendedores[cantidad].cuotaMin = cuotaMinima;
        
        vendedores[cantidad].articulosVendidos = 
                new struct ArticuloPedido [MAX_ART_VENDIDOS]{};
//        for (int i = 0; i < MAX_ART_VENDIDOS; i++)                    
//            vendedores[cantidad].articulosVendidos[i].codigo = new char [MAX_COD]{};            
        vendedores[cantidad].cantArtVendidos = 0;       
        vendedores[cantidad].articulosPerdidos = 
                new struct ArticuloPedido [MAX_ART_PERDIDOS]{};        
//        for (int i = 0; i < MAX_ART_PERDIDOS; i++)                    
//            vendedores[cantidad].articulosPerdidos[i].codigo = new char [MAX_COD]{};
        vendedores[cantidad].cantArtPerdidos = 0;       
        vendedores[cantidad].montoTotalVendido = 0;
        vendedores[cantidad].montoTotalPerdido = 0;

        cantidad++;

    }
}
void quitaGuiones(char* cadena){
    for (int i = 0; cadena[i]; i++) {
        if(cadena[i] == '/') cadena[i] = ' ';
    }

}

void emiteReporte(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidadVendedores, 
        struct Articulo* articulos, int cantidadArticulos){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }   
    
    archivo<<setw(MAX_CAR_LIN/2)<<"LISTADO DE VENDEDORES"<<endl;
    imprimeLinea('=', archivo);
    
    for (int i = 0; i < cantidadVendedores; i++) {        
        imprimeEncabezadoVendedores(archivo, i, vendedores[i]);
        
        imprimeLinea('-', archivo);
        archivo<<setw(ALING)<<" "<<"ARTICULOS VENDIDOS:"<<endl;
        imprimeEncabezadoVentas(archivo);
        for (int j = 0; j < vendedores[i].cantArtVendidos; j++) {
            archivo<<setw(ALING)<<" "                                            
                <<setw(2)<<setfill('0')<<right<<j+1
                <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "
                <<setw(MAX_CAR_CODIGO)<<vendedores[i].articulosVendidos[j].codigo
                <<setw(MAX_CAR_CANTIDAD)<<vendedores[i].articulosVendidos[j].cantidad
                <<setw(MAX_CAR_DINERO)<<vendedores[i].articulosVendidos[j].montoTotal
                <<setw(MAX_CAR_FECHA)<<vendedores[i].articulosVendidos[j].fechaUltPed
                <<endl;
        }
        imprimeLinea('-', archivo);
        archivo<<setw(ALING)<<" "<<"ARTICULOS PERDIDOS:"<<endl;
        imprimeEncabezadoVentas(archivo);
        for (int j = 0; j < vendedores[i].cantArtPerdidos; j++) {
            archivo<<setw(ALING)<<" "                                            
                <<setw(2)<<setfill('0')<<right<<j+1
                <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "                
                <<setw(MAX_CAR_CODIGO)<<vendedores[i].articulosPerdidos[j].codigo
                <<setw(MAX_CAR_CANTIDAD)<<vendedores[i].articulosPerdidos[j].cantidad
                <<setw(MAX_CAR_DINERO)<<vendedores[i].articulosPerdidos[j].montoTotal
                <<setw(MAX_CAR_FECHA)<<vendedores[i].articulosPerdidos[j].fechaUltPed
                <<endl;
            
        }
        imprimeLinea('-', archivo);
        
        archivo
                <<setw(ALING_TOTAL)<<"TOTAL PAGADO AL VENDEDOR: "
                <<(vendedores[i].montoTotalVendido-vendedores[i].cuotaMin)*vendedores[i].porcVentas<<endl
                <<setw(ALING_TOTAL)<<"TOTAL PAGADO AL VENDEDOR SI SE HUBIERAN VENDIDO TODOS LOS PRODUCTOS: "
                <<((vendedores[i].montoTotalVendido+vendedores[i].montoTotalPerdido)-vendedores[i].cuotaMin)*vendedores[i].porcVentas<<endl
                <<setw(ALING_TOTAL)
                <<"TOTAL PERDIDOS POR FALTA DE STOCK: "
                <<vendedores[i].montoTotalPerdido*vendedores[i].porcVentas<<endl;
        imprimeLinea('=', archivo);

        
    }
    
}
void imprimeEncabezadoVendedores(ofstream& archivo, int cont, struct Vendedor vendedor){
    archivo<<left
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_NOMBRE)<<"VENDEDOR"
            <<setw(MAX_CAR_PORCENT)<<"% VENTAS"
            <<setw(MAX_CAR_DINERO)<<"CUOTA MINIMA"
            <<setw(MAX_CAR_DINERO)<<"TOTAL VENDIDOS"
            <<setw(MAX_CAR_DINERO)<<"TOTAL NO VENDIDO"
            <<endl;
    archivo<<left<<fixed<<setprecision(2)
            <<setw(3)<<setfill('0')<<right<<cont+1
            <<left<<setfill(' ')<<setw(MAX_CAR_CONT-3)<<" "
            <<setw(MAX_CAR_NOMBRE)<<vendedor.nombre
            <<setw(MAX_CAR_PORCENT)<<vendedor.porcVentas
            <<setw(MAX_CAR_DINERO)<<vendedor.cuotaMin
            <<setw(MAX_CAR_DINERO)<<vendedor.montoTotalVendido
            <<setw(MAX_CAR_DINERO)<<vendedor.montoTotalPerdido
            <<endl;
}
void imprimeEncabezadoVentas(ofstream& archivo){
    archivo<<setw(ALING)<<" "
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_CODIGO)<<"ARTICULO"
            <<setw(MAX_CAR_CANTIDAD)<<"CANTIDAD"
            <<setw(MAX_CAR_DINERO)<<"MONTO"
            <<setw(MAX_CAR_FECHA)<<"FECHA MAS RECIENTE"            
            <<endl;
    imprimeLinea('.',archivo);
}

void leeVentas(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidadVendedores, 
        struct Articulo* articulos, int cantidadArticulos){
    ifstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    } 
    
    while(true){
        // JCW-489    13245501     5    2/09/2023
        char* codigo, descC;
        int nDNI, cantidadPedida, dd,mm,aa, fecha;
        
        codigo = leeCadena(archivo, ' ');
        if(archivo.eof())break;
        archivo>>nDNI>>cantidadPedida>>dd>>descC>>mm>>descC>>aa;
        fecha = aa*10000 +mm*100 +dd;
        archivo.get();
        
        int posArticulo, posVendedor;
        posArticulo = buscaProducto(codigo, articulos, cantidadArticulos);
        posVendedor = buscaVendedor(nDNI, vendedores, cantidadVendedores);
        
        if(posArticulo != NO_ENCONTRADO){
            double precio = articulos[posArticulo].precio;           
            if(articulos[posArticulo].stock >= cantidadPedida){ // si puede atenderlos 
                int posVenta;
                posVenta= buscaVenta(codigo, vendedores[posVendedor].articulosVendidos,
                        vendedores[posVendedor].cantArtVendidos); 
                if(posVenta == NO_ENCONTRADO){
                    vendedores[posVendedor].articulosVendidos[vendedores[posVendedor].cantArtVendidos].codigo = 
                            new char[strlen(codigo)+1]{};
                    strcpy(vendedores[posVendedor].articulosVendidos[vendedores[posVendedor].cantArtVendidos].codigo, codigo);
                    vendedores[posVendedor].cantArtVendidos++;
                }
                posVenta= buscaVenta(codigo, vendedores[posVendedor].articulosVendidos,
                        vendedores[posVendedor].cantArtVendidos); 
                
                vendedores[posVendedor].articulosVendidos[posVenta].cantidad=cantidadPedida;
                vendedores[posVendedor].articulosVendidos[posVenta].fechaUltPed=fecha;
                vendedores[posVendedor].articulosVendidos[posVenta].montoTotal=
                        cantidadPedida*precio;
                vendedores[posVendedor].montoTotalVendido +=cantidadPedida*precio ; 
                
                articulos[posArticulo].cantVendidos+=cantidadPedida;
                articulos[posArticulo].montoVendido+=cantidadPedida*precio;
                
                articulos[posArticulo].stock -= cantidadPedida;                                                
            }
            else{ // si no puede atenderlos
                int posPerdida;
                posPerdida= buscaPerdida(codigo, vendedores[posVendedor].articulosPerdidos,
                        vendedores[posVendedor].cantArtPerdidos);
                if(posPerdida == NO_ENCONTRADO){
                    vendedores[posVendedor].articulosPerdidos[vendedores[posVendedor].cantArtPerdidos].codigo = 
                            new char[strlen(codigo)+1];
                    strcpy(vendedores[posVendedor].articulosPerdidos[vendedores[posVendedor].cantArtPerdidos].codigo, codigo);
                    vendedores[posVendedor].cantArtPerdidos++;
                }                
                posPerdida= buscaPerdida(codigo, vendedores[posVendedor].articulosPerdidos,
                        vendedores[posVendedor].cantArtPerdidos);                
                
                vendedores[posVendedor].articulosPerdidos[posPerdida].cantidad= cantidadPedida;
                vendedores[posVendedor].articulosPerdidos[posPerdida].fechaUltPed=fecha;
                vendedores[posVendedor].articulosPerdidos[posPerdida].montoTotal=
                        cantidadPedida*precio; 
                vendedores[posVendedor].montoTotalPerdido += cantidadPedida*precio; 
                
                articulos[posArticulo].cantPerdidos+=cantidadPedida;
                articulos[posArticulo].montoPerdido+=cantidadPedida*precio;
                
            }
            
        }
        
        
    }
}
int buscaProducto(char* codigo, struct Articulo* articulos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(articulos[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaVendedor(int DNI, struct Vendedor* vendedores, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(vendedores[i].codigo==DNI) return i;
    }
    return NO_ENCONTRADO;
}
int buscaVenta(char* codigo, struct ArticuloPedido* articulos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(articulos[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaPerdida(char* codigo, struct ArticuloPedido* articulos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(articulos[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
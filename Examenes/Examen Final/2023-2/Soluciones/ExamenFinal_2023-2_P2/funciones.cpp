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

void datosArchivoIn(int& tamArchivo, int tamElemento, int& cantElementos, ifstream& archivo){
    archivo.seekg(0, ios::end);
    tamArchivo = archivo.tellg();
    cantElementos = tamArchivo / tamElemento;
    archivo.seekg(0, ios::beg);
    
}
void datosArchivoF(int& tamArchivo, int tamElemento, int& cantElementos, fstream& archivo){
    archivo.seekg(0, ios::end);
    tamArchivo = archivo.tellg();
    cantElementos = tamArchivo / tamElemento;
    archivo.seekg(0, ios::beg);
    
}

void leeArticulos(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Articulo articulo;
    while(true){
        // BIT-434,Campana Extractora modelo Glass,11,375.09
        char codigo[MAX_ART_COD];
        archivoCsv.getline(codigo, MAX_ART_COD, ',');
        if(archivoCsv.eof()) break;
        strcpy(articulo.codigo,codigo);
        archivoCsv.getline(articulo.descripcion, MAX_ART_DESC, ',');
        archivoCsv>>articulo.stock;
        archivoCsv.get();
        archivoCsv>>articulo.precio;
        archivoCsv.get();
                
        articulo.cantVendidos=0;
        articulo.montoVendido=0;
        articulo.montoPerdido=0;
        articulo.cantPerdidos=0;
            
        archivoBin.write(reinterpret_cast<const char*>(&articulo), sizeof(articulo));        
    }
}
void confirmaArticulos(const char* nombreArchivoReporte, const char* nombreArchivoDatos){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoDatos(nombreArchivoDatos, ios::in|ios::binary);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    
    
    
    archivoReporte<<right<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE LECTURA DE ARTICULOS"<<endl<<left;
    imprimeLinea('=', archivoReporte);
    archivoReporte
            <<setw(10)<<"CODIGO"
            <<setw(60)<<"DESCRIPCION"
            <<setw(10)<<"STOCK"
            <<setw(10)<<"PRECIO"
            <<setw(20)<<"CANTIDAD VENDIDA"
            <<setw(20)<<"MONTO VENDIDO"
            <<setw(20)<<"CANTIDAD NO VENDIDA"
            <<setw(20)<<"MONTO NO VENDIDO"
            <<endl;
       
    imprimeLinea('=', archivoReporte);
    
    int tamArchivo, tamElemento, cantElementos;
    tamElemento = sizeof(struct Articulo);
    datosArchivoIn(tamArchivo, tamElemento, cantElementos, archivoDatos);
    
    struct Articulo articulo;
    for (int i = 0; i < cantElementos; i++) {        
        archivoDatos.read(reinterpret_cast<char*>(&articulo), tamElemento);
              
        archivoReporte<<left
                <<setw(10)<<articulo.codigo
                <<setw(60)<<articulo.descripcion
                <<setw(10)<<articulo.stock
                <<setw(10)<<articulo.precio
                <<setw(20)<<articulo.cantVendidos
                <<setw(20)<<articulo.montoVendido
                <<setw(20)<<articulo.cantPerdidos
                <<setw(20)<<articulo.montoPerdido
                <<endl;
        
    }


}

void leeVendedores(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    struct Vendedor vendedor;
    while(true){
        // 11602775,HIJAR/ARCA/ADOLFO,5.61,67000.00
        int codigo;
        archivoCsv>>codigo;
        if(archivoCsv.eof()) break;
        vendedor.codigo = codigo;
        archivoCsv.get();
        archivoCsv.getline(vendedor.nombre, MAX_VEND_NOMBRE, ',');
        quitaGuiones(vendedor.nombre);
        archivoCsv>>vendedor.porcVentas;
        archivoCsv.get();
        archivoCsv>>vendedor.cuotaMin;
                
        vendedor.montoTotalVendido=0;
        vendedor.montoTotalPerdido=0;
        vendedor.cantArtVendidos=0;
        vendedor.cantArtPerdidos=0;        
        
        archivoBin.write(reinterpret_cast<const char*>(&vendedor), sizeof(struct Vendedor));        

    }
}
void quitaGuiones(char* cadena){
    for (int i = 0; cadena[i]; i++) {
        if(cadena[i] == '/') cadena[i] = ' ';
    }

}

void emiteReporte(const char* nombreArchivoReporte, const char* nombreArchivoDatos){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoDatos(nombreArchivoDatos, ios::in|ios::binary);
    if(not archivoDatos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"LISTADO DE VENDEDORES"<<endl;
    imprimeLinea('=', archivoReporte);
    
    int tamArchivo, tamElemento, cantElementos;
    tamElemento = sizeof(struct Vendedor);
    datosArchivoIn(tamArchivo, tamElemento, cantElementos, archivoDatos);
              
    struct Vendedor vendedor;
    for (int i = 0; i < cantElementos; i++) {
        archivoDatos.read(reinterpret_cast<char*>(&vendedor), tamElemento);
        imprimeEncabezadoVendedores(archivoReporte, i, vendedor);
        
        imprimeLinea('-', archivoReporte);
        archivoReporte<<setw(ALING)<<" "<<"ARTICULOS VENDIDOS:"<<endl;
        imprimeEncabezadoVentas(archivoReporte);
        for (int j = 0; j < vendedor.cantArtVendidos; j++) {
            archivoReporte<<setw(ALING)<<" "                                            
                <<setw(2)<<setfill('0')<<right<<j+1
                <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "
                <<setw(MAX_CAR_CODIGO)<<vendedor.articulosVendidos[j].codigo
                <<setw(MAX_CAR_CANTIDAD)<<vendedor.articulosVendidos[j].cantidad
                <<setw(MAX_CAR_DINERO)<<vendedor.articulosVendidos[j].montoTotal
                <<setw(MAX_CAR_FECHA)<<vendedor.articulosVendidos[j].fechaUltPed
                <<endl;
        }
        
        imprimeLinea('-', archivoReporte);
        archivoReporte<<setw(ALING)<<" "<<"ARTICULOS PERDIDOS:"<<endl;
        imprimeEncabezadoVentas(archivoReporte);
        for (int j = 0; j < vendedor.cantArtPerdidos; j++) {
            archivoReporte<<setw(ALING)<<" "                                            
                <<setw(2)<<setfill('0')<<right<<j+1
                <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "                
                <<setw(MAX_CAR_CODIGO)<<vendedor.articulosPerdidos[j].codigo
                <<setw(MAX_CAR_CANTIDAD)<<vendedor.articulosPerdidos[j].cantidad
                <<setw(MAX_CAR_DINERO)<<vendedor.articulosPerdidos[j].montoTotal
                <<setw(MAX_CAR_FECHA)<<vendedor.articulosPerdidos[j].fechaUltPed
                <<endl;
            
        }
        imprimeLinea('-', archivoReporte);
        
        
        double porcVentas = vendedor.porcVentas, cuotaMin = vendedor.cuotaMin;
        if(vendedor.cantArtVendidos==0 and vendedor.cantArtPerdidos==0) {
            porcVentas=0;       
            cuotaMin=0;
        }
        archivoReporte
                <<setw(ALING_TOTAL)<<"TOTAL PAGADO AL VENDEDOR: "
                <<(vendedor.montoTotalVendido-cuotaMin)*porcVentas<<endl
                <<setw(ALING_TOTAL)<<"TOTAL PAGADO AL VENDEDOR SI SE HUBIERAN VENDIDO TODOS LOS PRODUCTOS: "
                <<((vendedor.montoTotalVendido+vendedor.montoTotalPerdido)-cuotaMin)*porcVentas<<endl
                <<setw(ALING_TOTAL)
                <<"TOTAL PERDIDOS POR FALTA DE STOCK: "
                <<vendedor.montoTotalPerdido*vendedor.porcVentas<<endl;
        imprimeLinea('=', archivoReporte);

        
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

void leeVentas(const char* nombreArchivoVentas,const char* nombreArchivoVendedores, 
        const char* nombreArchivoArticulos){
    ifstream archivoVentas(nombreArchivoVentas, ios::in);
    if(not archivoVentas.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoVentas;
        exit(1);
    } 
    fstream archivoVendedores(nombreArchivoVendedores, ios::in|ios::out|ios::binary);
    if(not archivoVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoVendedores;
        exit(1);
    } 
    fstream archivoArticulos(nombreArchivoArticulos, ios::in|ios::out|ios::binary);
    if(not archivoArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoArticulos;
        exit(1);
    } 
    
    int tamArchivoArticulo, tamArticulo, cantArticulos;
    tamArticulo = sizeof(struct Articulo);
    datosArchivoF(tamArchivoArticulo, tamArticulo, cantArticulos, archivoArticulos);
    
    int tamArchivoVenderoes, tamVendedor, cantVendedores;
    tamVendedor = sizeof(struct Vendedor);
    datosArchivoF(tamArchivoVenderoes, tamVendedor, cantVendedores, archivoVendedores);       
    
    struct Articulo articulo;
    struct Vendedor vendedor;
    while(true){
        // JCW-489    13245501     5    2/09/2023
        char codigo[MAX_ART_COD], descC;
        int nDNI, cantidadPedida, dd,mm,aa, fecha;
        
        archivoVentas>>codigo;
        if(archivoVentas.eof())break;
        archivoVentas>>nDNI>>cantidadPedida>>dd>>descC>>mm>>descC>>aa;
        fecha = aa*10000 +mm*100 +dd;        
        
        int posArticulo, posVendedor;
        posArticulo = buscaArticulo(codigo, archivoArticulos, cantArticulos);
        posVendedor = buscaVendedor(nDNI, archivoVendedores, cantVendedores);
        
        archivoArticulos.seekg(posArticulo*tamArticulo, ios::beg);
        archivoArticulos.read(reinterpret_cast<char*>(&articulo), tamArticulo);
        
        archivoVendedores.seekg(posVendedor*tamVendedor, ios::beg);
        archivoVendedores.read(reinterpret_cast<char*>(&vendedor), tamVendedor);        
        
        if(posArticulo != NO_ENCONTRADO){            
            if(articulo.stock >= cantidadPedida){ // si puede atenderlos                                 
               
                atiendeVenta(vendedor.articulosVendidos, vendedor.cantArtVendidos, 
                        vendedor.montoTotalVendido, articulo.cantVendidos, articulo.montoVendido, 
                        codigo, cantidadPedida, fecha, articulo.precio);
                articulo.stock -= cantidadPedida;                                                
            }
            else{ // si no puede atenderlos
                atiendeVenta(vendedor.articulosPerdidos, vendedor.cantArtPerdidos, 
                        vendedor.montoTotalPerdido, articulo.cantPerdidos, articulo.montoPerdido, 
                        codigo, cantidadPedida, fecha, articulo.precio);
                
            }
            
        }
        
        archivoArticulos.seekg(posArticulo*tamArticulo, ios::beg);
        archivoArticulos.write(reinterpret_cast<const char*>(&articulo), tamArticulo);
        
        archivoVendedores.seekg(posVendedor*tamVendedor, ios::beg);
        archivoVendedores.write(reinterpret_cast<const char*>(&vendedor), tamVendedor);
        
        
    }
    
    
}
int buscaArticulo(char* codigo, fstream& archivo, int cantidad){
    struct Articulo articulo;
    archivo.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {
        archivo.read(reinterpret_cast<char*>(&articulo), sizeof(struct Articulo));
        if(strcmp(articulo.codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
int buscaVendedor(int DNI, fstream& archivo, int cantidad){
    struct Vendedor vendedor;
    archivo.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&vendedor), sizeof(struct Vendedor));
        if(vendedor.codigo==DNI) return i;
    }
    return NO_ENCONTRADO;
}
void atiendeVenta(struct ArticuloPedido* articulosTrans, int& cantArtVendidos, 
        double& montoTotalVendido, int& cantVendidos, double& montoVendido, 
        char*codigo, int cantidadPedida, int fecha, double precio){
    int posVenta;
    posVenta = buscaVenta(codigo, articulosTrans, cantArtVendidos);
    if(posVenta == NO_ENCONTRADO){
        strcpy(articulosTrans[cantArtVendidos].codigo, codigo);
        cantArtVendidos++;
    }
    posVenta = buscaVenta(codigo, articulosTrans, cantArtVendidos);
    articulosTrans[posVenta].cantidad = cantidadPedida;
    if(articulosTrans[posVenta].fechaUltPed < fecha)
        articulosTrans[posVenta].fechaUltPed = fecha;
    articulosTrans[posVenta].montoTotal = cantidadPedida*precio;
    
    montoTotalVendido += cantidadPedida*precio;
    cantVendidos+= cantidadPedida;
    montoVendido+= cantidadPedida*precio;
    
}
int buscaVenta(char* articulo, struct ArticuloPedido* articulos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(articulo, articulos[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;

}

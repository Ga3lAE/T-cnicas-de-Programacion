

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 18 de junio de 2023, 09:34 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "ProductoNoProcesado.h"
#include "Farmacias.h"
#include "Productos.h"
#include "funciones.h"


void leerFarmacias(struct Farmacia *farmacias,int &numFarmacias){
    
    ifstream archFarmacias("Farmacias.csv",ios::in);
    if(not archFarmacias.is_open()){
        cout<<"ERROR al abrir el archivo de farmacias"<<endl;
        exit(1);
    }
    
    int codigo;
    char distrito[30],*ptr_distrito;
    numFarmacias=0;
    while(true){
        archFarmacias>>codigo;
        if(archFarmacias.eof())break;
        archFarmacias.get();
        archFarmacias.getline(distrito,30);
        ptr_distrito = new char[strlen(distrito)+1];
        strcpy(ptr_distrito,distrito);
        farmacias[numFarmacias].codigoFarmacia=codigo;
        farmacias[numFarmacias].distrito = ptr_distrito;
        farmacias[numFarmacias].cantidadProductos=0;
        farmacias[numFarmacias].productosVendidos = new struct Producto[10];
        numFarmacias++;
    }
}

void leerVentas(struct Farmacia *farmacias,int numFarmacias,
        struct ProductoNoProcesado *productosNoProcesados,
        int &numProductosNoProcesados){
    
    ifstream archVentas("Ventas.csv",ios::in);
    if(not archVentas.is_open()){
        cout<<"ERROR al abrir el archivo de ventas"<<endl;
        exit(1);
    }
    numProductosNoProcesados=0;
    int codigoFarm,cantidad,posFarmacia;
    char *ptr_producto,*ptr_nombreProd;
    double precio;
    while(true){
        archVentas>>codigoFarm;
        if(archVentas.eof())break;
        archVentas.get();
        ptr_producto = leerCadenaExacta(archVentas);
        ptr_nombreProd = leerCadenaExacta(archVentas);
        archVentas>>cantidad;
        archVentas.get();
        archVentas>>precio;
        posFarmacia = buscarFarmacia(farmacias,codigoFarm,numFarmacias);
        if(posFarmacia!=-1){
            if(farmacias[posFarmacia].cantidadProductos<10){
                actualizarProductos(farmacias,numFarmacias,posFarmacia,
                        ptr_producto,ptr_nombreProd,cantidad,precio);
            }else{
                actualizarProductosNoProcesados(productosNoProcesados,
                        numProductosNoProcesados,codigoFarm,ptr_producto,ptr_nombreProd,
                        cantidad,precio);
            }
        }else while(archVentas.get()!='\n');
    }
}

void actualizarProductosNoProcesados(struct ProductoNoProcesado *productosNoProcesados,
        int &numProductosNoProcesados,int codigoFarm,char *ptr_producto,char *ptr_nombreProd,
        int cantidad,double precio){
    productosNoProcesados[numProductosNoProcesados].codigoFarmacia=codigoFarm;
    productosNoProcesados[numProductosNoProcesados].codigoProducto=ptr_producto;
    productosNoProcesados[numProductosNoProcesados].nombreProducto=ptr_nombreProd;
    productosNoProcesados[numProductosNoProcesados].cantidad=cantidad;
    productosNoProcesados[numProductosNoProcesados].precio=precio;
    numProductosNoProcesados++;
    
}

void actualizarProductos(struct Farmacia *farmacias,int numFarmacias,
        int posFarmacia,char *producto,char *nombreProducto,int cantidad,
        double precio){
    
    int posProd;
    posProd = buscarProducto(farmacias[posFarmacia],producto);   
    if(posProd==-1){/*Si es nuevo*/
        farmacias[posFarmacia].productosVendidos[farmacias[posFarmacia].
                cantidadProductos].cantidadTotalVendida=cantidad;
        farmacias[posFarmacia].productosVendidos[farmacias[posFarmacia].
                cantidadProductos].recaudacion=precio*cantidad;
        farmacias[posFarmacia].productosVendidos[farmacias[posFarmacia].
                cantidadProductos].nombreProducto= nombreProducto;
        farmacias[posFarmacia].productosVendidos[farmacias[posFarmacia].
                cantidadProductos].codigoProducto=producto;
        farmacias[posFarmacia].cantidadProductos++;
    }else{/*Si es un producto repetido*/
        farmacias[posFarmacia].productosVendidos[posProd].cantidadTotalVendida+=cantidad;
        farmacias[posFarmacia].productosVendidos[posProd].recaudacion=
                precio*farmacias[posFarmacia].productosVendidos[posProd].
                cantidadTotalVendida;  
    }
}

void emiteReporte(struct Farmacia *farmacias,int numFarmacias,
        struct ProductoNoProcesado *productosNoProcesados,
        int numProductosNoProcesados){
    ofstream archReporte("ReporteVentas.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de reporte"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(50)<<' '<<"CADENA DE FARMACIAS TP"<<endl;
    imprimeLinea('=',150,archReporte);
    archReporte<<"LISTADO DE FARMACIAS"<<endl;
    imprimeLinea('-',150,archReporte);
    for(int i=0;i<numFarmacias;i++){
        archReporte<<"CODIGO: "<<farmacias[i].codigoFarmacia<<setw(10)<<' '
                <<"DISTRITO: "<<farmacias[i].distrito<<endl;
        imprimeLinea('-',150,archReporte);
        archReporte<<"CODIGO"<<setw(10)<<' '<<"DESCRIPCION"<<setw(38)<<' '
                <<"CANTIDAD"<<setw(10)<<' '<<"MONTO TOTAL"<<endl;
        for(int k=0;k<farmacias[i].cantidadProductos;k++){
            archReporte<<farmacias[i].productosVendidos[k].codigoProducto<<setw(9)
                    <<' '<<left<<setw(35)<<farmacias[i].productosVendidos[k].nombreProducto
                    <<right<<setw(20)<<farmacias[i].productosVendidos[k].cantidadTotalVendida
                    <<setw(20)<<farmacias[i].productosVendidos[k].recaudacion<<endl;
        }
        imprimeLinea('=',150,archReporte);
    }
    imprimProductosNoProcesados(productosNoProcesados,numProductosNoProcesados,
            archReporte);   
}

void imprimProductosNoProcesados(struct ProductoNoProcesado *productosNoProcesados,
        int numProductosNoProcesados,ofstream &archReporte){
    archReporte<<endl<<endl;
    imprimeLinea('=',150,archReporte);
    archReporte<<"PRODUCTOS NO PROCESADOS"<<endl;
    imprimeLinea('-',150,archReporte);
    archReporte<<"FARMACIA"<<setw(10)<<' '<<"CODIGO"<<setw(10)<<' '
            <<"DESCRICPCION"<<setw(35)<<' '<<"CANTIDAD"<<setw(10)<<' '<<"PRECIO"<<endl;
    for(int j=0;j<numProductosNoProcesados;j++){
        archReporte<<productosNoProcesados[j].codigoFarmacia<<setw(12)<<' '
                <<productosNoProcesados[j].codigoProducto<<setw(9)<<' '<<left
                <<setw(35)<<productosNoProcesados[j].nombreProducto<<right
                <<setw(18)<<productosNoProcesados[j].cantidad<<setw(18)
                <<productosNoProcesados[j].precio<<endl;
    }
}

void imprimeLinea(char caracter, int cantidad, ofstream &arhcRep){
    for(int i=0;i<cantidad;i++)arhcRep<<caracter;
    arhcRep<<endl;
}
int buscarProducto(struct Farmacia &farmacias, char *codProd){
    for(int j=0;j<farmacias.cantidadProductos;j++)
        if(strcmp(farmacias.productosVendidos[j].codigoProducto,codProd)==0)
            return j;
        
    return -1;   
}

int buscarFarmacia(struct Farmacia *farmacias, int codigo,int numDatos){
    
    for(int i=0;i<numDatos;i++)
        if(farmacias[i].codigoFarmacia==codigo)return i;
    return -1;
}

char *leerCadenaExacta(ifstream &arch){
    
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    longitud = strlen(buffer);
    
    cadena = new char[longitud+1];
    strcpy(cadena,buffer);
    return cadena;
    
    
}


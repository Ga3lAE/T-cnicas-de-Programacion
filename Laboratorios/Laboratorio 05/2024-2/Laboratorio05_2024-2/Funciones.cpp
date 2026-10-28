/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 10 de mayo de 2025, 11:37 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 200
#define MAX_CAR_COD 10
#define MAX_CAR_DIN 18
#define MAX_CAR_DESC 20
#define MAX_CAR_VEH 13
#define MAX_CAR_NOMBRE 45
#define MAX_CAR_CANT 14

void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        archivo<<c;
    }
    archivo<<endl;
}


//BUSQUEDA
int buscaRepartidor(int cantidadRepartidores,
        char *vehiculosRepartidores, char vehiculoActual,
        int *codigosDistritosRepartidores, int codigoDistritoActual){
    for (int i = 0; i < cantidadRepartidores; i++)
        if(codigoDistritoActual == codigosDistritosRepartidores[i] 
                and 
                vehiculoActual == vehiculosRepartidores[i]) return i;
    return NO_ENCONTRADO;

}
int buscaPlato(int cantidadPlatos,
        int *codigosPlatos, int codigoPlatoPedido){
    for (int i = 0; i < cantidadPlatos; i++) 
        if(codigoPlatoPedido == codigosPlatos[i])
            return i;
    return NO_ENCONTRADO;    
}
//LECTURA
void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *dnis, char *vehiculos, int *codigosDistritos){
    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        archivo>>dnis[cantidad];
        if(archivo.eof()) break;        
        archivo>>vehiculos[cantidad];
        while(archivo.get()!= ' ');
        archivo>>codigosDistritos[cantidad];
        while(archivo.get()!='\n');
        
        cantidad++;
    }    
}
void leePlatos(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios, double *descuentos){
     ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
     
     while(true){
         archivo>>codigos[cantidad];
         if(archivo.eof()) break;
         archivo>>precios[cantidad];
         if(archivo.get()!='\n'){
             archivo>>descuentos[cantidad];
             archivo.get();
         }
         else
             descuentos[cantidad] = 0;
         
         cantidad++;
     }
}
//VERIFICACION DE LECTURA
void verificaLecturas(const char *nombreArchvo, 
        int cantidadRepartidores,
        int *dnis, char *vehiculos, int *codigosDistritos, 
        int cantidadPlatos,
        int *codigos, double *precios, double *descuentos){
    
    ofstream archivo(nombreArchvo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchvo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_CAR_LIN/2)<<"VERIRFICACION DE REPARTIDORES"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_VEH)<<"VEHICULO"
            <<setw(MAX_CAR_COD)<<"DISTRIRO"
            <<endl;
    imprimeLinea(archivo, '=');
    
    for (int i = 0; i < cantidadRepartidores; i++) {        
        archivo<<left
                <<setw(MAX_CAR_COD)<<dnis[i]
                <<setw(MAX_CAR_VEH)<<vehiculos[i]
                <<setw(MAX_CAR_COD)<<codigosDistritos[i]
                <<endl;
    }
    
    imprimeLinea(archivo, '=');
    
    archivo<<setw(MAX_CAR_LIN/2)<<"VERIRFICACION DE PLATOS"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO"
            <<endl;
    imprimeLinea(archivo, '=');
    
    for (int i = 0; i < cantidadPlatos; i++) {        
         archivo<<left
            <<setw(MAX_CAR_COD)<<codigos[i]
            <<right<<setw(6)<<precios[i]<<setw(MAX_CAR_DIN-6)<<' '
            <<right<<setw(6)<<descuentos[i]<<left<<setw(MAX_CAR_DESC-6)<<'%'<<left
            <<endl;
    }       
}

//ASIGNACION
void asignaRepartos(const char *nombreArchivo, 
            //los repartidores (arreglos y estadisticas finales)
            int cantidadRepartidores,  
            int *codigosDistritosRepartidores, int *totalesPlatosRepartidores, 
            char *vehiculosRepartidores, 
            double *montosTotalesPlatosRepartidores, double *descuentosPlatosRepartidores, 
            double *descuentosClientesRepartidores, double *pagosRepartidoresRepartidores, 
            double *totalesIngresadosRepartidores, 
            int &sumaTotalesPlatosRepartidores, 
            double &sumaMontosTotalesPlatosRepartidores, double &sumaDescuentosPlatosRepartidores, 
            double &sumaDescuentosClientesRepartidores, double &sumaPagosRepartidoresRepartidores, 
            double &sumaTotalesIngresadosRepartidores, 
            //los platos (arreglos y estadisticas finales)
            int cantidadPlatos, 
            int *codigosPlatos, int *cantidadesPlatos, 
            double *preciosPlatos, double *descuentosPlatos, 
            double *montosVendidosPlatos, double *descuentosPlatosPlatos, 
            double *descuentosClientesPlatos,double *totalesIngresadosPlatos, 
            int &sumaCantidadesPlatos, 
            double &sumaMontosVendidosPlatos, double &sumaDescuentosPlatosPlatos, 
            double &sumaDescuentosClientesPlatos, double &sumaTotalesIngresadosPlatos){    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoDistritoActual;
    char vehiculoActual;
    
    while(true){
        archivo>>codigoDistritoActual;
        if(archivo.eof()) break;
        archivo>>vehiculoActual;
        
        int posRepartidor = buscaRepartidor(cantidadRepartidores, 
                vehiculosRepartidores, vehiculoActual, 
                codigosDistritosRepartidores, codigoDistritoActual);
        
        if(posRepartidor == NO_ENCONTRADO)
            while(archivo.get()!='\n');
        else{
            while(archivo.get()!=']');
            double descuentoClienteActual;
            int cantidadPlatoPedida, codigoPlatoPedido;
            leeDescuento(archivo, descuentoClienteActual);
            while(true){
                if(archivo.get() == '\n') break;
                archivo>>cantidadPlatoPedida>>codigoPlatoPedido;
                
                int posPlato = buscaPlato(cantidadPlatos, 
                        codigosPlatos, codigoPlatoPedido);
                
                if(posPlato != NO_ENCONTRADO){
                    asignaPlatos(totalesPlatosRepartidores[posRepartidor], 
                            montosTotalesPlatosRepartidores[posRepartidor], 
                            descuentosPlatosRepartidores[posRepartidor], 
                            descuentosClientesRepartidores[posRepartidor], 
                            pagosRepartidoresRepartidores[posRepartidor], 
                            totalesIngresadosRepartidores[posRepartidor], 
                            sumaTotalesPlatosRepartidores, 
                            sumaMontosTotalesPlatosRepartidores, 
                            sumaDescuentosPlatosRepartidores, 
                            sumaDescuentosClientesRepartidores, 
                            sumaPagosRepartidoresRepartidores, 
                            sumaTotalesIngresadosRepartidores,
                            cantidadesPlatos[posPlato], 
                            montosVendidosPlatos[posPlato], 
                            descuentosPlatosPlatos[posPlato], 
                            descuentosClientesPlatos[posPlato], 
                            totalesIngresadosPlatos[posPlato], 
                            sumaCantidadesPlatos, 
                            sumaMontosVendidosPlatos, 
                            sumaDescuentosPlatosPlatos, 
                            sumaDescuentosClientesPlatos, 
                            sumaTotalesIngresadosPlatos,
                            /*procesamos los datos anteriores con respecto a:
                                * Los descuentos
                                * los precios
                                * las cantidades pedidas
                                * al vehiculo
                             */
                            descuentoClienteActual, descuentosPlatos[posPlato], 
                            preciosPlatos[posPlato], cantidadPlatoPedida, 
                            vehiculosRepartidores[posRepartidor]);
                }
            }
        }
    }
    
}
void asignaPlatos(int &totalPlatoRepartidor,
        double &montoTotalePlatoRepartidor,
        double &descuentoPlatoRepartidor,
        double &descuentoClienteRepartidor,
        double &pagoRepartidoresRepartidor,
        double &totalIngresadoRepartidor,
        int &sumaTotalPlatosRepartidor,
        double &sumaMontoTotalPlatoRepartidor,
        double &sumaDescuentoPlatoRepartidor,
        double &sumaDescuentoClienteRepartidor,
        double &sumaPagoRepartidoresRepartidor,
        double &sumaTotalIngresadoRepartidor,
        int &cantidadPlatos,
        double &montoVendidoPlato,
        double &descuentoPlatoPlato,
        double &descuentoClientePlato,
        double &totalIngresadoPlato,
        int &sumaCantidadPlatos,
        double &sumaMontoVendidoPlatos,
        double &sumaDescuentoPlatoPlatos,
        double &sumaDescuentoClientePlatos,
        double &sumaTotalIngresadoPlato,
        double descuentoCliente, double descuentoPlato,
        double precioPlato, int cantidadPlatosPedida, 
        char vehiculoRepartidor){        
    
    
    double pagoPlatoActual = cantidadPlatosPedida*precioPlato, 
            pagoRepartidor;
    
    totalPlatoRepartidor+=cantidadPlatosPedida;
    montoTotalePlatoRepartidor+=pagoPlatoActual;
    descuentoPlatoRepartidor += descuentoPlato/100.0*pagoPlatoActual;
    descuentoClienteRepartidor += descuentoCliente/100.0*pagoPlatoActual;
    if(vehiculoRepartidor == 'M')
        pagoRepartidor +=10/100.0*pagoPlatoActual;
    else if(vehiculoRepartidor == 'B')
        pagoRepartidor +=5/100.0*pagoPlatoActual;
    
    pagoRepartidoresRepartidor += pagoRepartidor;
    totalIngresadoRepartidor += pagoPlatoActual - 
            (descuentoPlato/100.0*pagoPlatoActual + descuentoCliente/100.0*pagoPlatoActual 
            + pagoRepartidor);
    
    sumaTotalPlatosRepartidor+=cantidadPlatosPedida;
    sumaMontoTotalPlatoRepartidor+=pagoPlatoActual;
    sumaDescuentoPlatoRepartidor += descuentoPlato/100.0*pagoPlatoActual;
    sumaDescuentoClienteRepartidor += descuentoCliente/100.0*pagoPlatoActual;
    sumaPagoRepartidoresRepartidor += pagoRepartidor;
    sumaTotalIngresadoRepartidor += pagoPlatoActual - 
            (descuentoPlato/100.0*pagoPlatoActual + descuentoCliente/100.0*pagoPlatoActual 
            + pagoRepartidor);
    
    double descuentoPlatoPorPlato = descuentoPlato/100.0*pagoPlatoActual,
            descuentoPlatoPorCliente = descuentoCliente/100.0*pagoPlatoActual;
    
    cantidadPlatos+=cantidadPlatosPedida;
    montoVendidoPlato +=pagoPlatoActual;
    descuentoPlatoPlato += descuentoPlatoPorPlato;
    descuentoClientePlato += descuentoPlatoPorCliente;
    totalIngresadoPlato+=pagoPlatoActual - (descuentoPlatoPorCliente 
            + descuentoPlatoPorPlato);
    
    sumaCantidadPlatos+=cantidadPlatosPedida;
    sumaMontoVendidoPlatos +=pagoPlatoActual;
    sumaDescuentoPlatoPlatos += descuentoPlatoPorPlato;
    sumaDescuentoClientePlatos += descuentoPlatoPorCliente;
    sumaTotalIngresadoPlato+=pagoPlatoActual - (descuentoPlatoPorCliente 
            + descuentoPlatoPorPlato);
    
    
}
void leeDescuento(ifstream &archivo, double &descuento){
    char tieneDescuento;
    archivo>>tieneDescuento;
    if(tieneDescuento == 'S'){
        archivo>>descuento;
        archivo.get();// para el %        
    }
    else
        descuento = 0;
}

//IMPRESION
void imprimeReporteRepartidores(const char* nombreArchivoReporte, 
        const char*nombreArchivoNombres,
        int cantidadRepartidores,
        int *dnisRepartidores, char *vehiculosRepartidores, int *codigosDistritosRepartidores,
        int *totalesPlatosRepartidores, double *montosTotalesPlatosRepartidores,
        double *descuentosPlatosRepartidores, double *descuentosClientesRepartidores,
        double *pagosRepartidoresRepartidores, double *totalesIngresadosRepartidores,
        int sumaTotalesPlatosRepartidores, double sumaMontosTotalesPlatosRepartidores,
        double sumaDescuentosPlatosRepartidores, double sumaDescuentosClientesRepartidores,
        double sumaPagosRepartidoresRepartidores, double sumaTotalesIngresadosRepartidores){
    ifstream archivoNombres(nombreArchivoNombres, ios::in);
    if(not archivoNombres.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoNombres;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE REPARTOS A DOMICILIO VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"ENTREGAS POR REPARTIDORES"<<endl;
    imprimeLinea(archivoReporte, '=');
    
    archivoReporte<<left
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_VEH)<<"VEHICULO"
            <<setw(MAX_CAR_COD)<<"DISTRITO"
            <<setw(MAX_CAR_CANT)<<"TOTAL PLATOS"
            <<setw(MAX_CAR_DIN)<<"MONTO PLATOS"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO PLATOS"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO CLIENTES"
            <<setw(MAX_CAR_DIN)<<"PAGO REPARTIDOR"
            <<setw(MAX_CAR_DIN)<<"TOTAL INGRESADO"
            <<endl;
    
    imprimeLinea(archivoReporte, '=');
    
    for (int i = 0; i < cantidadRepartidores; i++) {
         archivoReporte<<left
            <<setw(MAX_CAR_COD)<<dnisRepartidores[i];
         imprimeNombre(archivoNombres, archivoReporte, dnisRepartidores[i]);
         imprimeVehiculo(archivoReporte, vehiculosRepartidores[i]);
         archivoReporte<<setw(MAX_CAR_COD)<<codigosDistritosRepartidores[i]
            <<right<<setw(MAX_CAR_CANT/2)<<totalesPlatosRepartidores[i]<<left<<setw(MAX_CAR_CANT/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<montosTotalesPlatosRepartidores[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<descuentosPlatosRepartidores[i]<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<descuentosClientesRepartidores[i]<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<pagosRepartidoresRepartidores[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<totalesIngresadosRepartidores[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<endl;
    }
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<left
            <<setw(MAX_CAR_COD+MAX_CAR_NOMBRE+MAX_CAR_VEH+MAX_CAR_COD)<<' '            
            <<right<<setw(MAX_CAR_CANT/2)<<sumaTotalesPlatosRepartidores<<left<<setw(MAX_CAR_CANT/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<sumaMontosTotalesPlatosRepartidores<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<sumaDescuentosPlatosRepartidores<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<sumaDescuentosClientesRepartidores<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<sumaPagosRepartidoresRepartidores<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<sumaTotalesIngresadosRepartidores<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<endl;

}
void imprimeNombre(ifstream &archivoLectura, ofstream &archivoReporte, int codigo){
    archivoLectura.clear();
    archivoLectura.seekg(0, ios::beg);
    
    int dniActual;
    while(true){
        archivoLectura>>dniActual;
        if(archivoLectura.eof()) break;
        if(dniActual != codigo)
            while(archivoLectura.get()!='\n');
        else{
            archivoLectura>>ws;
            char letra;
            int cantidadLetras = 0;
            while(true){
                letra = archivoLectura.get();
                if(letra == '\n') break;
                cantidadLetras++;
                archivoReporte<<letra;
            }
            archivoReporte<<setw(MAX_CAR_NOMBRE-cantidadLetras)<<' ';
            
        }
            
    }
}
void imprimeVehiculo(ofstream &archivo, char vehiculo){
    if (vehiculo == 'B')
        archivo<<setw(MAX_CAR_VEH)<<"BICICLETA";
    else if (vehiculo == 'M')
        archivo<<setw(MAX_CAR_VEH)<<"MOTOCICLETA";
}


void imprimeReportePlatos(const char* nombreArchivoReporte, 
        const char*nombreArchivoNombres,
        int cantidadPlatos,
        int *codigosPlatos, double *preciosPlatos, double *descuentosPlatos, 
        int *cantidadesPlatos, double *montosVendidosPlatos, 
        double *descuentosPlatosPlatos, 
        double *descuentosClientesPlatos, 
        double *totalesIngresadosPlatos, 
        int sumaCantidadesPlatos, double sumaMontosVendidosPlatos, 
        double sumaDescuentosPlatosPlatos, 
        double sumaDescuentosClientesPlatos, 
        double sumaTotalesIngresadosPlatos){
    ifstream archivoNombres(nombreArchivoNombres, ios::in);
    if(not archivoNombres.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoNombres;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE REPARTOS A DOMICILIO VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"ENTREGAS POR PLATOS"<<endl;
    imprimeLinea(archivoReporte, '=');
    
    archivoReporte<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_NOMBRE)<<"DESCRIPCION"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD"
            <<setw(MAX_CAR_DIN)<<"MONTO VENDIDO"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO PLATO"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO CLIENTES"
            <<setw(MAX_CAR_DIN)<<"TOTAL INGRESADO"
            <<endl;
    
    imprimeLinea(archivoReporte, '=');
    
    for (int i = 0; i < cantidadPlatos; i++) {
        archivoReporte<<left
            <<setw(MAX_CAR_COD)<<codigosPlatos[i];
        imprimeNombre(archivoNombres, archivoReporte, codigosPlatos[i]);
        archivoReporte<<setw(MAX_CAR_DIN)<<preciosPlatos[i]
            <<right<<setw(MAX_CAR_DESC/2)<<descuentosPlatos[i]<<left<<setw(MAX_CAR_DESC/2)<<'%'
            <<right<<setw(MAX_CAR_CANT/2)<<cantidadesPlatos[i]<<left<<setw(MAX_CAR_CANT/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<montosVendidosPlatos[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<descuentosPlatosPlatos[i]<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<descuentosClientesPlatos[i]<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<totalesIngresadosPlatos[i]<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<endl;
    }
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<left
            <<setw(MAX_CAR_COD+MAX_CAR_NOMBRE+MAX_CAR_DIN+MAX_CAR_DESC)<<' '            
            <<right<<setw(MAX_CAR_CANT/2)<<sumaCantidadesPlatos<<left<<setw(MAX_CAR_CANT/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<sumaMontosVendidosPlatos<<left<<setw(MAX_CAR_DIN/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<sumaDescuentosPlatosPlatos<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DESC/2)<<sumaDescuentosClientesPlatos<<left<<setw(MAX_CAR_DESC/2)<<' '
            <<right<<setw(MAX_CAR_DIN/2)<<sumaTotalesIngresadosPlatos<<left<<setw(MAX_CAR_DIN/2)<<' '            
            <<endl;

}






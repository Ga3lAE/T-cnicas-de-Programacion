#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_CAR_CONT 4
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_COD 10
#define MAX_CAR_VEH 14
#define MAX_CAR_DIST 15
#define MAX_CAR_CANT 13
#define MAX_CAR_DIN 14

//impresion
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {       
        archivo<<c;
    }
    archivo<<endl;
}
void leeImprimeTexto(ifstream &archivoLectura, 
        ofstream &archivoReporte, char del, int espacio){
    char letra;
    int cantidadLetras = 0;
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == del) break;
        if(letra == '/') letra = ' ';
        cantidadLetras++;
        archivoReporte<<letra;
    }
    archivoReporte<<setw(espacio-cantidadLetras)<<' ';
    
} 
void leeImprimeVehiculo(ifstream &archivoLectura, 
        ofstream &archivoReporte,char &vehiculo){
    char letra;
    int cantidadLetras = 0;
    bool primeraLetra = true;
    archivoLectura>>ws;
    while(true){
        letra = archivoLectura.get();
        if(letra == ' ') break;
        cantidadLetras++;
        if(primeraLetra) vehiculo = letra;
        primeraLetra = false;
        if(letra<='z' and letra >='a') letra+='A'-'a';
        archivoReporte<<letra;
    }
    archivoReporte<<setw(MAX_CAR_VEH-cantidadLetras)<<' ';
    
} 

//busqueda
int buscaInt(int *arreglo, int elemento, int cantidadElementos){
    for (int i = 0; i < cantidadElementos; i++) {        
        if(arreglo[i]==elemento) return i;
    }
    return NO_ENCONTRADO;
}

//lectura
void leePlatos(const char *nombreArchivoPlatosOfrecidos,
        int &cantidadPlatos,
        int *codigosPlatos, double *preciosPlatos){
    
    ifstream archivoPlatos(nombreArchivoPlatosOfrecidos, ios::in);
    if(not archivoPlatos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPlatosOfrecidos;
        exit(1);
    }
    
    while(true){
        //31796 ANTICUCHO_DE_CORAZON_AL_PLATO   31.90   ESPECIALES                
        archivoPlatos>>codigosPlatos[cantidadPlatos];
        if(archivoPlatos.eof()) break;                
        archivoPlatos>>ws;
        while(archivoPlatos.get()!=' ');        
        archivoPlatos>>preciosPlatos[cantidadPlatos];        
        while (archivoPlatos.get()!='\n');
        cantidadPlatos++;
    }
}
void leeDatosEmiteReporte(int cantidadPlatos, 
        int *codigosPlatos, double *preciosPlatos,
        const char* nombreArchivoRepartidores, 
        const char* nombreArchivoRepartosARealizar, 
        const char* nombreArchivoReporte){
    
    ifstream archivoRepartidores(nombreArchivoRepartidores, ios::in);
    if(not archivoRepartidores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoRepartidores;
        exit(1);
    }
    ifstream archivoRepartos(nombreArchivoRepartosARealizar, ios::in);
    if(not archivoRepartos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoRepartosARealizar;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    double recaudadoPedidos=0, pagoRepartidores=0;
    
    leeProcesaArchivos(archivoRepartidores, 
            archivoRepartos,
            archivoReporte, 
            cantidadPlatos, codigosPlatos, preciosPlatos);
    
    imprimeEstadisticasFinales(archivoReporte, 
            recaudadoPedidos, pagoRepartidores);
    
}

void leeProcesaArchivos(ifstream &archivoRepartidores,
        ifstream &archivoRepartos,
        ofstream &archivoReporte, 
        int cantidadPlatos, int *codigosPlatos, double *preciosPlatos){
    
    imprimeEncabezado(archivoReporte);
    int cantidadRepartidores=0;
    
    int dniRepartidor, codigoDistritoRepartidor;
    char vehiculo;
    
    while(true){
        // 54805724   Vizcardo/Sinche/Maribel   Motocicleta   4826   Santa Rosa
        archivoRepartidores>>dniRepartidor;
        if(archivoRepartidores.eof()) break;
        cantidadRepartidores++;
        leeImprimeRepartidor(archivoRepartidores, archivoReporte, 
                dniRepartidor, vehiculo, codigoDistritoRepartidor, 
                cantidadRepartidores);       
        leeRepartos(archivoRepartos, archivoReporte, 
                codigoDistritoRepartidor, vehiculo,
                codigosPlatos, preciosPlatos, cantidadPlatos);
        
        
        
    }
    
}
void imprimeEncabezado(ofstream &archivo){
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE REPARTOS A DOMICILIO VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"ENTREGA QUE DEBEN DE REALIZAR LOS REPARTIDORES"<<endl;        
    imprimeLinea(archivo, '=');
}
void leeImprimeRepartidor(ifstream &archivoRepartidores, ofstream &archivoReporte,
        int dniRepartidor, char &vehiculo, int &codigoDistritoRepartidor,
        int cantidadRepartidores){
    archivoReporte<<right<<setfill('0')
            <<setw(2)<<cantidadRepartidores
            <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<')'
            <<"REPARTIDOR:"<<endl;
    archivoReporte<<left
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_VEH)<<"VEHICULO"
            <<setw(MAX_CAR_COD + MAX_CAR_DIST + 3)<<"DISTRITO A ATENDER"
            <<endl;
    
    leeImprimeTexto(archivoRepartidores, archivoReporte,' ', MAX_CAR_NOMBRE);
    archivoReporte<<setw(MAX_CAR_COD)<<dniRepartidor;
    leeImprimeVehiculo(archivoRepartidores, archivoReporte, vehiculo);
    archivoRepartidores>>codigoDistritoRepartidor;
    archivoReporte<<setw(MAX_CAR_COD)<<codigoDistritoRepartidor;
    leeImprimeTexto(archivoRepartidores, archivoReporte, '\n', MAX_CAR_DIST);
    archivoReporte<<endl;
    
    imprimeLinea(archivoReporte, '-');
    archivoReporte<<setw(MAX_CAR_CONT)<<' '
            <<"CLIENTES A ATENDER"<<endl;
}
void leeRepartos(ifstream &archivoRepartos, ofstream &archivoReporte,
        int codigoDistritoRepartidor, char vehiculo, 
        int *codigosPlatos, double *preciosPlatos, int cantidadPlatos){
    int cantidadClientes=0;
    int codigoDistritoActual;
    char vehiculoActual;
    
    archivoRepartos.clear();
    archivoRepartos.seekg(0, ios::beg);
    while(true){
        archivoRepartos>>codigoDistritoActual;
        if(archivoRepartos.eof()){
            if(cantidadClientes==0)
                archivoReporte<<"NO TTIENE REPARTOS XDXDXD"<<endl;
                imprimeLinea(archivoReporte, '=');
            break;
        }
        
        archivoRepartos>>vehiculoActual;
        if(codigoDistritoActual != codigoDistritoRepartidor or
                vehiculo != vehiculoActual) while(archivoRepartos.get()!='\n');
        else {
            cantidadClientes++;
            archivoReporte<<setw(MAX_CAR_CONT)<<' '
                    <<setw(MAX_CAR_CONT)<<cantidadClientes;
            leeImprimeTexto(archivoRepartos, archivoReporte, 
                    ']', MAX_CAR_NOMBRE);
            archivoReporte<<endl;
            archivoReporte<<setw(MAX_CAR_CONT*2)<<' '
                    <<"PLATOS SOLICITADOS:"<<endl
                    <<setw(MAX_CAR_CONT*3)<<' '
                    <<setw(MAX_CAR_COD)<<"CODIGO"
                    <<setw(MAX_CAR_CANT)<<"CANTIDAD"
                    <<setw(MAX_CAR_DIN)<<"PRECIO"
                    <<setw(MAX_CAR_DIN)<<"SUBTOTAL"
                    <<endl;
             
            int cantidadPlatosPedidos=0;
            int cantidadPedida, codigoPlatoPedido;
            double pagoCliente =0, pagoRepartidor=0, totalRecaudadoCliente=0;
            while(true){
                if(archivoRepartos.get() == '\n') break;
                archivoRepartos>>cantidadPedida>>codigoPlatoPedido;
                cantidadPlatosPedidos++;
                 
                //buscamos el plato en el arreglo. La posicion del plato nos dará su codigo y su precio
                int posicionPlato = buscaInt(codigosPlatos, codigoPlatoPedido, cantidadPlatos);
                if(posicionPlato!= NO_ENCONTRADO){
                    double subtotal = cantidadPedida*preciosPlatos[posicionPlato];
                    archivoReporte<<setw(MAX_CAR_CONT*2)<<' '                            
                            <<setw(MAX_CAR_CONT)<<cantidadPlatosPedidos
                            <<setw(MAX_CAR_COD)<<codigosPlatos[posicionPlato]
                            <<setw(MAX_CAR_CANT)<<cantidadPedida
                            <<setw(MAX_CAR_DIN)<<preciosPlatos[posicionPlato]
                            <<setw(MAX_CAR_DIN)<<subtotal
                            <<endl;
                    
                    asiganPagos(cantidadPedida, preciosPlatos[posicionPlato], 
                            pagoCliente, 
                            pagoRepartidor, vehiculo, 
                            totalRecaudadoCliente);
                 }
             }
            imprimeLinea(archivoReporte, '.');
            imprimeEstadisticasCliente(archivoReporte,
                    pagoCliente, pagoRepartidor, totalRecaudadoCliente);
            imprimeLinea(archivoReporte, '=');            
        }        
    }    
}
void asiganPagos(int cantidadPedida, double precioPlato,
        double &pagoCliente,
        double &pagoRepartidor, char vehiculo,
        double &totalRecaudadoCliente){
    pagoCliente += cantidadPedida*precioPlato;
    if(vehiculo == 'B')
        pagoRepartidor = pagoCliente*0.05;
    else if(vehiculo == 'M')
        pagoRepartidor = pagoCliente*0.1;
    
    totalRecaudadoCliente = pagoRepartidor+pagoCliente;
}
void imprimeEstadisticasCliente(ofstream &archivo, 
        double pagoCliente, double pagoRepartidor, double totalRecaudadoCliente){
    archivo<<setw(MAX_CAR_CONT*3+MAX_CAR_COD+MAX_CAR_CANT+MAX_CAR_DIN)<<"TOTAL A PAGAR:"
            <<pagoCliente<<endl
            <<setw(MAX_CAR_CONT*3+MAX_CAR_COD+MAX_CAR_CANT+MAX_CAR_DIN)<<"PAGO AL REPARTIDOR:"
            <<pagoRepartidor<<endl;
    imprimeLinea(archivo, '.');
    archivo<<setw(MAX_CAR_CONT*3+MAX_CAR_COD+MAX_CAR_CANT+MAX_CAR_DIN)<<"TOTAL RECAUDADO:"
            <<totalRecaudadoCliente<<endl;
}

void imprimeEstadisticasFinales(ofstream &archivo, 
        double recaudado, double pago){
    archivo<<fixed<<setprecision(2)
            <<"TOTAL RECAUDADO POR LOS PEDIDOS SOLICITADOS: "<<recaudado<<endl
            <<"TOTAL A PAGAR A LOS REPARTIDORES: "<<pago
            <<endl;
    imprimeLinea(archivo, '=');
}


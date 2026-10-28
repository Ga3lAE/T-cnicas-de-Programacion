/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 4 de junio de 2025, 12:23 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_NOMBRE_REPARTIDOR 60
#define MAX_CAR_DISTRITO_REPARTIDOR 30
#define MAX_CAR_VEHICULO_REPARTIDOR 15
#define MAX_CAR_NOMBRE_PLATO 50
#define MAX_CAR_CATEGORIA_PLATO 30

#define MAX_TAM_LIN 220
#define MAX_TAM_COD 12
#define MAX_TAM_DIN 20
#define MAX_TAM_CANT 16
#define MAX_TAM_NOMBRE_REPARTIDOR 50
#define MAX_TAM_VEHICULO_REPARTIDOR 20
#define MAX_TAM_DISTRITO_REPARTIDOR 30
#define MAX_TAM_NOMBRE_PLATO 50
#define MAX_TAM_CATEGORIA_PLATO 20

//LECTURA
char *leeCadena(ifstream &archivo, int tam){
    char aux[tam]{}, *cad;
    
    archivo>>aux;
    for (int i = 0; aux[i]; i++)
        if(aux[i]=='_')aux[i] = ' ';

    cad = new char[strlen(aux)+1]{};
    
    strcpy(cad, aux);
    return cad;
    
} 
void eliminaEspacios(char *texto){
    for (int i = 0; texto[i]; i++) {
        if(texto[i] == '_') texto[i] = ' ';
    }
}
void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *arrDni, char **arrNombre, char **arrVehiculo, 
        int *arrCodigoDistrito, char **arrNombreDistrito){        
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //60685215     Sakaguchi_Mori_Carlos_Ronal      Motocicleta     1439        Comas
        archivo>>arrDni[cantidad];
        if(archivo.eof()) break;        
        arrNombre[cantidad] = leeCadena(archivo, MAX_CAR_NOMBRE_REPARTIDOR);
        arrVehiculo[cantidad] = leeCadena(archivo, MAX_CAR_VEHICULO_REPARTIDOR);
        archivo>>arrCodigoDistrito[cantidad];
        arrNombreDistrito[cantidad] = leeCadena(archivo, MAX_CAR_DISTRITO_REPARTIDOR);
        
        cantidad++;
    }
    
}
void leePlatos(const char *nombreArchivo, int &cantidad,
        int *arrCodigo, char **arrNombre, char **arrCategoria, 
        double *arrPrecio, double *arrDescuento){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //11283   2_BOLAS_DE_HELADO      14.90   POSTRES    17.72%
        archivo>>arrCodigo[cantidad];
        if(archivo.eof()) break;        
        arrNombre[cantidad] = leeCadena(archivo, MAX_CAR_NOMBRE_PLATO);
        archivo>>arrPrecio[cantidad];        
        arrCategoria[cantidad] = leeCadena(archivo, MAX_CAR_CATEGORIA_PLATO);        
        if(archivo.get()=='\n') // no hay descuento
            arrDescuento[cantidad] = 0 ;
        else{
            archivo>>arrDescuento[cantidad];
            archivo.get();
        }
        
        cantidad++;
    }
}

void verificaLectura(const char *nombreArchivo,
        int cantidadRepartidores, 
        int *arrDniRepartidor, char **arrNombreRepartidor, char **arrVehiculoRepartidor, 
        int *arrCodigoDistritoRepartidor, char **arrNombreDistritoRepartidor, 
        int cantidadPlatos,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato, 
        double *arrPrecioPlato, double *arrDescuentoPlato){
    ofstream archivo(nombreArchivo, ios::out);
    if (not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<right
            <<setw(MAX_TAM_LIN/2)<<"VERIFICACION DE REPARTIDORES"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_TAM_COD)<<"DNI"
            <<setw(MAX_TAM_NOMBRE_REPARTIDOR)<<"NOMBRE"
            <<setw(MAX_TAM_VEHICULO_REPARTIDOR)<<"VEHICULO"
            <<setw(MAX_TAM_COD)<<"DIST COD"
            <<setw(MAX_TAM_DISTRITO_REPARTIDOR)<<"DIST NOMBRE"
            <<endl;
    imprimeLinea(archivo, '=');
    
    for (int i = 0; i < cantidadRepartidores; i++) {        
        archivo<<left
            <<setw(MAX_TAM_COD)<<arrDniRepartidor[i]
            <<setw(MAX_TAM_NOMBRE_REPARTIDOR)<<arrNombreRepartidor[i]
            <<setw(MAX_TAM_VEHICULO_REPARTIDOR)<<arrVehiculoRepartidor[i]
            <<setw(MAX_TAM_COD)<<arrCodigoDistritoRepartidor[i]
            <<setw(MAX_TAM_DISTRITO_REPARTIDOR)<<arrNombreDistritoRepartidor[i]
            <<endl;
    }
    imprimeLinea(archivo, '=');

    archivo<<right
            <<setw(MAX_TAM_LIN/2)<<"VERIFICACION DE PLATOS"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_NOMBRE_PLATO)<<"NOMBRE"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_CATEGORIA_PLATO)<<"CATEGORIA"
            <<setw(MAX_TAM_DIN)<<"DESCUENTO"            
            <<endl;
    imprimeLinea(archivo, '=');
    
    for (int i = 0; i < cantidadPlatos; i++) {        
        archivo<<left
            <<setw(MAX_TAM_COD)<<arrCodigoPlato[i]
            <<setw(MAX_TAM_NOMBRE_PLATO)<<arrNombrePlato[i]
            <<setw(MAX_TAM_DIN)<<arrPrecioPlato[i]
            <<setw(MAX_TAM_CATEGORIA_PLATO)<<arrCategoriaPlato[i]
            <<setw(MAX_TAM_DIN)<<arrDescuentoPlato[i]
            <<endl;
    }
}
void leeRepartos(const char *nombreArchivo,
        int cantidadRepartidores, 
        char **arrVehiculoRepartidor, int *arrCodigoDistritoRepartidor,
        int *arrTotalPlatosRepartidor, double *arrMontoTotalPlatosRepartidor, 
        double *arrDescuentoPlatosRepartidor, double *arrDescuentoClienteRepartidor, 
        double *arrPagoRepartidor, double *arrTotalIngresadoRepartidor, 
        int cantidadPlatos,
        int *arrCodigoPlato, double *arrPrecioPlato, double *arrDescuentoPlato, 
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int nroPedido, dniRep, codigoDistrito;
    char vehiculo[MAX_CAR_VEHICULO_REPARTIDOR]{} , 
            clienteConDescuento;
    double descuentoCliente;
    while(true){
        //804501   71422479   8280       Motocicleta       N              3   39475   1   15760
        archivo>>nroPedido;
        if(archivo.eof()) break;
        archivo>>dniRep>>codigoDistrito>>vehiculo>>clienteConDescuento;
        if(clienteConDescuento == 'S'){
            archivo>>descuentoCliente;
            archivo.get();
        }
        else
            descuentoCliente = 0;
        int posRep = buscaIntCad(arrCodigoDistritoRepartidor, arrVehiculoRepartidor, cantidadRepartidores, 
                codigoDistrito, vehiculo);
        int codigoPlato, cantidadPedida;
        if(posRep == NO_ENCONTRADO) while(archivo.get()!='\n');
        else{
            while(true){
                if(archivo.get()=='\n') break;
                archivo>>cantidadPedida>>codigoPlato;
                
                int posPlato = buscaInt(arrCodigoPlato, cantidadPlatos, codigoPlato);
                
                if(posPlato != NO_ENCONTRADO){
                    procesaRepartidor(arrTotalPlatosRepartidor[posRep], arrMontoTotalPlatosRepartidor[posRep],
                            arrDescuentoPlatosRepartidor[posRep], arrDescuentoClienteRepartidor[posRep], 
                            arrPagoRepartidor[posRep], arrTotalIngresadoRepartidor[posRep], 
                            cantidadPedida, arrPrecioPlato[posPlato], arrDescuentoPlato[posPlato], 
                            descuentoCliente, arrVehiculoRepartidor[posRep]);
                    procesaPlato(arrCantidadPlato[posPlato], arrMontoVendidoPlato[posPlato], arrDescuentoAlPlato[posPlato],
                            arrDescuentoAlCliente[posPlato], arrTotalIngresadoPlato[posPlato], 
                            cantidadPedida, arrPrecioPlato[posPlato], 
                            arrDescuentoPlato[posPlato], descuentoCliente);
                }
            }
        }
    }
}
void procesaRepartidor(int &totalPlatosRepartidor, double &montoTotalPlatosRepartidor,
        double &descuentoPlatosRepartidor, double &descuentoClienteRepartidor,
        double &pagoRepartidor, double &totalIngresadoRepartidor,
        int cantidadPedida, double precioPlato, double descuentoPlato, 
        double descuentoCliente, const char *vehiculo){
    double pagoPlato = cantidadPedida*precioPlato, 
            pagoRep = strcmp(vehiculo, "Motocicleta") == 0 ? 0.1*pagoPlato:0.05*pagoPlato;;
    totalPlatosRepartidor+=cantidadPedida;
    montoTotalPlatosRepartidor+=pagoPlato;
    descuentoPlatosRepartidor+=pagoPlato*(descuentoPlato/100.0);
    descuentoClienteRepartidor+=pagoPlato*(descuentoCliente/100.0);
    pagoRepartidor+=pagoRep;
    totalIngresadoRepartidor +=
            pagoPlato - (pagoRep+pagoPlato*(descuentoPlato/100.0)+pagoPlato*(descuentoCliente/100.0));
}
void procesaPlato(int &cantidadPlato, double &montoVendidoPlato, double &descuentoAlPlato,
        double &descuentoAlCliente, double &totalIngresadoPlato,
        int cantidadPedida, double precioPlato, 
        double descuentoPlato, double descuentoCliente){
    double vendido = cantidadPedida*precioPlato;
    cantidadPlato+=cantidadPedida;
    montoVendidoPlato+=vendido;
    descuentoAlPlato+=vendido*(descuentoPlato/100.0);
    descuentoAlCliente+=vendido*(descuentoCliente/100.0);
    totalIngresadoPlato+=
            vendido - (vendido*(descuentoPlato/100.0)+vendido*(descuentoCliente/100.0));    
}
//BUSQUEDA
int buscaIntCad(int *arrInt, char **arrCad, int cantidad,
        int codigo, char *cad){
    
    for (int i = 0; i < cantidad; i++) {        
        if(arrInt[i] == codigo and strcmp(arrCad[i], cad)==0) return i;
    }
    return NO_ENCONTRADO;   
}
int buscaInt(int *arrInt, int cantidad, int codigo){
    
    for (int i = 0; i < cantidad; i++) {        
        if(arrInt[i] == codigo) return i;
    }
    return NO_ENCONTRADO;   
}

//ORDENAMIENTO
void ordenaRepartidores(int cantidadRepartidores, char **arrNombreRepartidor,
        int *arrDniRepartidor, char **arrVehiculoRepartidor,
        int *arrCodigoDistritoRepartidor, char **arrNombreDistritoRepartidor) {
    for (int i = 0; i < cantidadRepartidores-1; i++) {        
        for (int j = i+1; j < cantidadRepartidores; j++) {            
            if(strcmp(arrNombreRepartidor[i], arrNombreRepartidor[j])>0){
                cambiaInt(arrDniRepartidor[i], arrDniRepartidor[j]);
                cambiaCadChar(arrNombreRepartidor[i], arrNombreRepartidor[j]);
                cambiaCadChar(arrVehiculoRepartidor[i], arrVehiculoRepartidor[j]);
                cambiaInt(arrCodigoDistritoRepartidor[i], arrCodigoDistritoRepartidor[j]);
                cambiaCadChar(arrNombreDistritoRepartidor[i], arrNombreDistritoRepartidor[j]);                
            }
        }
    }    
}
void ordenaPlatos(int cantidad,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato,
        double *arrPrecioPlato, double *arrDescuentoPlato,
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(arrCantidadPlato[i]<arrCantidadPlato[j]
                or
                (arrCantidadPlato[i]==arrCantidadPlato[j]           
                    and 
                strcmp(arrNombrePlato[i], arrNombrePlato[j])>0)){
                cambiaInt(arrCodigoPlato[i], arrCodigoPlato[j]);
                cambiaCadChar(arrNombrePlato[i], arrNombrePlato[j]);
                cambiaCadChar(arrCategoriaPlato[i], arrCategoriaPlato[j]);
                cambiaDouble(arrPrecioPlato[i], arrPrecioPlato[j]);
                cambiaDouble(arrDescuentoPlato[i], arrDescuentoPlato[j]);
                cambiaInt(arrCantidadPlato[i], arrCantidadPlato[j]);
                cambiaDouble(arrMontoVendidoPlato[i], arrMontoVendidoPlato[j]);
                cambiaDouble(arrDescuentoAlPlato[i], arrDescuentoAlPlato[j]);
                cambiaDouble(arrDescuentoAlCliente[i], arrDescuentoAlCliente[j]);
                cambiaDouble(arrTotalIngresadoPlato[i], arrTotalIngresadoPlato[j]);
            }
        }

    }

}
void cambiaInt(int &dato1, int &dato2){
    int aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}
void cambiaDouble(double &dato1, double &dato2){
    double aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}
void cambiaCadChar(char *&cad1, char *&cad2){
    char *aux;
    aux = cad1;
    cad1 = cad2;
    cad2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void emiteReportePlatos(const char *nombreArchivo,
        int cantidad,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato,
        double *arrPrecioPlato, double *arrDescuentoPlato,
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato){
    ofstream archivo(nombreArchivo, ios::out);
    if (not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);        
    
    archivo<<setw(MAX_TAM_LIN/2)<<"EMREPSA DE REPARTOS A DIOMICILIO VENUS S.A."<<endl
            <<setw(MAX_TAM_LIN/2-10)<<"ENTRGAS POR PLATOS"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_NOMBRE_PLATO)<<"DESCRIPCION"
            <<setw(MAX_TAM_CATEGORIA_PLATO)<<"CATEGORIA"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<setw(MAX_TAM_DIN)<<"DESCUENTO"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
            <<setw(MAX_TAM_DIN)<<"  VENDIDO"
            <<setw(MAX_TAM_DIN)<<"DESC PLA"            
            <<setw(MAX_TAM_DIN)<<"DESC CLI"
            <<setw(MAX_TAM_DIN)<<"TOTAL INGRESADO"
            <<endl;
    imprimeLinea(archivo, '=');
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_TAM_COD)<<arrCodigoPlato[i]
                <<setw(MAX_TAM_NOMBRE_PLATO)<<arrNombrePlato[i]
                <<setw(MAX_TAM_CATEGORIA_PLATO)<<arrCategoriaPlato[i]
                <<right<<setw(MAX_TAM_DIN*2/3)<<arrPrecioPlato[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrDescuentoPlato[i]<<left<<setw(MAX_TAM_DIN/3)<<'%'<<right
                <<setw(MAX_TAM_CANT*2/3)<<arrCantidadPlato[i]<<setw(MAX_TAM_CANT/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrMontoVendidoPlato[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrDescuentoAlPlato[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrDescuentoAlCliente[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrTotalIngresadoPlato[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<left
                <<endl;
    }
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD+MAX_TAM_NOMBRE_PLATO+MAX_TAM_CATEGORIA_PLATO+2*MAX_TAM_DIN+MAX_TAM_CANT)<<"TOTALES OBTENIDOS"            
            <<right<<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrMontoVendidoPlato, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrDescuentoAlPlato,cantidad)<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrDescuentoAlCliente, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrTotalIngresadoPlato, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
            <<left
            <<endl;
}
void emiteReporteRepartidores(const char *nombreArchivo,
        int cantidad,
        int *arrDniRepartidor, char **arrNombreRepartidor, char **arrVehiculoRepartidor,
        char **arrNombreDistritoRepartidor, int *arrTotalPlatosRepartidor, 
        double *arrMontoTotalPlatosRepartidor, double *arrDescuentoPlatosRepartidor, 
        double *arrDescuentoClienteRepartidor, double *arrPagoRepartidor, 
        double *arrTotalIngresadoRepartidor){
    ofstream archivo(nombreArchivo, ios::out);
    if (not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);        
    
    archivo<<setw(MAX_TAM_LIN/2)<<"EMREPSA DE REPARTOS A DIOMICILIO VENUS S.A."<<endl
            <<setw(MAX_TAM_LIN/2-10)<<"ENTRGAS POR REPARTIDOR"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"DNI"
            <<setw(MAX_TAM_NOMBRE_REPARTIDOR)<<"NOMBRE"
            <<setw(MAX_TAM_VEHICULO_REPARTIDOR)<<"VEHICULO"
            <<setw(MAX_TAM_DISTRITO_REPARTIDOR)<<"DISTRITO"
            <<setw(MAX_TAM_CANT)<<"CANTIDAD"
            <<setw(MAX_TAM_DIN)<<"TOTAL"
            <<setw(MAX_TAM_DIN)<<"DESC PLA"            
            <<setw(MAX_TAM_DIN)<<"DESC CLI"
            <<setw(MAX_TAM_DIN)<<"PAGO"
            <<setw(MAX_TAM_DIN)<<"TOTAL INGRESADO"
            <<endl;
    imprimeLinea(archivo, '=');
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_TAM_COD)<<arrDniRepartidor[i]
                <<setw(MAX_TAM_NOMBRE_REPARTIDOR)<<arrNombreRepartidor[i]
                <<setw(MAX_TAM_VEHICULO_REPARTIDOR)<<arrVehiculoRepartidor[i]
                <<setw(MAX_TAM_DISTRITO_REPARTIDOR)<<arrNombreDistritoRepartidor[i]
                <<right<<setw(MAX_TAM_CANT*2/3)<<arrTotalPlatosRepartidor[i]<<setw(MAX_TAM_CANT/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrMontoTotalPlatosRepartidor[i]<<left<<setw(MAX_TAM_DIN/3)<<' '<<right
                <<setw(MAX_TAM_DIN*2/3)<<arrDescuentoPlatosRepartidor[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrDescuentoClienteRepartidor[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrPagoRepartidor[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<setw(MAX_TAM_DIN*2/3)<<arrTotalIngresadoRepartidor[i]<<setw(MAX_TAM_DIN/3)<<' '
                <<left
                <<endl;
    }
    imprimeLinea(archivo, '=');
//    archivo<<left
//            <<setw(MAX_TAM_COD+MAX_TAM_NOMBRE_PLATO+MAX_TAM_CATEGORIA_PLATO+2*MAX_TAM_DIN+MAX_TAM_CANT)<<"TOTALES OBTENIDOS"            
//            <<right<<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrMontoVendidoPlato, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
//            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrDescuentoAlPlato,cantidad)<<setw(MAX_TAM_DIN/2)<<' '
//            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrDescuentoAlCliente, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
//            <<setw(MAX_TAM_DIN/2)<<sumaArrDouble(arrTotalIngresadoPlato, cantidad)<<setw(MAX_TAM_DIN/2)<<' '
//            <<left
//            <<endl;
}
double sumaArrDouble(double *arr, int cantidad){
    double total = 0;
    for (int i = 0; i < cantidad; i++) {        
        total += arr[i];
    }
    return total;
}

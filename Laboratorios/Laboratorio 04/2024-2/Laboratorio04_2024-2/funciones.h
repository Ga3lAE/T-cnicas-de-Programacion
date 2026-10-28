/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 22 de abril de 2025, 06:05 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//impresion
void imprimeLinea(ofstream &archivo, char c);
void leeImprimeTexto(ifstream &archivoLectura, 
        ofstream &archivoReporte, char del, int espacio); 
void leeImprimeVehiculo(ifstream &archivoLectura, 
        ofstream &archivoReporte,char &vehiculo);

//busqueda
int buscaInt(int *arreglo, int elemento, int cantidadElementos);

//lectura
void leePlatos(const char *nombreArchivoPlatosOfrecidos,
        int &cantidadPlatos,
        int *codigosPlatos, double *preciosPlatos);
void leeDatosEmiteReporte(int cantidadPlatos, 
        int *codigosPlatos, double *preciosPlatos,
        const char* nombreArchivoRepartidores, 
        const char* nombreArchivoRepartosARealizar, 
        const char* nombreArchivoReporte);

void leeProcesaArchivos(ifstream &archivoRepartidores,
        ifstream &archivoRepartos,
        ofstream &archivoReporte, 
        int cantidadPlatos, int *codigosPlatos, double *preciosPlatos);
void imprimeEncabezado(ofstream &archivo);
void leeImprimeRepartidor(ifstream &archivoRepartidores, ofstream &archivoReporte,
        int dniRepartidor, char &vehiculo, int &codigoDistritoRepartidor,
        int cantidadRepartidores);
void leeRepartos(ifstream &archivoRepartos, ofstream &archivoReporte,
        int codigoDistritoRepartidor, char vehiculo, 
        int*, double *, int);

void asiganPagos(int cantidadPlatosPedidos, double precioPlato,
        double &pagoCliente,
        double &pagoRepartidor, char vehiculo,
        double &totalRecaudadoCliente);
void imprimeEstadisticasCliente(ofstream &archivo, 
        double pagoCliente, double pagoRepartidor, double totalRecaudadoCliente);

void imprimeEstadisticasFinales(ofstream &archivo, 
        double recaudado, double pago);

#endif /* FUNCIONES_H */


/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 7 de junio de 2025, 05:00 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void leeTablaInfracciones(const char *nombreArchivo, int &cantidad,
        int *arrCodigo, double *arrMultas);
void leeInfracciones(const char *nombreArchivoInfraccionesCometidas, const char *nombreArchivoPlacasRegistradas,
        int &cantidadRepresentates,
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTottalMultas, double *arrTotalPendientes, double *arrTotalPagadas, 
        int*arrCodigoInfracciom, double *arrMultaInfracciones, int cantidadInfracciones);
int leeFecha(ifstream &archivo);

//BUSQUEDA
int buscaIntBinAsc(int *arr, int cant, int el);

//BUSQUEDA
void insertaInfraccion(int *arrCodigo, double *arrMultas, int &cantidad,
        int codigo, double multa);
int agregaRepresentante(int &cantidad, 
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTotalMultas, double *arrTotalPendientes, double *arrTotalPagadas, 
        int dni);

//PLACA
int cuentaPlacas(const char*listaPlacas);
void obtenerPlaca(const char *listaDePlacas, int n,char *&placa);
void agregarPlaca(char *listaDePlacas, const char *placa);
bool comparaPlacas(const char *placa1, const char *placa2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emiteReporte(const char *nombreArchivoReporte, const char *nombreArchivoPlacasRegistradas,
        int &cantidad, 
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTotalMultas, double *arrTotalPendientes, double *arrTotalPagadas);
void imprimePlaca(ofstream &archivoReo, ifstream &archivoPlac, int dni);
void imprimeFecha(ofstream &archivo, int fecha);

#endif /* FUNCIONES_H */

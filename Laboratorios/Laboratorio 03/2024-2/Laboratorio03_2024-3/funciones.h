/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 15 de abril de 2025, 09:13 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char c);

void leeProcesaArchivos(const char *nombreArchivoPedidos, 
        const char *nombreArchivoPlatos, 
        const char *nombreArchivoReporte);

void procesaDatos(ifstream &archivoPedidos, ifstream &archivoPlatos, 
        ofstream &archivoReporte, 
        double &totalRecaudado);
void procesaRepartos(ifstream& archivoRepartos, ofstream& archivoReporte, 
        int codigoPlato, double precioPlato, 
        double &totalRecaudado);
void leeHora(ifstream& archivo, int& hora);
void imprimeEncabezado(ofstream& archivo);
void imprimeDatosPlato(ifstream &archivoPlatos, 
        ofstream &archivoReporte, 
        int codigoPlato, double &precioPlato);
void imprimeEncabezado(ofstream& archivo);
void imprimeEncabezadoRepartos(ofstream& archivoReporte);
void imprimeCategorias(ofstream& archivoReportes);
void imprimeDescripcionPlato(ifstream &archivoPlatos, 
        ofstream &archivoReporte);
void imprimeTipoPlato(ifstream &archivoPlatos, 
        ofstream &archivoReporte);
void imprimePlato(ofstream& archivoReporte, 
        int codigoRepartidor, int horaPartida, 
        int cantidadPedida,
        int& cantidadAtendia, double& pagoEnvios,
        double precio, double& totalRecaudado);
void imprimeHora(ofstream& archivo, int hora);

#endif /* FUNCIONES_H */


/* 
 * File:   funcionesAuxiliares.h
 * Author: arias
 *
 * Created on 12 de abril de 2025, 11:02 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimeLinea(ofstream& archivo, char car);

void leeProcesaDatos(const char* nombreArchivoCitas, 
        const char* nombreArchivoReporte);
void procesaArchivos(ifstream& archivoCitas, ofstream& archivoReporte, 
        int& cantidadRegistrosTotal, int& cantidadRegistrosProcesados);
void leeFecha(ifstream& archivoLectura, int& fecha);
void leeHora(ifstream& archivoLectura, int& hora);
void procesaImprimeDatos(ofstream &archivoReporte, 
        int fecha, int dni, int horaInicio, int horaFin, 
        double descuento, double tarifaMedico, double pagoMedicinas, 
        double &totalIngresos);

void imprimeEncabezado(ofstream& archivoReporte, int duracionMinima, int duracionMaxima);
void imprimeCategorias(ofstream& archivoReporte);
void imprimeFecha(ofstream& archivoReporte, int fecha);
void imprimeHora(ofstream& archivoReporte, int hora);
void imprimeEstadisticas(ofstream& archivoReporte, 
        int cantidadRegistrosTotal, int cantidadRegistrosProcesados, 
        double porcentajeRegistrosProcesados);

#endif /* FUNCIONESAUXILIARES_H */


/* 
 * File:   funcionesAuxiliares.h
 * Author: arias
 *
 * Created on 13 de abril de 2025, 12:15 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimeLinea(ofstream &archivoReporte, char c);

void leeProcesaDatos(const char *nombreArchivoRegistro, 
        const char *nombreArchivoReporte);

void procesaArchivos(ifstream &archivoRegistro, ofstream &archivoReporte, 
            int &cantidadTelevidentes, 
            int &tiempoTotalVistoMenoresYAdultos, int &cantidadMenoresYADultos, 
            int &cantidadMujeres, int &cantidadMujeresVenTvpucp);
void leeImprimeNombre(ifstream &archivoEntrada, ofstream &archivoSalida, char del);
void leeFecha(ifstream &archivoEntrada, int &fecha);
void leeHora(ifstream &archivoEntrada, int &hora);

void imprimeEncabezado(ofstream& archivoReporte);
void imprimeCategorias(ofstream& archivoReporte);
void imprimeEstadisticas(ofstream& archivoReporte, 
        int cantidadTelevidentes, double promedioTiempoVistoMenoresYAdultos, 
        double porcentajeMujeresVenTvpucp);
void imprimeHora(ofstream &archivoReporte, int hora);
void imprimeSexo(ofstream& archivoReporte, char sexo);
void imprimeCategoria(ofstream& archivoReporte, int fecha);
void imprimeCompania(ofstream& archivoReporte, char empresa);

#endif /* FUNCIONESAUXILIARES_H */


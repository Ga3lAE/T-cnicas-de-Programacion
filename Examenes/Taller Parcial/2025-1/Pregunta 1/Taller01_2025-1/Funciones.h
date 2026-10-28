/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 13 de mayo de 2025, 10:36 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char c);

void procesaArchivos(const char *nombreArchivoVendedores, 
        const char *nombreArchivoArticulos,
        const char *nombreArchivoVentas, 
        const char *nombreArchivoReporte);
void procesaDatos(ifstream &archivoVendedores, ifstream &archivoArticulos, 
        ifstream &archivoVentas, ofstream &archivoReporte, 
        double &ventasTotales,
        int &cantidadVendedoresCuotaMinima, int &cantidadVendedoresNoCuotaMinima, 
        double &porcentajeComisionTotal, 
        int &dniVendedorMayorVenta, double &montoMayorVenta, 
        int &dniVendedorMenorVenta, double &montoMenorVenta);
void leeImprimeVendedor(ifstream &archivoLectura, ofstream &archivoReporte, 
        int &dni, double &porcentaje, double &cuotaMinima, int &cantidad);
void imprimeNombreVendedor(ifstream &archivoLectura, ofstream &archivoReporte);

void procesaVentas(ifstream &archivoVentas, ifstream &archivoArticulos,
        ofstream &archivoReporte,
        double &ventasTotales,
        int &cantidadVendedoresCuotaMinima, int &cantidadVendedoresNoCuotaMinima,
        double &porcentajeComisionTotal,
        int &dniVendedorMayorVenta, double &montoMayorVenta,
        int &dniVendedorMenorVenta, double &montoMenorVenta,
        int dniVendedor, double porcentajeComisionVendedor, double cuotaMinimaVendedor);

void leeCodigoArticulo(ifstream &archivo,
        char &cod1, char &cod2, char &cod3, int &codNum);
void leeFecha(ifstream &archivo, int &fecha);
void buscaArticulo(ifstream &archivoArticulos, ofstream &archivoReporte,
        char cod1, char cod2, char cod3, int codNum, 
        double &precio, int &cantidadArticulos, 
        int cantidadComprada, int fecha);
void imprimeArticulo(ifstream &archivoLectura, ofstream &archivoReporte);
void imprimeFecha(ofstream &archivo, int &fecha);


#endif /* FUNCIONES_H */

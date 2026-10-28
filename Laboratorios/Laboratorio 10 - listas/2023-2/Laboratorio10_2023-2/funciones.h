/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 10:16 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>


void imprimeLinea(char c, ofstream& archivo);
void datosArchivoIf(int& tamArch, int tamElemento, int& cantidad, ifstream& archivo);
void datosArchivoF(int& tamArch, int tamElemento, int& cantidad, fstream& archivo);

void leeArticulos(const char* nombreArchivoLec, const char* nombreArchivoBin);

void leeVendedores(const char* nombreArchivoLec, const char* nombreArchivoBin);
void quitaGuiones(char* cad);

void leeVentas(const char* nombreArchivoLec, const char* nombreArchivoVendedores, 
        const char* nombreArchivoArticulos);
int buscaArticulo(char* codigo, fstream& archivo, int cantidad);
int buscaVendedor(int nDNI, fstream& archivo, int cantidad);
int buscaVenta(char* codigo, struct ArticuloVendido* ventas, int cantidad);


void emiteReporte(const char* nombreArchivoReporte, const char* nombreArchivoVendedores, 
        const char* nombreArchivoArticulos);
void imprimeEncabezadoVendedores(const struct Vendedor& vendedor, int cont, 
        ofstream& archivo);
void imprimeVentas(Vendedor vendedor, ofstream& archivo, ifstream& archivoArticulos);
void nombraArticulo(char* codigo, ifstream& archivo, char* descripcion);
void imprimeEncabezadoArticulos(ofstream& archivo);
void imprimeArticulo(Articulo articulo, int cont, ofstream& archivo, double&);

#endif /* FUNCIONES_H */


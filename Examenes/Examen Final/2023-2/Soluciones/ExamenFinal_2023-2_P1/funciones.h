/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 06:02 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);

char* leeCadena(ifstream& archivo, char del);

void leeArticulos(const char* nombreArchivo, struct Articulo* articulos, 
        int& cantidad);
void confirmaArticulos(const char* nombreArchivo, struct Articulo* articulos, 
        int cantidad);

void leeVendedores(const char* nombreArchivo, Vendedor* vendedores, int& cantidad);
void quitaGuiones(char* cadena);

void emiteReporte(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidadVendedores, 
        struct Articulo* articulos, int cantidadArticulos);
void imprimeEncabezadoVendedores(ofstream& archivo, int cont, Vendedor vendedor);
void imprimeEncabezadoVentas(ofstream& archivo);

void leeVentas(const char* nombreArchivo, struct Vendedor* vendedores, 
        int cantidadVendedores, struct Articulo* articulos, int cantidadArticulos);
int buscaProducto(char* codigo, struct Articulo* articulos, int cantidad);
int buscaVendedor(int DNI, struct Vendedor* vendedores, int cantidad);
int buscaVenta(char* codigo, struct ArticuloPedido* articulos, int cantidad);
int buscaPerdida(char* codigo, struct ArticuloPedido* articulos, int cantidad);

#endif /* FUNCIONES_H */


/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 02:54 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
char* leeCadena(ifstream& archivo, char del);

void leeArticulos(const char* nombreArchivo, 
        struct Articulo* articulos, int& cantidad);
void pruebaArticulos(const char* nombreArchivo, 
        struct Articulo* articulos, int cantidad);

void leeVendedores(const char* nombreArchivo, 
        struct Vendedor* vendedores, int& cantidad);
void quitaEspacios(char* nombre);

void emiteReporte(const char* nombreArchivo, 
        struct Vendedor* vendedores, int cantidad);
void imprimeVendedor(ofstream& archivo, 
        const struct Vendedor& vendedor, int cont);
void imprimeVentas(ofstream& archivo, 
        const struct ArticuloPedido& venta, int cont, 
        double& total);

void leeVentas(const char* nombreArchivo, struct Vendedor* vendedores, 
        int cantidadVendedores, Articulo* articulos, int cantidadAritculos);
int buscaArticulo(char* codigo, struct Articulo* articulos, int cantidad);
int buscaVendedor(int codigo, struct Vendedor* vendedores, int cantidad);
void procesaArticulo(struct Articulo& articulo, struct ArticuloPedido& articuloPedido, 
        double& montoTotal, int &cantArtTotal, 
        double& montoTotalArticulo, int& cantTotalArticulo, 
        int cantidadPedida, int fecha);
void procesaVenta(struct Articulo& articulo, struct Vendedor& vendedor, 
        int cantidadPedida, int fecha);

#endif /* FUNCIONES_H */


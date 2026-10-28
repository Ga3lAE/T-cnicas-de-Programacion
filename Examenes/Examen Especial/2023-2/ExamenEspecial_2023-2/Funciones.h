/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 27 de junio de 2025, 07:20 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
int leeFecha(ifstream &archivo);
char *copiaCadena(const char *cad);
void leeArticulos(const char *nombreArchivo, struct NodoArticulo *&lista);
void leeVendedores(const char *nombreArchivo, struct NodoVendedor *&lista);
void leeVentas(const char *nombreArchivo, 
        struct NodoArticulo *listaArticulos, 
        struct NodoVendedor *listaVenedores);

//INSERCION
void insertaArticuloOrdenado(struct Articulo articulo, struct NodoArticulo *&lista);
void insertaVendedorOrdenado(struct Vendedor vendeddor, struct NodoVendedor *&lista);

//BUSQUEDA
struct NodoArticulo *buscaArticulo(struct NodoArticulo *lista, const char *codigo);
struct NodoVendedor *buscaVendedor(struct NodoVendedor *lista, int dni);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void imprimeArticulos(const char *nombreArchivo, struct NodoArticulo *lista);
void imprimeVendedores(const char *nombreArchivo, struct NodoVendedor *lista);
void imprimeArticulo(ofstream &archivo, struct ArticuloPedido *articulos, int cantidad, 
        double &suma);


#endif /* FUNCIONES_H */

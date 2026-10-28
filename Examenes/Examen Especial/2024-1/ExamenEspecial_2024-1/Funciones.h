/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 13 de junio de 2025, 10:39 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
int leeFecha(ifstream &archivo);
void leeClientes(const char *nombreArchivo, 
        struct NodoCliente *&listaClientes);
void leeLibros(const char *nombreArchivo, 
        struct NodoLibro *&lista);
void leeVentas(const char *nombreArchivo, 
        struct NodoCliente *listaClientes, 
        struct NodoLibro *listaLibros);
void procesaCliente(struct NodoCliente* clienteActual, 
        struct NodoLibro* libroActual);
int insertaLibreria(struct Libro &libro, int codigoLibreria);
void asignaCalificacion(int &cantidad, double &suma, int calificacion);
void procesaLibro(int codigoLibreria, int fechaCompra, 
        int dniComprador, int calificacion, 
        struct NodoCliente* clienteActual, 
        struct NodoLibro* libroActual);

//INSERCION
void insertaClienteLista(struct Cliente cliente, 
        struct NodoCliente *&listaCliente);
void insertaLibroLista(struct Libro libro, 
        struct NodoLibro *&lista);

//BUSQUEDA
struct NodoCliente *buscaCliente(struct NodoCliente *lista, int dato);
struct NodoLibro *buscaLibro(struct NodoLibro *lista, const char *dato);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void verificaClientes(const char *nombreArchivo, 
        struct NodoCliente *listaClientes);
void verificaLibros(const char *nombreArchivo, 
        struct NodoLibro *lista);

#endif /* FUNCIONES_H */

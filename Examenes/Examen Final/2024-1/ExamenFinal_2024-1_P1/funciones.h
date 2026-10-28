/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 09:30 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
char* leeCadena(ifstream& archivo, char del);

void leeClientes(const char* nombreArchivo, 
        struct Cliente* clientes, int& cantidad);
void confirmaClientes(const char* nombreArchivo, 
        struct Cliente* clientes, int cantidad);

void leeLibros(const char* nombreArchivo, 
        struct Libro* libros, int& cantidad);

void emiteReporte(const char* nombreArchivo, 
        struct Libro* libros, int cantidadLibros);
void imprimeLibro(ofstream& archivo, 
        const struct Libro& libro, int cont);
double hallaPromedio(double suma, int cantidad);
void imprimeLibreria(ofstream& archivo, 
        const struct Libreria& libreria);
void imprimeVenta(ofstream& archivo, 
        const struct Venta& venta, int cont);

void leeVentas(const char* nombreArchivo, 
        struct Libro* libros, int cantidadLibros, 
        struct Cliente* clientes, int cantidadClientes);
int buscaLibro(char* codigo, struct Libro* libros, int cantidad);
int buscaCliente(int dni, struct Cliente* clientes, int cantidad);
void procesaVenta(struct Libro& libro, struct Cliente& cliente, 
        int calificacion, int codigoLibreria, int fecha);
int buscaLibreria(int codigo, struct Libreria* librerias, int cantidad);

#endif /* FUNCIONES_H */


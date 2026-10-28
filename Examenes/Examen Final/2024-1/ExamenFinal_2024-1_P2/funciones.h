/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 2 de diciembre de 2024, 12:22 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
int datosArchivoF(int tamElem, fstream& archivo);
int datosArchivoIf(int tamElem, ifstream& archivo);

void leeClientes(const char* nombreArchivoDatos, 
        const char* nombreArchivoBin);
void confirmaClientes(const char* nombreArchivoReporte, 
        const char* nombreArchivoBin);

void leeLibros(const char* nombreArchivoDatos, 
        const char* nombreArchivoBin);
void emiteReporte(const char* nombreArchivoReporte, 
        const char* nombreArchivoBin);
void imprimeLibro(ofstream& archivo, const struct Libro& libro, int cont);
void imprimeLibreria(ofstream& archivo, const struct Libreria& libreria);
void imprimeVenta(ofstream& archivo, const struct Venta& venta, int cont);
double hallaPromedio(double suma, int cantidad);

void leeVentas(const char* nombreArchivoVentas, 
        const char* nombreArchivoLibros, 
        const char* nombreArchivoClientes);
void leeCompras(ifstream& archivoVentas, fstream& archivoClientes, fstream& archivoLibros, 
        struct Cliente& cliente, struct Libro& libro, 
        int cantLibros, int tamLibro, int cantClientes, int tamCliente, 
        int codigoLibreria, int fechaVenta);
int buscaCliente(int dni, fstream& archivo, int cantidad, int tamElem);
int buscaLibro(char* codigo, fstream& archivo, int cantidad, int tamElem);
void  procesaVenta(struct Libro& libro, struct Cliente& cliente, 
        int calificacion, int codigoLibreria, int fecha);
int buscaLibreria(int codigo, struct Libreria* librerias, int cantidad);







#endif /* FUNCIONES_H */


/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 09:15 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
char* leeCadena(ifstream& archivo, char del);

void leeLibros(const char* nombreArchivo, struct Libro* libros, int& cantidad);
void confirmaLibros(const char* nombreArchivo, struct Libro* libros, int cantidad);

void leePrestamos(const char* nombreArchivo, 
        struct RegistroPrestamo* prestamos, int& cantidad);
void confirmaPrestamos(const char* nombreArchivo, 
        struct RegistroPrestamo* prestamos, int cantidad);

void leeSolicitudes(const char* nombreArchivo, const char* nombreArchivoReporte,
        struct RegistroPrestamo* prestamos, int& cantidadPrestamos, 
        struct Libro* libros, int cantidadLibros);
int buscaLibro(char* codigo, struct Libro* libros, int cantidad);
int buscaUsuario(int codigo, struct RegistroPrestamo* prestamos, int cantidad);
void imprimeEnReporte(ofstream& archivo, 
        int dni, const struct RegistroPrestamo& prestamo, 
        const struct Libro& libro, int tipo);

#endif /* FUNCIONES_H */


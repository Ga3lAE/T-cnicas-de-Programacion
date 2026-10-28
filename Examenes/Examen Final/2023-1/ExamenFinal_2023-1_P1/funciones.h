/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 09:57 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);

void leeLibros(const char* nombreArchivoLec, const char* nombreArchivoBin);

void verificaLibros(const char* nombreArchivo, Libro* libros, int cantidad);

void leeUsuarios(const char* nombreArchivo, Usuario* usuarios, int& cantidad);

void verificaUsuarios(const char* nombreArchivo, Usuario* usuarios, int cantidad);

void leeDevoluciones(const char* nombreArchivo, Usuario* usuarios, 
        int cantidadUsuarios, Libro* libros, int cantidadLibros);

int buscaLibro(char* codigo, Libro* libros, int cantidad);
int buscaUsuario(int nDNI, Usuario* usuarios, int cantidad);
void eliminaLibroEnPoder(struct LibroEnSuPoder* libros, char* codigo, int& cantidad);
void procesaDevolucion(struct Libro& libro, int fecha, struct Usuario& usuario);

#endif /* FUNCIONES_H */


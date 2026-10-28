/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 24 de noviembre de 2024, 09:57 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
void datosArchivoIn(int tamElemento, int& cantidad, ifstream& archivoDatos);

void leeLibros(const char* nombreArchivoLec, const char* nombreArchivoBin);
void verificaLibros(const char* nombreArchivoReporte, const char* nombreArchivoDatos);

void leeUsuarios(const char* nombreArchivoLec, const char* nombreArchivoBin);
void verificaUsuarios(const char* nombreArchivoReporte, const char* nombreArchivoDatos);


void leeDevoluciones(const char* nombreArchivoDevoluciones, 
        const char* nombreArchivoLibros, const char* nombreArchivoUsuarios);

int buscaLibro(char* codigo,  fstream& archivo, int cantidad);
int buscaUsuario(int nDNI,  fstream& archivo, int cantidad);

void eliminaLibroEnPoder(fstream& archivoUsuarios, int posUsuario, char* codigo);
void procesaDevolucion(fstream& archivo, fstream& archivoUsuarios, 
        int posLibro, int fecha, int dni);

#endif /* FUNCIONES_H */


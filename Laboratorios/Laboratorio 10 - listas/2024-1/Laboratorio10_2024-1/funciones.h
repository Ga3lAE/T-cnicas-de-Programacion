/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 23 de noviembre de 2024, 11:57 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);

void leeClientes(const char* nombreArchivoCsv, const char* nombreArchivoBin);
void leeLibros(const char* nombreArchivoCsv, const char* nombreArchivoBin);

void leeVentas(const char* nombreArchivoCsv, const char* nombreArchivoLibros, 
        const char* nombreArchivoClientes);
int buscaLibro(char* codigo, fstream& archivo, int cantidad);
void asignaNombreSegunDni(char* nombre, int dni, ifstream& archivo);
int buscaCliente(int nDNI, ifstream& archivo, int cantidad);

void asignaRankings(const char* nombreArchivoLibros);
void oredenaLibros(const char* nombreArchivoLibros);

void emiteReporte(const char* nombreArchivoReporte, const char* nombreArchivoLibros);
void datosArchivoF(int& tamArchivo, int tamDato, int& cantidad, fstream& archivo);
void datosArchivoIn(int& tamArchivo, int tamDato, int& cantidad, ifstream& archivo);
void imprimeEncabezadoLibros(ofstream& archivoReporte, int cont, struct Libro libro);
void imprimeEncabezadoVentas(ofstream& archivoReporte);
void imprimeFecha(struct Fecha fecha, ofstream& archivo);


#endif /* FUNCIONES_H */


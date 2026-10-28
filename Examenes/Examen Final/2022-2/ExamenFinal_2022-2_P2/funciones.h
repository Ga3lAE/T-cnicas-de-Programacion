/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 05:53 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);

void cargarDirecciones(const char* nombreArchivoCsv, const char* nombreArchivoBin);

void cargarPedidos(const char* nombreArchivoCsv, const char* nombreArchivoBin);

#endif /* FUNCIONES_H */


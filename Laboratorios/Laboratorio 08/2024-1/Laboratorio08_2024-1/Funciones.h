/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 14 de junio de 2025, 08:30 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaEscata(ifstream &archivo, char del);
void leeNotas(const char *nombreArchivo,
        struct Alumno *arr, int &cantidad);;
void leeAlumnos(const char *nombreArchivo,
        struct Alumno *arr, int cantidad);
void leeFacultades(const char *nombreArchivo,
        struct Alumno *arr, int cantidad);

//BUSQUEDA
int buscaAlumno(struct Alumno *arr, int cantidad, int el);

//AGREGA
int agregaAlumno(struct Alumno *arr, int &cantidad, int codigo);

//ORDENAMIENTO
void ordenaAlumnos(struct Alumno *arr, int cantidad);
void cambiaAlumno(struct Alumno &al1, struct Alumno &al2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void preocesaReporte(const char *nombreArchivo,
        struct Alumno *arr, int cantidad);

#endif /* FUNCIONES_H */

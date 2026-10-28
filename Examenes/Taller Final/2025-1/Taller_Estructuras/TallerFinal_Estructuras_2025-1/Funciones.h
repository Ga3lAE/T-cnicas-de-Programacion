/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 6 de julio de 2025, 12:10 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
void leeCursos(const char *nombreArchivo, struct Curso *arr, int &cantidad);
void leeEscalas(const char *nombreArchivo, struct Escala *arr, int &cantidad);
void leeAlumnos(const char *nombreArchivo, struct Alumno *arr, int &cantidad);
void leeMatricula(const char *nombreArchivo, 
        struct Curso *arrCursos, int cantidadCursos, 
        struct Escala *arrEscalas, int cantidadEscalas, 
        struct Alumno *arrAlumnos, int cantidadAlumnos, 
        int anio, int ciclo);

//PREOCESAMIENTO
char *copiaCadena(const char *cad);
void procesaCursoMatriculado(struct Alumno &alumno, 
        struct Escala escala,
        struct Curso curso);

//BUSQUEDA
int buscaAlumno(struct Alumno *arr, int cantidad, int cod);
int buscaEscala(struct Escala *arr, int cantidad, 
        int anio, int ciclo, char escala);
int buscaCurso(struct Curso *arr, int cantidad, int cod);

//ORDENAMIENTO 
void ordenaAlumnos(struct Alumno *arr, int cantidad);
void cambiaAlumno(struct Alumno &al1,struct Alumno &al2);

#endif /* FUNCIONES_H */

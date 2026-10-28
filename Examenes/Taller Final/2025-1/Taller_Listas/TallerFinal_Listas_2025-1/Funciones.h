/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 5 de julio de 2025, 04:58 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
char *copiaCadena(const char *cad);
void leeCursos(const char *nombreArchivo, struct NodoCurso *&lista);
void leeEscalas(const char *nombreArchivo, struct NodoEscala *&lista);
void pideCiclo(bool& inicial, int& anioAnalisis, int& cicloAnalisis);
void leeAlumnos(const char *nombreArchivo, struct NodoAlumno *&lista);
void leeMatricula(const char *nombreArchivo, 
        struct NodoEscala *listaEscala, 
        struct NodoAlumno *listaAlumnos, 
        struct NodoCurso *listaCursos, 
        int anioProc, int cicloProc);

//INSERCION
void insertaCurso(struct Curso curso, struct NodoCurso *&lista);
void insertaEscala(struct Escala escala, struct NodoEscala *&lista);
void insertaAlumno(struct Alumno alumno, struct NodoAlumno *&lista);

//BUSQUEDA
struct NodoEscala *buscaEscala(struct NodoEscala *lista, 
        int anio, int ciclo, char escala);
struct NodoAlumno *buscaAlumno(struct NodoAlumno *lista, int codigo);
struct NodoCurso *buscaCurso(struct NodoCurso *lista, int codigo);

//ELIMINA
void eliminaNoMatriculados(struct NodoAlumno *&lista);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void imprimeReporte(const char *nombreArchivo, struct NodoAlumno *lista, 
        bool inicial, int anio, int ciclo);
void imprimeCursos(ofstream &archivo, struct Alumno alumno);

#endif /* FUNCIONES_H */

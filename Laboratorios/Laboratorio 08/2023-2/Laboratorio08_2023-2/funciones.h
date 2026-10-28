/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 10 de noviembre de 2024, 04:32 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H


void imprimeLinea(char c, ofstream& archivo);

void solicitaCiclo(int& ciclo);

void leeAlumnos(const char* nombreArchivo, struct Alumno* alumnos, int& cantidadAlumnos);
int buscaAlumno(const struct Alumno &aux, struct Alumno* alumnos, int cantidad);
void agregaAlumno(const struct Alumno &aux, struct Alumno* alumnos, int& cantidad);

void leeCursos(const char* nombreArchivo, struct Curso* cursos, int& cantidad);
int buscaCurso(const struct Curso& aux, struct Curso* cursos, int cantidad);
void agregaCurso(const struct Curso& aux, struct Curso* curso, int& cantidad);
void modificaNombre(char* nombre);

void leeEscalas(const char* nombreArchivo, struct Escala* escalas, int& cantidad);
int buscaEscala(const struct Escala& aux, struct Escala* escalas, int cantidad);
void agregaEscala(const struct Escala& aux, struct Escala* escalas, int& cantidad);

void leeMatricula(const char* nombreArchivo, int cicloValido, 
        struct Curso* cursos, int cantidadCursos, 
        struct Alumno* alumnos, int cantidadAlumos, 
        struct Escala* escalas, int cantidadEscalas);

void ordenaCursos(struct Curso* cursos, int cantidad);
void cambiaCurso(struct Curso &c1, struct Curso &c2); 

void imprimeReporte(const char* nombreArchivo, int cicloValido, 
        struct Curso* cursos, int cantidadCursos);
void imprimeEncabezado(ofstream& archivo, int ciclo);

#endif /* FUNCIONES_H */


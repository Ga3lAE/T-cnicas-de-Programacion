/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:33 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
char* leeCadena(ifstream& archivo, char del);

void leeCursos(const char* nombreArchivo, Curso* cursos, int& cantidad);

void leeAlumnos(const char* nombreArchivo, Alumno* alumnos, int& cantidad);
void confirmaAlumnos(const char* nombreArchivo, Alumno* alumnos, int cantidad);

void leeNotas(const char* nombreArchivo, 
        Alumno* alumnos, int cantidadAlumnos, 
        Curso* cursos, int cantidadCursos);

int buscaAlumno(int codigo, Alumno* alumnos, int cantidad);
int buscaCurso(char* codigo, Curso* cursos, int cantidad);
void procesaAlumno(Alumno& alumno, Curso& curso, int nota);
void procesaNotas(int& cantidad, double& promedio, int& sumaNotas, double& sumaCreditos, double credito,
        int nota);
int buscaCursoMatricula(char* codigo, struct CursoMatriculado* cursos, int cantidad);

void ordenaAlumnos(Alumno* alumnos, int cantidad);
void cambiarAlumnos(Alumno& alumno1, Alumno& alumno2);
void ordenaCursos(CursoMatriculado* cursos, int cantidad);
void cambiaCursos(CursoMatriculado& curso1, CursoMatriculado& curso2);

void emiteReporte(const char* nombreArchivo, Alumno* alumnos, int cantidad);
void imprimeAlumno(ofstream& archivo, const Alumno& alumno, int cont);
void imprimeCurso(ofstream& archivo, const CursoMatriculado& curso, int cont);
void imprimeResultados(ofstream& archivo, const Alumno& alumno);

#endif /* FUNCIONES_H */


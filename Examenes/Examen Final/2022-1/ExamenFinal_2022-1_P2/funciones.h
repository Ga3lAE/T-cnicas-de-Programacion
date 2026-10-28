/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 28 de noviembre de 2024, 08:33 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
int cantidadElementosIf(ifstream& archivo, int tam);
int cantidadElementosF(fstream& archivo, int tam);

void leeCursos(const char* nombreArchivoCsv, const char* nombreArchivoBin);
void confirmaCursos(const char* nombreArchivoCsv, const char* nombreArchivoBin);

void leeAlumnos(const char* nombreArchivoCsv, const char* nombreArchivoBin);
void confirmaAlumnos(const char* nombreArchivoReporte, const char* nombreArchivoBin);

void leeNotas(const char* nombreArchivoNotas, 
        const char* nombreArchivoAlumnos, 
        const char* nombreArchivoCursos);

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


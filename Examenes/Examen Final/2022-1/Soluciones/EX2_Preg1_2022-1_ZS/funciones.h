

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 29 de junio de 2023, 01:27 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerCursos(struct Curso* cursos, int& numCursos);
void leerAlumnos(struct Alumno* alumnos, int& numAlumnos);
void emiteReporteSimpleAlumnos(struct Alumno *alumnos,int numAlumnos);
void leerProcesarNotas(struct Alumno* alumnos, int numAlumnos,struct Curso* cursos,
        int numCursos);
void asignarValores(struct Curso& curso, struct Alumno& alumno, int nota);
void emiteReporte(struct Alumno *alumnos,int numAlumnos,struct Curso *cursos,
        int numCursos);
void imprimeCursosMatriculados(struct Alumno &alumno,double &creditosAprobCiclo,
        double &creditosDesaprobCiclo,double &creditosTotales,ofstream &archReporte);
void imprimeResultadosFinal(struct Alumno &alumno,double creditosAprobCiclo,
        double creditosDesaprobCiclo,double creditosTotales,ofstream &archReporte);
int buscarAlumno(struct Alumno* alumnos, int codigo, int numAlumnos);
int buscarCurso(struct Curso* cursos, char* codCurso, int numCursos);
void imprimeLinea(char caracter, int cantidad, ofstream &archRep);
char *leerCadenaExacta(ifstream& arch);

#endif /* FUNCIONES_H */


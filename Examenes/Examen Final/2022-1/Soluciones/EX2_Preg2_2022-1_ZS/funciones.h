

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 27 de junio de 2023, 03:03 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearCursosBin(const char* nombArchCsv, const char* nombArchBin);
void mostrarCursosBin(const char* nombArchBin, const char* nombArchTxt);
void crearAlumnosBin(const char* nombArchCsv, const char* nombArchBin);
void actualizarAlumnosBin(const char* nombAlumnosBin, const char* nomCursosBin, 
        const char* nombArchTxt);
void registrarValores(struct Curso &curso,fstream &archAlumnosBin,
        int tamRegAlumno,int numRegAlumno,ifstream &archNotas);
void ordearAlumnosBin(const char *nombArchBin);
void emiteReporte(const char* nombArchBin, const char* nombArchTxt);
void imprimeAlumnosYresumen(int &contAlumnos,double &promedio,
        double &creditosTotales,struct Alumno &alumno,ofstream &archReporte);
void imprimeYanalizaResumen(struct Alumno &alumno,double promedio,ofstream &archReporte);
int buscarAlumno(fstream& arch, int codigo, int numReg);
int buscarCurso(ifstream& arch, char* codigo, int numReg);
void datosArchivoAlumnos(fstream& arch, int& tamArch, int tamReg, int& numReg);
void datosArchivoCursos(ifstream& arch, int& tamArch, int tamReg, int& numReg);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);
#endif /* FUNCIONES_H */


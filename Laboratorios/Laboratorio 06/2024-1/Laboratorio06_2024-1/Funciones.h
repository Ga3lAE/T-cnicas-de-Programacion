/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 31 de mayo de 2025, 02:21 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void leeCalificaciones(const char* nombreArchivo, int &cantidad,
        int *arrCodigoAlumno, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos);
int agregaAlumno(int &cantidad, int *arrCod, int *arrNumCursos, 
        double *arrSumPondera, double *arrNumCred, int codigo);
void acumulaAlumno(int &numeroCursoa, double &sumaPonderada, 
        double &numeroCreditos, int nota, double creditos);

//BUSQUEDA
int buscaIntBinAsc(int *arr, int cantidad, int elemento);

//REPORTE
void emiteReporte(const char* nombreArchivoAlumnos, const char* nombreArchivoFacultades, const char* nombreArchivoReporte,
        int codigoFacultad, 
        int cantidadAlumnos,
        int *arrCodigoAlumno, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos);
void imprimeLinea(ofstream &archivo, char c);
void imprimeEncabezado(ofstream &archivo, char *nombreFacultad);
void imprimeAlumno(ofstream &archivo, 
        int codigoAlumno, char *nombreAlumno,
        int numCursos, double sumaPonderada,
        double numCreditos);
void procesaNombre(char *nombre);

#endif /* FUNCIONES_H */

/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 9 de junio de 2025, 05:11 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
int leePeriodo(ifstream &archivo);
char *leeCadenaExacta(ifstream &archivo);
void leeAlumnos(const char *nombreArchivo, int &cantidad, 
        int *arrCodigoAlumnos, char **arrNombreAlumnos, char *arrEscalaAlumnos);
void leeCursos(const char *nombreArchivo, int &cantidad, 
        int *arrCodigos, char **arrNombres, double *arrCreditos);
void leeEscalas(const char *nombreArchivo, int &cantidad, 
        int *arrPeriodos, char *arrCodigos, double *arrPrecios);
void leeMatricula(const char *nombreArchivo, int periodoElegido,  
        int cantidadEscalas,
        int *arrPeriodoEscalas, char *arrCodigoEscalas, double *arrPrecioEscalas,
        int cantidadAlumnos,
        int *arrCodigoAlumnos, char *arrEscalaAlumnos,
        int cantidadCursos,
        int *arrCodigoCursos, double *arrCreditoCursos,
        int *arrCantidadCursosAlumnos, double *arrCreditosCursosAlumnos, double *arrMontoPagadoAlumnos);

//BUSQUEDA
int buscaInt(int *arr, int cantidad, int el);
int buscaIntChar(int *arrI, char *arrC, int cantidad, 
        int elI, char elC);

#endif /* FUNCIONES_H */

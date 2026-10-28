/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 31 de mayo de 2025, 06:01 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void leeAlumnos(const char* nombreArchivo, int &cantidad,
        int *arrCodigo, char *arrEscala);

void leeCursos(const char* nombreArchivo, int &cantidad,
        int *arrCodigoCurso,double *arrCreditosCurso);

void leeEscalas(const char* nombreArchivo, int &cantidad,
        int *arrPeriodoEscala, char *arrCodigoEscala, double *arrPagoEscala);

void leeMatricula(const char* nombreArchivo, int periodo,
        int cantidadAlumnos, int *arrCodigoAlumno, char *arrEscalaAlumno,
        int cantidadCursos, int *arrCodigoCurso, double *arrCreditosCurso,
        int cantidadEscalas, int *arrPeriodoEscala, char *arrCodigoEscala, double *arrPagoEscala,
        int *arrCantidadCursosAlumno, double *arrTotalCreditosAlumno, double *arrMontoPagadoAlumno);
void  procesaDatos(int &cantidadCursos, double &totalCreditos, double &montoPagadoAlumno,
        double creditosCurso, double pagoEscala);

//BUSQUEDA
int buscaIntBinAsc(int *arr, int cantidad, int elemento);
int buscaIntChar(int *arrInt, char *arrChar, int cantidad, 
        int elementoInt, char elementoChar);
//AGREGAR
void agregaAlumno(int &cantidad,
        int *arrCodigo, char *arrEscala,
        int codigo, char escala);

void agregaCurso(int &cantidad,
        int *arrCodigo, double *arrCreditos,
        int codigo, double creditos);

//TEXTO
void modificaTexto(char *apellidoNombre, char *apellidoMaterno);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emitirReporte(const char* nombreArchivoReporte, int periodo,  
        const char* nombreArchivoAlumnosNombres, 
        const char* nombreArchivoAlumnosApellidos,
        int cantidadAlumnos, int *arrCodigoAlumno, int *arrCantidadCursosAlumno,
        double *arrTotalCreditosAlumno, char *arrEscalaAlumno, double *arrMontoPagadoAlumno);
void imprimeEncabezado(ofstream &archivo, int periodo);
double sumaArrDouble(double *arr, int cantidad);

#endif /* FUNCIONES_H */

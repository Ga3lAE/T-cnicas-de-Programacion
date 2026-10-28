/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 11 de mayo de 2025, 12:52 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H


//BUSQUEDA
int buscaInt(int *arreglo, int cantidad, int elemento);

void imprimeLinea(ofstream& archivo, char c);

//LECTURAS
void leeAlumnos(const char* nombreArchivo, int& cantidad, int* codigos, int* escalas);
void leeCursos(const char* nombreArchivo, int& cantidad, int* codigos, double* creditos);
void leeEscalas(const char* nombreArchivo, int& cantidad, double* pagos);

//PROCESAMOS 
void procesaMatricula(const char *nombreArchivo,
        int cantidadAlumnos, int *codigosAlumnos, int *escalasPagosdAlumnos,
        int cantidadCursos, int *codigosCursos, double *creditosCursos, 
        int cantidadEscalas, double *pagosEscalas,
        double *totalesCreditosAlumnos, int *totalesCursosAlumnos, double *totalesPagosAlumnos,
        int *alumnosMatriculadosCursos, double *totalesIngresosCursos);

void ordenaAlumnos(int cantidad, int *codigos, int *escalas,
        double *totalesCreditos, int *totalesCursos, double *totalesPagos);
void ordenaCursos(int cantidad, int *codigos, double *creditos,
        int *alumnosMatriculados, double *totalesPagos);

void cambiarInt(int &dato1, int &dato2);
void cambiarDouble(double &dato1, double &dato2);

//IMPRESION
void imprimeReporte(const char *nombreArchivo,
        int cantidadAlumnos, int *codigosAlumnos, 
        int *escalasPagosAlumnos, double *totalesCreditosAlumnos, 
        int *totalesCursosAlumnos, double *totalesPagosAlumnos,
        int cantidadCursos, int *codigosCursos, double *creditosCursos, 
        int *alumnosMatriculadosCursos, double *totalesIngresosCursos);
void imprimeEncaebzadoAlumnos(ofstream &archivo);
void imprimeEncaebzadoCursos(ofstream &archivo);

#endif /* FUNCIONES_H */

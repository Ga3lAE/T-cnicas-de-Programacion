/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 6 de junio de 2025, 05:37 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//BUSQUEDA
int buscaInt(int *arr, int cant, int el);
//LECTURA
char *leeCadena(ifstream &archivo, char del);
void leeCalificaciones(const char *nombreArchivo, int &cantidad,
        int *arrCodigoAlumnos, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos);
void leeAlumnos(const char *nombreArchivo, int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, char **arrNombreFacultadAlumnos);
void leeFacultades(const char *nombreArchivo, int &cantidad,
        char **arrCodigoFacultades, char **arrNombreFacultades);

//ORDENAMIENTO
void ordenaAlumnos(int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos, 
        char **arrCodigoFacultadAlumnos);
void cambiaInt(int &d1, int &d2);
void cambiaDouble(double &d1, double &d2);
void cambiaCad(char *&d1, char *&d2);

//IMPRESION
void imprimeLinea(ofstream &arch, char c);
void emiteReporte(const char *nombreArchivoFacultades, const char *nombreArchivoReporte, int cantidad,
        int *arrCodigoAlumnos, char **arrNombreAlumnos, int *arrNumCursos, 
        double *arrSumaPonderada, double *arrNumCreditos,
        char **arrCodigoFacultadAlumnos, 
        const char *codigoFacultad1, const char *codigoFacultad2);
void imprimeFacultades(ifstream &archivoFacultades, ofstream &archivoReporte,
        const char *codigoFacultad1, const char *codigoFacultad2);
#endif /* FUNCIONES_H */

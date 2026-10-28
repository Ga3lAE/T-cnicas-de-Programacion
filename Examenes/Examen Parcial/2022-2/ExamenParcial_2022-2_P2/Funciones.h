/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 15 de mayo de 2025, 06:19 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA

void leeFecha(ifstream &archivo, int &fecha);
void leeCodigoUsuario(ifstream &archivo, int &codigo);
void saltaDato(ifstream &archivo, char del);

void leeTiktoks(const char *nombreArchivo, int &cantidad,
        int *fechas, int *cantidadesLikes, int *cantidadesReproducciones,
        int fechaInicio, int fechaFin);
void leeUsuarios(const char *nombreArchivo, int &cantidad,
        int *codigos, bool *sonCuentasPublicas);

//PROCESAMIENTO
void procesaComentarios(const char *nombreArchivo,
        int *fechasTktks, int *cantidadesComentariosTktks,
        int *cantidadesLikesComentariosTktks, int *cantidadesReproduccioneeTktks,
        double *ratiosComentariosTktks, bool *sonViralesTktks, int *cantidadesSeguidoresPublicosTktks,
        int cantidadTktks,
        int *codigosUsuarios, bool *sonCuentasPublicasUsuarios, 
        int cantidadUsuarios);
void procesaDatosComentarios(int &cantidadComentarios,
        int &cantidadLikesComentario,
        int &cantidadSeguidoresPublicos,
        bool esCuentaPublicaUsuario,
        int cantidadLikesComentarioRecibido);
void procesaDatosRecuento(int cantidad, int *cantidadesReproduccionee,
        int *cantidadesLikesComentarios, int *cantidadesComentarios,
        double *ratiosComentarios, bool *sonVirales);

//BUSQUEDA
int buscaInt(int *arr, int cantidad, int dato);

//ORDENAMIENTO
void ordenaTiktoks(int cantidad,
        int *fechas, int *cantidadesLikes, int *cantidadesReproducciones);
void cambiarInt(int &d1, int&d2);

//IMPRESION 
void imprimeLinea(ofstream &archivo, char c);
void imprimeFecha(ofstream &archivo, int fecha);
void imprimeReporte(const char *nombreArchivo, int cantidad,
        int fechaInicio, int fechaFin,
        int *fechas, int *cantidadesComentarios,
        int *cantidadesLikesComentarios, int *cantidadesReproducciones,
        double *ratiosComentariosTktks, bool *sonViralesTktks, int *cantidadesSeguidoresPublicosTktks);
void imprimeEncabezado(ofstream &archivo, int fechaInicio, int fechaFin);


#endif /* FUNCIONES_H */

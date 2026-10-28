/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 19 de mayo de 2025, 11:35 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void leeFechaCin(int &fecha);
void leeFecha(ifstream &archivo, int &fecha);
void leeCodigoUsuario(ifstream &archivo, int &codigo);
void saltaLinea(ifstream &archivo);
void saltaDatoDel(ifstream &archivo, char del);
//PROCESA
void leeProcesaArchivos(const char *nombreArchivoTiktoks,
        const char *nombreArchivoComentarios,
        const char *nombreArchivoUsuarios, const char *nombreArchivoPaises,
        const char *nombreArchivoReporte);
void leeArchivos(ifstream &archivoTktks,
        ifstream &archivoComentarios, ifstream &archivoUsuarios, ifstream &archivoPaises,
        int fechaInicio, int fechaFinal, int &fechaMejor,
        ofstream &archivoReporte);
void leeComentarios(ifstream &archivoComentarios, ifstream &archivoUsuarios, 
        ifstream &archivoPais, ofstream &archivoReporte,
        int fechaTktk, 
        int &cantidadComentarios, 
        int &cantidadSeguidoresPublicos, int &cantidadSeguidoresPrivados);

//IMPRESION
void imprimeLinea(ofstream & archivo, char c);
void imprimeFecha(ofstream &archivo, int fecha);
void imprimeNombre(ifstream &archivoLectura, ofstream &archivoImpresion, char del);
void imprimeTexto(ifstream &archivoLectura, ofstream &archivoImpresion, int tam, char del);
void imprimeUsuario(ifstream &archivoUsuarios, ifstream &archivoPais, ofstream &archivoReporte,
        int codigoUser, int cantidadLikes,         
        int &cantidadSeguidoresPublicos, int &cantidadSeguidoresPrivados);
void imprimeEncabezado(ofstream &archivo, int fechaInicio, int fechaFinal);
void imprimeTktk(ofstream &archivo, int fecha, int contador);
void imprimePais(ifstream &archivoPais, ofstream &archivoReporte, int codigo);
void imprimeResumenTktk(ofstream &archivo, int cantidadLikes, int cantidadReprod,
        int cantidadComentarios, int cantidadSeguidoresPublicos, int cantidadSeguidoresPrivados,
        double ratioViral);
void imprimeNombreSeguidor(ifstream &archivoComentarios, ifstream &archivoUsuarios,
        ofstream &archivoReporte,
        int fechaMejor);

#endif /* FUNCIONES_H */

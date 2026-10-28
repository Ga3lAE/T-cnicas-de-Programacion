/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 09:46 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archiv, char c);
//MANEJO DE ARCHIVOS
void datosArchivoIf(int tamEl, ifstream &archivo, int &cantidad);
void datosArchivoF(int tamEl, fstream &archivo, int &cantidad);
void leeLexicon(const char *nombreArchivoCsv, const char *nombreArchivoBin);
void verificaLexicon(const char *nombreArchivoTxt, const char *nombreArchivoBin);
void leePlatos(const char *nombreArchivoCsv, const char *nombreArchivoBin);
void verificaPlatos(const char *nombreArchivoTxt, const char *nombreArchivoBin);

int leeHora(ifstream &archivo);
void leeAtenciones(const char *nombreArchivoTxt, 
        const char *nombreArchivoAtenciones, 
        const char *nombreArchivoPlatos);
double buscaPrecioPlato(ifstream &archivoPlatos, int cantidad, char *codigo);

void imprimeAtencion(const char *nombreArchivoTxt, const char *nombreArchivoBin);
void imprimeHora(ofstream &archivo, int hora);

void leeComentarios(const char *nombreArchivoCsv, 
        const char *nombreArchivoAtenciones, 
        const char *nombreArchivoLexicon);
int buscaAtencion(fstream &archivo, int cantidad, int codigo);
char *preprocesaComentario(char *preprocesado, const char *comentario);
void procesaComentario(struct Comentario &comentario, 
        ifstream &archivoLexicon, int cantidadLexicon);
int cuentaPalabras(char *palabras);
void procesaPalabra(struct Palabra &palabra, char *comentario, int &cantidad);
void buscaPolaridad(ifstream &archivo, int cantidad, struct Palabra &palabra);
#endif /* FUNCIONES_H */

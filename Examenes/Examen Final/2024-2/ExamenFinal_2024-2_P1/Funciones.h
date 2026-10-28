/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 03:47 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);

void leeLexicon(const char *nombreArchivo,
        struct Palabra *lexicon, int &cantidad);
struct Plato *leePlatos(const char *nombreArchivo,
        int max, int &cantidad);
void leeAtenciones(const char *nombreArchivo,
        struct Atencion *atenciones, int &cantidadAtenciones,
        struct Plato *platos, int cantidadPlatos);
void leeComentarios(const char *nombreArchivo,
        struct Atencion *atenciones, int cantidadAtenciones,
        struct Palabra *lexicon, int cantidadLexicon);
//BUSQUEDA
int buscaPlato(struct Plato *platos, int cantidad, char *codigo);
int buscaAtencion(struct Atencion *atenciones, int cantidad, int codigo);
int buscaPolaridad(struct Palabra *lexicon, int cantidad, char *txt);
//PROCESA COMENTARIO
char *preprocesaComentario(char *comentario);
void procesaComentario(struct Comentario &comentario, 
        struct Palabra *lexicon, int cantidadLexicon);
int cuentaPalabras(char *palabras);
void procesaPalabra(struct Palabra &palabra, char *comentario, int &cantidad);
void buscaPolaridad(struct Palabra *lexicon, int cantidad, struct Palabra &palabra);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emitirReporte(const char *nombreArchivo,
        struct Atencion *atenciones, int cantidad);
void imprimeEncabezado(ofstream &archivo);
void imprimeEncabezadoAtenciones(ofstream &archivo,
        int codigo, int hora);
void imprimeHora(ofstream &archivo, int hora);
int sumaPolaridad(struct Comentario *comentarios, int cantidad);

#endif /* FUNCIONES_H */

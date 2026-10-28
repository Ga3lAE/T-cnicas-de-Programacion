/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:18 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
char *copiaCadena(const char *cadena);
void leeLexicon(const char *nombreArchivo, struct NodoPalabra *&lista);
void leePlatos(const char *nombreArchivo, struct NodoPlato *&lista);
void leeAtenciones(const char *nombreArchivo, struct NodoAtencion *&lista, 
        struct NodoPlato *listaPlatos);
void leeComentarios(const char *nombreArchivo, struct NodoAtencion *lista, 
        struct NodoPalabra *listaLexicon);
//PROCESAMIENTO
void completaPlato(struct Plato &platoNuevo,
        int &cantidadPlatos,
        struct NodoPlato *plato, 
        double &total, int cantidad);
void procesaComentario(struct Comentario &comentario, struct NodoPalabra *lista);
char *preprocesaTexto(const char *texto);
int cuentaPalabras(const char *texto);
void completaArregloPalabras(const char *texto, struct Palabra *palabras);
int sumaPolaridad(struct Palabra *palabras, int cantidad, struct NodoPalabra *lista);

//INSERCION
void insertaPalabra(struct Palabra palabra, struct NodoPalabra *&lista);
void insertaOrdenadoPlato(struct Plato plato, struct NodoPlato *&lista);
void insertaAtencion(struct Atencion atencion, struct NodoAtencion *&lista);

//BUSQUEDA
struct NodoPlato *buscaPlato(struct NodoPlato *lista, const char *codigo);
struct NodoAtencion *buscaAtencion(struct NodoAtencion *lista, int codigo);
struct NodoPalabra *buscaPalabra(struct NodoPalabra *lista, const char *pal);

//ORDENAMIENTO
void ordenaAtenciones(struct NodoAtencion *lista);
void cambiaAtencion(struct Atencion &d1, struct Atencion &d2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void verificaLexicon(const char *nombreArchivo, struct NodoPalabra *lista);
void verificaPlatos(const char *nombreArchivo, struct NodoPlato *lista);
void emiteReporte(const char *nombreArchivo, struct NodoAtencion *lista);

#endif /* FUNCIONES_H */

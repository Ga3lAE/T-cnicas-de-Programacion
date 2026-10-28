/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 21 de junio de 2025, 11:47 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);  
void leeFecha(ifstream &archivo, struct Fecha &fecha);
char *cadenaAMayusculas(char *cad);
void leeEmpresas(const char *nombreArchivo, struct NodoEmpresa *&lista);
void leeInfracciones(const char *nombreArchivo, struct NodoInfraccion *&lista);
void leePlacas(const char *nombreArchivo, struct NodoEmpresa *lista);
void leeInfraccionesCometidas(const char *nombreArchivo, 
        struct NodoEmpresa *listaEmpresas, 
        struct NodoInfraccion *listaInfracciones); 

//AGREGA
void agregaEmpresa(struct Empresa aux, struct NodoEmpresa *&lista);
void agregaInfraccion(struct Infraccion aux, struct NodoInfraccion *&lista);

//BUSQUEDA
struct NodoEmpresa *buscaEmpresa(struct NodoEmpresa *lista, int dni);
struct NodoEmpresa *buscaPlaca(struct NodoEmpresa *lista, const char *placa);
struct NodoInfraccion *buscaInfraccion(struct NodoInfraccion *lista, const char *codigo);

//ORDENA
void ordenaInfracciones(struct NodoInfraccion *lista);
void ordenaEmpresas(struct NodoEmpresa *lista);

#endif /* FUNCIONES_H */

/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 23 de junio de 2025, 11:46 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void operator << (ofstream &archivo, struct Cliente cliente);

//LECTUAR
char *leeCadenaExacta(ifstream &archivo, char del);
void leePlatos(const char *nombreArchivo, struct NodoPlato *&lista);
void leeClientes(const char *nombreArchivo, struct NodoCliente *&lista);
void leePedidos(const char *nombreArchivo, 
        struct NodoCliente *listaClientes,
        struct NodoPlato *listaPlatos,
        double descuento, const char *categoriaDescuento);
//INSERCION
void insertaPlatoLista(struct Plato plato, struct NodoPlato *&lista);
void insertaClienteLista(struct Cliente plato, struct NodoCliente *&lista);

//BUSQUEDA
struct NodoPlato *buscaPlato(struct NodoPlato *lista, const char *cod);
struct NodoCliente *buscaCliente(struct NodoCliente *lista, int dni);

//IMPRESION
void emiteReporte(const char *nombreArchivo, 
        struct NodoCliente *listaClientes,
        struct NodoPlato *listaPlatos, 
        double descuento, const char *categoriaDescuento);

#endif /* FUNCIONES_H */

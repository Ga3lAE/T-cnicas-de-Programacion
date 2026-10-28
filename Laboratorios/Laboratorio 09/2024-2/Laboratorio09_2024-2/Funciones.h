/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 15 de junio de 2025, 02:21 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
void leePlatos(const char *nombreArchivo, struct Plato *arr, int &cantidad);
void leeDistritos(const char *nombreArchivo, struct Distrito *arr, int &cantidad);
void leeClientes(const char *nombreArchivo, struct Cliente *arr, int &cantidad);


void leePedidos(const char *nombreArchivo,
            struct Plato *arrPlatos, int cantidadPlatos,
            struct Distrito *arrDistritos, int cantidadDistritos, 
            struct Cliente *arrClientes, int cantidadClientes);

//BUSQUEDA
int buscaPlato(struct Plato *arr, int cantidad, const char *codigo);
int buscaCliente(struct Cliente *arr, int cantidad, int dni);
int buscaPedido(struct PlatoPedido *arr, int cantidad, 
        int codigo, const char *codigoPedido);
int buscaDistrito(struct Distrito *arr, int cantidad, const char *codigo);

//AGREGAR
int agregapedido(struct PlatoPedido *pedidos, int &cantidad, 
        int codigo, struct Plato plato);
char *copiaCadChar(const char *cad);

//ORDENAMIENTO
void ordenaClientes(struct Cliente *arrClientes, int cantidad);
void cambiaCliente(struct Cliente &cliente1, struct Cliente &cliente2);
void cambiaPedido(struct PlatoPedido &plato1, struct PlatoPedido &plato2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emiteReporte(const char *nombreArchivo, struct Cliente *arr, int cantidad);
void imprimeEncabezadoClientes(ofstream &archivo);
void imprimeEncabezadoPedidos(ofstream &archivo);

#endif /* FUNCIONES_H */

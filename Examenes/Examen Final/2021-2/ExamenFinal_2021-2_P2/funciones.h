/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 11:20 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <complex>


void imprimeLinea(char c, ofstream& archivo);

char* leeCadena(ifstream& archivo, char del);

void leeStock(const char* nombreArchivo, 
        struct StockProducto* productos, int& cantidad);
void confirmaStock(const char* nombreArchivo, 
        struct StockProducto* productos, int cantidad);

void leePedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int& cantidad);
void confirmaPedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidad);

void completaPedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos, 
        struct StockProducto* productos, int cantidadProductos);
int buscaPedido(int numero, struct Pedido* pedidos, int cantidad);
int buscaProducto(char* codigo, struct StockProducto* productos, int cantidad);
void procesaPedido(struct Pedido& pedido, struct StockProducto& producto, int cantidad);

void emiteReporte(const char* nombreArchivo, struct Pedido* pedidos, int cantidad);
void imprimePedido(ofstream& archivo, const struct Pedido& pedido);
void imprimeEntregas(ofstream& archivo, const struct Entregado& entrega);
void imprimeNoEntregas(ofstream& archivo, const struct NoEntregado& entrega);

#endif /* FUNCIONES_H */


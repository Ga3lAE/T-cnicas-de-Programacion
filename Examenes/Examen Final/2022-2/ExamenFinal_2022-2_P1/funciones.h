/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 12:29 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);
char* leeCadena(ifstream& archivo, char del);

void cargarDirecciones(const char* nombreArchivo, struct Direccion* direcciones,
        int& cantidad);

void cargarPedidos(const char* nombreArchivo, Pedido* pedidos, int& cantidad);
int buscaPedido(int codigo, Pedido* pedidos, int cantidad);

void completaPedidos(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos, 
        struct Direccion* direcciones, int cantidadDirecciones);
int buscaUsuario(char* codigo, Direccion* direcciones, int cantidad);

void emiteReporte(const char* nombreArchivo, 
        struct Pedido* pedidos, int cantidadPedidos);

void imprimeTitulo(ofstream& archivo);
void imprimePedidos(ofstream& archivo, struct Pedido pedido);
void imprimeProductos(ofstream& archivo, ProductoPedido* productos, int cantidad);

#endif /* FUNCIONES_H */


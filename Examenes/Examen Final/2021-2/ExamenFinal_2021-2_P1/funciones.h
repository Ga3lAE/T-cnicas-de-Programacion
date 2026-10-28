/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 30 de noviembre de 2024, 06:27 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(char c, ofstream& archivo);

void leeStock(const char* nombreArchivoDatos, const char* nombreArchivoBin);
void confirmaStock(const char* nombreArchivoReporte, const char* nombreArchivoBin);

void leePedidos(const char* nombreArchivoDatos, const char* nombreArchivoBin);
void confirmaPedidos(const char* nombreArchivoReporte, const char* nombreArchivoBin);

void completaPedidos(const char* nombreArchivoDatos, 
        const char* nombreArchivoPedidos, const char* nombreArchivoStock);
int buscaPedido(int codigo, fstream& archivo, int cantidad, int tamElemento);
int buscaProducto(char* codigo, fstream& archivo, int cantidad, int tamElemento);
void procesaPedido(struct PedidoPorInternet& pedido, 
        struct StockDeProductos& producto, int cantidadPedida);

void emiteReporte(const char* nombreArchivoReporte, 
        const char* nombreArchivoPedidos);

void imprimePedido(ofstream& archivo, const struct PedidoPorInternet& pedido);
void imprimeFechaHora(int dato, char tipo, ofstream& archivo);
void imprimeProducto(ofstream& archivo, const struct ProductoSolicitado producto);

#endif /* FUNCIONES_H */


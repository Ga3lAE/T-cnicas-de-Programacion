

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 23 de junio de 2023, 01:14 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearStocksProdBin(const char *nombArchCsv,const char *nombArchBin);
void mostrarStocksProdBin(const char *nombArchBin,const char *nombArchTxt);
void crearPedidosBin(const char* nombArchTxt, const char* nombArchBin);
void mostrarPedidosBin(const char* nombArchBin, const char* nombArchTxt);
void actualizarPedidos(const char* nomArchStockBin, const char* nomArchPedidosBin,
        const char *nombArchTxt);
void modificarArchivos(struct StockProd &producto, int tamRegProd,int tamArchProd,
        int numRegProd,struct Pedido &pedido,int tamRegPedido,int tamArchPedido,
        int numRegPed,fstream &archStock, fstream &archPedidos, ifstream &archDetalles);
void asignarDatos(struct StockProd &producto,struct Pedido &pedido,
        int cantidadSolicitada,int posProducto,int posPedido,int tamRegProd,
        int tamRegPedido,fstream &archStock,fstream &archPedidos);
void emiteReporte(const char* nombArchBin, const char* nombArchTxt);
void imprimLinea(char caracter, int cantidad, ofstream& archRep);
int buscarPedido(fstream &archPedidos,int numPedido, int numReg);
int buscarProducto(fstream &archStock,char *codProd,int numReg);
void datosArchivo(fstream &archBin, int tamReg,int &tamArch, int &numReg);
#endif /* FUNCIONES_H */


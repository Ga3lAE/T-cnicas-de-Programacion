

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 15 de junio de 2023, 12:38 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerStockProductos(struct StockProd *productos,int &numProductos);
void emiteProductos(struct StockProd *productos,int numProductos);
void leerPedidos(stPedidos* pedidos, int& numPedidos);
void emitePedidos(struct stPedidos *pedidos,int numPedidos);
void leerDetallesPedidos(StockProd* productos, int numProductos, stPedidos* pedidos, int numPedidos);
void asignarProductosEntregados(struct stPedidos &pedidos,struct StockProd &productos,
        int cantidad_solicitada);
void asignarProductosNoEntregados(struct stPedidos &pedidos,struct StockProd &productos,
        int cantidad);
void emitirReporte(StockProd* productos, int numProductos, stPedidos* pedidos, int numPedidos);
void imprimeProductosNoEntregados(struct stPedidos &pedidos,ofstream &archReporte);
void imprimeProductosEntregados(struct stPedidos &pedidos,ofstream &archReporte);
void separaFecha(int &dia,int &mes,int &anio,int fecha);
void separaHora(int& hora, int& min, int& seg, int horaAux);
void imprimeLinea(char caracter, int cantidad, ofstream &archRep);
int buscarPedido(struct stPedidos *pedidos,int codPedido_evaluar,int numPedidos);
int buscarProducto(struct StockProd *productos,char *codProducto,int numDatos);
char *leerCadenaExacta(ifstream& arch);

#endif /* FUNCIONES_H */


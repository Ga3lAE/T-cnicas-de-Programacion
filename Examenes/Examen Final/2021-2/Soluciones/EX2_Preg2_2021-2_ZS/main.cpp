

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 15 de junio de 2023, 12:38 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAX_PROD 40

#include "NoEntregado.h"
#include "Entregado.h"
#include "stPedidos.h"
#include "StockProd.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct StockProd *productos;
    struct stPedidos *pedidos;
    productos = new struct StockProd[MAX_PROD];
    pedidos = new struct stPedidos[50];
    
    int numProductos,numPedidos;
    leerStockProductos(productos,numProductos);
    emiteProductos(productos,numProductos);
    leerPedidos(pedidos,numPedidos);
    emitePedidos(pedidos,numPedidos);
    leerDetallesPedidos(productos,numProductos,pedidos,numPedidos);
    emitirReporte(productos,numProductos,pedidos,numPedidos);
    return 0;
}


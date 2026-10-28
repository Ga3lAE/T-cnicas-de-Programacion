

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 23 de junio de 2023, 01:12 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    
    crearStocksProdBin("StockDeProductos.csv","StockDeProductos.bin");
    mostrarStocksProdBin("StockDeProductos.bin","reporteStocks.txt");
    crearPedidosBin("Pedidos.txt","PedidosPorInternet.bin");
    mostrarPedidosBin("PedidosPorInternet.bin","reportePedidos.txt");
    actualizarPedidos("StockDeProductos.bin","PedidosPorInternet.bin",
            "DetalleDeLosPedidos.txt");
    emiteReporte("PedidosPorInternet.bin","ReporteDePedidos.txt");
    return 0;
}


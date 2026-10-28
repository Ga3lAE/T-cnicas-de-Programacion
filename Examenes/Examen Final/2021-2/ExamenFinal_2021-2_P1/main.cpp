/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 30 de noviembre de 2024, 06:24 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "StockDeProductos.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {

    leeStock("StockDeProductos.csv", "StockDeProductos.bin");
    confirmaStock("ConfirmaStockDeProductos.txt", "StockDeProductos.bin");
    
    leePedidos("Pedidos.txt", "PedidosPorInternet.bin");
    confirmaPedidos("ConfirmaPedidos.txt", "PedidosPorInternet.bin");
    
    completaPedidos("DetalleDeLosPedidos.txt", 
            "PedidosPorInternet.bin", 
            "StockDeProductos.bin");
    
    emiteReporte("ReporteDePedido.txt", "PedidosPorInternet.bin");
    
    return 0;
}


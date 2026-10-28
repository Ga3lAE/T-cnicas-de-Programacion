/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 1 de diciembre de 2024, 11:18 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "StockProducto.h"
#include "Pedido.h"
#include "Entregado.h"
#include "NoEntregado.h"
#include "funciones.h"


#define MAX_PRODUCTOS 30
#define MAX_PEDIDOS 40

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct StockProducto* productos;
    int cantidadProductos=0;
    productos = new struct StockProducto [MAX_PRODUCTOS]{};
    
    leeStock("StockDeProductos.csv", productos, cantidadProductos);
    confirmaStock("ConfirmacionStock.txt", productos, cantidadProductos);
    
    struct Pedido* pedidos;
    int cantidadPedidos=0;
    pedidos = new struct Pedido [MAX_PEDIDOS]{};
    leePedidos("Pedidos.txt", pedidos, cantidadPedidos);
    confirmaPedidos("ConfirmaPedidos.txt", pedidos, cantidadPedidos);
    
    completaPedidos("DetalleDeLosPedidos.txt", 
            pedidos, cantidadPedidos, 
            productos, cantidadProductos);
    
    emiteReporte("ReporteDePedidos.txt", pedidos, cantidadPedidos);
    
    confirmaPedidos("PedidosFinal.txt", pedidos, cantidadPedidos);
    confirmaStock("StockFinal.txt", productos, cantidadProductos);

    return 0;
}
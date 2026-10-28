/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 12:23 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include"Direccion.h"
#include"Pedido.h"
#include"ProductoPedido.h"
#include"funciones.h"

#define MAX_DIRECCIONES 50
#define MAX_PEDIDOS 100

/*
 * 
 */
int main(int argc, char** argv) {

    struct Direccion* direcciones;
    int cantidadDirecciones=0;
    direcciones = new struct Direccion [MAX_DIRECCIONES]{};
    
    cargarDirecciones("direcciones.csv", direcciones, 
            cantidadDirecciones);
    
    struct Pedido* pedidos;
    int cantidadPedidos=0;
    pedidos = new struct Pedido [MAX_PEDIDOS]{};
    
    cargarPedidos("pedidos.csv", pedidos, cantidadPedidos);
    
    completaPedidos("rappi.csv", pedidos, cantidadPedidos, 
            direcciones, cantidadDirecciones);
    
    emiteReporte("ReportePedidos.txt", pedidos, cantidadPedidos);
    
    return 0;
}


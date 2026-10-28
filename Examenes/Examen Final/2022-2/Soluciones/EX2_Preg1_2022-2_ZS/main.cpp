

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 30 de junio de 2023, 09:05 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "StructPedido.h"
#include "StructDireccion.h"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Direccion direcciones[50];
    int numDirecciones;
    
    struct Pedido pedidos[100]{};
    int numPedidos;
    
    leerDirecciones(direcciones,numDirecciones);
    leerPedidos(pedidos,numPedidos);
    completarPedidos(direcciones,numDirecciones,pedidos,numPedidos);
    emiteReporte(direcciones,numDirecciones,pedidos,numPedidos);
    return 0;
}


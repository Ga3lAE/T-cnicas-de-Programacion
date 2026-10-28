/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 26 de noviembre de 2024, 05:34 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Direccion.h"
#include "Pedido.h"
#include "ProductoPedido.h"
#include "funciones.h"


/*
 * 
 */
int main(int argc, char** argv) {

    cargarDirecciones("direcciones.csv", "Direcciones.bin");
    
    cargarPedidos("pedidos.csv", "Pedidos.bin");
    
    completaPedidos("Pedidos.bin", "Direcciones.bin", "rappi.csv");
    
    return 0;
}


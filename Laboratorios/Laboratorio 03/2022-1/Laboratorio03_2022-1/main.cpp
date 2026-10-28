/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 12 de mayo de 2025, 11:10 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_CLIENTES 30
#define MAX_CANT_PEDIDOS 100




/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadClientes = 0;
    int dnisClientes[MAX_CANT_CLIENTES]{},
            telefonosClientes[MAX_CANT_CLIENTES]{};
    
    leeClientes("Clientes.txt", cantidadClientes, 
            dnisClientes, telefonosClientes);
    
    ordenaClientes(cantidadClientes, 
            dnisClientes, telefonosClientes);
    
    int cantidadProductos=0;
    int codigosProductos[MAX_CANT_PEDIDOS]{};
    double preciosProductos[MAX_CANT_PEDIDOS]{}, 
            cantidadesProductos[MAX_CANT_PEDIDOS]{},
            totalesProductos[MAX_CANT_PEDIDOS]{};
    
    double gastosClientes[MAX_CANT_CLIENTES]{};
    
    leePedidos("Pedidos.txt", cantidadProductos, 
            codigosProductos, preciosProductos, 
            cantidadesProductos, totalesProductos,
            cantidadClientes, dnisClientes, gastosClientes);
    
    imprimeReporte("Reporte.txt", 
            cantidadClientes, 
            dnisClientes, telefonosClientes, gastosClientes, 
            cantidadProductos, 
            codigosProductos, preciosProductos, cantidadesProductos, totalesProductos);
    

    return 0;
}


/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 15 de junio de 2025, 02:20 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Cliente.h"
#include "Distrito.h"
#include "Plato.h"
#include "PlatoPedido.h"

#define MAX_CANT_CLIENTES 125
#define MAX_CANT_DISTRITOS 50
#define MAX_CANT_PLATOS 125

/*
 * 
 */

int main(int argc, char** argv) {

    //DISTRITOS
    int cantidadDistritos=0;
    struct Distrito arrDistritos[MAX_CANT_DISTRITOS]{};
    //PLATOS
    int cantidadPlatos=0;
    struct Plato arrPlatos[MAX_CANT_PLATOS]{};
    //CLIENTES
    int cantidadClientes=0;
    struct Cliente arrClientes[MAX_CANT_CLIENTES]{};
        
    leePlatos("PlatosOfrecidos.csv", arrPlatos, cantidadPlatos);
    leeDistritos("Distritos.csv", arrDistritos, cantidadDistritos);
    leeClientes("Clientes.csv", arrClientes, cantidadClientes);
    
    leePedidos("PedidosRealizados.txt", 
            arrPlatos, cantidadPlatos,
            arrDistritos, cantidadDistritos, 
            arrClientes, cantidadClientes);
    
    
    ordenaClientes(arrClientes, cantidadClientes);    
    
    emiteReporte("Reporte.txt", arrClientes, cantidadClientes);
    
    return 0;
}


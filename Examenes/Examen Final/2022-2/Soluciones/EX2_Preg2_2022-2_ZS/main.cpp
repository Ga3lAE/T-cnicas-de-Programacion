/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: aml
 *
 * Created on 26 de junio de 2023, 06:25 PM
 */

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    crearArchDireccionesBin("direcciones.csv","direcciones.bin");
    crearArchPedidosBin("pedidos.csv","pedidos.bin");
    actualizarPedidosBin("pedidos.bin","direcciones.bin","rappi.csv");
    ordenarArchivos("pedidos.bin");
    imprimeReporte("pedidos.bin","Reporte_tp_rappi.txt");

    
    return 0;
}


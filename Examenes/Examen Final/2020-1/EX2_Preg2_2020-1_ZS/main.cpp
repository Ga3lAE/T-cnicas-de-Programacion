

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 12:41 AM
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
    
    crearClientesBin("Clientes.bin","Clientes.csv");
    modificarClientesBin("Clientes.bin","Transacciones.csv");
    emiteReportes("Clientes.bin","EstadoDeCuentasHabiles.txt",
            "EstadoDeCuentasNoHabiles.txt");
    return 0;
}


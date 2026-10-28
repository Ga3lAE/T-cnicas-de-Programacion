/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 23 de junio de 2025, 11:45 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "Cliente.h"
#include "Plato.h"
#include "NodoPlato.h"
#include "NodoCliente.h"

/*
 * 
 */

int main(int argc, char** argv) {

    double descuento;
    char categoriaDescuento[50]{};
    cout<<"Ingrese el descuento para los pedidos: "<<endl;
//    cin>>descuento;
    descuento = 50;
    cout<<"Ingrese la categoria para los descuento: "<<endl;
//    cin>>categoriaDescuento;
    strcpy(categoriaDescuento, "ADICIONAL");
    
    struct NodoPlato *listaPlatos = NULL;
    leePlatos("PlatosOfrecidos.csv", listaPlatos);
    
    struct NodoCliente *listaClientes = NULL;
    leeClientes("Clientes.csv", listaClientes);           
    
    leePedidos("PedidosRealizados.txt", listaClientes, listaPlatos, 
            descuento, categoriaDescuento);
    
    emiteReporte("Reporte.txt", listaClientes, listaPlatos, 
            descuento, categoriaDescuento);        
    
    return 0;
}


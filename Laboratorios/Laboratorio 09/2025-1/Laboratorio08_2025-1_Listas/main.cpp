/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 21 de junio de 2025, 11:46 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"
#include "NodoEmpresa.h"
#include "NodoInfraccion.h"


/*
 * 
 */

int main(int argc, char** argv) {

    struct NodoEmpresa *listaEmpresas = NULL;
    leeEmpresas("EmpresasRegistradas.csv", listaEmpresas);
    
    struct NodoInfraccion *listaInfracciones = NULL;
    leeInfracciones("TablaDeInfracciones.csv", listaInfracciones);
    
    leePlacas("PlacasRegistradas.txt", listaEmpresas);        
    
    leeInfraccionesCometidas("InfraccionesCometidas.csv", listaEmpresas, listaInfracciones);
    
    ordenaInfracciones(listaInfracciones);
    ordenaEmpresas(listaEmpresas);
    
    ofstream arch("wewe.txt", ios::out);
    struct NodoEmpresa *ptr;
    ptr = listaEmpresas;
    while(ptr){
        arch<<left
                <<setw(10)<<ptr->empresa.dni
                <<setw(50)<<ptr->empresa.nombre
                <<setw(30)<<ptr->empresa.distrito;
        for (int i = 0; i <ptr->empresa.cantidadPlacas ; i++) {            
            arch<<ptr->empresa.placas[i]<<'/';
        }
        arch<<setw(50-(ptr->empresa.cantidadPlacas)*9)<<" "             
                <<setw(12)<<ptr->empresa.fechaInfraccion.fecha
                <<setw(12)<<ptr->empresa.fechaPago.fecha
                <<setw(10)<<ptr->empresa.totalPagado
                <<setw(10)<<ptr->empresa.totalAdeudado
                <<setw(10)<<ptr->empresa.totalMultas
                <<setw(10)<<ptr->empresa.cantidadFaltas
                <<endl;
        ptr = ptr->siguiente;        
    }
    
    return 0;
}


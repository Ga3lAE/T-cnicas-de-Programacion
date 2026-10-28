/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 31 de mayo de 2025, 09:55 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_PRODUCTOS 300

/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadProductos=0;
    int arrCodigoProductos[MAX_CANT_PRODUCTOS]{},
            arrAlmacenProsducto[MAX_CANT_PRODUCTOS]{}, 
            arrStockProductos[MAX_CANT_PRODUCTOS]{};
    leeStock("StrockProductos.txt", cantidadProductos, 
            arrCodigoProductos, arrAlmacenProsducto, arrStockProductos);
    verificaStock("VerificaStrockProductos.txt", cantidadProductos, 
            arrCodigoProductos, arrAlmacenProsducto, arrStockProductos);
    
    int fecha1, fecha2;
    cout<<"INGRESE 2 FECHAS (dd/mm/aa):"<<endl;
    leeFecha(fecha1);
    leeFecha(fecha2);
    
//    leeTransacciones("Transacciones.txt");
    
    
    return 0;
}


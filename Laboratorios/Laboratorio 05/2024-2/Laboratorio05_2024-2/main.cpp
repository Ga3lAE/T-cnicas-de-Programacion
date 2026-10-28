/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 10 de mayo de 2025, 11:37 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_REPARTIDORES 50
#define MAX_CANT_PLATOS 150

/*
 * 
 */
int main(int argc, char** argv) {
    
    //definimos los arreglos de repartidores
    int dnisRepartidores[MAX_CANT_REPARTIDORES]{}, 
            codigosDistritosRepartidores[MAX_CANT_REPARTIDORES]{}, 
            totalesPlatosRepartidores[MAX_CANT_REPARTIDORES]{};
    double montosTotalesPlatosRepartidores[MAX_CANT_REPARTIDORES]{}, 
            descuentosPlatosRepartidores[MAX_CANT_REPARTIDORES]{},
            descuentosClientesRepartidores[MAX_CANT_REPARTIDORES]{}, 
            pagosRepartidoresRepartidores[MAX_CANT_REPARTIDORES]{}, 
            totalesIngresadosRepartidores[MAX_CANT_REPARTIDORES]{};
    char vehiculosRepartidores[MAX_CANT_REPARTIDORES]{};
    int cantidadRepartidores=0;
    //definimos las estadisticas de los repartidores
    int sumaTotalesPlatosRepartidores = 0;
    double sumaMontosTotalesPlatosRepartidores=0,
            sumaDescuentosPlatosRepartidores=0,
            sumaDescuentosClientesRepartidores=0,
            sumaPagosRepartidoresRepartidores=0,
            sumaTotalesIngresadosRepartidores=0;
    
    
    //definimos los arreglos de platos
    int codigosPlatos[MAX_CANT_PLATOS]{}, 
            cantidadesPlatos[MAX_CANT_PLATOS]{};
    double preciosPlatos[MAX_CANT_PLATOS]{}, 
            descuentosPlatos[MAX_CANT_PLATOS]{}, 
            montosVendidosPlatos[MAX_CANT_PLATOS]{},
            descuentosPlatosPlatos[MAX_CANT_PLATOS]{}, 
            descuentosClientesPlatos[MAX_CANT_PLATOS]{}, 
            totalesIngresadosPlatos[MAX_CANT_PLATOS]{};
    int cantidadPlatos=0;
    //definimos las estadisticas de platos
    int sumaCantidadesPlatos=0;
    double sumaMontosVendidosPlatos=0,
            sumaDescuentosPlatosPlatos=0, 
            sumaDescuentosClientesPlatos=0, 
            sumaTotalesIngresadosPlatos=0;
    //hacemos las lecturas y verificaiones correspondientes
    leeRepartidores("Repartidores.txt", cantidadRepartidores, 
            dnisRepartidores, vehiculosRepartidores, codigosDistritosRepartidores);    
    leePlatos("PlatosOfrecidos.txt", cantidadPlatos, 
            codigosPlatos, preciosPlatos, descuentosPlatos);    
    verificaLecturas("VerificaRepartidores.txt", cantidadRepartidores, 
            dnisRepartidores, vehiculosRepartidores, codigosDistritosRepartidores, 
            cantidadPlatos, 
            codigosPlatos, preciosPlatos, descuentosPlatos);
    
    //asignamos lo correspondiente
    asignaRepartos("RepartosARealizar.txt",
            //los repartidores (arreglos y estadisticas finales)
            cantidadRepartidores,  
            codigosDistritosRepartidores, totalesPlatosRepartidores, 
            vehiculosRepartidores, 
            montosTotalesPlatosRepartidores, descuentosPlatosRepartidores, 
            descuentosClientesRepartidores, pagosRepartidoresRepartidores, 
            totalesIngresadosRepartidores, 
            sumaTotalesPlatosRepartidores, 
            sumaMontosTotalesPlatosRepartidores, sumaDescuentosPlatosRepartidores, 
            sumaDescuentosClientesRepartidores, sumaPagosRepartidoresRepartidores, 
            sumaTotalesIngresadosRepartidores, 
            //los platos (arreglos y estadisticas finales)
            cantidadPlatos, 
            codigosPlatos, cantidadesPlatos, 
            preciosPlatos, descuentosPlatos, 
            montosVendidosPlatos, descuentosPlatosPlatos, 
            descuentosClientesPlatos, totalesIngresadosPlatos, 
            sumaCantidadesPlatos, 
            sumaMontosVendidosPlatos, sumaDescuentosPlatosPlatos, 
            sumaDescuentosClientesPlatos, sumaTotalesIngresadosPlatos);

    imprimeReporteRepartidores("TotalPorRepartidor.txt", "NombresRepartidores.txt", 
            cantidadRepartidores, 
            dnisRepartidores, vehiculosRepartidores, codigosDistritosRepartidores, 
            totalesPlatosRepartidores, montosTotalesPlatosRepartidores, 
            descuentosPlatosRepartidores, descuentosClientesRepartidores, 
            pagosRepartidoresRepartidores, totalesIngresadosRepartidores, 
            sumaTotalesPlatosRepartidores, sumaMontosTotalesPlatosRepartidores, 
            sumaDescuentosPlatosRepartidores, sumaDescuentosClientesRepartidores, 
            sumaPagosRepartidoresRepartidores, sumaTotalesIngresadosRepartidores);
    
    imprimeReportePlatos("TotalPorPlatos.txt", "NombresPlatos.txt", 
            cantidadPlatos, 
            codigosPlatos, preciosPlatos, descuentosPlatos, 
            cantidadesPlatos, montosVendidosPlatos, 
            descuentosPlatosPlatos, 
            descuentosClientesPlatos, 
            totalesIngresadosPlatos, 
            sumaCantidadesPlatos, sumaMontosVendidosPlatos, 
            sumaDescuentosPlatosPlatos, 
            sumaDescuentosClientesPlatos, 
            sumaTotalesIngresadosPlatos);
                        
    return 0;
}
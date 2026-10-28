/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 4 de junio de 2025, 12:23 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_PLATOS 120
#define MAX_CANT_REPARTIDORES 70

/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadPlatos=0;
    int arrCodigoPlato[MAX_CANT_PLATOS]{}, 
            arrCantidadPlato[MAX_CANT_PLATOS]{};
    double arrPrecioPlato[MAX_CANT_PLATOS]{},
            arrDescuentoPlato[MAX_CANT_PLATOS]{}, 
            arrMontoVendidoPlato[MAX_CANT_PLATOS]{}, 
            arrDescuentoAlPlato[MAX_CANT_PLATOS]{}, 
            arrDescuentoAlCliente[MAX_CANT_PLATOS]{}, 
            arrTotalIngresadoPlato[MAX_CANT_PLATOS]{};
    char *arrNombrePlato[MAX_CANT_PLATOS]{}, 
            *arrCategoriaPlato[MAX_CANT_PLATOS]{};
    
    int cantidadRepartidores=0;
    int arrDniRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrCodigoDistritoRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrTotalPlatosRepartidor[MAX_CANT_REPARTIDORES]{};
    char *arrNombreRepartidor[MAX_CANT_REPARTIDORES]{},
            *arrVehiculoRepartidor[MAX_CANT_REPARTIDORES]{},
            *arrNombreDistritoRepartidor[MAX_CANT_REPARTIDORES]{};
    double arrMontoTotalPlatosRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrDescuentoPlatosRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrDescuentoClienteRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrPagoRepartidor[MAX_CANT_REPARTIDORES]{}, 
            arrTotalIngresadoRepartidor[MAX_CANT_REPARTIDORES]{};
    
    leeRepartidores("Repartidores.txt", cantidadRepartidores, 
            arrDniRepartidor, arrNombreRepartidor, arrVehiculoRepartidor, 
            arrCodigoDistritoRepartidor, arrNombreDistritoRepartidor);
    
    
    leePlatos("PlatosOfrecidos.txt", cantidadPlatos, 
            arrCodigoPlato, arrNombrePlato, arrCategoriaPlato, 
            arrPrecioPlato, arrDescuentoPlato);
    
    verificaLectura("ReporteDePrueba.txt", 
            cantidadRepartidores, 
            arrDniRepartidor, arrNombreRepartidor, arrVehiculoRepartidor, 
            arrCodigoDistritoRepartidor, arrNombreDistritoRepartidor,
            cantidadPlatos, 
            arrCodigoPlato, arrNombrePlato, arrCategoriaPlato, 
            arrPrecioPlato, arrDescuentoPlato);
    
    ordenaRepartidores(cantidadRepartidores, arrNombreRepartidor, 
            arrDniRepartidor, arrVehiculoRepartidor, 
            arrCodigoDistritoRepartidor, arrNombreDistritoRepartidor);                    
    
    verificaLectura("ReporteOrdenadoDePrueba.txt", 
            cantidadRepartidores, 
            arrDniRepartidor, arrNombreRepartidor, arrVehiculoRepartidor, 
            arrCodigoDistritoRepartidor, arrNombreDistritoRepartidor,
            cantidadPlatos, 
            arrCodigoPlato, arrNombrePlato, arrCategoriaPlato, 
            arrPrecioPlato, arrDescuentoPlato);
    
    leeRepartos("RepartosARealizar.txt", 
            cantidadRepartidores, 
            arrVehiculoRepartidor, arrCodigoDistritoRepartidor,
            arrTotalPlatosRepartidor, arrMontoTotalPlatosRepartidor, 
            arrDescuentoPlatosRepartidor, arrDescuentoClienteRepartidor, 
            arrPagoRepartidor, arrTotalIngresadoRepartidor, 
            cantidadPlatos, 
            arrCodigoPlato, arrPrecioPlato, arrDescuentoPlato, 
            arrCantidadPlato, arrMontoVendidoPlato, arrDescuentoAlPlato, 
            arrDescuentoAlCliente, arrTotalIngresadoPlato);  
    
    ordenaPlatos(cantidadPlatos, 
            arrCodigoPlato, arrNombrePlato, arrCategoriaPlato, 
            arrPrecioPlato, arrDescuentoPlato, 
            arrCantidadPlato, arrMontoVendidoPlato, arrDescuentoAlPlato, 
            arrDescuentoAlCliente, arrTotalIngresadoPlato);
    
    emiteReportePlatos("EntregasPorPlato.txt", cantidadPlatos, 
            arrCodigoPlato, arrNombrePlato, arrCategoriaPlato, 
            arrPrecioPlato, arrDescuentoPlato, 
            arrCantidadPlato, arrMontoVendidoPlato, arrDescuentoAlPlato, 
            arrDescuentoAlCliente, arrTotalIngresadoPlato);
    emiteReporteRepartidores("EntregasPorRepartidor.txt", cantidadRepartidores,             
            arrDniRepartidor, arrNombreRepartidor, arrVehiculoRepartidor, 
            arrNombreDistritoRepartidor, arrTotalPlatosRepartidor, 
            arrMontoTotalPlatosRepartidor, arrDescuentoPlatosRepartidor, 
            arrDescuentoClienteRepartidor, arrPagoRepartidor, 
            arrTotalIngresadoRepartidor);
    
    return 0;
}


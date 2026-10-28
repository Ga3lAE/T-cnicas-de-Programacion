/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 14 de junio de 2025, 10:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_PLATOS 125
#define MAX_CANT_DISTRITOS 50
#define MAX_CANT_CLIENTES 125
#define MAX_CANT_REPARTIDORES 75
#define MAX_CANT_PEDIDOS 300

/*
 * 
 */

int main(int argc, char** argv) {
    
    //PLATOS
    int cantidadPlatos=0;
    char *arrCodigoPlatos[MAX_CANT_PLATOS]{}, 
            *arrDescripcionPlatos[MAX_CANT_PLATOS]{}, 
            *arrCategoriaPlato[MAX_CANT_PLATOS]{};
    double arrPrecioPlato[MAX_CANT_PLATOS]{}, 
            arrDescuentoPlatos[MAX_CANT_PLATOS]{};
    
    //DISTRITOS
    int cantidadDistritos=0;
    char *arrCodigoDistritos[MAX_CANT_DISTRITOS]{}, 
            *arrNombreDistritos[MAX_CANT_DISTRITOS]{},
            *arrUbicacionDistritos[MAX_CANT_DISTRITOS]{};
    
    //CLIENTES
    int cantidadClientes=0;
    int arrDniClientes[MAX_CANT_CLIENTES]{};
    char *arrNombreClientes[MAX_CANT_CLIENTES]{}, 
            *arrDistritoClientes[MAX_CANT_CLIENTES]{}, 
            *arrVehiculoClientes[MAX_CANT_CLIENTES]{};
    double arrDescuentoClientes[MAX_CANT_CLIENTES]{};
    
    //REPARTIDORES
    int cantidadRepartidores=0;
    int arrCodigoRepartidores[MAX_CANT_REPARTIDORES]{};
    char *arrNombreRepartidores[MAX_CANT_REPARTIDORES]{}, 
            *arrVehiculoRepartidores[MAX_CANT_REPARTIDORES]{}, 
            *arrDistritorepartidores[MAX_CANT_REPARTIDORES]{};
    
    //REPORTE
    int arrCantidadPlatos[MAX_CANT_PLATOS]{};
    double arrMontoVendidoPlatos[MAX_CANT_PLATOS]{}, 
            arrDescuentoPlatoPlatos[MAX_CANT_PLATOS]{}, 
            arrDescuentoClientePlatos[MAX_CANT_PLATOS]{}, 
            arrTotalIngresadoPlatos[MAX_CANT_PLATOS]{};
    
    int cantidadPedidos = 0;
    int arrCodigoPedidos[MAX_CANT_PEDIDOS]{};
    double arrIngresoBrutoPedidos[MAX_CANT_PEDIDOS]{},
            arrIngresoDescuentoPedidos[MAX_CANT_PEDIDOS]{}, 
            arrIngresoNetoPedidos[MAX_CANT_PEDIDOS]{};
    int arrClienteDniPedidos[MAX_CANT_PEDIDOS]{},
            arrRepartidorDniPedidos[MAX_CANT_PEDIDOS]{};
    char *arrClienteNombrePedidos[MAX_CANT_PEDIDOS]{},
            *arrClienteDistritoPedidos[MAX_CANT_PEDIDOS]{}, 
            *arrRepartidorNombrePedidos[MAX_CANT_PEDIDOS]{},
            *arrRepartidorVehiculoPedidos[MAX_CANT_PEDIDOS]{};
    double arrPagoRepartidorPedidos[MAX_CANT_PEDIDOS]{};
    
    
    leePlatos("PlatosOfrecidos.csv", cantidadPlatos, 
            arrCodigoPlatos, arrDescripcionPlatos,
            arrPrecioPlato, arrCategoriaPlato, 
            arrDescuentoPlatos);
    
    leeDistritos("DistritosDeLima.csv", cantidadDistritos, 
            arrCodigoDistritos, arrNombreDistritos, arrUbicacionDistritos);
    
    leeClientes("Clientes.csv", cantidadClientes, 
            arrDniClientes, arrNombreClientes, 
            arrDistritoClientes, arrVehiculoClientes, 
            arrDescuentoClientes);
    
    leeRepartidores("Repartidores.csv", cantidadRepartidores, 
            arrCodigoRepartidores, arrNombreRepartidores, 
            arrVehiculoRepartidores, arrDistritorepartidores);    
    
    leePedidos("PedidosPorAtender.txt", cantidadPedidos,
            arrCodigoPedidos, arrIngresoBrutoPedidos, 
            arrIngresoDescuentoPedidos, arrIngresoNetoPedidos, 
            arrClienteDniPedidos, arrClienteNombrePedidos, arrClienteDistritoPedidos,  
            arrRepartidorDniPedidos, arrRepartidorNombrePedidos, arrRepartidorVehiculoPedidos, 
            arrPagoRepartidorPedidos,
        cantidadPlatos, arrCodigoPlatos,
            arrPrecioPlato, arrDescuentoPlatos,
            arrCantidadPlatos, arrMontoVendidoPlatos, arrDescuentoPlatoPlatos,
            arrDescuentoClientePlatos, arrTotalIngresadoPlatos,         
        cantidadDistritos, arrCodigoDistritos, arrNombreDistritos, 
        cantidadClientes, arrDniClientes, arrNombreClientes, 
            arrDistritoClientes, arrVehiculoClientes,
            arrDescuentoClientes,
        cantidadRepartidores, arrCodigoRepartidores,
            arrVehiculoRepartidores, arrDistritorepartidores, 
            arrNombreRepartidores);
    
    //imprimir resportes y terminar el acumulado       
    
    emiteReporte("PedidosAtendidos.txt", cantidadPedidos, 
            arrCodigoPedidos, arrIngresoBrutoPedidos, 
            arrIngresoDescuentoPedidos, arrIngresoNetoPedidos, 
            arrClienteDniPedidos, arrClienteNombrePedidos, arrClienteDistritoPedidos,  
            arrRepartidorDniPedidos, arrRepartidorNombrePedidos, arrRepartidorVehiculoPedidos, 
            arrPagoRepartidorPedidos, 
            "PlatosAtendidos.txt", cantidadPlatos, 
                arrCodigoPlatos, arrDescripcionPlatos, arrCategoriaPlato, 
                arrPrecioPlato, arrDescuentoPlatos,
                arrCantidadPlatos, arrMontoVendidoPlatos, arrDescuentoPlatoPlatos,
                arrDescuentoClientePlatos, arrTotalIngresadoPlatos);
    
    return 0;
}


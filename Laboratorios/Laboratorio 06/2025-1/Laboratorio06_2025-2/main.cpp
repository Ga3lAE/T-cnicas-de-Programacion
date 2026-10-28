/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 7 de junio de 2025, 05:00 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_INFRACCIONES 500
#define MAX_CANT_REPRESENTANTES 1000

/*
 * 
 */

int main(int argc, char** argv) {
    
    int cantidadInfracciones=0;
    int arrCodigoInfraccion[MAX_CANT_INFRACCIONES]{};
    double arrMultasInfracciones[MAX_CANT_INFRACCIONES]{};
    
    leeTablaInfracciones("TablaDeInfracciones.txt", cantidadInfracciones, 
            arrCodigoInfraccion, arrMultasInfracciones);                
    
    int cantidadRepresentates=0;
    int arrDni[MAX_CANT_REPRESENTANTES]{}, 
            arrMasMultaAntigua[MAX_CANT_REPRESENTANTES]{}, 
            arrUltimaPendiente[MAX_CANT_REPRESENTANTES]{};
    double arrTottalMultas[MAX_CANT_REPRESENTANTES]{},
            arrTotalPagadas[MAX_CANT_REPRESENTANTES]{},
            arrTotalPendientes[MAX_CANT_REPRESENTANTES]{};
    
    leeInfracciones("InfraccionesCometidas.txt", "PlacasRegistradas.txt", 
            cantidadRepresentates, 
            arrDni, arrMasMultaAntigua, arrUltimaPendiente, 
            arrTottalMultas, arrTotalPendientes, arrTotalPagadas, 
            arrCodigoInfraccion, arrMultasInfracciones, cantidadInfracciones); 
    
    emiteReporte("Reporte.txt", "PlacasRegistradas.txt", 
            cantidadRepresentates,
            arrDni, arrMasMultaAntigua, arrUltimaPendiente, 
            arrTottalMultas, arrTotalPendientes, arrTotalPagadas);

    return 0;
}
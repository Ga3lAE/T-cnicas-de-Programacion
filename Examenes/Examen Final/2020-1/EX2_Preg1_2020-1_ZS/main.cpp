

/* 
 * File:   main.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 28 de junio de 2023, 06:02 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

#include "Empleados.h"
#include "Areas.h"
#include "TotalHoraxMes.h"
#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Area *areas;
    areas = new struct Area[20]{};
    
    int numAreas;
    leerAreas(areas,numAreas);
    leerCamposEmpleados(areas,numAreas);
    int anio,trimestre;
    solicitudDeTrimestreyAnio(anio,trimestre);
    leerHorasTrabajo(areas,numAreas,anio,trimestre);
    emiteReporte(areas,numAreas,anio,trimestre);
    return 0;
}


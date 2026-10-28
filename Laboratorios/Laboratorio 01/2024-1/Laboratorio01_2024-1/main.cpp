/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 10 de abril de 2025, 11:41 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

/*
 * 
 */
int main(int argc, char** argv) {

    //Datos para las estadisticas finales
    int cantidadPacientes=0, cantidadSiMedicina=0, cantidadNoMedicina=0,  
            cantidadDermaSiMedicina=0, cantidadPed=0, 
            cantidadCardFecha=0, cantidadNoMedicinasGastom=0;
    double gastosMedicina=0, gastosDermaSiMedicina=0;
    
    leeRegistraDatos(cantidadPacientes, 
            cantidadSiMedicina,cantidadNoMedicina, 
            cantidadDermaSiMedicina, cantidadPed, 
            cantidadCardFecha, cantidadNoMedicinasGastom,
            gastosMedicina, gastosDermaSiMedicina);
    
    double promedioGastosSiMedicina, promediogastosSiMedicinaDerma, 
            porcentajeNoMedicinas, porcentajePed, 
            porcentajeNoMedicinaGastom;
    
    promedioGastosSiMedicina = gastosMedicina/cantidadSiMedicina;
    promediogastosSiMedicinaDerma = gastosDermaSiMedicina/cantidadDermaSiMedicina;
    porcentajeNoMedicinas=cantidadNoMedicina*100.0/cantidadPacientes;
    porcentajePed=cantidadPed*100.0/cantidadPacientes;
    porcentajeNoMedicinaGastom=cantidadNoMedicinasGastom*100.0/cantidadSiMedicina;
    
    imprimeReporteFinal(promedioGastosSiMedicina, 
            promediogastosSiMedicinaDerma, 
            porcentajeNoMedicinas, 
            porcentajePed, 
            cantidadCardFecha, 
            porcentajeNoMedicinaGastom);                       
    return 0;
}

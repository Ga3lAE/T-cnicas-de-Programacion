/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 18 de mayo de 2025, 05:08 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_PACIENTES 100
#define MAX_CANT_MEDICINASA 250

/*
 * 
 */

int main(int argc, char** argv) {

    int cantidadPacientes;
    int dnisPacientes[MAX_CANT_PACIENTES]{}, 
            distritosPacientes[MAX_CANT_PACIENTES]{}, 
            aniosNacimientoPacientes[MAX_CANT_PACIENTES]{};
    double porcentajesDescuentosPacientes[MAX_CANT_PACIENTES]{};
    
    leePacientes("Pacientes.txt", cantidadPacientes, 
            dnisPacientes, distritosPacientes, aniosNacimientoPacientes, 
            porcentajesDescuentosPacientes);
    
    int cantidadmedicianas;
    int codigosMedicinas[MAX_CANT_MEDICINASA]{};
    double preciosMedicinas[MAX_CANT_MEDICINASA]{};
    
    leeMedicinas("Medicinas.txt", cantidadmedicianas, 
            codigosMedicinas, preciosMedicinas);
    
    verificaLecturas("Verificacion.txt", 
            cantidadPacientes, 
            dnisPacientes, distritosPacientes, aniosNacimientoPacientes, 
            porcentajesDescuentosPacientes, 
            cantidadmedicianas, 
            codigosMedicinas, preciosMedicinas);
    
    
    //creamos los arreglos que necesitaremos apra cada uno de los pacientes
    char clasficicacionesPacientes[MAX_CANT_PACIENTES]{};
    int cantidadesCitasPacientes[MAX_CANT_PACIENTES]{},
            cantidadesMedicinasPacientes[MAX_CANT_PACIENTES]{};
    double pagosMedicinasPacientes[MAX_CANT_PACIENTES]{};
    
    procesaCitas("CitasMedicas.txt", 
            cantidadPacientes, 
            dnisPacientes, porcentajesDescuentosPacientes, 
            cantidadmedicianas, 
            codigosMedicinas, preciosMedicinas, 
            cantidadesCitasPacientes, cantidadesMedicinasPacientes, 
            pagosMedicinasPacientes);
    
    asignaCalificacionesYOrdena(cantidadPacientes, 
            dnisPacientes, distritosPacientes, aniosNacimientoPacientes, 
            porcentajesDescuentosPacientes, clasficicacionesPacientes, 
            cantidadesCitasPacientes, cantidadesMedicinasPacientes, 
            pagosMedicinasPacientes);
    
    emiteReporte("ConsolidadoPacientes.txt", cantidadPacientes, 
            clasficicacionesPacientes, distritosPacientes, 
            dnisPacientes, porcentajesDescuentosPacientes, 
            cantidadesCitasPacientes, cantidadesMedicinasPacientes, 
            pagosMedicinasPacientes);
    
    
    return 0;
}


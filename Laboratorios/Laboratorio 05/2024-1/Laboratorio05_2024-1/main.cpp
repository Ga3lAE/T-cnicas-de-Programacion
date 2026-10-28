/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 10 de mayo de 2025, 04:00 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CANT_MEDICOS 50
#define MAX_CANT_MEDICINAS 220

/*
 * 
 */
int main(int argc, char** argv) {
    
    int codigosMedicos[MAX_CANT_MEDICOS]{};
    double tarifasMedicos[MAX_CANT_MEDICOS]{};
    int cantidadMedicos=0;
    
    leeMedicos("Medicos.txt", cantidadMedicos, 
            codigosMedicos, tarifasMedicos);
    
    
    int codigosMedicinas[MAX_CANT_MEDICINAS]{};
    double preciosMedicinas[MAX_CANT_MEDICINAS]{};
    int cantidadMedicinas=0;
    leeMedicinas("Medicinas.txt", cantidadMedicinas, 
            codigosMedicinas, preciosMedicinas);
    
    verificaLecturas("VerficaLecturas.txt", 
            cantidadMedicos, codigosMedicos, tarifasMedicos, 
            cantidadMedicinas, codigosMedicinas, preciosMedicinas);
    
    //definimos los arreglos para los reportes de ingresos
        //primero con los medicos
    double ingresosCitasMedicos[MAX_CANT_MEDICOS]{},
            ingresosMedicinasMedicos[MAX_CANT_MEDICOS]{}, 
            totalesIngresadosMedicos[MAX_CANT_MEDICOS]{};
    int cantidadesPacientesMedicinasMedicos[MAX_CANT_MEDICOS]{}, 
            cantidadesPacientesSinMedicinasMedicos[MAX_CANT_MEDICOS]{}, 
            cantidadesPacientesMedicos[MAX_CANT_MEDICOS]{};
        //segundo con las medicinas
    int cantidadesVendidasMedicinas[MAX_CANT_MEDICINAS]{};
    double ingresosNoDescuentosMedicinas[MAX_CANT_MEDICINAS]{}, 
            descuentosSegurosMedicinas[MAX_CANT_MEDICINAS]{}, 
            totalesIngresadosMedicinas[MAX_CANT_MEDICINAS]{};
    procesaCitas("CitasMedicas.txt", 
            //datos de los medicos
            cantidadMedicos, 
            codigosMedicos, tarifasMedicos, 
            ingresosCitasMedicos, ingresosMedicinasMedicos, 
            totalesIngresadosMedicos, cantidadesPacientesMedicinasMedicos, 
            cantidadesPacientesSinMedicinasMedicos, cantidadesPacientesMedicos, 
            //datos de las medicinas
            cantidadMedicinas, 
            codigosMedicinas, preciosMedicinas, 
            cantidadesVendidasMedicinas, ingresosNoDescuentosMedicinas, 
            descuentosSegurosMedicinas, totalesIngresadosMedicinas);
    
    ofstream archivoReporte("ReporteDeIngresos.txt", ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<"ReporteDeIngresos.txt";
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    imprimeIngresosMedicos(archivoReporte, cantidadMedicos, 
            codigosMedicos, tarifasMedicos, ingresosCitasMedicos, 
            ingresosMedicinasMedicos, totalesIngresadosMedicos, 
            cantidadesPacientesMedicinasMedicos, cantidadesPacientesSinMedicinasMedicos, 
            cantidadesPacientesMedicos);
    imprimeIngresosMedicinas(archivoReporte, cantidadMedicinas, 
            codigosMedicinas, preciosMedicinas, 
            cantidadesVendidasMedicinas, ingresosNoDescuentosMedicinas, 
            descuentosSegurosMedicinas, totalesIngresadosMedicinas);
    
    double promedioIngresosMedicos = sumaArrDouble(totalesIngresadosMedicos, cantidadMedicos)/cantidadMedicos;
    filtraMedicos(cantidadMedicos, 
            codigosMedicos, tarifasMedicos, ingresosCitasMedicos, 
            ingresosMedicinasMedicos, totalesIngresadosMedicos, 
            cantidadesPacientesMedicinasMedicos, cantidadesPacientesSinMedicinasMedicos, 
            cantidadesPacientesMedicos, promedioIngresosMedicos);
    // por filtar y reeimprimir el reporte con los mejores medicos
    
     ofstream archivoReporteMejores("ReporteDeIngresosMejoresMedicos.txt", ios::out);
    if(not archivoReporteMejores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<"ReporteDeIngresosMejoresMedicos.txt";
        exit(1);
    }
    archivoReporteMejores<<fixed<<setprecision(2);
    imprimeIngresosMedicos(archivoReporteMejores, cantidadMedicos, 
        codigosMedicos, tarifasMedicos, ingresosCitasMedicos, 
        ingresosMedicinasMedicos, totalesIngresadosMedicos, 
        cantidadesPacientesMedicinasMedicos, cantidadesPacientesSinMedicinasMedicos, 
        cantidadesPacientesMedicos);  
    
    return 0;
}


/* 
 * File:   funcionesAuxiliares.h
 * Author: arias
 *
 * Created on 10 de abril de 2025, 11:41 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimeLinea(char c);

void leeRegistraDatos(int& cantidadPacientes, 
        int& cantidadSiMedicina, int& cantidadNoMedicina, 
        int& cantidadDermaSiMedicina, int& cantidadPed, 
        int& cantidadCardFecha, int& cantidadNoMedicinasGastom, 
        double& gastosMedicina, double& gastosDermaSiMedicina);
void leeFecha(int& fecha);
void leeHora(int& hora);
void procesaDatos(int& cantidadPacientes, 
        int& cantidadSiMedicina, int& cantidadNoMedicina, 
        int& cantidadDermaSiMedicina, int& cantidadPed, int& cantidadCardFecha, 
        int& cantidadNoMedicinasGastom, 
        double& gastosMedicina, double& gastosDermaSiMedicina, 
        int fecha, int horaInicio, int horaFin, 
        double tarifaMedico, char especialidad, 
        double pagoMedicinas, char recibeMedicina, 
        int& duracionHMS, double& duracionH, double& pagoTotal);

void imprimeDatos(int fecha, int dniPaciente, 
        int horaInicio, int horaFin, 
        int duracionHMS, double duracionH, char especialidad, double pagoTotal);
void imprimeEncabezado();
void imprimeCategorias();
void imprimeFecha(int fecha);
void imprimeHora(int hora);
void imprimeEspecialidad(char especialidad);

void imprimeReporteFinal(double promedioGastosSiMedicina,
        double promediogastosSiMedicinaDerma, 
        double porcentajeNoMedicinas, 
        double porcentajePed, 
        int cantidadCardFecha, 
        double porcentajeNoMedicinaGastom);


#endif /* FUNCIONESAUXILIARES_H */


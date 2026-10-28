/* 
 * File:   funciones.h
 * Author: arias
 *
 * Created on 15 de abril de 2025, 05:10 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char car);

void leeProcesaArchivos(const char *nombreArchivoCitas, const char *nombreArchivoMedicos,
        const char *nombreArchivoReporte);

void leeProcesaDatos(ifstream &archivoCitas, ifstream &archivoMedicos, 
        ofstream &archivoReporte, 
        double &totalIngresos, int &dniMayorGasto, double &mayorGasto);
void leeFecha(ifstream &archivo, int &fecha);
void leeHora(ifstream &archivo, int &hora);

void imprimeFecha(ofstream &archivo, int fecha);
void imprimeHora(ofstream &archivo, int hora);
void imprimeEncabezado(ofstream &archivoReporte);
void imprimeCategorias(ofstream &archivo);
void imprimeDatosPaciente(ofstream &archivo, 
        int fecha, int dni, int horaInicio, int horaFin, double porcentajeDescuento);
void procesaImprimeDatosMedico(ifstream& archivoMedicos, ofstream& archivoReporte, 
        int codigoMedico, 
        int duracion, 
        double porcentajeDescuento, double pagoMedicina, 
        double& totalIngresos, 
        int& dniMayorGasto, double& mayorGasto, 
        bool& primerPaciente, int dniPaciente);
void procesaMayor(int& dniMayor, double& mayorGasto, bool& primerPaciente, int dniPaciente, double pagoPaciente);
void leeImprimeNombre(ifstream &archivoLectura, ofstream &archivoImpresion);
void leeImprimeEspecialidad(ifstream &archivoLectura, ofstream &archivoImpresion);
void imprimeEstadisticas(ofstream &archivoReporte, 
        double totalIngresos, int dniPacienteMayorGasto, double mayorGastoPaciente);

#endif /* FUNCIONES_H */


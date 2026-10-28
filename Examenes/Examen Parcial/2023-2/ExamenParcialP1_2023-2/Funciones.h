/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 18 de mayo de 2025, 06:29 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char c);

//LECTURA
void leeFecha(ifstream &archivo, int &fecha);
void leeHora(ifstream &archivo, int &hora);

//PROCESAMIENTO
void leeProcesaArchivos(const char *nombreArchivoPacientes, 
        const char *nombreArchivoCitas,
        const char *nombreArchivoMedicos, 
        const char *nombreArchivoMedicinas, 
        const char *nombreArchivoReporte);
void leeArchivos(ifstream &archivoPacientes, ifstream &archivoCitas, 
            ifstream &archivoMedicos, ifstream &archivoMedicinas, 
            ofstream &archivoReporte);
void leeImprimePaciente(ifstream &archivoPacientes, ofstream &archivoReporte,
        int dni, int& anio, double& descuento);
void imprimeNombre(ifstream &archLec, ofstream &archRep, char del);
void procesaCitas(ifstream &archivoCitas, ifstream &archivoMedicos, ifstream &archivoMedicinas, 
                ofstream &archivoReporte, 
                int dniPaciente, double descuentoPaciente, 
                double &pagoTotalPaciente);
void imprimeFecha(ofstream &archivo, int fecha);
void imprimeHora(ofstream &archivo, int hora);
void imprimeMedico(ifstream &archivoMedico, ofstream &archivoReporte, 
        int codigoMedico, 
        double &pagoCita, int duracion, double descuento);
void imprimeDescripcion(ifstream &archivoMedico, ofstream &archivoReporte);
void procesaMedicinas(ifstream &archivoMedicinas, ofstream &archivoReporte,
        int codigoMedicina, int cantidadRecetada, int contadorMedicinas, 
        double &pagoMedicinas, double descuento);
void imprimeEncabezadoMedicinas(ofstream &archivo);

#endif /* FUNCIONES_H */

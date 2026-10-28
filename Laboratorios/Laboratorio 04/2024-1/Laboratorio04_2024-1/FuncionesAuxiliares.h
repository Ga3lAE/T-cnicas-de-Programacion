/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file_header.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: arias
 *
 * Created on 4 de mayo de 2025, 04:57 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H


//Lectura generica
void leeFecha(ifstream &archivo, int &fecha);
void leeHora(ifstream &archivo, int &hora);

//Impresion generica
void imprimeLinea(ofstream &archivo, char c);
void imprimeTexto(ifstream &archivoMedicos, ofstream &archivoReporte, int tam, char del);
void imprimeHora(ofstream& archivo, int hora);

//impresion exacta
void imprimeEncabezadoCitas(ofstream &archivoReporte);
void imprimeNombreMedico(ifstream &archivoMedicos, ofstream &archivoReporte, 
        char del);
void imprimeEncabezadoPacientes(ofstream &archivo);
void imprimeEncabezadoMedicinas(ofstream& archivo);
void imprimeEstadisticasMedicinas(ofstream& archivoReporte, 
        double pagoTotalMedicinas, double pagoTotal);

//Lectura y procesamiento de archivos
void leeProcesaArchivos(const char *nombreArchivoMedicos, 
        const char *nombreArchivoCitasMedicas,
        const char *nombreArchivoMedicinas,
        const char *nombreArchivoReporte);
void procesaArchivos(ifstream &archivoMedicos, 
        ifstream &archivoCitasMedicas, 
        ifstream &archivoMedicinas,
        ofstream &archivoReporte,
        int &codigoMedicoMayorAporte, double &ingresoMedicoMayorAporte);
void procesaCitas(ifstream &archivoCitasMedicas, ifstream &archivoMedicinas, 
        ofstream &archivoReporte, 
        int codigoMedico, double tarifa,
        int &codigoMedicoMayorAporte, double &ingresoMedicoMayorAporte);
void procesaMedicinas(ifstream &archivoMedicinas,ofstream &archivoReporte, 
        int cantidadMedicinasRecetada, int codigoMedicinaRecetada,
        double &pagoTotalMedicinas, int &contadorMedicinas);

#endif /* FUNCIONESAUXILIARES_H */

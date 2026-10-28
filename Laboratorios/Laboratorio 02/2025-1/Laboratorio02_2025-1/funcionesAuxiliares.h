/* 
 * File:   funcionesAuxiliares.h
 * Author: arias
 *
 * Created on 17 de abril de 2025, 01:58 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimeLinea(ofstream &archivo, char c);

void procesaArchivos(ifstream &archivoInfracciones, ofstream &archivoReporte,        
        int &dniMayorPago, int &dniMenorPago, 
        double &mayorPago, double &menorPago);
void procesaMultas(ifstream &archivoInfracciones, ofstream &archivoReporte, 
                double &pagoTotal, int fecha1, int fecha2);

void asignaMayorMenor(int &dniMayorPago, int &dniMenorPago, 
        double &mayorPago, double &menorPago, bool &primerLectura, 
        int dni, double pagoTotal);
void asignaMulta(double& multa, char tipo);
void asingaIncrementos(double multa, 
         double &incrementoFecha, double &incrementoHora, double &incrementoTipo,
         int fecha1, int fecha2, int fechaInfraccion, 
        int horaInfraccion, 
        char tipoCarro);

void leeFecha(ifstream &archivo, int &fecha);
void leeHora(ifstream &archivo, int &hora);
void leeImprimeDatos(ifstream &archivoInfracciones, ofstream &archivoReporte, 
        int &dni, int &cantidadCompanias);
void leeImprimeNombre(ifstream &archivoLectura, ofstream &archivoImpresion);

void imprimeEncabezado(ofstream &archivo, int fecha1, int fecha2);
void imprimeCategoriasMulta(ofstream &archivoReporte);
void imprimeFecha(ofstream& archivo, int fecha);
void imprimeHora(ofstream& archivo, int hora);
void imprimeTipoCarro(ofstream &archivo, char tipo);
void imprimeGravedad(ofstream &archivo, char tipo);
void imprimeEstadisticas(ofstream&archivoReporte,
        int dniMayorPago, int dniMenorPago, 
        double mayorPago, double menorPago);
#endif /* FUNCIONESAUXILIARES_H */


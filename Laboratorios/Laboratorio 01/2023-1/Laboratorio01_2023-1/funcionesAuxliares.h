/* 
 * File:   funcionesAuxliares.h
 * Author: arias
 *
 * Created on 12 de abril de 2025, 07:55 PM
 */

#ifndef FUNCIONESAUXLIARES_H
#define FUNCIONESAUXLIARES_H

void imprimeLinea(char c);

void leeImprimeDatos(int& codigoDocenteMayorDeuda, double& montoDocenteMayorDeuda, 
        int& codigoEstudianteMayorDeuda, double& montoEstudianteMayorDeuda);
void leeFecha(int& fecha);

void procesaImprimeLibro(int codigoLibro, 
        int fechaPrestamo, double precioLibro, char reincide, double multa, 
        int &cantidadLibros, double &totalMultas);
void asignaMaximaDeuda(bool primeraLectura, 
        int& codigoMayorDeuda, double& montoMayorDeuda, 
        int codigo, double montoDeuda);


void imprimeEncabezado(int fechaLimiteEstudiantes, int fechaLimiteDocentes);
void imprimeFecha(int fecha);
void imprimeSubEncabezado(int codigo, char tipo, char reincide);
void imprimeTipo(char tipo);
void imprimeReincidencias(char reincide);
void imprimeRecuentoSimple(int cantidadLibros, double totalDeuda);
void imprimeResumen(int codigoDocenteMayorDeuda, double montoDocenteMayorDeuda, 
        int codigoEstudianteMayorDeuda, double montoEstudianteMayorDeuda);
#endif /* FUNCIONESAUXLIARES_H */


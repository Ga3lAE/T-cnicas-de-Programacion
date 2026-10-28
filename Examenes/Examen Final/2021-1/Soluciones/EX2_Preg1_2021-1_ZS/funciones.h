/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: aml
 *
 * Created on 20 de junio de 2023, 04:48 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearLibrosBin(const char* nombArchCsv, const char* nombArchBin);
void mostrarLibrosBin(const char* nombArchBin, const char* nombArchTxt);
void crearRegistrosBin(const char* nombArchCsv, const char* nombArchBin);
void mostrarRegistrosBin(const char* nombArchBin, const char* nombArchTxt);
void actualizarSolicitudes(const char *nombArchCsv,const char *nomLibrosBin,
        const char *nomRegiBin,const char *nombArchTxt);
void leeImprimeRegistrosActualizados(ifstream& archSolicitudes, 
        fstream& archLibrosBin, fstream& archRegistrosBin, ofstream& archReporte);
void actualizarArchivos(struct Registros &registro,char *codLibro,int fechaProcesar,
        int posUsuario,struct Libro &libro,int posLibro,int tamRegLibros,
        int tamRegPrestamos,fstream &archLibrosBin,fstream &archRegistrosBin,
        ofstream &archReporte);
void asignarNuevoRegistro(struct Registros &registro,int dni,char *nombre,
        char *codLibro,int fechaProcesar,struct Libro &libro,int posLibro,
        int tamRegLibros,int tamRegPrestamos,fstream &archRegistrosBin,
        fstream &archLibrosBin,ofstream &archReporte);
int verificaLibros(struct Registros &registro, int cantidad, int fecha);
void imprimeObservacion(int dni,char *nombre,const char *nomLibro,char *codLibro,
        int observacion,ofstream &archReporte);
int buscarUsuario(fstream &archRegistrosBin,int dni);
int buscarPosicion(fstream& archLibrosBin, char* codiLibro);
void leeImprimeEncabezado(int &fechaProcesar,int &fechaLimite,ifstream &archSolicitudes,
        ofstream &archReporte);
void datosArchivos(fstream &archLibrosBin,int tamReg,int &tamArch, int &numReg);
#endif /* FUNCIONES_H */


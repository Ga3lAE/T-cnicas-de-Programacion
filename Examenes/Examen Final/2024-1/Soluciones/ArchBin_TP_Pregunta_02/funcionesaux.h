/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funcionesaux.h
 * Author: aml
 *
 * Created on 1 de julio de 2024, 08:18 PM
 */

#ifndef FUNCIONESAUX_H
#define FUNCIONESAUX_H

void leyendoClientes(const char*nomArch,const char*nomArchBin);
void  modificando(char*nombre);
void  corroborandoClientes(const char*nomArch,const char*nomArchBin);
void headerClientes(ofstream&arch);
void datosIfstream(int tamReg,int&numReg,int&tamArch,ifstream&archBin);
void leyendoLibros(const char*nomArch,const char*nomArchBin);
void emitiendoReporte(const char*nomArch,const char*nomArchBinClientes,
        const char*nomArchBinLibros);
void headerLibro(struct Libro&arrLibros,ofstream&arch,int i);
void imprimiendoLibreriasPerBook(struct Libreria*librerias,
                int cantidadLibrerias,ofstream&arch);
void imprimiendoVentasLibreria(struct Venta*ventas,int cantidadVentas,
        ofstream&arch);
void leyendoVentas(const char*nomArch,const char*nomArchBinClientes,
        const char*nomArchBinLibros);
void datosFstream(int tamReg,int&numReg,int&tamArch,fstream&archBin);
int buscandoLibro(char*codeLibroVerif,fstream&archBinLib,int numRegLib);
int buscandoCliente(int dniVerif,fstream&archBinCli,int numRegCli);
void actualizandoInformacion(struct Libro&arrLibros,
                        struct Cliente&arrCliente,int fecha,
        int codeLibreriaVerif,int calificacion);
int buscandoLibreria(int codeLibreriaVerif,struct Libreria*librerias,
            int cantidadLibrerias);
void ActualizandoLibrerias(struct Libro&arrLibros,int u,
        struct Cliente&arrCliente,int codeLibreriaVerif,
                int calificacion,int fecha);

#endif /* FUNCIONESAUX_H */


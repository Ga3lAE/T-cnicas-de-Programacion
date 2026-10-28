/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funcionesaux.h
 * Author: aml
 *
 * Created on 1 de julio de 2024, 06:38 PM
 */

#ifndef FUNCIONESAUX_H
#define FUNCIONESAUX_H

void leyendoClientes(const char*nomArch,struct Cliente*arrCliente,
        int&cantClientes);
char*leyendoCadena(ifstream&arch,char fin);
void corroborandoClientes(const char*nomArch,struct Cliente*arrCliente,
        int cantClientes);
void headerClientes(ofstream&arch);
void leyendoLibros(const char*nomArch,struct Libro*arrLibros,
        int&cantLibros);
void emitiendoReporte(const char*nomArch,struct Cliente*arrCliente,
        struct Libro*arrLibros,int cantClientes,int cantLibros);
void headerLibro(struct Libro&arrLibros,ofstream&arch,int i);
void imprimiendoLibreriasPerBook(struct Libreria*librerias,
                int cantidadLibrerias,ofstream&arch);
void imprimiendoVentasLibreria(struct Venta*ventas,int cantidadVentas,
        ofstream&arch);
void leyendoVentas(const char*nomArch,struct Libro*arrLibros,
        struct Cliente*arrCliente,
        int cantClientes,int cantLibros);
int buscandoLibro(char*codeLibroVerif,struct Libro*arrLibros,int cantLibros);
int buscandoCliente(int dniVerif,struct Cliente*arrCliente,int cantClientes);
void actualizandoInformacion(struct Libro&arrLibros,
                        struct Cliente&arrCliente,int fecha,
        int codeLibreriaVerif,int calificacion);
int buscandoLibreria(int codeLibreriaVerif,struct Libreria*librerias,
            int cantidadLibrerias);
void ActualizandoLibrerias(struct Libro&arrLibros,int u,
        struct Cliente&arrCliente,int codeLibreriaVerif,
                int calificacion,int fecha);
void  modificando(char*nombre);

#endif /* FUNCIONESAUX_H */


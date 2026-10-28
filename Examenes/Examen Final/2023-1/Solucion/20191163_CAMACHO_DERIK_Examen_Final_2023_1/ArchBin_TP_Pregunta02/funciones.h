/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 08:03 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearLibrosBin(const char* nombArchCsv, const char* nombArchBin);
void leerDatosArchivo(ofstream& archLibrosBin, ifstream& archLibros);
void mostrarLibrosBin(const char* nombArchBin, const char* nombArchTxt);
void imprimeEncabezadosLibros(ofstream& archReporte);
void crearUsuariosBin(const char *nombArchCsv,const char *nombArchBin);
void leerDatosUsuarios(ofstream &archUsuariosBin,ifstream &archUsuarios);
void mostrarUsuariosBin(const char* nombArchBin, const char* nombArchTxt);
void imprimeEncabezadoUsuarios(ofstream& archReporte);
void modificarArchivosLibrosyUsuariosBin(const char *nombLibrosBin,
        const char *nombUsuariosBin,const char *nombArcTxt);
void modificarArchivos(int fechaDevolucion,int dni,char *ptr_codLibro,
        fstream &archLibros,fstream &archUsuarios);
void eliminarLibro(char *codigoLibro,int posUsuario,int posLibroEliminar,fstream &archUsuarios);
int buscarLibro(char *codigoLibro, fstream &archLibros);
int buscarUsuario(int dni,fstream &archUsuarios);
int buscarUsuarioDeLibro(int dni,struct Libro &libro);
int buscarLibroDeUsuario(char *codigLibro,struct Usuario &usuario);
void emiteReporteLibrosBin(const char *nombArchBin, const char *nombArchTxt);
void emiteReporteUsuariosBin(const char *nombArchBin,const char *nombArchTxt);
void datosArchivo(fstream &arch,int tamReg, int &tamArch,int &numReg);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);

#endif /* FUNCIONES_H */


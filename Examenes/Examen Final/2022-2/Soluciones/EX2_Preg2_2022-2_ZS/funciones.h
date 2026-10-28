/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: aml
 *
 * Created on 26 de junio de 2023, 06:27 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearArchDireccionesBin(const char *nombArchCsv,const char *nombArchBin);
void crearArchPedidosBin(const char* nombArchCsv, const char* nombArchBin);
void asignarProductos(struct Pedido& pedido, ifstream& archCsv);
void crearArchivo(const char* nombArchBin);
void actualizarPedidosBin(const char *nombPedidosBin,const char *nombDirecBin,
        const char *nombArchCsv);
void asignarValores(int tiempo,char *nombreRappi,char *codUsuario,
        int posDireccion,int posPedido,ifstream &archDireccionesBin,
        fstream &archPedidosBin);
void ordenarArchivos(const char *nombArchBin);
void imprimeReporte(const char *nombArchBin,const char *nombArchTxt);
int buscarDireccion(ifstream &arch, char *codigo);
int buscarPedido(fstream &archBin, int codigo);
void datosArchivoDireccion(ifstream &arch,int &tamArch,int tamReg,int &numReg);
void datosArchivo(fstream& archBin, int& tamArch, int tamReg, int& numReg);
void imprimeLinea(char caracter, int cantidad, ofstream &archRep);
#endif /* FUNCIONES_H */


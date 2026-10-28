

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 12:44 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void crearClientesBin(const char *nombArchBin,const char *nombArchCsv);
void modificaNombre(char *cadena);
void leerNombreCompleto(ifstream &archClientes,char *apellidoPaterno,
        char *apellidoMaterno,char *nombre,char *nombreCompleto);
void modificaApellido(char *cadena);
void modificarClientesBin(const char* nombArchBin, const char* nombArchCsv);
void leerYasignarDatos(struct Cliente &cliente,double &cantidad,
        char &tipo,int posClinte,int tamReg,ifstream &archTransacciones,
        fstream &archClientesBin);
void emiteReportes(const char* nombArchBin, const char* nombRepTxt1,
        const char* nombRepTxt2);
void imprimePrimerReporte(struct Cliente &cliente,const char *nombArchBin,
        ofstream &archPrimerReporte);
void imprimeSegundoReporte(struct Cliente &cliente,const char *nombArchBin,
        ofstream &archSegundoReporte);
void imprimeLinea(char caracter,int cantidad, ofstream &archRep);
void datosArchivo(fstream& archBin, int tamReg, int& tamArch, int& numReg);
int buscarCliente(fstream& archClientesBin, int numeroCuenta, int numReg);

#endif /* FUNCIONES_H */


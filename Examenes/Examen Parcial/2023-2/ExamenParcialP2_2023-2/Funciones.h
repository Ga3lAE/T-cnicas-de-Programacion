/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 18 de mayo de 2025, 05:08 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void saltaTextoUnDel(ifstream &archivo, char del);
void leePacientes(const char *nombreArchivo, int &cantidad,
        int *dnis, int *distritos, int *anios,
        double *porcentajesDescuentos);
void leeMedicinas(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios);

//BUSQUEDA  
int buscaInt(int *arr, int can, int el);
//PROCESAMOS
void procesaCitas(const char *nombreArchivo,
        int cantidadPacientes,
        int *dnisPacientes, double *porcentajesDescuentosPacientes,
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesCitasPacientes, int *cantidadesMedicinasPacientes,
        double *pagosMedicinasPacientes);

void asignaCalificacionesYOrdena(int cantidad, 
        int *dnis, int *distritos, int *aniosNacimiento, 
        double *porcentajesDescuentos, char *clasficicaciones, 
        int *cantidadesCitas, int *cantidadesMedicinas,
        double *pagosMedicinas);
void cambiaInt(int &d1, int&d2);
void cambiaChar(char&d1, char &d2);
void cambiaDouble(double &d1, double &d2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void verificaLecturas(const char *nombreArchivo,
        int cantidadPacientes,
        int *dnisPacientes, int *distritosPacientes, int *aniosNacimientoPacientes,
        double *porcentajesDescuentosPacientes,
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas);
void emiteReporte(const char *nombreArchivo, int cantidad, 
            char *clasficicaciones, int *distritos, 
            int *dnis, double *porcentajesDescuentos, 
            int *cantidadesCitas, int *cantidadesMedicinas, 
            double *pagosMedicinas);
double sumaArrDouble(double *arr, int cant);
#endif /* FUNCIONES_H */

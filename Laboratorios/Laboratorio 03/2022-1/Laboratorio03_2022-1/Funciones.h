/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 12 de mayo de 2025, 11:11 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char c);

//LECTURA
void leeClientes(const char *nombreArchivo, int &cantidad,
        int  *dnis, int *telefonos);
void leePedidos(const char *nombreArchivo, int &cantidadProductos,
        int *codigosProductos, double *preciosProductos,
        double *cantidadesProductos, double *totalesProductos,
        int cantidadClientes, int *dnisClientes, double *gastosClientes);
int buscaInt(int *arr, int cantidad, int elemento);

//ORDENAMIENTO
void cambiarInt(int &dato1, int &dato2);

void ordenaClientes(int cantidad,
        int *dnis, int *telefonos);

void imprimeReporte(const char *nombreArchivo,
        int cantidadClientes, 
        int *dnisClientes, int *telefonosClientes, double *gastosClientes,
        int cantidadPedidos, 
        int *codigosProductos, double *preciosProductos, double *cantidadesProductos, double *totalesProductos);
void imprimeEncabezadoProductos(ofstream &archivo);
void imprimeEncabezadoClientes(ofstream& archivo);


#endif /* FUNCIONES_H */

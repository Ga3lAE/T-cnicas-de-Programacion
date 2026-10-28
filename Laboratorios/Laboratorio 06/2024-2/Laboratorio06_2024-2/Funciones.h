/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 27 de mayo de 2025, 05:24 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
void leeRepartos(const char *nombreArchivo, int &cantidad,
        int *codigos, int *numeros);
void leePlatos(const char *nombreArchivo, int cantidad, 
        int *codigos, int *numeros,
        double *precios, double *ingresos,
        bool *tienenDescuentos, double *descuentos, double *totales);
//BUSQUEDA
int buscaIntBinDesc(int *arr, int cantidad, int elemento);
//INSERCION
void agregaPlato(int *codigos, int *numeros, int &cantidad, 
        int codigo, int numero);
//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void verificaArreglos(const char *nombreArchivo, int cantidad,
        int *codigos, double *precios, int *platosVendidos,
        double *ingresosBruto, double *totales,
        bool *tieneDescuento, double *descuentos);
void emiteReporte(const char *nombreArchivoPlatos, const char *nombreArchivoReporte,
        int cantidadPlatos,
        int *arrCodigosPlatos, double *arrPrecio, int *arrNumPlatosVendidos,
        double *arrIngresoBruto, double *arrTotal,
        bool *arrTieneDescuento, double *arrDescuento);
void imprimeEncabezado(ofstream &archivo);
void imprimeDescripcion(ifstream &archivoPlatos, ofstream &archivoReporte, 
        int codigo, bool hayDescuento);
void procesaCadena(char *descripcionCompleta, char *descripcion, char *categoria,
        char *cadenaDescuento, char separador, bool hayDescuento);
void imprimeDescuento(ofstream &archivo, bool hay, double descuento);

#endif /* FUNCIONES_H */

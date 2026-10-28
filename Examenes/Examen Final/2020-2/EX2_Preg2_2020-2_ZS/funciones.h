

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 18 de junio de 2023, 09:34 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Farmacias.h"
void leerFarmacias(struct Farmacia* farmacias, int& numFarmacias);
void leerVentas(struct Farmacia *farmacias,int numFarmacias,
        struct ProductoNoProcesado *productosNoProcesados,
        int &numProductosNoProcesados);
void actualizarProductosNoProcesados(struct ProductoNoProcesado *productosNoProcesados,
        int &numProductosNoProcesados,int codigoFarm,char *ptr_producto,char *ptr_nombreProd,
        int cantidad,double precio);
void actualizarProductos(struct Farmacia *farmacias,int numFarmacias,
        int posFarmacia,char *producto,char *nombreProducto,int cantidad,
        double precio);
void emiteReporte(struct Farmacia* farmacias, int numFarmacias, 
        struct ProductoNoProcesado* productosNoProcesados, 
        int numProductosNoProcesados);
void imprimProductosNoProcesados(struct ProductoNoProcesado *productosNoProcesados,
        int numProductosNoProcesados,ofstream &archReporte);
void imprimeLinea(char caracter, int cantidad, ofstream &arhcRep);
int buscarProducto(struct Farmacia &farmacias, char *codProd);
int buscarFarmacia(struct Farmacia *farmacias, int codigo,int numDatos);
char *leerCadenaExacta(ifstream &arch);

#endif /* FUNCIONES_H */


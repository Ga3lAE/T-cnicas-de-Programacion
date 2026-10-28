

/* 
 * File:   funcions.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 01:23 PM
 */

#ifndef FUNCIONS_H
#define FUNCIONS_H

void crearFarmaciasBin(const char* nombArchCsv, const char* nombArchBin);
void mostrarFarmaciasBin(const char* nombArchBin, const char* nombArchTxt);
void actualizarFarmaciasBin(const char *nombArchBin,const char *nombArchProdBin,
        const char *nombArchCsv);
void asignaModificaArchivoBin(struct ProductoNoProcesado &producto,
        struct Farmacia &farmacia,int codigoFarmacia,
        char *codigoProducto,char *nombreProducto,int cantidadVendida,
        double precio,int tamReg,int numReg,fstream &archFarmaciasBin,
        ofstream &archProdBin);
void registrarProductos(struct ProductoNoProcesado &producto,
        struct Farmacia &farmacia,int codigoFarmacia,
        char *codigoProducto,char *nombreProducto,int cantidadVendida,
        double precio,ofstream &archProdBin);
void emiteReporte(const char *nombArchBin,const char *nombArchProdBin,
        const char *nombArchTxt);
void imprimeProductosNoProcesados(ifstream &archProdNoProcBin,
        ofstream &archReporte);
void imprimeFarmaciasYproductos(ifstream& archFarmaciaBin, ofstream& archReporte);
int buscarProducto(struct Producto *producto, char* codigo, int numDatos);
int buscarFarmmacia(fstream &archFarmaciasBin,int codigoFarmacia,int numReg);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);
void datosArchivo(fstream& archBin, int tamReg, int& tamArch, int& numReg);

#endif /* FUNCIONS_H */


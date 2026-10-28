/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 14 de junio de 2025, 10:58 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del);
void leePlatos(const char *nombreArchivo, int &cantidad,
        char **arrCodigoPlatos, char **arrDescripcionPlatos,
        double *arrPrecioPlato, char **arrCategoriaPlato, 
        double *arrDescuentoPlatos);
void leeDistritos(const char *nombreArchivo, int &cantidad,
        char **arrCodigo, char **arrNombre,
        char **arrUbicacion);
void leeClientes(const char *nombreArchivo, int &cantidad,
        int *arrDniClientes, char **arrNombreClientes,
        char **arrDistritoClientes, char **arrVehiculoClientes,
        double *arrDescuentoClientes);
void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *arrCodigoReprtidores, char **arrNombreRepartidores,
        char **arrVehiculoRepartidores, char **arrDistritorepartidores);
void leePedidos(const char *nombreArchivo, int &cantidad,
            int *arrCodigoPedidos, double *arrIngresoBrutoPedidos, 
            double *arrIngresoDescuentoPedidos, double *arrIngresoNetoPedidos, 
            int *arrClienteDniPedidos, char **arrClienteNombrePedidos, char **arrClienteDistritoPedidos,  
            int *arrRepartidorDniPedidos, char **arrRepartiorNombrePedidos, char **arrRepartidorVehiculoPedidos, 
            double *arrPagoRepartidorPedidos,
        int cantidadPlatos, char **arrCodigoPlatos,
            double *arrPrecioPlato, double *arrDescuentoPlatos,
            int *arrCantidadPlatos, double *arrMontoVendidoPlatos, double *arrDescuentoPlatoPlatos,
            double *arrDescuentoClientePlatos, double *arrTotalIngresadoPlatos,         
        int cantidadDistritos, char **arrCodigoDistritos, char **arrNombredistritos, 
        int cantidadClientes, int *arrDniClientes, char **arrNombreClientes, 
            char **arrDistritoClientes, char **arrVehiculoClientes,
            double *arrDescuentoClientes,
        int cantidadRepartidores, int *arrCodigoRepartidores,
            char **arrVehiculoRepartidores, char **arrDistritorepartidores, 
            char **arrNombreRepartidores);
char *duplicaCadChar(const char *cad);

//BUSQUEDA
int buscaInt(int *arr, int cantidad, int el);
int buscaCadChar(char **arr, int cantidad, const char *el);
int buscaCadCharDoble(char **arr1, char **arr2,  int cantidad, 
        const char *el1, const char *el2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emiteReporte(const char *nombreArchivoPedidos,
        int cantidadPedidos,
            int *arrCodigoPedidos, double *arrIngresoBrutoPedidos,
            double *arrIngresoDescuentoPedidos, double *arrIngresoNetoPedidos,
            int *arrClienteDniPedidos, char **arrClienteNombrePedidos, char **arrClienteDistritoPedidos,
            int *arrRepartidorDniPedidos, char **arrRepartidorNombrePedidos, char **arrRepartidorVehiculoPedidos,
            double *arrPagoRepartidorPedidos, 
        const char *nombreArchivoPlatos, int cantidadPlatos,
            char **arrCodigoPlatos, char **arrDescripcionPlatos, char **arrCategoriaPlato,
            double *arrPrecioPlato, double *arrDescuentoPlatos,
            int *arrCantidadPlatos, double *arrMontoVendidoPlatos, double *arrDescuentoPlatoPlatos,
            double *arrDescuentoClientePlatos, double *arrTotalIngresadoPlatos);

#endif /* FUNCIONES_H */

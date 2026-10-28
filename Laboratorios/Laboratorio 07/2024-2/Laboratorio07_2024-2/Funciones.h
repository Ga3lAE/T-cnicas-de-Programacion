/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 4 de junio de 2025, 12:23 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//LECTURA
char *leeCadena(ifstream &archivo, int tam);
void eliminaEspacios(char *texto);
void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *arrDni, char **arrNombre, char **arrVehiculo, 
        int *arrCodigoDistrito, char **arrNombreDistrito);
void leePlatos(const char *nombreArchivo, int &cantidad,
        int *arrCodigo, char **arrNombre, char **arrCategoria, 
        double *arrPrecio, double *arrDescuento);
void verificaLectura(const char *nombreArchivo,
        int cantidadRepartidores, 
        int *arrDniRepartidor, char **arrNombreRepartidor, char **arrVehiculoRepartidor, 
        int *arrCodigoDistritoRepartidor, char **arrNombreDistritoRepartidor, 
        int cantidadPlatos,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato, 
        double *arrPrecioPlato, double *arrDescuentoPlato);
void leeRepartos(const char *nombreArchivo,
        int cantidadRepartidores, 
        char **arrVehiculoRepartidor, int *arrCodigoDistritoRepartidor,
        int *arrTotalPlatosRepartidor, double *arrMontoTotalPlatosRepartidor, 
        double *arrDescuentoPlatosRepartidor, double *arrDescuentoClienteRepartidor, 
        double *arrPagoRepartidor, double *arrTotalIngresadoRepartidor, 
        int cantidadPlatos,
        int *arrCodigoPlato, double *arrPrecioPlato, double *arrDescuentoPlato, 
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato);
void procesaRepartidor(int &totalPlatosRepartidor, double &montoTotalPlatosRepartidor,
        double &descuentoPlatosRepartidor, double &descuentoClienteRepartidor,
        double &pagoRepartidor, double &totalIngresadoRepartidor,
        int cantidadPedida, double precioPlato, double descuentoPlato, 
        double descuentoCliente, const char *vehiculo);
void procesaPlato(int &cantidadPlato, double &montoVendidoPlato, double &descuentoAlPlato,
        double &descuentoAlCliente, double &totalIngresadoPlato,
        int cantidadPedida, double precioPlato, 
        double descuentoPlato, double descuentoCliente);

//BUSQUEDA
int buscaIntCad(int *arrInt, char **arrCad, int cantidad,
        int codigo, char *cad);
int buscaInt(int *arr, int cantidad, int codigo);
//ORDENAMIENTO
void ordenaRepartidores(int cantidadRepartidores, char **arrNombreRepartidor,
        int *arrDniRepartidor, char **arrVehiculoRepartidor,
        int *arrCodigoDistritoRepartidor, char **arrNombreDistritoRepartidor);
void ordenaPlatos(int cantidad,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato,
        double *arrPrecioPlato, double *arrDescuentoPlato,
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato);
void cambiaInt(int &dato1, int &dato2);
void cambiaDouble(double &dato1, double &dato2);
void cambiaCadChar(char *&cad1, char *&cad2);

//IMPRESION
void imprimeLinea(ofstream &archivo, char c);
void emiteReportePlatos(const char *nombreArchivo,
        int cantidad,
        int *arrCodigoPlato, char **arrNombrePlato, char **arrCategoriaPlato,
        double *arrPrecioPlato, double *arrDescuentoPlato,
        int *arrCantidadPlato, double *arrMontoVendidoPlato, double *arrDescuentoAlPlato,
        double *arrDescuentoAlCliente, double *arrTotalIngresadoPlato);
void emiteReporteRepartidores(const char *nombreArchivo, int cantidad,
        int *arrDniRepartidor, char **arrNombreRepartidor, char **arrVehiculoRepartidor,
        char **arrNombreDistritoRepartidor, int *arrTotalPlatosRepartidor, 
        double *arrMontoTotalPlatosRepartidor, double *arrDescuentoPlatosRepartidor, 
        double *arrDescuentoClienteRepartidor, double *arrPagoRepartidor, 
        double *arrTotalIngresadoRepartidor);
double sumaArrDouble(double *arr, int cantidad);


#endif /* FUNCIONES_H */

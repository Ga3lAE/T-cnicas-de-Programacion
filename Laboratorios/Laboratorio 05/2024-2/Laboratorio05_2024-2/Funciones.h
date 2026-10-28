/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 10 de mayo de 2025, 11:37 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimeLinea(ofstream &archivo, char c);


//BUSQUEDA
int buscaRepartidor(int cantidadRepartidores,
        char *vehiculosRepartidores, char vehiculoActual,
        int *codigosDistritosRepartidores, int codigoDistritoActual);
int buscaPlato(int cantidadPlatos,
        int *codigosPlatos, int codigoPlatoPedido);
//LECTURA
void leeRepartidores(const char *nombreArchivo, int &cantidad,
        int *dnis, char *vehiculos, int *codigosDistritos);
void leePlatos(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios, double *descuentos);
//VERIFICACION DE LECTURA
void verificaLecturas(const char *nombreArchvo, 
        int cantidadRepartidores,
        int *dnis, char *vehiculos, int *codigosDistritos, 
        int cantidadPlatos,
        int *codigos, double *precios, double *descuentos);

//ASIGNACION
void asignaRepartos(const char *nombreArchivo, 
            //los repartidores (arreglos y estadisticas finales)
            int cantidadRepartidores,  
            int *codigosDistritosRepartidores, int *totalesPlatosRepartidores, 
            char *vehiculosRepartidores, 
            double *montosTotalesPlatosRepartidores, double *descuentosPlatosRepartidores, 
            double *descuentosClientesRepartidores, double *pagosRepartidoresRepartidores, 
            double *totalesIngresadosRepartidores, 
            int &sumaTotalesPlatosRepartidores, 
            double &sumaMontosTotalesPlatosRepartidores, double &sumaDescuentosPlatosRepartidores, 
            double &sumaDescuentosClientesRepartidores, double &sumaPagosRepartidoresRepartidores, 
            double &sumaTotalesIngresadosRepartidores, 
            //los platos (arreglos y estadisticas finales)
            int cantidadPlatos, 
            int *codigosPlatos, int *cantidadesPlatos, 
            double *preciosPlatos, double *descuentosPlatos, 
            double *montosVendidosPlatos, double *descuentosPlatosPlatos, 
            double *descuentosClientesPlatos,double *totalesIngresadosPlatos, 
            int &sumaCantidadesPlatos, 
            double &sumaMontosVendidosPlatos, double &sumaDescuentosPlatosPlatos, 
            double &sumaDescuentosClientesPlatos, double &sumaTotalesIngresadosPlatos);
void asignaPlatos(int &totalPlatoRepartidor,
        double &montoTotalePlatoRepartidor,
        double &descuentoPlatoRepartidor,
        double &descuentoClienteRepartidor,
        double &pagoRepartidoresRepartidor,
        double &totalIngresadoRepartidor,
        int &sumaTotalPlatosRepartidor,
        double &sumaMontoTotalPlatoRepartidor,
        double &sumaDescuentoPlatoRepartidor,
        double &sumaDescuentoClienteRepartidor,
        double &sumaPagoRepartidoresRepartidor,
        double &sumaTotalIngresadoRepartidor,
        int &cantidadPlatos,
        double &montoVendidoPlato,
        double &descuentoPlatoPlato,
        double &descuentoClientePlato,
        double &totalIngresadoPlato,
        int &sumaCantidadPlatos,
        double &sumaMontoVendidoPlatos,
        double &sumaDescuentoPlatoPlatos,
        double &sumaDescuentoClientePlatos,
        double &sumaTotalIngresadoPlato,
        double descuentoCliente, double descuentoPlato,
        double precioPlato, int cantidadPlatosPedida, 
        char vehiculoRepartidor);
void leeDescuento(ifstream &archivo, double &descuento);

//IMPRESION
void imprimeReporteRepartidores(const char* nombreArchivoReporte, 
        const char*nombreArchivoNombres,
        int cantidadRepartidores,
        int *dnisRepartidores, char *vehiculosRepartidores, int *codigosDistritosRepartidores,
        int *totalesPlatosRepartidores, double *montosTotalesPlatosRepartidores,
        double *descuentosPlatosRepartidores, double *descuentosClientesRepartidores,
        double *pagosRepartidoresRepartidores, double *totalesIngresadosRepartidores,
        int sumaTotalesPlatosRepartidores, double sumaMontosTotalesPlatosRepartidores,
        double sumaDescuentosPlatosRepartidores, double sumaDescuentosClientesRepartidores,
        double sumaPagosRepartidoresRepartidores, double sumaTotalesIngresadosRepartidores);

void imprimeNombre(ifstream &archivoLectura, ofstream &archivoReporte, int codigo);
void imprimeVehiculo(ofstream &archivo, char vehiculo);
void imprimeReportePlatos(const char* nombreArchivoReporte, 
        const char*nombreArchivoNombres,
        int cantidadPlatos,
        int *codigosPlatos, double *preciosPlatos, double *descuentosPlatos, 
        int *cantidadesPlatos, double *montosVendidosPlatos, 
        double *descuentosPlatosPlatos, 
        double *descuentosClientesPlatos, 
        double *totalesIngresadosPlatos, 
        int sumaCantidadesPlatos, double sumaMontosVendidosPlatos, 
        double sumaDescuentosPlatosPlatos, 
        double sumaDescuentosClientesPlatos, 
        double sumaTotalesIngresadosPlatos);

#endif /* FUNCIONES_H */

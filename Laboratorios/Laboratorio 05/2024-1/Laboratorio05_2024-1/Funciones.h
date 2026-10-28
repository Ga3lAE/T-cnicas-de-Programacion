/* 
 * File:   Funciones.h
 * Author: arias
 *
 * Created on 10 de mayo de 2025, 04:07 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//IMPRESION GENERAL
void imprimeLinea(ofstream &archivo, char c);
//BUSQUEDA
int buscaInt(int *arreglo, int cantidad, int elemento);
//LECTURA Y CONFIRMACION
void leeMedicos(const char *nombreArchivo, int &cantidad,
        int *codigos, double *tarifas);
void leeMedicinas(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios);
void verificaLecturas(const char *nombreArchivo,
        int cantidadMedicos, int *codigosMedicos, double *tarifasMedicos,
        int cantidadMedicinas, int *codigosMedicinas, double *preciosMedicinas);

//PROCESAMIENTO DE DATOS
void procesaCitas(const char *nombreArchivo,
        //datos de los medicos
        int cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos,
        double *ingresosCitasMedicos, double *ingresosMedicinasMedicos,
        double *totalesIngresadosMedicos, int *cantidadPacientesMedicinasMedicos,
        int *cantidadPacientesSinMedicinasMedicos, int *cantidadPacientesMedicos,
        //datos de las medicinas
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas);
void procesaMedico(ifstream &archivo,
        double tarifaMedico, double &ingresoCitasMedico,
        double &ingresoMedicinasMedico, double &totalIngresadoMedico,
        int &cantidadPacientesMedicinasMedico, 
        int &cantidadPacientesSinMedicinasMedico,
        int &cantidadPacientesMedico,
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas, 
        int duracion, double descuentoPaciente);

void procesaMedicinas(ifstream &archivo, 
        double &ingresoMedicinasMedico, double &totalIngresadoMedico, 
        int cantidadMedicinas, 
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas,
        double descuentoPaciente);
void leeHora(ifstream& archivo, int& hora);

//IMPRESION
void imprimeIngresosMedicos(ofstream &archivoReporte, int cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos, double *ingresosCitasMedicos, 
        double *ingresosMedicinasMedicos, double *totalesIngresadosMedicos, 
        int *cantidadesPacientesMedicinasMedicos, int *cantidadesPacientesSinMedicinasMedicos, 
        int *cantidadesPacientesMedicos);
void imprimeEncabezadoMedicos(ofstream &archivo);
void imprimeTotalesMedicos(ofstream &archivoReporte, int cantidadMedicos, 
        double *ingresosCitasMedicos, double *ingresosMedicinasMedicos,
        double *totalesIngresadosMedicos, int *cantidadesPacientesMedicinasMedicos,
        int *cantidadesPacientesSinMedicinasMedicos, int *cantidadesPacientesMedicos);

void imprimeIngresosMedicinas(ofstream& archivoReporte, int cantidadMedicinas, 
        int* codigosMedicinas, double* preciosMedicinas, 
        int* cantidadesVendidasMedicinas, double* ingresosNoDescuentosMedicinas, 
        double* descuentosSegurosMedicinas, double* totalesIngresadosMedicinas);
void imprimeEncabezadoMedicinas(ofstream& archivo);
void imprimeTotalesMedicinas(ofstream& archivoReporte, int cantidadMedicinas, 
        int* cantidadesVendidasMedicinas, double* ingresosNoDescuentosMedicinas, 
        double* descuentosSegurosMedicinas, double* totalesIngresadosMedicinas);

double sumaArrDouble(double* arr, int cantidad);
int sumaArrInt(int* arr, int cantidad);

void filtraMedicos(int &cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos, double *ingresosCitasMedicos, 
        double *ingresosMedicinasMedicos, double *totalesIngresadosMedicos, 
        int *cantidadesPacientesMedicinasMedicos, int *cantidadesPacientesSinMedicinasMedicos, 
        int *cantidadesPacientesMedicos,  double promedioIngresos);
void cambiarDouble(double& dato1, double& dato2);
void cambiarInt(int& dato1, int& dato2);

#endif /* FUNCIONES_H */

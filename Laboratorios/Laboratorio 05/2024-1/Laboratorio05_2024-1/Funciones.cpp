/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 10 de mayo de 2025, 04:07 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_CAR_COD 10
#define MAX_CAR_DIN 20
#define MAX_CAR_CONT 5
#define MAX_CAR_CANT 20

//IMPRESION GENERAL
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
//BUSQUEDA
int buscaInt(int *arreglo, int cantidad, int elemento){
    for (int i = 0; i < cantidad; i++)
        if(arreglo [i] == elemento) return i;
    return NO_ENCONTRADO;
}
//LECTURA Y CONFIRMACION
void leeMedicos(const char *nombreArchivo, int &cantidad,
        int *codigos, double *tarifas){

    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        archivo>>codigos[cantidad];
        if(archivo.eof()) break;
        for (int i = 0; i < 2; i++)
            while(archivo.get()!='/');
        archivo>>ws;
        while(archivo.get()!=' ');
        archivo>>tarifas[cantidad];
        
        cantidad++;
    }
}
void leeMedicinas(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios){

    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        archivo>>codigos[cantidad];
        if(archivo.eof()) break;
        archivo>>ws;
        while(archivo.get()!=' ');
        archivo>>precios[cantidad];
        
        cantidad++;
    }
}
void verificaLecturas(const char *nombreArchivo,
        int cantidadMedicos, int *codigosMedicos, double *tarifasMedicos,
        int cantidadMedicinas, int *codigosMedicinas, double *preciosMedicinas){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE MEDICOS"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DIN)<<"TARIFA"
            <<endl;
    
    imprimeLinea(archivo, '=');    
    for (int i = 0; i < cantidadMedicos; i++) {        
        archivo<<left
                <<right<<setw(MAX_CAR_COD/2)<<codigosMedicos[i]<<left<<setw(MAX_CAR_COD/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<tarifasMedicos[i]<<left<<setw(MAX_CAR_COD/2)<<' '
                <<endl;        
    }
    imprimeLinea(archivo, '='); 
    
    archivo<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE MEDICINAS"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_DIN)<<"PRECIO"
            <<endl;
    
    imprimeLinea(archivo, '=');    
    for (int i = 0; i < cantidadMedicinas; i++) {        
        archivo<<left
                <<right<<setw(MAX_CAR_COD/2)<<codigosMedicinas[i]<<left<<setw(MAX_CAR_COD/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<preciosMedicinas[i]<<left<<setw(MAX_CAR_COD/2)<<' '
                <<endl;        
    }
    imprimeLinea(archivo, '=');    

}

//PROCESAMIENTO DE DATOS
void procesaCitas(const char *nombreArchivo,
        //datos de los medicos
        int cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos,
        double *ingresosCitasMedicos, double *ingresosMedicinasMedicos,
        double *totalesIngresadosMedicos, int *cantidadesPacientesMedicinasMedicos,
        int *cantidadesPacientesSinMedicinasMedicos, int *cantidadesPacientesMedicos,
        //datos de las medicinas
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivo;
        exit(1);
    }
    
    double descuentoPaciente;
    int horaInicio, horaFin, duracion, codigoMedicoAtencion;
    while(true){
        int descI;
        archivo>>descI;
        if(archivo.eof())break;
        while(archivo.get()!=' ');
        archivo>>descI>>descuentoPaciente;
        leeHora(archivo, horaInicio);
        leeHora(archivo, horaFin);
        duracion = horaFin-horaInicio;
        archivo>>codigoMedicoAtencion;
        int posMedico = buscaInt(codigosMedicos, cantidadMedicos, codigoMedicoAtencion);
        if(posMedico == NO_ENCONTRADO){
            while(archivo.get()!='\n');
        }
        else
            procesaMedico(archivo,
                    tarifasMedicos[posMedico], ingresosCitasMedicos[posMedico], 
                    ingresosMedicinasMedicos[posMedico], totalesIngresadosMedicos[posMedico], 
                    cantidadesPacientesMedicinasMedicos[posMedico], 
                    cantidadesPacientesSinMedicinasMedicos[posMedico], 
                    cantidadesPacientesMedicos[posMedico],
                    cantidadMedicinas, 
                    codigosMedicinas, preciosMedicinas, 
                    cantidadesVendidasMedicinas, ingresosNoDescuentosMedicinas, 
                    descuentosSegurosMedicinas, totalesIngresadosMedicinas, 
                    duracion, descuentoPaciente);
        
    }
    
}
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
        int duracion, double descuentoPaciente){    
    //como entontramos al medico, preocesamos sus datos respectivos
    double ingresoCita;
    ingresoCita = tarifaMedico*duracion/3600.0*(100-descuentoPaciente)/100.0;

    cantidadPacientesMedico++;
    ingresoCitasMedico+= ingresoCita;
    totalIngresadoMedico+= ingresoCita;

    if (archivo.get() != '\n') { // le recetaron medicinas
        cantidadPacientesMedicinasMedico++;
        procesaMedicinas(archivo, 
                ingresoMedicinasMedico, totalIngresadoMedico, 
                cantidadMedicinas, codigosMedicinas, preciosMedicinas, 
                cantidadesVendidasMedicinas, ingresosNoDescuentosMedicinas, 
                descuentosSegurosMedicinas, totalesIngresadosMedicinas, 
                descuentoPaciente);

    } 
    else { // no le recetaron medicina
        cantidadPacientesSinMedicinasMedico++;
    }


}
void procesaMedicinas(ifstream &archivo, 
        double &ingresoMedicinasMedico, double &totalIngresadoMedico, 
        int cantidadMedicinas, 
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas,
        double descuentoPaciente){
    int codigoMedicinaRecetada, cantidadMedicinaRecetada;

    double ingresoMedicina = 0;
    while (true) {
        if (archivo.get() == '\n')break;
        archivo >> codigoMedicinaRecetada>>cantidadMedicinaRecetada;
        int posMedicina = buscaInt(codigosMedicinas, cantidadMedicinas, codigoMedicinaRecetada);
        if (posMedicina != NO_ENCONTRADO) {
            // como existe la medicina, procesamos sus datos respectivos
            cantidadesVendidasMedicinas[posMedicina] += cantidadMedicinaRecetada;
            

            double ingresoSinDescuentoMedicina = preciosMedicinas[posMedicina]*cantidadMedicinaRecetada, 
                    descuentoMedicina = ingresoSinDescuentoMedicina*(descuentoPaciente/200.0);
            
            ingresoMedicina = ingresoSinDescuentoMedicina-descuentoMedicina;
            
            ingresosNoDescuentosMedicinas[posMedicina]+=ingresoSinDescuentoMedicina;
            descuentosSegurosMedicinas[posMedicina]+=descuentoMedicina;
            totalesIngresadosMedicinas[posMedicina]+=ingresoMedicina;
        }
    }
    
    ingresoMedicinasMedico+= ingresoMedicina;
    totalIngresadoMedico+= ingresoMedicina;
}
void leeHora(ifstream &archivo, int &hora){
    int hh, mm, ss;
    char sep;
    archivo>>hh>>sep>>mm>>sep>>ss;

    hora = hh*3600+mm*60+ss;
}

//IMPRESION
void imprimeIngresosMedicos(ofstream &archivoReporte, int cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos, double *ingresosCitasMedicos, 
        double *ingresosMedicinasMedicos, double *totalesIngresadosMedicos, 
        int *cantidadesPacientesMedicinasMedicos, int *cantidadesPacientesSinMedicinasMedicos, 
        int *cantidadesPacientesMedicos){
    
    imprimeEncabezadoMedicos(archivoReporte);
    for (int i = 0; i < cantidadMedicos; i++) {        
        archivoReporte<<left
                <<setw(MAX_CAR_CONT)<<i+1
                <<setw(MAX_CAR_COD)<<codigosMedicos[i]
                <<right<<setw(MAX_CAR_DIN/2)<<tarifasMedicos[i]<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<ingresosCitasMedicos[i]<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<ingresosMedicinasMedicos[i]<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalesIngresadosMedicos[i]<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<cantidadesPacientesMedicinasMedicos[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<cantidadesPacientesSinMedicinasMedicos[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<cantidadesPacientesMedicos[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<endl;
    }
    imprimeTotalesMedicos(archivoReporte, cantidadMedicos,
            ingresosCitasMedicos, ingresosMedicinasMedicos, 
            totalesIngresadosMedicos, cantidadesPacientesMedicinasMedicos, 
            cantidadesPacientesSinMedicinasMedicos, cantidadesPacientesMedicos);

}
void imprimeEncabezadoMedicos(ofstream &archivo){
    
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"REGISTRO DE INGRESOS POR MEDICO"<<endl;
    imprimeLinea(archivo, '=' );
    archivo<<left
              <<setw(MAX_CAR_CONT)<<"No."
              <<setw(MAX_CAR_COD)<<"CODIGO"
              <<setw(MAX_CAR_DIN)<<"TARIFA"
              <<setw(MAX_CAR_DIN)<<"INGRESO CITA"
              <<setw(MAX_CAR_DIN)<<"INGRESO MEDICINAS"
              <<setw(MAX_CAR_DIN)<<"TOTAL INGRESO"
              <<setw(MAX_CAR_CANT)<<"PACIENTES MEDICINA"
              <<setw(MAX_CAR_CANT)<<"PACIENTES  MEDICINA"
              <<setw(MAX_CAR_CANT)<<"TOTAL PACIENTES"
              <<endl;
    
}
void imprimeTotalesMedicos(ofstream &archivoReporte, int cantidadMedicos, 
        double *ingresosCitasMedicos, double *ingresosMedicinasMedicos,
        double *totalesIngresadosMedicos, int *cantidadesPacientesMedicinasMedicos,
        int *cantidadesPacientesSinMedicinasMedicos, int *cantidadesPacientesMedicos){
     
    imprimeLinea(archivoReporte, '=');
    
    double totalIngresosCitasMedicos = sumaArrDouble(ingresosCitasMedicos, cantidadMedicos), 
            totalIngresosMedicinasMedicos = sumaArrDouble(ingresosMedicinasMedicos, cantidadMedicos), 
            totalTotalesIngresadosMedicos = sumaArrDouble(totalesIngresadosMedicos, cantidadMedicos);
    int totalCantidadesPacientesMedicinasMedicos = sumaArrInt(cantidadesPacientesMedicinasMedicos, cantidadMedicos), 
            totalCantidadesPacientesSinMedicinasMedicos = sumaArrInt(cantidadesPacientesSinMedicinasMedicos, cantidadMedicos),
            totalCantidadesPacientesMedicos = sumaArrInt(cantidadesPacientesMedicos, cantidadMedicos);
    
    archivoReporte<<left
                <<setw(MAX_CAR_CONT+MAX_CAR_COD+MAX_CAR_DIN)<<' '              
                <<right<<setw(MAX_CAR_DIN/2)<<totalIngresosCitasMedicos<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalIngresosMedicinasMedicos<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalTotalesIngresadosMedicos<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<totalCantidadesPacientesMedicinasMedicos<<setw(MAX_CAR_CANT/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<totalCantidadesPacientesSinMedicinasMedicos<<setw(MAX_CAR_CANT/2)<<' '
                <<right<<setw(MAX_CAR_CANT/2)<<totalCantidadesPacientesMedicos<<setw(MAX_CAR_CANT/2)<<' '
                <<endl;
}
void imprimeIngresosMedicinas(ofstream &archivoReporte, int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas){
    
    imprimeEncabezadoMedicinas(archivoReporte);
    for (int i = 0; i < cantidadMedicinas; i++) {
        archivoReporte << left
                << setw(MAX_CAR_CONT) << i + 1
                << setw(MAX_CAR_COD) << codigosMedicinas[i]
                << right << setw(MAX_CAR_DIN / 2) << preciosMedicinas[i] << setw(MAX_CAR_DIN / 2) << ' '
                << right << setw(MAX_CAR_CANT / 2) << cantidadesVendidasMedicinas[i] << setw(MAX_CAR_CANT / 2) << ' '
                << right << setw(MAX_CAR_DIN / 2) << ingresosNoDescuentosMedicinas[i] << setw(MAX_CAR_DIN / 2) << ' '
                << right << setw(MAX_CAR_DIN / 2) << descuentosSegurosMedicinas[i] << setw(MAX_CAR_DIN / 2) << ' '
                << right << setw(MAX_CAR_DIN / 2) << totalesIngresadosMedicinas[i] << setw(MAX_CAR_DIN / 2) << ' '                
                << endl;
    }
    imprimeTotalesMedicinas(archivoReporte, cantidadMedicinas,
            cantidadesVendidasMedicinas, ingresosNoDescuentosMedicinas,
            descuentosSegurosMedicinas, totalesIngresadosMedicinas);   
}
void imprimeEncabezadoMedicinas(ofstream &archivo){
    
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"REGISTRO DE INGRESOS POR MEDICINAS"<<endl;
    imprimeLinea(archivo, '=' );
    archivo<<left
              <<setw(MAX_CAR_CONT)<<"No."
              <<setw(MAX_CAR_COD)<<"CODIGO"
              <<setw(MAX_CAR_DIN)<<"PRECIO"
              <<setw(MAX_CAR_CANT)<<"UNIDADES VENDIDAS"
              <<setw(MAX_CAR_DIN)<<"INGRESOS NO DESC"
              <<setw(MAX_CAR_DIN)<<"DESCUENTOS"
              <<setw(MAX_CAR_DIN)<<"TOTAL INGRESADO"              
              <<endl;
    
}
void imprimeTotalesMedicinas(ofstream &archivoReporte, int cantidadMedicinas, 
        int *cantidadesVendidasMedicinas, double *ingresosNoDescuentosMedicinas,
        double *descuentosSegurosMedicinas, double *totalesIngresadosMedicinas){
     
    imprimeLinea(archivoReporte, '=');
    
    double totalIngresosCitasNoDescuentosMedicinas = sumaArrDouble(ingresosNoDescuentosMedicinas, cantidadMedicinas), 
            totalDescuentosMedicinas = sumaArrDouble(descuentosSegurosMedicinas, cantidadMedicinas), 
            totalTotalesIngresadosMedicinas = sumaArrDouble(totalesIngresadosMedicinas, cantidadMedicinas);
    int totalCantidadesVendidasMedicamentos = sumaArrInt(cantidadesVendidasMedicinas, cantidadMedicinas);   
    
    archivoReporte<<left
                <<setw(MAX_CAR_CONT+MAX_CAR_COD+MAX_CAR_DIN)<<"TOTALES OBTENIDOS:"              
                <<right<<setw(MAX_CAR_DIN/2)<<totalCantidadesVendidasMedicamentos<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalIngresosCitasNoDescuentosMedicinas<<setw(MAX_CAR_DIN/2)<<' '
                <<right<<setw(MAX_CAR_DIN/2)<<totalDescuentosMedicinas<<setw(MAX_CAR_DIN/2)<<' '                                
                <<right<<setw(MAX_CAR_DIN/2)<<totalTotalesIngresadosMedicinas<<setw(MAX_CAR_DIN/2)<<' '
                <<endl;
}

double sumaArrDouble(double *arr, int cantidad){
    double total=0;
    for (int i = 0; i < cantidad; i++) {        
        total+=arr[i];
    }
    return total;
}
int sumaArrInt(int *arr, int cantidad){
    int total=0;
    for (int i = 0; i < cantidad; i++) {        
        total+=arr[i];
    }
    return total;
}

//FILTRAMOS LOS DATOS
void filtraMedicos(int &cantidadMedicos,
        int *codigosMedicos, double *tarifasMedicos, double *ingresosCitasMedicos, 
        double *ingresosMedicinasMedicos, double *totalesIngresadosMedicos, 
        int *cantidadesPacientesMedicinasMedicos, int *cantidadesPacientesSinMedicinasMedicos, 
        int *cantidadesPacientesMedicos,  
        double promedioIngresos){
    
    for (int i =cantidadMedicos-1; i>=0; i--) {        
        if(totalesIngresadosMedicos[i]<promedioIngresos){
            for (int j = i; j < cantidadMedicos-1; j++) {
                codigosMedicos[j] = codigosMedicos[j+1];
                tarifasMedicos[j] = tarifasMedicos[j+1];
                ingresosCitasMedicos[j] = ingresosCitasMedicos[j+1];
                ingresosMedicinasMedicos[j] = ingresosMedicinasMedicos[j+1];
                totalesIngresadosMedicos[j], totalesIngresadosMedicos[j+1];
                cantidadesPacientesMedicinasMedicos[j] = cantidadesPacientesMedicinasMedicos[j+1];
                cantidadesPacientesSinMedicinasMedicos[j], cantidadesPacientesSinMedicinasMedicos[j+1];
                cantidadesPacientesMedicos[j], cantidadesPacientesMedicos[j+1];
            }                      
            cantidadMedicos--;
        }
    }   
}
void cambiarInt(int &dato1, int&dato2){
    int aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}
void cambiarDouble(double &dato1, double &dato2){
    double aux;
    aux = dato1;
    dato1=dato2;
    dato2=aux;
}
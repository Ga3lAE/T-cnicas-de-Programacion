/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 18 de mayo de 2025, 05:08 PM
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
#define MAX_CAR_ANIO 12
#define MAX_CAR_DESC 14
#define MAX_CAR_DIN 18
#define MAX_CAR_CANT 18
#define MAX_CAR_CLAS 16

//LECTURA
void saltaTextoUnDel(ifstream &archivo, char del){
    archivo>>ws;
    while(archivo.get()!=del);
}
void leePacientes(const char *nombreArchivo, int &cantidad,
        int *dnis, int *distritos, int *anios,
        double *porcentajesDescuentos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    cantidad=0;
    
    while(true){
        //57182371     [GONZALO  VEGA MUNOZ]   15068   1955   35.11
        archivo>>dnis[cantidad];
        if(archivo.eof()) break;
        saltaTextoUnDel(archivo, ']');
        archivo>>distritos[cantidad]
                >>anios[cantidad]
                >>porcentajesDescuentos[cantidad];
        
        cantidad++;
    }
    
}
void leeMedicinas(const char *nombreArchivo, int &cantidad,
        int *codigos, double *precios){
     ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    cantidad=0;
    
    while(true){
        //95196 DIGOXINA_0.250_MG_C/24   62.05
        archivo>>codigos[cantidad];
        if(archivo.eof()) break;
        saltaTextoUnDel(archivo, ' ');
        archivo>>precios[cantidad];
        
        cantidad++;
    }
}

//BUSQUEDA  
int buscaInt(int *arr, int can, int el){
    for (int i = 0; i < can; i++) {        
        if(arr[i] == el) return i;
    }
    return NO_ENCONTRADO;

}
//PROCESAMOS
void procesaCitas(const char *nombreArchivo,
        int cantidadPacientes,
        int *dnisPacientes, double *porcentajesDescuentosPacientes,
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas,
        int *cantidadesCitasPacientes, int *cantidadesMedicinasPacientes,
        double *pagosMedicinasPacientes){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int descI, dniActual;
    while(true){
        //9/9/2023   94683380   11:17:52   12:48:30   40414   28409   5
        archivo>>descI;
        if(archivo.eof()) break;
        saltaTextoUnDel(archivo, ' ');
        archivo>>dniActual;
                
        int posPaciente = buscaInt(dnisPacientes, cantidadPacientes, dniActual);
        if(posPaciente == NO_ENCONTRADO)
            while(archivo.get()!='\n');
        else{
            // existe el paciente y tiene una cita mas
            cantidadesCitasPacientes[posPaciente]++;
            //saltamos los dos datos siguientes como si fueran caracteres
            for (int i = 0; i < 2; i++) saltaTextoUnDel(archivo, ' ');
            // no podemos saltar el ultimo porque puede no tener mediciinas recetados y del != ' ' sino del == '\n'
            archivo>>descI;
            
            int codMedicinaActual, cantidadRecetada;
            while(true){
                if(archivo.get()=='\n') break;
                archivo>>codMedicinaActual>>cantidadRecetada;
                
                int posMedicina = buscaInt(codigosMedicinas, cantidadMedicinas, codMedicinaActual);
                if(posMedicina != NO_ENCONTRADO){
                    cantidadesMedicinasPacientes[posPaciente]+=cantidadRecetada;
                    pagosMedicinasPacientes[posPaciente] += 
                            cantidadRecetada*preciosMedicinas[posMedicina]*(1-porcentajesDescuentosPacientes[posPaciente]/200.0);
                }
            }

        }
        
        
    }
}

void asignaCalificacionesYOrdena(int cantidad, 
        int *dnis, int *distritos, int *aniosNacimiento, 
        double *porcentajesDescuentos, char *clasficicaciones, 
        int *cantidadesCitas, int *cantidadesMedicinas,
        double *pagosMedicinas){
    //en primer lugar asignamos
    for (int i = 0; i < cantidad; i++) {        
        if(aniosNacimiento[i]>=2019)
            clasficicaciones[i] = 'A';
        else if (aniosNacimiento[i]>=2013)
            clasficicaciones[i] = 'B';
        else if (aniosNacimiento[i] >= 2006)
            clasficicaciones[i] = 'C';
        else if (aniosNacimiento[i] >= 1998)
            clasficicaciones[i] = 'D';
        else if (aniosNacimiento[i] >= 1965)
            clasficicaciones[i] = 'E';
        else 
            clasficicaciones[i] = 'F';
    }
    
    for (int i = 0; i < cantidad-1; i++) {
        for (int j = i+1; j < cantidad; j++) {
            if(clasficicaciones[i]>clasficicaciones[j] 
                    or
                    (clasficicaciones[i]==clasficicaciones[j] 
                        and 
                    distritos[i]<distritos[j])){
                cambiaInt(dnis[i], dnis[j]);
                cambiaInt(distritos[i], distritos[j]);
                cambiaInt(aniosNacimiento[i], aniosNacimiento[j]);
                cambiaDouble(porcentajesDescuentos[i], porcentajesDescuentos[j]);
                cambiaChar(clasficicaciones[i], clasficicaciones[j]);
                cambiaInt(cantidadesCitas[i], cantidadesCitas[j]);
                cambiaInt(cantidadesMedicinas[i], cantidadesMedicinas[j]);
                cambiaDouble(pagosMedicinas[i], pagosMedicinas[j]);
            }

        }


    }


}
void cambiaInt(int &d1, int&d2){
    int aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}
void cambiaChar(char&d1, char &d2){
    char aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}
void cambiaDouble(double &d1, double &d2){
    double aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void verificaLecturas(const char *nombreArchivo,
        int cantidadPacientes,
        int *dnisPacientes, int *distritosPacientes, int *aniosNacimientoPacientes,
        double *porcentajesDescuentosPacientes,
        int cantidadMedicinas,
        int *codigosMedicinas, double *preciosMedicinas){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_CAR_LIN/2)<<"VERFICACION DE LECTURA"<<endl
            <<right<<setw(MAX_CAR_LIN/2)<<"PACIENTES"<<endl;
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_COD)<<"DISTRITO"
            <<setw(MAX_CAR_ANIO)<<"NACIMIENTO"
            <<setw(MAX_CAR_DESC)<<"DESCUENTO %"
            <<endl;
    
    for (int i = 0; i < cantidadPacientes; i++) {
        archivo << left
                << setw(MAX_CAR_COD) <<dnisPacientes[i]
                << setw(MAX_CAR_COD) <<distritosPacientes[i]
                << setw(MAX_CAR_ANIO) << aniosNacimientoPacientes[i]
                << setw(MAX_CAR_DESC) <<porcentajesDescuentosPacientes[i]
                << endl;

    }

    imprimeLinea(archivo, '=');
    archivo<<right<<setw(MAX_CAR_LIN/2)<<"MEDICINAS"<<endl;
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"           
            <<setw(MAX_CAR_DESC)<<"PRECIO"
            <<endl;
    
    for (int i = 0; i < cantidadMedicinas; i++) {
        archivo << left
                << setw(MAX_CAR_COD) <<codigosMedicinas[i]
                << setw(MAX_CAR_DIN) <<preciosMedicinas[i]                
                << endl;

    }
}
void emiteReporte(const char *nombreArchivo, int cantidad, 
            char *clasficicaciones, int *distritos, 
            int *dnis, double *porcentajesDescuentos, 
            int *cantidadesCitas, int *cantidadesMedicinas, 
            double *pagosMedicinas){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE SALUD VENUS S.A."<<endl;
    imprimeLinea(archivo, '=');
    archivo<<setw(MAX_CAR_LIN/2)<<"CONSOLIDADE DE ATENCION A LOS CLINTES"<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_CAR_CLAS)<<"CLASIFICACION"
            <<setw(MAX_CAR_COD)<<"DISITRITO"
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_DESC)<<"%DESCUENTO"
            <<setw(MAX_CAR_CANT)<<"CANT CITAS"
            <<setw(MAX_CAR_CANT)<<"CANT MEDICINAS"
            <<setw(MAX_CAR_DIN)<<"PAGO MEDICINAS"
            <<endl;
    
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
            <<right<<setw(MAX_CAR_CLAS/2)<<clasficicaciones[i]<<setw(MAX_CAR_CLAS/2)<<' '
            <<left<<setw(MAX_CAR_COD)<<distritos[i]
            <<setw(MAX_CAR_COD)<<dnis[i]
            <<right<<setw(MAX_CAR_DESC/2)<<porcentajesDescuentos[i]<<left<<setw(MAX_CAR_DESC/2)<<'%'
            <<right<<setw(MAX_CAR_CANT/2)<<cantidadesCitas[i]<<setw(MAX_CAR_CANT/2)<<' '
            <<right<<setw(MAX_CAR_CANT/2)<<cantidadesMedicinas[i]<<setw(MAX_CAR_CANT/2)<<' '            
            <<right<<setw(MAX_CAR_DIN/2)<<pagosMedicinas[i]<<setw(MAX_CAR_DIN/2)<<' '
            <<endl;
    }   
    
    imprimeLinea(archivo, '=');
    archivo<<left<<"RESUMEN"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left<<"PAGO TOTAL POR MEDICINAS: "<<sumaArrDouble(pagosMedicinas, cantidad)<<endl;;
    
}
double sumaArrDouble(double *arr, int cant){
    double total = 0;
    
    for (int i = 0; i < cant; i++) {        
        total+=arr[i];
    }
    
    return total;

}
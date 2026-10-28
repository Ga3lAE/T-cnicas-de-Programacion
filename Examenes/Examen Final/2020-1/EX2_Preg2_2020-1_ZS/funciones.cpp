

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 12:44 AM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

#define MAX_LINE 150
#define NO_ENCONTRADO -1
#include "StructCliente.h"
#include "funciones.h"


void crearClientesBin(const char *nombArchBin,const char *nombArchCsv){
    ofstream archClientesBin(nombArchBin,ios::out | ios::binary);
    if(not archClientesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }  
    ifstream archClientes(nombArchCsv,ios::in | ios::binary);
    if(not archClientes.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }    
    struct Cliente cliente;
    int numeroCuenta;
    double montoInicial;
    char apellidoPaterno[60],apellidoMaterno[60],nombre[60],nombreCompleto[60];   
    while(true){
        archClientes>>numeroCuenta;
        if(archClientes.eof())break;
        archClientes.get();
        leerNombreCompleto(archClientes,apellidoPaterno,apellidoMaterno,nombre,
                nombreCompleto);
        archClientes>>montoInicial;  
        cliente.numeroDeCuenta = numeroCuenta;
        strcpy(cliente.nombre,nombreCompleto);
        cliente.montoInicial = montoInicial;
        if(montoInicial>0){
            cliente.haber = montoInicial;
            cliente.debe = 0;
            strcpy(cliente.estado,"HABILITADO");
        }else if(montoInicial<0){
            cliente.debe = montoInicial*(-1);
            cliente.haber =0;
            strcpy(cliente.estado,"INHABILITADO");
        }
        archClientesBin.write(reinterpret_cast<const char*>(&cliente),
                sizeof(struct Cliente));
    }
}

void leerNombreCompleto(ifstream &archClientes,char *apellidoPaterno,
        char *apellidoMaterno,char *nombre,char *nombreCompleto){
    archClientes.getline(nombre,60,',');
    modificaNombre(nombre);
    archClientes.getline(apellidoPaterno,60,',');
    modificaApellido(apellidoPaterno);
    archClientes.getline(apellidoMaterno,60,',');
    modificaApellido(apellidoMaterno);           
    strcpy(nombreCompleto,apellidoPaterno);
    strcat(nombreCompleto,"/");
    strcat(nombreCompleto,apellidoMaterno);
    strcat(nombreCompleto,"/");
    strcat(nombreCompleto,nombre);
}

void modificaNombre(char *cadena){
    
    int primeraLetra=1;
    for(int i=0;cadena[i];i++){
        if(cadena[i]!=' '){
            if(primeraLetra)primeraLetra=0;
            else if(!primeraLetra)cadena[i]+='a'-'A';   
        }else if(cadena[i]==' ')primeraLetra=1;
    }
}

void modificaApellido(char *cadena){
    
    for(int i=1;cadena[i];i++)
        cadena[i]=tolower(cadena[i]);
}


void modificarClientesBin(const char* nombArchBin,const char* nombArchCsv){
    ifstream archTransacciones(nombArchCsv,ios::in);
    if(not archTransacciones.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    fstream archClientesBin(nombArchBin,ios::in | ios::out | ios::binary);
    if(not archClientesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    struct Cliente cliente;
    int numeroCuenta,posClinte,tamArch,numReg;
    int tamReg = sizeof(struct Cliente);
    char tipo;
    double cantidad;
    datosArchivo(archClientesBin,tamReg,tamArch,numReg);
    while(true){
        archTransacciones>>numeroCuenta;
        if(archTransacciones.eof())break;
        archTransacciones.get();
        posClinte=buscarCliente(archClientesBin,numeroCuenta,numReg);
        if(posClinte!=NO_ENCONTRADO){
            archClientesBin.seekg(posClinte*tamReg,ios::beg);
            archClientesBin.read(reinterpret_cast<char*>(&cliente),tamReg);
            leerYasignarDatos(cliente,cantidad,tipo,posClinte,tamReg,
                    archTransacciones,archClientesBin);
        }else while(archTransacciones.get()!='\n');
    }
}

void leerYasignarDatos(struct Cliente &cliente,double &cantidad,
        char &tipo,int posClinte,int tamReg,ifstream &archTransacciones,
        fstream &archClientesBin){
    while(true){
        archTransacciones>>tipo;
        archTransacciones.get();
        archTransacciones>>cantidad;
        if(tipo=='D'){
            /*Verificamos el monto entre los campos*/
            if(strcmp(cliente.estado,"HABILITADO")==0){
                cliente.haber+=cantidad;
            }else if(strcmp(cliente.estado,"INHABILITADO")==0){
                cliente.debe-=cantidad;
                if(cliente.debe<0){
                    cliente.haber=cliente.debe*(-1);
                    cliente.debe =0;
                    strcpy(cliente.estado,"HABILITADO");
                }
            }
        }else if(tipo=='R'){
            if(strcmp(cliente.estado,"HABILITADO")==0){
                cliente.haber-=cantidad;
                if(cliente.haber<0){
                    cliente.debe = cliente.haber*(-1);
                    cliente.haber=0;
                    strcpy(cliente.estado,"INHABILITADO");
                }
            }else if(strcmp(cliente.estado,"INHABILITADO")==0){
                cliente.debe+=cantidad;
            }
        }
        archClientesBin.seekg(posClinte*tamReg,ios::beg);
        archClientesBin.write(reinterpret_cast<const char*>(&cliente),
                tamReg);
        archClientesBin.flush();
        if(archTransacciones.get()=='\n')break;
    }
}

void emiteReportes(const char *nombArchBin, const char *nombRepTxt1,
        const char *nombRepTxt2){
    
    ofstream archPrimerReporte(nombRepTxt1,ios::out);
    if(not archPrimerReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombRepTxt1<<endl;
        exit(1);
    }
    
    ofstream archSegundoReporte(nombRepTxt2,ios::out);
    if(not archSegundoReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombRepTxt2<<endl;
        exit(1);
    }
    
    archPrimerReporte<<setprecision(2);
    archPrimerReporte<<fixed;
    archSegundoReporte<<setprecision(2);
    archSegundoReporte<<fixed;  
    struct Cliente cliente;
    imprimePrimerReporte(cliente,nombArchBin,archPrimerReporte);
    imprimeSegundoReporte(cliente,nombArchBin,archSegundoReporte);
}

void imprimePrimerReporte(struct Cliente &cliente,const char *nombArchBin,
        ofstream &archPrimerReporte){
    
    ifstream archClientesBin(nombArchBin,ios::in | ios::binary);
    if(not archClientesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    archPrimerReporte<<"BANCO ABC: ESTADO DE CUENTAS HABILES"<<endl;
    imprimeLinea('=',MAX_LINE,archPrimerReporte);
    archPrimerReporte<<"CUENTA"<<setw(10)<<' '<<"TITULAR"<<setw(40)<<' '
            <<"SALDO INICIAL"<<setw(10)<<' '<<"SALDO FINAL"<<endl;
    imprimeLinea('=',MAX_LINE,archPrimerReporte);
    while(true){
        archClientesBin.read(reinterpret_cast<char*>(&cliente),
                sizeof(struct Cliente));
        if(archClientesBin.eof())break;
        if(strcmp(cliente.estado,"HABILITADO")==0){
            archPrimerReporte<<cliente.numeroDeCuenta<<setw(10)<<' '
                    <<left<<setw(50)<<cliente.nombre<<right<<setw(10)
                    <<cliente.montoInicial<<setw(10)<<' '<<setw(10)
                    <<cliente.haber<<endl;
        }
    }
}

void imprimeSegundoReporte(struct Cliente &cliente,const char *nombArchBin,
        ofstream &archSegundoReporte){
    
        ifstream archClientesBin(nombArchBin,ios::in | ios::binary);
    if(not archClientesBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    archSegundoReporte<<"BANCO ABC: ESTADO DE CUENTAS NO HABILES"<<endl;
    imprimeLinea('=',MAX_LINE,archSegundoReporte);
    archSegundoReporte<<"CUENTA"<<setw(10)<<' '<<"TITULAR"<<setw(40)<<' '
            <<"SALDO INICIAL"<<setw(10)<<' '<<"SALDO FINAL"<<endl;
    imprimeLinea('=',MAX_LINE,archSegundoReporte);
    while(true){
        archClientesBin.read(reinterpret_cast<char*>(&cliente),
                sizeof(struct Cliente));
        if(archClientesBin.eof())break;
        if(strcmp(cliente.estado,"INHABILITADO")==0){
            archSegundoReporte<<cliente.numeroDeCuenta<<setw(10)<<' '
                    <<left<<setw(50)<<cliente.nombre<<right<<setw(10)
                    <<cliente.montoInicial<<setw(10)<<' '<<setw(10)
                    <<cliente.debe<<endl;
        }
    }
}

void imprimeLinea(char caracter,int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}
void datosArchivo(fstream &archBin,int tamReg,int &tamArch,int &numReg){
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

int buscarCliente(fstream &archClientesBin,int numeroCuenta,int numReg){
    
    struct Cliente cliente;
    archClientesBin.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        archClientesBin.read(reinterpret_cast<char*>(&cliente),
                sizeof(struct Cliente));
        if(cliente.numeroDeCuenta==numeroCuenta)return i;
    }
    return NO_ENCONTRADO;
}
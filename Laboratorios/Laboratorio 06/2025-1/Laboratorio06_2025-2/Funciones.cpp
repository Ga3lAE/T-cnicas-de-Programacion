/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 7 de junio de 2025, 05:00 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1 

#define MAX_CAR_PLACA 9
#define MAX_CANT_PLACAS_REPRESENTANTE 7

#define MAX_TAM_PLACA 9
#define MAX_TAM_LIN 150
#define MAX_TAM_COD 12
#define MAX_TAM_FECHA 16
#define MAX_TAM_DIN 16

//LECTURA
void leeTablaInfracciones(const char *nombreArchivo, int &cantidad,
        int *arrCodigo, double *arrMultas){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigo;
    double multa;
    while(true){
        //1029   586.45      Conducir un vehiculo especial que no se ajuste a las exigencias reglamentarias sin la autorizacion correspondiente.
        archivo>>codigo;
        if(archivo.eof()) break;
        archivo>>multa;
        while(archivo.get()!='\n');
        
        int posMulta = buscaIntBinAsc(arrCodigo, cantidad, codigo);
        
        if(posMulta == NO_ENCONTRADO)
            insertaInfraccion(arrCodigo, arrMultas, cantidad, 
                    codigo, multa);
        
    }
}
void leeInfracciones(const char *nombreArchivoInfraccionesCometidas, const char *nombreArchivoPlacasRegistradas,
        int &cantidadRepresentates,
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTottalMultas, double *arrTotalPendientes, double *arrTotalPagadas, 
        int*arrCodigoInfracciom, double *arrMultaInfracciones, int cantidadInfracciones){
    ifstream archivoInfracciones(nombreArchivoInfraccionesCometidas, ios::in);
    if(not archivoInfracciones.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoInfraccionesCometidas;
        exit(1);
    }
    ofstream archivoPlacas(nombreArchivoPlacasRegistradas, ios::out);
    if(not archivoPlacas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPlacasRegistradas;
        exit(1);
    }
    
    int fechaInfraccion, dni, codigoInfraccion, fechaPago;
    char placa[MAX_CAR_PLACA]{}, pago;
    bool sePago;
    while(true){
        //13/10/2024   P582-282       84186239      1045   P   11/1/2025
        fechaInfraccion = leeFecha(archivoInfracciones);
        if(archivoInfracciones.eof()) break;
        archivoInfracciones>>placa>>dni>>codigoInfraccion;
        if(archivoInfracciones.get()!='\n'){
            sePago = true;
            archivoInfracciones>>pago;
            fechaPago = leeFecha(archivoInfracciones);
        }
        else
            sePago = false;
        
        int posMulta = buscaIntBinAsc(arrCodigoInfracciom, cantidadInfracciones, codigoInfraccion);
        if(posMulta != NO_ENCONTRADO){
            int posRep = buscaIntBinAsc(arrDni, cantidadRepresentates, dni);
            if(posRep == NO_ENCONTRADO){
                posRep = agregaRepresentante(cantidadRepresentates, 
                        arrDni, arrMasMultaAntigua, arrUltimaPendiente,
                        arrTottalMultas, arrTotalPendientes, arrTotalPagadas, 
                        dni);
            }            
            
            if(fechaInfraccion<arrMasMultaAntigua[posRep])
                arrMasMultaAntigua[posRep] = fechaInfraccion;            
            if(sePago){
                if(fechaPago>arrUltimaPendiente[posRep])
                    arrUltimaPendiente[posRep] = fechaPago;
                arrTotalPagadas[posRep]+=arrMultaInfracciones[posMulta];                
            }
            else{
                arrTotalPendientes[posRep]+=arrMultaInfracciones[posMulta];               
            }
            
            arrTottalMultas[posRep] += arrMultaInfracciones[posMulta];
            
            archivoPlacas<<dni<<' '<<placa<<endl;
        }                                
    }
}
int leeFecha(ifstream &archivo){
    int dd, mm, aa;
    char sep;
    archivo>>dd;
    if(archivo.eof()) return -1;
    archivo>>sep>>mm>>sep>>aa;
    
    return aa*10000 + mm*100 +dd;
}
//BUSQUEDA
int buscaIntBinAsc(int *arr, int cant, int el){
    int posInicio=0, posFin=cant-1, posMedio;
    while(true){
        posMedio = (posFin+posInicio)/2;
                
        if(posFin<posInicio) return NO_ENCONTRADO;
                
        if(arr[posMedio] == el) return posMedio;
        else if(arr[posMedio] > el) posFin = posMedio-1;
        else if(arr[posMedio] < el) posInicio = posMedio+1;
        
    }
}

//INSERCION
void insertaInfraccion(int *arrCodigo, double *arrMultas, int &cantidad,
        int codigo, double multa){
    int i;
    for (i = cantidad-1; i>=0 and arrCodigo[i]>codigo; i--) {        
        arrCodigo[i+1] = arrCodigo[i];
        arrMultas[i+1] = arrMultas[i];
    }
    arrCodigo[i+1] = codigo;
    arrMultas[i+1] = multa;
    
    cantidad++;    
}
int agregaRepresentante(int &cantidad, 
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTotalMultas, double *arrTotalPendientes, double *arrTotalPagadas, 
        int dni){
    int i;
    for (i = cantidad-1; i>=0 and arrDni[i]>dni; i--) {        
        arrDni[i+1] = arrDni[i];
        arrMasMultaAntigua[i+1] = arrMasMultaAntigua[i];
        arrUltimaPendiente[i+1] = arrUltimaPendiente[i];
        arrTotalMultas[i+1] = arrTotalMultas[i];
        arrTotalPendientes[i+1] = arrTotalPendientes[i];
        arrTotalPagadas[i+1] = arrTotalPagadas[i];        
    }
    arrDni[i+1] = dni;
    arrMasMultaAntigua[i+1] = 99999999;
    arrUltimaPendiente[i+1] = 0;
    arrTotalMultas[i+1] = 0;
    arrTotalPendientes[i+1] = 0;
    arrTotalPagadas[i+1] = 0;        
    
    cantidad++;
    
    return i+1;
}

//PLACA
int cuentaPlacas(const char*listaPlacas){
    // G760-721/G760-721/G760-721
    // G760-721
    // 
    int cantidad=0;
    int i;
    for (i = 0; listaPlacas[i]; i++) {          
        if(listaPlacas[i] == '-') cantidad++; // todas las placas tiene un separador intermedio
    }    
    return cantidad;
}
void obtenerPlaca(const char *listaDePlacas, int n, char *&placa){
    int numeroPlacas = cuentaPlacas(listaDePlacas);
//    bool condicion = n>numeroPlacas or n>1; //originalmente
    bool condicion = n>numeroPlacas and n>1; // debe ser AND, porque creo que sale con AND (bajo la logica posterior de agregar datos)
    //n<=numeroPlacas or n<=1 . si la condicion fuera con AND
    //n<=numeroPlacas and n<=1 , lc condicion que e evalua originalmente (basta con tener n = 2 y numeroPlacas = 3 para que no cumpla)
    
    if(not condicion){
        placa = new char[MAX_CAR_PLACA]{};
        int i, k;                
        for (i = n*(9), k = 0; listaDePlacas[i]!='/' and listaDePlacas[i]; i++, k++) {            
            placa[k] = listaDePlacas[i];
        }
        placa[k] = 0;
    }          
}
void agregarPlaca(char *listaDePlacas, const char *placa){
    int cantidadPlacas = cuentaPlacas(listaDePlacas);
    bool seAgrega = true;
    char *placaActual;      
        for (int  i = 0; i <cantidadPlacas; i++) {                
            obtenerPlaca(listaDePlacas, i, placaActual);

            if(comparaPlacas(placa, placaActual))
                seAgrega = false;
        }
    
    
    if(seAgrega){
        int j = (cantidadPlacas)*9-1, k=0;
            if(cantidadPlacas != 0)
                listaDePlacas[j] = '/';
            
            j++;                            
                                    
            for ( j, k=0; placa[k] ; j++, k++) {                
                listaDePlacas[j] = placa[k];                                
            }
            
            listaDePlacas[j] = 0;                        
    }
        
}
bool comparaPlacas(const char *placa1, const char *placa2){
    for (int i = 0; placa1[i]; i++) {        
        if(placa1[i] != placa2[i]) return false;
    }
    return true;

}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void emiteReporte(const char *nombreArchivoReporte, const char *nombreArchivoPlacasRegistradas,
        int &cantidad, 
        int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
        double *arrTotalMultas, double *arrTotalPendientes, double *arrTotalPagadas){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    ifstream archivoPlacas(nombreArchivoPlacasRegistradas, ios::in);
    if(not archivoPlacas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPlacasRegistradas;
        exit(1);
    }
    
    
    archivoReporte<<setw(MAX_TAM_LIN/2)<<"MINISTERIO DE TRANSPORTES"<<endl
            <<setw(MAX_TAM_LIN/2)<<"LISTADO DE INFRACCIONES"<<endl;
    imprimeLinea(archivoReporte, '=');
    archivoReporte<<left
            <<setw(MAX_TAM_COD)<<"DNI"
            <<setw(MAX_TAM_PLACA*MAX_CANT_PLACAS_REPRESENTANTE)<<"PLACAS"
            <<setw(MAX_TAM_FECHA)<<"+ OLD"
            <<setw(MAX_TAM_FECHA)<<"ULT PAY"
            <<setw(MAX_TAM_DIN)<<"TOTAL"
            <<setw(MAX_TAM_DIN)<<"PAGADAS"
            <<setw(MAX_TAM_DIN)<<"PENDIENTES"
            <<endl;
    imprimeLinea(archivoReporte, '=');
    for (int i = 0; i < cantidad; i++) {             
        archivoReporte<<left
                <<setw(MAX_TAM_COD)<<arrDni[i];
        imprimePlaca(archivoReporte, archivoPlacas, arrDni[i]);
        imprimeFecha(archivoReporte, arrMasMultaAntigua[i]);
        imprimeFecha(archivoReporte, arrUltimaPendiente[i]);
        archivoReporte<<setw(MAX_TAM_DIN)<<arrTotalMultas[i]
            <<setw(MAX_TAM_DIN)<<arrTotalPagadas[i]
            <<setw(MAX_TAM_DIN)<<arrTotalPendientes[i]
            <<endl;
    }
    imprimeLinea(archivoReporte, '=');

    
}
void imprimePlaca(ofstream &archivoReo, ifstream &archivoPlac, int dni){
    archivoPlac.clear();
    archivoPlac.seekg(0, ios::beg);
    
    int dniAc, cont = 0;
    char placa[MAX_CAR_PLACA]{}, 
            listaPlaca[MAX_CAR_PLACA*MAX_CANT_PLACAS_REPRESENTANTE]{};
    
    while(true){
        archivoPlac>>dniAc;
        if(archivoPlac.eof()) break;
        archivoPlac>>placa;
        
        if(dniAc == dni){
            agregarPlaca(listaPlaca, placa);
            cont++;
        }
        
    }
    
    archivoReo<<setw(MAX_TAM_PLACA*MAX_CANT_PLACAS_REPRESENTANTE)<<listaPlaca;
}
void imprimeFecha(ofstream &archivo, int fecha){
    
    if(fecha == 0 or fecha == 99999999)
        archivo<<setw(MAX_TAM_FECHA/2)<<"NO HAY FECHA"<<setw(MAX_TAM_LIN/2)<<' ';
    else{
        int dd, mm, aa;
        char sep = '/';

        aa = fecha /10000;
        fecha %= 10000;
        mm = fecha /100;
        dd = fecha %100;

        archivo<<right<<setfill('0')
                <<setw(2)<<dd<<sep
                <<setw(2)<<mm<<sep
                <<setw(4)<<aa
                <<left<<setfill(' ')
                <<setw(MAX_TAM_FECHA-10)<<' ';       
    }
}


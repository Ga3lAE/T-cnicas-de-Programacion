/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 15 de mayo de 2025, 06:19 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define NO_ENCONTRADO -1  

#define MAX_CAR_LIN 150
#define MAX_CAR_FECHA 12
#define MAX_CAR_CANT 16
#define MAX_CAR_RATIO 14
#define MAX_CAR_VIRAL 10
//#define MAX_CAR_
//#define MAX_CAR_


//LECTURA
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    
    archivo>>dd;
    if(archivo.eof()) return;
    archivo>>sep>>mm>>sep>>aa;
    
    fecha = dd + mm*100 + aa*10000;    
}
void leeCodigoUsuario(ifstream &archivo, int &codigo){
    int cod1, cod2;
    char sep;
    archivo>>cod1;
    if(archivo.eof()) return;
    archivo>>sep>>cod2;
    
    codigo = cod1*1000 + cod2;
}
void saltaDato(ifstream &archivo, char del){
    archivo>>ws;
    while(archivo.get()!=del);
}

void leeTiktoks(const char *nombreArchivo, int &cantidad,
        int *fechas, int *cantidadesLikes, int *cantidadesReproducciones,
        int fechaInicio, int fechaFin){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //4/09/2022   4677   16955
        leeFecha(archivo, fechas[cantidad]);
        if(archivo.eof()) break;
        if(fechas[cantidad]<fechaFin and fechas[cantidad]>fechaInicio){
            archivo
                    >>cantidadesLikes[cantidad]
                    >>cantidadesReproducciones[cantidad];
            
            cantidad++;
        }
        else while(archivo.get()!='\n');
    }
}

void leeUsuarios(const char *nombreArchivo, int &cantidad,
        int *codigos, bool *sonCuentasPublicas){
     ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }

     char tipoCuenta;
    while(true){
        //604-54    @erasmo   721   V
        leeCodigoUsuario(archivo, codigos[cantidad]);
        if(archivo.eof()) break;
        for (int i = 0; i < 2; i++)
            saltaDato(archivo, ' ');
        
        archivo>>tipoCuenta;
        sonCuentasPublicas[cantidad] = tipoCuenta == 'V';
        
        cantidad++;            
    }
}
//PROCESAMIENTO
void procesaComentarios(const char *nombreArchivo, 
        int *fechasTktks, int *cantidadesComentariosTktks,
        int *cantidadesLikesComentariosTktks, int *cantidadesReproduccioneeTktks,
        double *ratiosComentariosTktks, bool *sonViralesTktks, int *cantidadesSeguidoresPublicosTktks,
        int cantidadTktks,
        int *codigosUsuarios, bool *sonCuentasPublicasUsuarios, 
        int cantidadUsuarios){
    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    
    int fechaActual, codigoUserComentario, cantidadLikesComentarioActual;
    while(true){
        //14/07/2022   17-121   We_aint_forgot_that_time_he_tricked_us_all_into_thinking_we_could_win_a_Tesla   1134   
                    //76-712   daviddobrik_run_some_modern_warfare_wit_me   2806
        leeFecha(archivo, fechaActual);
        if(archivo.eof()) break;
        int posTktk = buscaInt(fechasTktks, cantidadTktks, fechaActual);
        if(posTktk == NO_ENCONTRADO){
            while(archivo.get()!='\n');
        }
        else{
            while(true){
                if(archivo.get()=='\n') break;
                
                leeCodigoUsuario(archivo, codigoUserComentario);
                int posUser = buscaInt(codigosUsuarios, cantidadUsuarios, codigoUserComentario);

                if (posUser == NO_ENCONTRADO) {
                    for (int i = 0; i < 2; i++)
                        //nos saltamos los dos datos siguientes (el comentario y sus likes)
                        saltaDato(archivo, ' ');
                } 
                else {
                    //nos saltamos lo escrito en el comentario
                    saltaDato(archivo, ' ');
                    archivo>>cantidadLikesComentarioActual;
                    
                    //hasta acá es que leimos todos los datos de lo que procesaremos
                    
                    procesaDatosComentarios(cantidadesComentariosTktks[posTktk], 
                            cantidadesLikesComentariosTktks[posTktk], 
                            cantidadesSeguidoresPublicosTktks[posTktk], 
                            sonCuentasPublicasUsuarios[posUser], 
                            cantidadLikesComentarioActual);
                }
            }                        
        }
    }
    
    //como ya procesamos todos los datos ahora podemos sacar las estadisticas finales como el ratio y ver si es viral
    procesaDatosRecuento(cantidadTktks, cantidadesReproduccioneeTktks, 
            cantidadesLikesComentariosTktks,cantidadesComentariosTktks,  
            ratiosComentariosTktks, sonViralesTktks);
}
void procesaDatosComentarios(int &cantidadComentarios,
        int &cantidadLikesComentario,
        int &cantidadSeguidoresPublicos,
        bool esCuentaPublicaUsuario, 
        int cantidadLikesComentarioRecibido){
    
    cantidadComentarios++;
    cantidadLikesComentario+=cantidadLikesComentarioRecibido;
    if(esCuentaPublicaUsuario)
        cantidadSeguidoresPublicos++;
    
}
void procesaDatosRecuento(int cantidad, int *cantidadesReproduccionee,
        int *cantidadesLikesComentarios, int *cantidadesComentarios, 
        double *ratiosComentarios, bool *sonVirales){
    for (int i = 0; i < cantidad; i++) {        
        ratiosComentarios[i] = (double)cantidadesReproduccionee[i]/cantidadesLikesComentarios[i]*100.0;
        sonVirales[i] = cantidadesComentarios[i]>ratiosComentarios[i];
    }        
}

//BUSQUEDA
int buscaInt(int *arr, int cantidad, int dato){
    for (int i = 0; i < cantidad; i++) {        
        if(arr[i] == dato) return i;
    }
    return NO_ENCONTRADO;
}

//ORDENAMIENTO
void ordenaTiktoks(int cantidad,
        int *fechas, int *cantidadesLikes, int *cantidadesReproducciones){
    for (int i = 0; i < cantidad-1; i++) {
        for (int j = i+1; j < cantidad; j++) {            
            if(cantidadesReproducciones[i]<cantidadesReproducciones[j] 
                or 
                    cantidadesReproducciones[i] == cantidadesReproducciones[j] 
                    and
                    fechas[i]>fechas[j]){
                cambiaDatos(fechas, cantidadesLikes, cantidadesReproducciones, i, j);                                
            }
        }


    }

}
void cambiaDatos(int* fechas, int* cantidadesLikes, int* cantidadesReproducciones, int i, int j){
    cambiarInt(fechas[i], fechas[j]);
    cambiarInt(cantidadesLikes[i], cantidadesLikes[j]);
    cambiarInt(cantidadesReproducciones[i], cantidadesReproducciones[j]);
}
void cambiarInt(int &d1, int &d2){
    int aux;
    aux = d1;
    d1 = d2;
    d2=aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep = '/';
    
    aa= fecha/10000;
    fecha %=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')
            <<setw(MAX_CAR_FECHA-10);
}
void imprimeReporte(const char *nombreArchivo, int cantidad,
        int fechaInicio, int fechaFin,
        int *fechas, int *cantidadesComentarios,
        int *cantidadesLikesComentarios, int *cantidadesReproducciones,
        double *ratiosComentariosTktks, bool *sonViralesTktks, int *cantidadesSeguidoresPublicosTktks) {
    
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    
    imprimeEncabezado(archivo, fechaInicio, fechaFin);
    
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left;
        imprimeFecha(archivo, fechas[i]);
        archivo<<right<<setw(MAX_CAR_CANT/2)<<cantidadesComentarios[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<setw(MAX_CAR_CANT/2)<<cantidadesLikesComentarios[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<setw(MAX_CAR_CANT/2)<<cantidadesReproducciones[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<setw(MAX_CAR_RATIO/2)<<ratiosComentariosTktks[i]<<setw(MAX_CAR_RATIO/2)<<' '
                <<setw(MAX_CAR_VIRAL/2)<<sonViralesTktks[i]<<setw(MAX_CAR_VIRAL/2)<<' '
                <<setw(MAX_CAR_CANT/2)<<cantidadesSeguidoresPublicosTktks[i]<<setw(MAX_CAR_CANT/2)<<' '
                <<endl;
    }
    imprimeLinea(archivo, '=');

    
    
}
void imprimeEncabezado(ofstream &archivo, int fechaInicio, int fechaFin){
    archivo<<setw(MAX_CAR_LIN/2)<<"VENUS VIDEOS"<<endl
            <<setw(MAX_CAR_LIN/2)<<"REPORTES PARA LA COMPANIA"<<endl
            <<setw(MAX_CAR_LIN/2)<<"FECHA INICIAL: ";
    imprimeFecha(archivo, fechaInicio);
    archivo<<'-'<<"FECHA FINAL: ";
    imprimeFecha(archivo, fechaFin);
    archivo<<endl;
    imprimeLinea(archivo, '=');
    
    archivo<<left
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_CANT)<<"COMENTS"
            <<setw(MAX_CAR_CANT)<<"LIKES COM"
            <<setw(MAX_CAR_CANT)<<"REPROD"
            <<setw(MAX_CAR_RATIO)<<"RATIO"
            <<setw(MAX_CAR_VIRAL)<<"VIRAL?"
            <<setw(MAX_CAR_CANT)<<"SEGUIDORES PIBLICOS"
            <<endl;
}
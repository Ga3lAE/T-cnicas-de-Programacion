/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 19 de mayo de 2025, 11:35 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_FECHA 12
#define MAX_CAR_COMNT 70
#define MAX_CAR_USER 15
#define MAX_CAR_CANT 18
#define MAX_CAR_PAIS 20
#define MAX_CAR_RES 20

//LECTURA
void leeFechaCin(int &fecha){
    int dd, mm, aa;
    char sep;
    
    cin>>dd>>sep>>mm>>sep>>aa;
    
    fecha = dd + mm*100+ aa*10000; 
}
void leeFecha(ifstream &archivo, int &fecha){
    int dd, mm, aa;
    char sep;
    
    archivo>>dd;
    if(archivo.eof()) return;
    archivo>>sep>>mm>>sep>>aa;
    
    fecha = dd + mm*100+ aa*10000; 
}
void leeCodigoUsuario(ifstream &archivo, int &codigo){
    int cod1, cod2;
    char sep;
    
    archivo>>cod1;
    if(archivo.eof()) return;
    archivo>>sep>>cod2;
    
    codigo = cod1*1000 + cod2;
}
void saltaLinea(ifstream &archivo){
    while(archivo.get()!='\n') ;
}
void saltaDatoDel(ifstream &archivo, char del){
    archivo>>ws;
    while(archivo.get()!=del);
}
//PROCESA
void leeProcesaArchivos(const char *nombreArchivoTiktoks,
        const char *nombreArchivoComentarios,
        const char *nombreArchivoUsuarios, const char *nombreArchivoPaises,
        const char *nombreArchivoReporte){
    ifstream archivoTktks(nombreArchivoTiktoks, ios::in);
    if(not archivoTktks.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoTiktoks;
        exit(1);
    }
    ifstream archivoComentarios(nombreArchivoComentarios, ios::in);
    if(not archivoComentarios.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoComentarios;
        exit(1);
    }
    ifstream archivoUsuarios(nombreArchivoUsuarios, ios::in);
    if(not archivoUsuarios.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoUsuarios;
        exit(1);
    }
    ifstream archivoPaises(nombreArchivoPaises, ios::in);
    if(not archivoPaises.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPaises;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    archivoReporte<<fixed<<setprecision(2);
    
    int fechaInicial, fechaFinal;
    cout<<"Ingrese un intervalo de fechas para los datos:"<<endl;
    leeFechaCin(fechaInicial);
    leeFechaCin(fechaFinal);
    
    fechaInicial = 20221005;
    fechaFinal = 20221031;
                
    int fechaMejorTktk;
    
    leeArchivos(archivoTktks, 
            archivoComentarios, archivoUsuarios, archivoPaises, 
            fechaInicial, fechaFinal, fechaMejorTktk,
            archivoReporte);
    
    archivoReporte<<"RESUMEN MEJOR TIKTOK:"<<endl
            <<"FECHA: ";
    imprimeFecha(archivoReporte, fechaMejorTktk);
    archivoReporte<<endl
            <<"SEGUIDOR QUE OBTUVO MAYOR NUMERO DE LIKES: ";
    imprimeNombreSeguidor(archivoComentarios, archivoUsuarios, 
            archivoReporte, 
            fechaMejorTktk);
}
void leeArchivos(ifstream &archivoTktks,
        ifstream &archivoComentarios, ifstream &archivoUsuarios, ifstream &archivoPaises,
        int fechaInicio, int fechaFinal, int &fechaMejor,
        ofstream &archivoReporte){
    
    imprimeEncabezado(archivoReporte, fechaInicio, fechaFinal);
    
    int contadorTkTks=0, cantidadComentarios=0, 
            cantidadSeguidoresPublicos=0, cantidadSeguidoresPrivados=0;
    double ratioMayor = 0;
    
    int fechaTktk, cantidadLikesTktk, cantidadReprodTkt;
    double ratioViral;    
    //procesamos los datos para cada tiktok
    while(true){
        //14/10/2022   3772   24198
        leeFecha(archivoTktks, fechaTktk);
        if(archivoTktks.eof()) break;
        contadorTkTks++;
        archivoTktks>>cantidadLikesTktk>>cantidadReprodTkt;
        //calculamos el ratio para ver si es el más viral
        ratioViral = cantidadReprodTkt/cantidadLikesTktk*100.0;        
        if(ratioViral > ratioMayor){
            ratioMayor = ratioViral;
            fechaMejor = fechaTktk;
        }
        //imprimimos los datos para este tiktok
        imprimeTktk(archivoReporte, fechaTktk, contadorTkTks);        
        //ya tenemos el tiktok más viral
        leeComentarios(archivoComentarios, archivoUsuarios, 
                archivoPaises, archivoReporte, 
                fechaTktk, 
                cantidadComentarios, cantidadSeguidoresPublicos, cantidadSeguidoresPrivados);
        imprimeResumenTktk(archivoReporte, cantidadLikesTktk, cantidadReprodTkt, 
                cantidadComentarios, cantidadSeguidoresPublicos, cantidadSeguidoresPrivados, 
                ratioViral);
    }            
}
void leeComentarios(ifstream &archivoComentarios, ifstream &archivoUsuarios, 
        ifstream &archivoPais, ofstream &archivoReporte,
        int fechaTktk, 
        int &cantidadComentarios, 
        int &cantidadSeguidoresPublicos, int &cantidadSeguidoresPrivados){
    
    archivoComentarios.clear();
    archivoComentarios.seekg(0, ios::beg);
    
    int fechaComent, codigoUser, cantidadLikesComent;
    while(true){
        //10/08/2022   59-315   but_can_he   3070   59-315   ok_but_does_he_get_a_tesla   133
        leeFecha(archivoComentarios, fechaComent);
        if(archivoComentarios.eof()) break;
        if(fechaComent != fechaTktk) saltaLinea(archivoComentarios);
        else{
            while(true){
                if(archivoComentarios.get()=='\n') break;
                cantidadComentarios++;
                leeCodigoUsuario(archivoComentarios, codigoUser);
                imprimeTexto(archivoComentarios, archivoReporte, MAX_CAR_COMNT, ' ');
                archivoComentarios>>cantidadLikesComent;
                imprimeUsuario(archivoUsuarios, archivoPais, archivoReporte, 
                        codigoUser, cantidadLikesComent, 
                        cantidadSeguidoresPublicos, cantidadSeguidoresPrivados);
            }
        }
        
    }
    
}

//IMPRESION
void imprimeLinea(ofstream & archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void imprimeFecha(ofstream &archivo, int fecha){
    int dd, mm, aa;
    char sep = '/';
    
    aa = fecha /10000;
    fecha%=10000;
    mm= fecha /100;
    dd = fecha %100;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')
            <<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeTexto(ifstream &archivoLectura, ofstream &archivoImpresion, int tam, char del){
    char letra;
    int cantL=0;
    archivoLectura>>ws;
    
    while(true){
        letra = archivoLectura.get();
        if(letra == del) break;
        cantL++;
        archivoImpresion<<letra;                
    }
    archivoImpresion<<setw(tam-cantL)<<' ';
}
void imprimeUsuario(ifstream &archivoUsuarios, ifstream &archivoPais, ofstream &archivoReporte,
        int codigoUser, int cantidadLikes,         
        int &cantidadSeguidoresPublicos, int &cantidadSeguidoresPrivados){
    
    archivoUsuarios.clear();
    archivoUsuarios.seekg(0, ios::beg);
    
    int codigoActual, codigoPais, cantidadSeguidores;
    bool esPublico;
    char publico;
    while(true){
        //604-104    @miguel   604   V
        leeCodigoUsuario(archivoUsuarios, codigoActual);
        if(archivoUsuarios.eof()) break;
        if(codigoUser != codigoActual) saltaLinea(archivoUsuarios);
        else {
            imprimeTexto(archivoUsuarios, archivoReporte, MAX_CAR_COMNT, ' ');
            archivoUsuarios>>cantidadSeguidores>>publico;
            codigoPais = codigoUser/ 1000;
            esPublico = publico == 'V';        
            
            archivoReporte<<setw(MAX_CAR_CANT)<<cantidadLikes;
            
            if(esPublico){
                imprimePais(archivoPais, archivoReporte, codigoPais);
                cantidadSeguidoresPublicos++;
            }
            else {
                archivoReporte<<setw(MAX_CAR_PAIS)<<"NO PUBLICO";
                cantidadSeguidoresPrivados++;
            }
            archivoReporte<<endl;
        }
        
    }
    
}
void imprimeEncabezado(ofstream &archivo, int fechaInicio, int fechaFinal){
    archivo<<setw(MAX_CAR_LIN/2)<<"VENUS TIKTOKS"<<endl
            <<setw(MAX_CAR_LIN/2)<<"REPORTE PARA LA CAMPANA"<<endl
            <<setw(MAX_CAR_LIN/2)<<"FECHA INICIAL: ";
    imprimeFecha(archivo, fechaInicio);
    archivo<<"FECHA INICIAL: ";
    imprimeFecha(archivo, fechaFinal);
    archivo<<endl;    
}

void imprimeTktk(ofstream &archivo, int fecha, int contador){
    
    imprimeLinea(archivo, '=');
    
    archivo<<"TIK TOK "<<right<<setw(3)<<contador<<')'<<setw(10)<<' ';
    imprimeFecha(archivo, fecha);
    archivo<<endl;
    
    archivo<<left
            <<setw(MAX_CAR_COMNT)<<"COMENTARIO"
            <<setw(MAX_CAR_USER)<<"AUTOR"
            <<setw(MAX_CAR_CANT)<<"CANTIDAD LIKES"
            <<setw(MAX_CAR_PAIS)<<"PAIS DEL AUTOR"
            <<endl;
    imprimeLinea(archivo, '-');
}
void imprimePais(ifstream &archivoPais, ofstream &archivoReporte, int codigo){
    archivoPais.clear();
    archivoPais.seekg(0, ios::beg);
    
    int codigoActual;
    while(true){
        archivoPais>>codigoActual;
        if(archivoPais.eof()) break;
        if(codigo != codigoActual) saltaLinea(archivoPais);
        else
            imprimeTexto(archivoPais, archivoReporte, MAX_CAR_PAIS, '\n');
    }
    
}

void imprimeResumenTktk(ofstream &archivo, int cantidadLikes, int cantidadReprod,
        int cantidadComentarios, int cantidadSeguidoresPublicos, int cantidadSeguidoresPrivados,
        double ratioViral){
    
    imprimeLinea(archivo, '-');
    archivo<<left
            <<setw(MAX_CAR_RES)<<"RESUMEN TIKTOK"
            <<"LIKES: "<<setw(MAX_CAR_CANT)<<cantidadLikes
            <<"VISTAS: "<<setw(MAX_CAR_CANT)<<cantidadReprod
            <<endl;
    archivo<<"CANTIDAD DE COMENTARIOS: "<<cantidadComentarios<<endl
            <<"CANTIDAD DE SEGUIDORES PUBLICOS: "<<cantidadSeguidoresPublicos<<endl
            <<"CANTIDAD DE SEGUIDORES NO PUBLICOS: "<<cantidadSeguidoresPrivados<<endl;
    if(cantidadComentarios>ratioViral/cantidadReprod and cantidadComentarios>ratioViral/cantidadLikes){
        archivo<<right<<setw(MAX_CAR_LIN/2)<<"ES VIRAL"<<endl;
    }
            
    
} 

void imprimeNombreSeguidor(ifstream &archivoComentarios, ifstream &archivoUsuarios,
        ofstream &archivoReporte,
        int fechaMejor){
    
    archivoUsuarios.clear();
    archivoUsuarios.seekg(0, ios::beg);
    
    int codigo, codigoMayor=0, totalLikes=0, cantidadLikesMayor, cantidadLikes;
    while(true){
        //604-54    @erasmo   721   V
        leeCodigoUsuario(archivoUsuarios, codigo);
        if(archivoUsuarios.eof()) break;
        saltaLinea(archivoUsuarios);
        
        archivoComentarios.clear();
        archivoComentarios.seekg(0, ios::beg);
        
        int fecha, codigoActual;
        while (true) {
            //31/10/2022   59-315   get_him_a_tesla   4913
            leeFecha(archivoComentarios, fecha);
            if (archivoComentarios.eof()) break;
            if (fecha != fechaMejor)
                saltaLinea(archivoComentarios);
            else {
                leeCodigoUsuario(archivoComentarios, codigoActual);
                saltaDatoDel(archivoComentarios, ' ');
                archivoComentarios>>cantidadLikes;
                if (codigo == codigoActual){
                    totalLikes+=cantidadLikes;
                }
            }

        }
        
        if(totalLikes>cantidadLikesMayor)
            codigoMayor = codigo;
    }
    
    archivoUsuarios.clear();
    archivoUsuarios.seekg(0, ios::beg);
        
    while(true){
        //604-104    @miguel   604   V
        leeCodigoUsuario(archivoUsuarios, codigo);
        if(archivoUsuarios.eof()) break;
        if(codigo != codigoMayor) saltaLinea(archivoUsuarios);
        else{
            imprimeTexto(archivoUsuarios, archivoReporte, MAX_CAR_USER, ' ');            
            archivoReporte<<endl;
            break;
        }
    }               
}
 
/* 
 * File:   main.cpp
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

#define MAX_CANT_TKTKS 1000
#define MAX_CANT_USERS 20

/*
 * 
 */



int main(int argc, char** argv) {
    
    int cantidadTktks=0;
    int fechasTktks[MAX_CANT_TKTKS]{}, 
            cantidadesLikesTkts[MAX_CANT_TKTKS]{}, 
            cantidadesReproduccioneeTktks[MAX_CANT_TKTKS]{};
    int fechaInicio, fechaFin;
    fechaInicio = 20220904;
    fechaFin = 20221010;
        
    
    leeTiktoks("TikToks.txt", cantidadTktks, 
            fechasTktks, cantidadesLikesTkts, cantidadesReproduccioneeTktks, 
            fechaInicio, fechaFin);
    ordenaTiktoks(cantidadTktks,
            fechasTktks, cantidadesLikesTkts, cantidadesReproduccioneeTktks);
    
    
    //los datos que necesitamos para el reporte por cada tiktok son
    int cantidadesComentariosTktks[MAX_CANT_TKTKS]{}, 
            cantidadesLikesComentariosTktks[MAX_CANT_TKTKS]{}, 
            cantidadesSeguidoresPublicosTktks[MAX_CANT_TKTKS]{};
    double ratiosComentariosTktks[MAX_CANT_TKTKS]{};
    bool sonViralesTktks[MAX_CANT_TKTKS]{};
    
    // de los usuarios solo nos importa si son de cuenta publica o privada
    int cantidadUsuarios=0;
    int codigosUsuarios[MAX_CANT_USERS]{};
    bool sonCuentasPublicasUsuarios[MAX_CANT_USERS]{};
    
    leeUsuarios("Usuarios.txt", cantidadUsuarios, 
            codigosUsuarios, sonCuentasPublicasUsuarios);
    
    //ahora solo procesamos los comentarios
    procesaComentarios("Comentarios.txt", 
            fechasTktks, cantidadesComentariosTktks, 
            cantidadesLikesComentariosTktks, cantidadesReproduccioneeTktks, 
            ratiosComentariosTktks, sonViralesTktks, cantidadesSeguidoresPublicosTktks, 
            cantidadTktks, 
            codigosUsuarios, sonCuentasPublicasUsuarios, 
            cantidadUsuarios);
    
    imprimeReporte("Reporte.txt", cantidadTktks, 
            fechaInicio, fechaFin, 
            fechasTktks, cantidadesComentariosTktks, 
            cantidadesLikesComentariosTktks, cantidadesReproduccioneeTktks, 
            ratiosComentariosTktks, sonViralesTktks, cantidadesSeguidoresPublicosTktks);

    return 0;
}


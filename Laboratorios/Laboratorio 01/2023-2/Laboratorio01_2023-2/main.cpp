/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 12 de abril de 2025, 04:48 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int cantidadTelevidentes=0, 
            cantidadMenoresVenRangoHora=0, 
            cantidadMujeresAdultasFueraRangoHora=0, 
            cantidadHombresJovenesMinimoHoras=0,  
            cantidadVenCanalesExclusivamente=0, 
            cantidadJovenesYAdultos=0, tiempoTotalVistoJovenesyAdultos=0, 
            cantidadMujeresVenTvpucp=0, cantidadMujeres=0, 
            cantidadHombresJovenesVenTptele=0, cantidadHombresJovenes=0, 
            cantidadAdultosRegistrados=0, 
            cantidadCanalesVistos=0;
    
    
    leeImprimeDatos(cantidadTelevidentes, 
            cantidadMenoresVenRangoHora, 
            cantidadMujeresAdultasFueraRangoHora, 
            cantidadHombresJovenesMinimoHoras, 
            cantidadVenCanalesExclusivamente, 
            cantidadJovenesYAdultos, tiempoTotalVistoJovenesyAdultos, 
            cantidadMujeresVenTvpucp, cantidadMujeres, 
            cantidadHombresJovenesVenTptele, cantidadHombresJovenes, 
            cantidadAdultosRegistrados, 
            cantidadCanalesVistos);
    
    
    double promedioTiempoVistaJovenesYAdultos, 
            porcentajeMujeresVenTvpucp, 
            porcentajeHombresJovensVenTptele, 
            porcentajeAdultosRegistrados, 
            promedioCanalesVenTelevidentes;
    
    promedioTiempoVistaJovenesYAdultos = tiempoTotalVistoJovenesyAdultos/3600.0/cantidadJovenesYAdultos;
    porcentajeMujeresVenTvpucp = cantidadMujeresVenTvpucp*100.0/cantidadMujeres;
    porcentajeHombresJovensVenTptele = cantidadHombresJovenesVenTptele*100.0/cantidadHombresJovenes;
    porcentajeAdultosRegistrados = cantidadAdultosRegistrados*100.0/cantidadTelevidentes;
    promedioCanalesVenTelevidentes = cantidadCanalesVistos*1.0/cantidadTelevidentes;
    
    imprimeEstadisticas(cantidadTelevidentes, 
            cantidadMenoresVenRangoHora, 
            cantidadMujeresAdultasFueraRangoHora, 
            cantidadHombresJovenesMinimoHoras, 
            cantidadVenCanalesExclusivamente, 
            promedioTiempoVistaJovenesYAdultos, 
            porcentajeMujeresVenTvpucp, 
            porcentajeHombresJovensVenTptele, 
            porcentajeAdultosRegistrados, 
            promedioCanalesVenTelevidentes);
    
    
    
    
    
    
    return 0;
}


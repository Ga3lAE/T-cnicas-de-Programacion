/* 
 * File:   funcionesAuxiliares.h
 * Author: arias
 *
 * Created on 12 de abril de 2025, 04:48 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimeLinea(char c);

void leeImprimeDatos(int &cantidadTelevidentes, 
            int &cantidadMenoresVenRangoHora, 
            int &cantidadMujeresAdultasFueraRangoHora, 
            int &cantidadHombresJovenesMinimoHoras, 
            int &cantidadVenCanalesExclusivamente, 
            int &cantidadJovenesYAdultos, int &tiempoTotalVistoJovenesyAdultos, 
            int &cantidadMujeresVenTvpucp, int &cantidadMujeres, 
            int &cantidadHombresJovenesVenTptele, int &cantidadHombresJovenes, 
            int &cantidadAdultosRegistrados, 
            int &cantidadCanalesVistos);
void leeFecha(int& fecha);
void leeHora(int& hora);

void procesaDatos(int &cantidadTelevidentes, 
        int &cantidadMenoresVenRangoHora, 
        int &cantidadMujeresAdultasFueraRangoHora, 
        int &cantidadHombresJovenesMinimoHoras, 
        int &cantidadVenCanalesExclusivamente, 
        int &cantidadJovenesYAdultos, int &tiempoTotalVistoJovenesyAdultos, 
        int &cantidadMujeresVenTvpucp, int &cantidadMujeres, 
        int &cantidadHombresJovenesVenTptele, int &cantidadHombresJovenes, 
        int &cantidadAdultosRegistrados, 
        int &cantidadCanalesVistos, 
        char sexo, int fechaNacimiento,
        int horaInicio, int horaFin, int tiempoVisto, 
        int canal1, int canal2, int canal3, char empresa);

void imprimeEncabezado();
void imprimeEncabezados();
void imprimeDatos(int dni, char sexo, int fechaNacimiento, 
        int horaInicio, int horaFin, 
        int tiempoVisto, 
        int canal1, int canal2, int canal3, char empresaAsociada);
void imprimeSexo(char sexo);
void imprimeCategoria(int fechaNacimiento);
void imprimeHora(int hora);
void imprimeCanales(int canal1, int canal2, int canal3);
void imprimeCompania(char empresa);
void imprimeEstadisticas(int cantidadTelevidentes, 
            int cantidadMenoresVenRangoHora, 
            int cantidadMujeresAdultasFueraRangoHora, 
            int cantidadHombresJovenesMinimoHoras, 
            int cantidadVenCanalesExclusivamente, 
            double promedioTiempoVistaJovenesYAdultos, 
            double porcentajeMujeresVenTvpucp, 
            double porcentajeHombresJovensVenTptele, 
            double porcentajeAdultosRegistrados, 
            double promedioCanalesVenTelevidentes);



#endif /* FUNCIONESAUXILIARES_H */


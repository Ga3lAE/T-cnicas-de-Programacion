

/* 
 * File:   funcions.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 28 de junio de 2023, 06:42 PM
 */

#ifndef FUNCIONS_H
#define FUNCIONS_H

#include "Empleados.h"
#include "Areas.h"
void leerAreas(struct Area* areas, int& numAreas);
void leerCamposEmpleados(struct Area* areas, int numAreas);
void solicitudDeTrimestreyAnio(int &anio,int &trimestre);
void leerHorasTrabajo(struct Area* areas, int numAreas, int anio, int trimestre);
void asignarHoras(struct Area *areas,int posArea,int posEmpleado,int horaIni,
        int minIni,int segIni,int horaFin,int minFin,int segFin,int anioLaboral,
        int mesLaboral,double &tiempoxDia);
void calculaHoraxAnio(struct Area *areas,int posArea,int posEmpleado);
void imprimEncabezado(ofstream& archReporte, int anio, int trimestre);
void emiteReporte(struct Area *areas,int numAreas,int anio,int trimestre);
void imprimeAreasyEncabezado(struct Area &area,ofstream &archReporte);
void imprimeResumenParcial(ofstream& archReporte, int contEmpleados, 
        double horasParcialesExtras);
void imprimeResumenTotal(ofstream& archReporte, int cantEmpladosTotales,
        double horasTotalesExtras);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);
void buscarEmpleado(struct Area *areas, int codigo, int numDatos,int &posArea,
        int &posEmpleado);
void analizaRango(int &minMes,int &maxMes,int trimestre);
char *leerCadenaExacta(ifstream& arch);
int analizaMaximoMes(int trimestre);
#endif /* FUNCIONS_H */


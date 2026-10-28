

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 28 de junio de 2023, 06:41 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "TotalHoraxMes.h"
#include "Empleados.h"
#include "Areas.h"


#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "funciones.h"


void leerAreas(struct Area *areas,int &numAreas){
    
    ifstream archAreas("areas.csv",ios::in);
    if(not archAreas.is_open()){
        cout<<"ERROR al abrir el archivo de areas"<<endl;
        exit(1);
    }
    
    int codigoArea;
    char *ptr_nombArea;
    double horasLaborales;
    
    numAreas=0;
    while(true){
        archAreas>>codigoArea;
        if(archAreas.eof())break;
        archAreas.get();
        ptr_nombArea = leerCadenaExacta(archAreas);
        archAreas>>horasLaborales;
        
        areas[numAreas].codigo = codigoArea;
        areas[numAreas].nombre = ptr_nombArea;
        areas[numAreas].horasLaborales = horasLaborales;
        areas[numAreas].numeroEmpleados=0;
        areas[numAreas].empleados = new struct Empleado[25];
        numAreas++;
    }
}


void leerCamposEmpleados(struct Area *areas, int numAreas){
    
    ifstream archEmpleados("empleados.csv",ios::in);
    if(not archEmpleados.is_open()){
        cout<<"ERROR al abrir el archivo de empleados"<<endl;
        exit(1);
    }
    int dni,codArea,dia,mes,anio;
    char *ptr_nombEmpleado,c;
    while(true){
        archEmpleados>>dni;
        if(archEmpleados.eof())break;
        archEmpleados.get();
        ptr_nombEmpleado = leerCadenaExacta(archEmpleados);
        archEmpleados>>dia>>c>>mes>>c>>anio>>c;
        archEmpleados>>codArea;
        
        for(int i=0;i<numAreas;i++){
            if(areas[i].codigo==codArea){
                areas[i].empleados[areas[i].numeroEmpleados].dni = dni;
                areas[i].empleados[areas[i].numeroEmpleados].nombre =ptr_nombEmpleado;
                areas[i].empleados[areas[i].numeroEmpleados].diaIngreso=dia;
                areas[i].empleados[areas[i].numeroEmpleados].mesIngreso=mes;
                areas[i].empleados[areas[i].numeroEmpleados].anioIngreso=anio;
                areas[i].empleados[areas[i].numeroEmpleados].codigoArea =codArea;
                areas[i].empleados[areas[i].numeroEmpleados].numeroMesesLaborales=0;
                areas[i].empleados[areas[i].numeroEmpleados].horasTrabajadas = new struct TotalHoraxMes[3];
                
                areas[i].numeroEmpleados++;
            }
        }
    }
}

void solicitudDeTrimestreyAnio(int &anio,int &trimestre){
    cout<<"Ingrese anio: ";
    cin>>anio;
    cout<<"Ingrese trimestre: ";
    cin>>trimestre;
}

void leerHorasTrabajo(struct Area *areas,int numAreas,int anio,int trimestre){   
    ifstream archHoras("horas_trabajo.csv",ios::in);
    if(not archHoras.is_open()){
        cout<<"ERROR al abrir el archivo de horas_trabajo"<<endl;
        exit(1);
    }
    int mesLaboral,dniEmpleado,anioLaboral,diaLaboral,horaIni,minIni,segIni,
            horaFin,minFin,segFin,minMes,maxMes,posArea,posEmpleado,cantDias;
    analizaRango(minMes,maxMes,trimestre);
    double tiempoxDia;
    char c;
    while(true){
        archHoras>>dniEmpleado;
        if(archHoras.eof())break;
        archHoras.get();
        buscarEmpleado(areas,dniEmpleado,numAreas,posArea,posEmpleado);
        if(posEmpleado!=NO_ENCONTRADO){
            archHoras>>anioLaboral>>c>>mesLaboral>>c;
            if(mesLaboral>=minMes and mesLaboral<=maxMes){
                tiempoxDia=0;
                cantDias=0;
                while(true){
                    archHoras>>diaLaboral>>c;
                    archHoras>>horaIni>>c>>minIni>>c>>segIni>>c;
                    archHoras>>horaFin>>c>>minFin>>c>>segFin;
                    if(cantDias<28){
                        asignarHoras(areas,posArea,posEmpleado,horaIni,minIni,
                                segIni,horaFin,minFin,segFin,anioLaboral,
                                mesLaboral,tiempoxDia);
                    }
                    cantDias++;
                    if(archHoras.get()=='\n')break;
                }
                areas[posArea].empleados[posEmpleado].numeroMesesLaborales++;
            }else while(archHoras.get()!='\n');
        }else while(archHoras.get()!='\n');
    }
}

void asignarHoras(struct Area *areas,int posArea,int posEmpleado,int horaIni,
        int minIni,int segIni,int horaFin,int minFin,int segFin,int anioLaboral,
        int mesLaboral,double &tiempoxDia){
    
    tiempoxDia+=(horaFin-horaIni)+(double)(minFin-minIni)/60+
            (double)(segFin-segIni)/3600;
    
    /*Asignando anio laboral*/
    areas[posArea].empleados[posEmpleado].horasTrabajadas[areas[posArea].
            empleados[posEmpleado].numeroMesesLaborales].anioTrabajado=anioLaboral;
    
    /*Asignando mes laboral*/
    areas[posArea].empleados[posEmpleado].horasTrabajadas[areas[posArea].
            empleados[posEmpleado].numeroMesesLaborales].mesTrabajado=mesLaboral;
    
    /*Asignando las horas laborales en el mes*/
    areas[posArea].empleados[posEmpleado].horasTrabajadas[areas[posArea].
        empleados[posEmpleado].numeroMesesLaborales].totalHorasTrabajadoxMes=tiempoxDia;
}

void emiteReporte(struct Area *areas,int numAreas,int anio,int trimestre){  
    ofstream archReporte("Control_Horas_Trabajadas.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de Control_Horas_Trabajadas"<<endl;
        exit(1);
    }
    int contEmpleados,cantEmpladosTotales=0;
    archReporte<<setprecision(2);
    archReporte<<fixed;
    imprimEncabezado(archReporte,anio,trimestre);
    double horasTotales,horasJornada,horasExtras,horasParcialesExtras,horasTotalesExtras=0;
    for(int i=0;i<numAreas;i++){
        imprimeAreasyEncabezado(areas[i],archReporte);
        contEmpleados=0;
        horasParcialesExtras=0;
        for(int k=0;k<areas[i].numeroEmpleados;k++){
            if(areas[i].empleados[k].numeroMesesLaborales>0){
                contEmpleados++;
                cantEmpladosTotales++;
                archReporte<<contEmpleados<<')'<<setw(10)<<areas[i].empleados[k].
                        dni<<setw(10)<<' '<<left<<setw(40)<<areas[i].empleados[k].
                        nombre<<setw(10)<<' '<<right<<setw(2)<<areas[i].empleados[k].
                        diaIngreso<<'/'<<setw(2)<<areas[i].empleados[k].
                        mesIngreso<<'/'<<areas[i].empleados[k].anioIngreso<<setw(10)<<' ';
                horasTotales=0;
                for(int j=0;j<areas[i].empleados[k].numeroMesesLaborales;j++){
                    horasTotales+=areas[i].empleados[k].horasTrabajadas[j].totalHorasTrabajadoxMes;         
                }
                archReporte<<horasTotales<<setw(10)<<' ';
                horasJornada=4.5*areas[i].horasLaborales*
                        areas[i].empleados[k].numeroMesesLaborales;
                horasExtras=horasTotales-horasJornada; 
                archReporte<<horasJornada<<setw(15)<<horasExtras<<endl;
                horasParcialesExtras+=horasExtras;
            }
            horasTotalesExtras+=horasExtras;
        }imprimeResumenParcial(archReporte,contEmpleados,horasParcialesExtras);
    }imprimeResumenTotal(archReporte,cantEmpladosTotales,horasTotalesExtras);
}
void imprimEncabezado(ofstream &archReporte,int anio,int trimestre){
    archReporte<<"CONTROL DE HORAS TRABAJADA POR AREA"<<endl;
    archReporte<<"ANIO: "<<anio;
    archReporte<<"Trimestre: "<<trimestre;
    if(trimestre==1)archReporte<<"Enero a Marzo"<<endl;
    else if(trimestre==2)archReporte<<"Abril a Junio"<<endl;
    else if(trimestre==3)archReporte<<"Julio a Setiembre"<<endl;
    else if(trimestre==4)archReporte<<"Octubre a diciembre"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}

void imprimeResumenTotal(ofstream &archReporte,int cantEmpladosTotales,
        double horasTotalesExtras){
    archReporte<<"RESUMEN:"<<endl;
    archReporte<<"Total de empleados: "<<cantEmpladosTotales<<endl;
    archReporte<<"Total horas extras en el trimestre: "<<horasTotalesExtras<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}
void imprimeResumenParcial(ofstream &archReporte,int contEmpleados,
        double horasParcialesExtras){
    imprimeLinea('-',MAX_LINE,archReporte);
    archReporte<<"Total de empleados: "<<contEmpleados<<endl;
    archReporte<<"Total horas extras en el trimestre: "<<horasParcialesExtras<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}

void imprimeAreasyEncabezado(struct Area &area,ofstream &archReporte){
    archReporte<<"Area: "<<area.codigo<<" - "<<area.nombre<<endl;
    archReporte<<"Horas de la jornada semanal: "<<area.horasLaborales<<endl;
    imprimeLinea('-',MAX_LINE,archReporte);
    archReporte<<setw(6)<<' '<<"DNI"<<setw(13)<<' '<<"NOMBRE"<<setw(40)<<' '
            <<"Fecha de Ingreso"<<setw(5)<<' '<<"HORAS TOTALES"<<setw(2)<<' '
            <<"HORAS JORNADA"<<setw(4)<<' '<<"HORAS EXTRAS"<<endl;
}

void imprimeLinea(char caracter, int cantidad , ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}

void buscarEmpleado(struct Area *areas, int codigo, int numDatos,int &posArea,
        int &posEmpleado){
    
    for(int i=0;i<numDatos;i++)
        for(int k=0;k<areas[i].numeroEmpleados;k++){
            if(areas[i].empleados[k].dni == codigo){
                posArea=i;
                posEmpleado=k;
                return ;
            }
        }
    posArea=NO_ENCONTRADO;
    posEmpleado=NO_ENCONTRADO;
}

void analizaRango(int &minMes,int &maxMes,int trimestre){
    if(trimestre==1){
        minMes=1;
        maxMes=3;
    }else if(trimestre==2) {
        minMes=4;
        maxMes=6;
    }else if(trimestre==3){
        minMes=7;
        maxMes=9;
    }else if(trimestre==4){
        minMes=10;
        maxMes=12;
    }
}


char *leerCadenaExacta(ifstream &arch){
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    
    longitud = strlen(buffer);
    cadena = new char[longitud+1];
    
    strcpy(cadena,buffer);
    return cadena;
}
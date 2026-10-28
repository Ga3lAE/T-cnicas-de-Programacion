#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxiliares.h"

#define MAX_CAR_LIN 150
#define MAX_CAR_FECHA 12
#define MAX_CAR_DNI 10
#define MAX_CAR_HORA 14
#define MAX_CAR_DURA 18
#define MAX_CAR_ESP 20
#define MAX_CAR_PAG 16

#define FECHA_LIMITE 20240115
#define MINIMO_GASTO 350.00

void imprimeLinea(char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        cout<<c;
    }
    cout<<endl;
}

void leeRegistraDatos(int &cantidadPacientes, 
            int &cantidadSiMedicina,int &cantidadNoMedicina, 
            int &cantidadDermaSiMedicina, int &cantidadPed, 
            int &cantidadCardFecha, int &cantidadNoMedicinasGastom,
            double &gastosMedicina, double &gastosDermaSiMedicina){
    
    imprimeEncabezado();
    
    //16/01/2024   36471787   09:28:04   09:54:07   342.86   C   S   44.37
    int fecha, dniPaciente, horaInicio, horaFin;
    double tarifaMedico, pagoMedicinas=0;
    char especialidad, recibeMedicina;
       
    double totalIngresos=0; 
    
    while(true){
        leeFecha(fecha);
        if(cin.eof()) break;
        cin>>dniPaciente;
        leeHora(horaInicio);
        leeHora(horaFin);
        cin>>tarifaMedico>>especialidad>>recibeMedicina;
        if(recibeMedicina == 'S'){
            cin>>pagoMedicinas;
        }
        
        int duracionHMS;
        double duracionH, pagoTotal;
        
        procesaDatos(cantidadPacientes, 
                cantidadSiMedicina,cantidadNoMedicina, 
                cantidadDermaSiMedicina, cantidadPed, 
                cantidadCardFecha, cantidadNoMedicinasGastom,
                gastosMedicina, gastosDermaSiMedicina, 
                fecha, horaInicio, horaFin, 
                tarifaMedico, especialidad, 
                pagoMedicinas, recibeMedicina,
                duracionHMS, duracionH, pagoTotal);
        
        imprimeDatos(fecha, dniPaciente, horaInicio, horaFin, 
                duracionHMS, duracionH, especialidad, pagoTotal);
        totalIngresos+=pagoTotal;
       
    }
    
    imprimeLinea('=');
    cout<<"TOTAL DE INGRESOS: "<<totalIngresos<<endl;
    imprimeLinea('=');            
}
void leeFecha(int& fecha){
    int dd,mm,aa;
    char sep;
    cin>>dd;
    if(cin.eof()) return;
    cin>>sep>>mm>>sep>>aa;
    
    fecha = aa*10000+mm*100+dd;
}
void leeHora(int& hora){
    int hh, mm, ss;
    char sep;
    cin>>hh>>sep>>mm>>sep>>ss;
    
    hora = hh*3600+mm*60+ss;
}
void procesaDatos(int &cantidadPacientes, 
                int &cantidadSiMedicina, int &cantidadNoMedicina, 
                int &cantidadDermaSiMedicina, int &cantidadPed, 
                int &cantidadCardFecha, int &cantidadNoMedicinasGastom,
                double &gastosMedicina, double &gastosDermaSiMedicina, 
                int fecha, int horaInicio, int horaFin, 
                double tarifaMedico, char especialidad, 
                double pagoMedicinas, char recibeMedicina,
                int &duracionHMS, double &duracionH, double &pagoTotal){
    
    
    duracionHMS = horaFin-horaInicio;
    duracionH = duracionHMS/3600.0;
    pagoTotal = pagoMedicinas + tarifaMedico*duracionH;
    
    cantidadPacientes++;
    if(recibeMedicina=='S'){
        cantidadSiMedicina++;
        if(especialidad == 'D'){
            cantidadDermaSiMedicina++;
            gastosDermaSiMedicina+=pagoMedicinas;
                
        }
        
    }
    else{
        cantidadNoMedicina++;           
        if(pagoTotal<=MINIMO_GASTO)
            cantidadNoMedicinasGastom++;
    } 
      
    if(especialidad == 'P')
        cantidadPed++;
    if(especialidad == 'C' and fecha >=FECHA_LIMITE)
        cantidadCardFecha++;
    
    gastosMedicina+=pagoMedicinas;                                
}

void imprimeDatos(int fecha, int dniPaciente, 
        int horaInicio, int horaFin, 
        int duracionHMS, double duracionH, char especialidad, double pagoTotal){
    cout<<left<<fixed;
    imprimeFecha(fecha);
    cout<<setw(MAX_CAR_DNI)<<dniPaciente;
    imprimeHora(horaInicio);
    imprimeHora(horaFin);
    imprimeHora(duracionHMS);
    cout<<setw(MAX_CAR_DURA-MAX_CAR_HORA)<<' ';
    cout<<setw(MAX_CAR_DURA)<<setprecision(4)<<duracionH<<setprecision(2);
    imprimeEspecialidad(especialidad);
    cout<<right<<setw(MAX_CAR_PAG)<<pagoTotal<<left
            <<endl;
}
void imprimeEncabezado(){
    cout<<setw(MAX_CAR_LIN/2)<<"EMRPESA DE SALUD S.A."<<endl;
    imprimeLinea('=');
    cout<<left<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS:"<<endl; 
    imprimeCategorias();
}
void imprimeCategorias(){
    cout<<left
            <<setw(MAX_CAR_FECHA)<<"FECHA"
            <<setw(MAX_CAR_DNI)<<"PACIENTE"
            <<setw(MAX_CAR_HORA)<<"INICIO"
            <<setw(MAX_CAR_HORA)<<"FIN"
            <<setw(MAX_CAR_DURA)<<"DURACION (H:M:S)"
            <<setw(MAX_CAR_DURA)<<"DURACION (H)"
            <<setw(MAX_CAR_ESP)<<"ESPECIALIDAD"
            <<setw(MAX_CAR_PAG)<<"PAFO (cita+medicina)"<<endl;
    imprimeLinea('-');
}
void imprimeFecha(int fecha){
    int dd,mm,aa;
    char sep='/';
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    cout<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')
            <<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeHora(int hora){
    int hh, mm, ss;
    char sep=':';
    hh=hora/3600;
    hora%=3600;
    mm=hora/60;
    ss=hora%60;
    
    cout<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<left<<setfill(' ')
            <<setw(MAX_CAR_HORA-8)<<' ';        
}
void imprimeEspecialidad(char especialidad){
    if(especialidad =='P')
        cout<<setw(MAX_CAR_ESP)<<"PEDIATRIA";
    else if(especialidad =='C')
        cout<<setw(MAX_CAR_ESP)<<"CARDIOLOGIA";
    else if(especialidad =='D')
        cout<<setw(MAX_CAR_ESP)<<"DERMATOLOGIA";
}

void imprimeReporteFinal(double promedioGastosSiMedicina, 
            double promediogastosSiMedicinaDerma, 
            double porcentajeNoMedicinas, 
            double porcentajePed, 
            int cantidadCardFecha, 
            double porcentajeNoMedicinaGastom){
    cout<<"ESTADISTICAS OBTENIDAS:"<<endl
            <<"Promedio de gastos por medicina de los pacientes que les recetaron medicina: "<<promedioGastosSiMedicina<<endl
            <<"Promedio de gastos por medicinas de los pacientes que se atendieron en deramtologia: "<<promediogastosSiMedicinaDerma<<endl
            <<"Porcentaje de pacientes que no le recetaron medicina: "<<porcentajeNoMedicinas<<'%'<<endl
            <<"Porcentaje de pacientes que se atendieron en pediatria: "<<porcentajePed<<'%'<<endl
            <<"Cantidad de pacientes que se atendieron en cardiologia despues del ";
    imprimeFecha(FECHA_LIMITE);
    cout<<": "<<cantidadCardFecha<<endl
        <<"Porcetaje de pacientes que no le recetaron medicinasy que gasto más de "<<MINIMO_GASTO<<": "<<porcentajeNoMedicinaGastom<<'%'<<endl;
    imprimeLinea('=');
    
}
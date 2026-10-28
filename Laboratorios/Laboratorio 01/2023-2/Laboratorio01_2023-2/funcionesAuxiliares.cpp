#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

#include "funcionesAuxiliares.h"

#define MAX_CAR_LIN 150

#define CANTIDAD_CANALES_MAXIMA 3
#define FECHA_MINIMA_MENOR 2009
#define FECHA_MINIMA_JOVEN 1988
#define RANGO_F_HORA_INICIO 9*3600+30*60
#define RANGO_F_HORA_FIN 12*3600+45*60
#define RANGO_M_HORA_INICIO 14*3600
#define RANGO_M_HORA_FIN 19*3600
#define TVPUCUP 'A'
#define CABLEMAS 'B'
#define TPVISION 'C'

#define MAX_CAR_DNI 10
#define MAX_CAR_SEXO 15
#define MAX_CAR_CTG 15
#define MAX_CAR_HORA 16
#define MAX_CAR_CANAL 15
#define MAX_CAR_COMP 18

void imprimeLinea(char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        cout<<c;
    }
    cout<<endl;
}

void leeImprimeDatos(int &cantidadTelevidentes, 
            int &cantidadMenoresVenRangoHora, 
            int &cantidadMujeresAdultasFueraRangoHora, 
            int &cantidadHombresJovenesMinimoHoras, 
            int &cantidadVenCanalesExclusivamente, 
            int &cantidadJovenesYAdultos, int &tiempoTotalVistoJovenesyAdultos, 
            int &cantidadMujeresVenTvpucp, int &cantidadMujeres, 
            int &cantidadHombresJovenesVenTptele, int &cantidadHombresJovenes, 
            int &cantidadAdultosRegistrados, 
            int &cantidadCanalesVistos){
    
    imprimeEncabezado();
    //datos de los televidentes
    //69323674    M    31/03/2013  13:54:27     16:12:37   556    0    0     B
    int dni, fechaNacimiento, horaInicio, horaFin, canal1, canal2, canal3;
    char sexo, empresaAsociada;
    
    int tiempoVisto;
    
    while(true){
        cin>>dni;
        if(cin.eof()) break;
        cin>>sexo;
        leeFecha(fechaNacimiento);
        leeHora(horaInicio);
        leeHora(horaFin);
        
        tiempoVisto = horaFin-horaInicio;
        
        cin>>canal1>>canal2>>canal3>>empresaAsociada;
        
        procesaDatos(cantidadTelevidentes, 
                cantidadMenoresVenRangoHora, 
                cantidadMujeresAdultasFueraRangoHora, 
                cantidadHombresJovenesMinimoHoras, 
                cantidadVenCanalesExclusivamente, 
                cantidadJovenesYAdultos, tiempoTotalVistoJovenesyAdultos, 
                cantidadMujeresVenTvpucp, cantidadMujeres, 
                cantidadHombresJovenesVenTptele, cantidadHombresJovenes, 
                cantidadAdultosRegistrados, 
                cantidadCanalesVistos, 
                sexo, fechaNacimiento, 
                horaInicio, horaFin, tiempoVisto, 
                canal1, canal2, canal3, empresaAsociada);
                
        imprimeDatos(dni, sexo, fechaNacimiento, horaInicio, horaFin, tiempoVisto, 
                canal1, canal2, canal3, empresaAsociada);
        
    }
    imprimeLinea('=');
}

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
        int canal1, int canal2, int canal3, char empresa){
    
    cantidadTelevidentes++;
    
    if(sexo=='F'){ 
        cantidadMujeres++;
        if((horaFin<RANGO_F_HORA_INICIO or horaInicio>RANGO_F_HORA_FIN) 
            and 
            fechaNacimiento<=FECHA_MINIMA_JOVEN){
                cantidadMujeresAdultasFueraRangoHora++;
            }
        if(empresa == TVPUCUP)
            cantidadMujeresVenTvpucp++;
    }
    else if(sexo =='M'){
        if(fechaNacimiento <FECHA_MINIMA_MENOR and fechaNacimiento >=FECHA_MINIMA_JOVEN){
            cantidadHombresJovenes++;
            if(tiempoVisto>3*3600+30*60)
                cantidadHombresJovenesMinimoHoras++;
            if(empresa == TPVISION)
                cantidadHombresJovenesVenTptele++;            
        }        
    }
    
    if(fechaNacimiento>=FECHA_MINIMA_MENOR){
        if(horaFin<RANGO_M_HORA_INICIO or horaInicio>RANGO_M_HORA_FIN)
            cantidadMenoresVenRangoHora++;
    }
    else if(fechaNacimiento>=FECHA_MINIMA_JOVEN){
        cantidadJovenesYAdultos++;
        tiempoTotalVistoJovenesyAdultos+=tiempoVisto;
    }
    else{
        cantidadJovenesYAdultos++;
        tiempoTotalVistoJovenesyAdultos+=tiempoVisto;
        cantidadAdultosRegistrados++;
    }
    
    cantidadCanalesVistos+=(canal1!=0)?1:0;
    cantidadCanalesVistos+=(canal2!=0)?1:0;
    cantidadCanalesVistos+=(canal3!=0)?1:0;        
}

void leeFecha(int &fecha){
    int dd,mm,aa;
    char sep;
    
    cin>>dd>>sep>>mm>>sep>>aa;
    fecha = aa;
}
void leeHora(int &hora){
    int hh, mm, ss;
    char sep;
    
    cin>>hh>>sep>>mm>>sep>>ss;
    hora = hh*3600+mm*60+ss;
}

void imprimeEncabezado(){
    cout<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE OPINION DE MERCADO VENUS S.A."<<endl;
    imprimeLinea('=');
    cout<<left<<"REGIOSTRO DE PREFERENCIA DE TELEVIDENTES"<<endl;
    imprimeLinea('=');
    imprimeEncabezados();
}
void imprimeEncabezados(){
    cout<<left
            <<setw(MAX_CAR_DNI)<<"DNI No."
            <<setw(MAX_CAR_SEXO)<<"SEXO"
            <<setw(MAX_CAR_CTG)<<"CATEGORIA"
            <<setw(MAX_CAR_HORA)<<"HORA (P)"
            <<setw(MAX_CAR_HORA)<<"HORA (A)"
            <<setw(MAX_CAR_HORA)<<"DURACION(H:M:S)"
            <<setw(MAX_CAR_HORA)<<"DURACION(H)"
            <<setw(MAX_CAR_CANAL)<<"CANALES"
            <<setw(MAX_CAR_COMP)<<"COMPANIA"
            <<endl;
    
    imprimeLinea('-');
}
void imprimeDatos(int dni, char sexo, int fechaNacimiento, 
        int horaInicio, int horaFin, int tiempoVisto, 
        int canal1, int canal2, int canal3, char empresaAsociada){
    cout<<left
            <<setw(MAX_CAR_DNI)<<dni;
    imprimeSexo(sexo);
    imprimeCategoria(fechaNacimiento);
    imprimeHora(horaInicio);
    imprimeHora(horaFin);
    imprimeHora(tiempoVisto);
    cout<<fixed<<setprecision(4)
            <<setw(MAX_CAR_HORA)<<tiempoVisto/3600.0;
    imprimeCanales(canal1, canal2, canal3);
    imprimeCompania(empresaAsociada);
    cout<<endl;
}
void imprimeSexo(char sexo){
    if(sexo == 'M')
        cout<<setw(MAX_CAR_SEXO)<<"MASCULINO";
    else if(sexo == 'F')
        cout<<setw(MAX_CAR_SEXO)<<"FEMENINO";
}
void imprimeCategoria(int fechaNacimiento){
    if(fechaNacimiento>FECHA_MINIMA_MENOR)
        cout<<setw(MAX_CAR_SEXO)<<"MENOR";
    else if(fechaNacimiento<FECHA_MINIMA_JOVEN)
        cout<<setw(MAX_CAR_CTG)<<"JOVEN";
    else 
        cout<<setw(MAX_CAR_CTG)<<"ADULTO";
    
}
void imprimeHora(int hora){
    int hh, mm, ss;
    char sep=':';
    hh=hora/3600;
    hora%=3600;
    mm=hora/60;
    ss=hora%60;
    
    cout<<setfill('0')<<right
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm<<sep
            <<setw(2)<<ss
            <<setfill(' ')<<left<<setw(MAX_CAR_HORA-8)<<' ';
    
}
void imprimeCanales(int canal1, int canal2, int canal3){
    char sep='/';
    cout<<setfill('0')<<right
            <<setw(3)<<canal1<<sep
            <<setw(3)<<canal2<<sep
            <<setw(3)<<canal3
            <<setfill(' ')<<left<<setw(MAX_CAR_CANAL-11)<<' ';
}
void imprimeCompania(char empresa){
    if(empresa =='A')
        cout<<setw(MAX_CAR_COMP)<<"TVPUCP";
    else if(empresa =='B')
        cout<<setw(MAX_CAR_COMP)<<"CABLEMAS";
    if(empresa =='C')
        cout<<setw(MAX_CAR_COMP)<<"TPVISION";
}

void imprimeEstadisticas(int cantidadTelevidentes, 
            int cantidadMenoresVenRangoHora, 
            int cantidadMujeresAdultasFueraRangoHora, 
            int cantidadHombresJovenesMinimoHoras, 
            int cantidadVenCanalesExclusivamente, 
            double promedioTiempoVistaJovenesYAdultos, 
            double porcentajeMujeresVenTvpucp, 
            double porcentajeHombresJovensVenTptele, 
            double porcentajeAdultosRegistrados, 
            double promedioCanalesVenTelevidentes){
    cout<<left<<fixed<<setprecision(2)
            <<"ESTADISTICAS OBTENIDAS:"<<endl
            <<"CANTIDAD DE TELEVIDENTES REGISTRADOS: "<<cantidadTelevidentes<<endl            
            <<"CANTIDAD DE MENORES QUE VEN ENTRE LAS 14:00:00 Y LAS 19:00:00: "<<cantidadMenoresVenRangoHora<<endl            
            <<"CANTIDAD DE MUJERES ADULTAS QUE NO VEN TELEVISION ENTRE LAS 9:30:00 Y LAS 12:45:00: "<<cantidadMujeresAdultasFueraRangoHora<<endl            
            <<"CANTIDAD DE HOMBRES JOVENES QUE VE MAS DE 3 HORAS Y MEDIA: "<<cantidadHombresJovenesMinimoHoras<<endl            
            <<"CANTIDAD DE PERSONAS QUE VEN LOS CANALES 770, 312 O 577 PERO NO 314 NI 555: "<<cantidadVenCanalesExclusivamente<<endl
            <<"TIEMPO PROMEDIO QUE VEN LOS MENORES Y ADULTOS: "<<promedioTiempoVistaJovenesYAdultos<<endl
            <<"PORCENTAJE DE MUJERES QUE VEN TVPUCP: "<<porcentajeMujeresVenTvpucp<<'%'<<endl
            <<"PORCENTAJE DE HOMBRES JOVENES QUE VEN TPVISION: "<<porcentajeHombresJovensVenTptele<<'%'<<endl
            <<"PORCENTAJE DE ADULTOS REGISTRADOS: "<<porcentajeAdultosRegistrados<<'%'<<endl
            <<"PROMEDIO DE CANALES QUE VEN LOS TELEVIDENTES: "<<promedioCanalesVenTelevidentes<<endl;            
}
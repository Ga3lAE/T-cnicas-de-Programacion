#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxliares.h"

#define MULTA_ESTUDIANTE 0.01
#define MULTA_DOCENTE 0.0225

#define MAX_CAR_LIN 150
#define SANGRIA 5
#define MAX_CAR_FECHA 12
#define MAX_CAR_COD 10
#define MAX_CAR_TIPO 15
#define MAX_CAR_REIN 10
#define MAX_CAR_MULTA 10

void imprimeLinea(char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        cout<<c;
    }
    cout<<endl;
}

void leeImprimeDatos(int &codigoDocenteMayorDeuda, double &montoDocenteMayorDeuda,
            int &codigoEstudianteMayorDeuda, double &montoEstudianteMayorDeuda){
    
    int fechaLimiteEstudiantes, fechaLimiteDocentes;
    leeFecha(fechaLimiteDocentes);
    leeFecha(fechaLimiteEstudiantes);
    imprimeEncabezado(fechaLimiteEstudiantes, fechaLimiteDocentes);
    //35030611E   R      06135    26/6/2021    77.27    05731    3/7/2021    352.26
    int codigo;
    char tipo, reincide;
    
    bool primeraLecturaDocente=true, primeraLecturaEstudiante=true;
    while(true){
        int cantidadLibrosAdeudados=0;
        double totalMultas=0;
        cin>>codigo;
        if(cin.eof()) break;
        cin>>tipo>>reincide;
        
        int codigoLibro, fechaPrestamo;
        double precioLibro;
        
        imprimeSubEncabezado(codigo, tipo, reincide);
        while(true){
            if(cin.get()=='\n') break;
            cin>>codigoLibro;
            leeFecha(fechaPrestamo);
            cin>>precioLibro;
            if(tipo =='E'){
                procesaImprimeLibro(codigoLibro, fechaPrestamo, precioLibro, 
                        reincide, MULTA_ESTUDIANTE, 
                        cantidadLibrosAdeudados, totalMultas);
                if(reincide=='R')
                    asignaMaximaDeuda(primeraLecturaEstudiante, 
                            codigoEstudianteMayorDeuda, montoEstudianteMayorDeuda, 
                            codigo, totalMultas);
            }
            else if(tipo =='D'){
                procesaImprimeLibro(codigoLibro, fechaPrestamo, precioLibro, 
                        reincide, MULTA_DOCENTE, 
                        cantidadLibrosAdeudados, totalMultas);
                if(reincide == 'R')
                    asignaMaximaDeuda(primeraLecturaDocente, 
                            codigoDocenteMayorDeuda, montoDocenteMayorDeuda, 
                            codigo, totalMultas);
                
                
            }
        }
        imprimeRecuentoSimple(cantidadLibrosAdeudados, totalMultas);
    }
}
void leeFecha(int& fecha){
    int dd, mm, aa;
    char sep;
    cin>>dd>>sep>>mm>>sep>>aa;
    fecha = aa*10000+mm*100+dd;
}
void procesaImprimeLibro(int codigoLibro, int fechaPrestamo, double precioLibro, 
        char reincide, double multa, 
        int &cantidadLibros, double &totalMultas){
    
    cantidadLibros++;
    totalMultas+=cantidadLibros*2;
    
    cout<<setw(SANGRIA*2)<<' '<<fixed<<setprecision(2)
            <<right<<setfill('0')
            <<setw(5)<<codigoLibro
            <<left<<setfill(' ')<<setw(MAX_CAR_COD-5)<<' ';
    imprimeFecha(fechaPrestamo);
    cout<<setw(MAX_CAR_MULTA)<<totalMultas<<endl;
}
void asignaMaximaDeuda(bool primeraLectura, 
        int &codigoMayorDeuda, double &montoMayorDeuda, 
        int codigo, double montoDeuda){
    if(primeraLectura){
        codigoMayorDeuda=codigo;
        montoMayorDeuda=montoDeuda;
    }
    else{
        if(montoDeuda>montoMayorDeuda){
            montoMayorDeuda=montoDeuda;
            codigoMayorDeuda=codigo;
        }
    }
}

void imprimeEncabezado(int fechaLimiteEstudiantes, int fechaLimiteDocentes){
    cout<<setw(MAX_CAR_LIN/2)<<"BIBLIOTECA GENERAL VENUS"<<endl;
    imprimeLinea('=');
    cout<<left<<"FECHA LIMITE DE DEVOLUCION:"<<endl
            <<"DOCENTES: ";
    imprimeFecha(fechaLimiteDocentes);
    cout<<endl
            <<"ESTUDIANTES: ";
    imprimeFecha(fechaLimiteEstudiantes);
    cout<<endl;
    imprimeLinea('-');
    cout<<right<<setw(MAX_CAR_LIN/2)<<"RELACION DE USUARIOS RETRASADOS EN SU ENTREGA"
            <<endl<<left;
    
}
void imprimeFecha(int fecha){
    int dd, mm, aa;
    char sep='/';
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    
    cout<<right<<setfill('0')
            <<setw(2)<<dd<<sep
            <<setw(2)<<mm<<sep
            <<setw(4)<<aa
            <<left<<setfill(' ')<<setw(MAX_CAR_FECHA-10)<<' ';
}
void imprimeSubEncabezado(int codigo, char tipo, char reincide){
    imprimeLinea('=');
    cout<<left<<setw(SANGRIA)<<' '
            <<"CARNE No.: "<<setw(MAX_CAR_COD)<<codigo;
    imprimeTipo(tipo);
    imprimeReincidencias(reincide);
    imprimeLinea('-');
    cout<<"LIBROS EN SU PODER RETRASADOS, RETRASADOS EN SU ENTREGA: "<<endl;
    cout<<setw(SANGRIA*2)<<' '
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_FECHA)<<"F. ENTREGA"    
            <<setw(MAX_CAR_MULTA)<<"MULTA"<<endl;
    
}
void imprimeTipo(char tipo){
    cout<<"TIPO: ";
    if(tipo=='E')
        cout<<setw(MAX_CAR_TIPO)<<"ESTUDIANTE";
    else if(tipo=='D')
        cout<<setw(MAX_CAR_TIPO)<<"DOCENTE";
}
void imprimeReincidencias(char reincide){    
    if(reincide=='R')
        cout<<"- "<<setw(MAX_CAR_REIN)<<"REINCIDENTE";
    cout<<endl;
}
void imprimeRecuentoSimple(int cantidadLibros, double totalDeuda){
    imprimeLinea('=');
    cout<<fixed<<setprecision(2)
            <<setw(SANGRIA*1)<<' '<<"CANTIDAD DE LIBROS ADEUDADOS: "<<cantidadLibros<<endl
            <<setw(SANGRIA*1)<<' '<<"TOTAL DE DEUDAS POR MULTA: "<<totalDeuda<<endl;
    imprimeLinea('=');
    imprimeLinea('/');
            
}
void imprimeResumen(int codigoDocenteMayorDeuda, double montoDocenteMayorDeuda,
            int codigoEstudianteMayorDeuda, double montoEstudianteMayorDeuda){
    cout<<"RESUMEN:"<<endl<<fixed<<setprecision(2); 
    cout<<"REINCIDENTE CON MAYOR DEUDA: "<<endl
            <<"DOCENTE: "
            <<setw(MAX_CAR_COD)<<codigoDocenteMayorDeuda
            <<setw(MAX_CAR_MULTA)<<montoDocenteMayorDeuda<<endl
            <<"ESTUDIANTE: "
            <<setw(MAX_CAR_COD)<<codigoEstudianteMayorDeuda
            <<setw(MAX_CAR_MULTA)<<montoEstudianteMayorDeuda<<endl;
            
}
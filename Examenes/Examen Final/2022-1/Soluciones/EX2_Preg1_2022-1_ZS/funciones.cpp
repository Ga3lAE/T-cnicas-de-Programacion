

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 29 de junio de 2023, 01:27 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "StructCursoMatriculado.h"
#include "StructAlumno.h"
#include "StructCurso.h"
#include "funciones.h"

void leerCursos(struct Curso *cursos,int &numCursos){
       
    ifstream archCursos("Cursos.csv",ios::in);
    if(not archCursos.is_open()){
        cout<<"ERROR al abrir el archivo de cursos "<<endl;
        exit(1);
    }
    
    char *ptr_codCurso,*ptr_nombCurso;
    double creditos;
    numCursos=0;
    
    while(true){
        ptr_codCurso = leerCadenaExacta(archCursos);
        if(archCursos.eof())break;
        ptr_nombCurso = leerCadenaExacta(archCursos);
        archCursos>>creditos;
        archCursos.get();
        cursos[numCursos].codigo= ptr_codCurso;
        cursos[numCursos].nombre = ptr_nombCurso;
        cursos[numCursos].creditos = creditos;
        numCursos++;
    }
    
}

void leerAlumnos(struct Alumno *alumnos,int &numAlumnos){  
    ifstream archAlumnos("alumnos.csv",ios::in);
    if(not archAlumnos.is_open()){
        cout<<"ERROR al abrir el archivo de alumnos"<<endl;
        exit(1);
    }
    int codigo;
    char *ptr_nombAlumno,c;
    double credAprob,credDesaprob,credFaltantes;
    numAlumnos=0;
    while(true){
        archAlumnos>>codigo;
        if(archAlumnos.eof())break;
        archAlumnos.get();
        ptr_nombAlumno = leerCadenaExacta(archAlumnos);
        archAlumnos>>credAprob>>c>>credDesaprob>>c>>credFaltantes;
        alumnos[numAlumnos].codigo = codigo;
        alumnos[numAlumnos].nombre = ptr_nombAlumno;
        alumnos[numAlumnos].credTotalAprob=credAprob;
        alumnos[numAlumnos].credTotalDesaprob=credDesaprob;
        alumnos[numAlumnos].credFaltantes=credFaltantes;
        alumnos[numAlumnos].cursosMatriculados = new struct CursoMatriculado[10];
        alumnos[numAlumnos].cantCursosMatric=0;
        alumnos[numAlumnos].promedioPonderado=0;
        alumnos[numAlumnos].promedioPonderadoAprobados=0;
        alumnos[numAlumnos].promedioPonderadoDesaprobados=0;
        numAlumnos++;
    }
}

void emiteReporteSimpleAlumnos(struct Alumno *alumnos,int numAlumnos){
    
    ofstream archReporte("alumnosInicial.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de alumnosInicial"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    archReporte<<"Datos Iniciales"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numAlumnos;i++){
        archReporte<<alumnos[i].codigo<<setw(10)<<' '
                <<left<<setw(40)<<alumnos[i].nombre<<right
                <<alumnos[i].credTotalAprob<<setw(10)<<' '
                <<alumnos[i].credTotalDesaprob<<setw(10)<<' '
                <<alumnos[i].credFaltantes<<endl;
    }
}

void leerProcesarNotas(struct Alumno *alumnos,int numAlumnos,
        struct Curso *cursos,int numCursos){
    ifstream archNotas("notas.txt",ios::in);
    if(not archNotas.is_open()){
        cout<<"ERROR al abrir el archivo de notas"<<endl;
        exit(1);
    }
    
    char codCurso[7],*ptr_codCurso;
    int codAlumno,nota,posCurso,posAlumno;
    
    while(true){
        archNotas>>codCurso;
        if(archNotas.eof())break;
        ptr_codCurso = new char[strlen(codCurso)+1];
        strcpy(ptr_codCurso,codCurso);
        posCurso=buscarCurso(cursos,ptr_codCurso,numCursos);
        if(posCurso!=NO_ENCONTRADO){
            while(true){
                archNotas>>codAlumno;
                archNotas>>nota;
                posAlumno=buscarAlumno(alumnos,codAlumno,numAlumnos);
                if(posAlumno!=NO_ENCONTRADO)
                    asignarValores(cursos[posCurso],alumnos[posAlumno],nota);
                if(archNotas.get()=='\n')break;
            }
        }else while(archNotas.get()!='\n');
    }
}

void asignarValores(struct Curso &curso,struct Alumno &alumno,int nota){
    
    if(nota>=11){
        alumno.credTotalAprob +=curso.creditos;
        alumno.credFaltantes-=curso.creditos;
        alumno.cursosMatriculados[alumno.cantCursosMatric].codigo = curso.codigo;
        alumno.cursosMatriculados[alumno.cantCursosMatric].nombre = curso.nombre;
        alumno.cursosMatriculados[alumno.cantCursosMatric].creditos = curso.creditos;
        alumno.cursosMatriculados[alumno.cantCursosMatric].nota=nota;
        alumno.promedioPonderado+=
                alumno.cursosMatriculados[alumno.cantCursosMatric].creditos*nota;
        alumno.promedioPonderadoAprobados+=
                alumno.cursosMatriculados[alumno.cantCursosMatric].creditos*nota;
        alumno.cantCursosMatric++;
    }else if(nota<11){
        alumno.credTotalDesaprob+=curso.creditos;
        alumno.cursosMatriculados[alumno.cantCursosMatric].codigo = curso.codigo;
        alumno.cursosMatriculados[alumno.cantCursosMatric].nombre = curso.nombre;
        alumno.cursosMatriculados[alumno.cantCursosMatric].creditos = curso.creditos;
        alumno.cursosMatriculados[alumno.cantCursosMatric].nota=nota;
        alumno.promedioPonderado+=
                alumno.cursosMatriculados[alumno.cantCursosMatric].creditos*nota;
        alumno.promedioPonderadoDesaprobados+=
                alumno.cursosMatriculados[alumno.cantCursosMatric].creditos*nota;
        alumno.cantCursosMatric++;
    }
}

void emiteReporte(struct Alumno *alumnos,int numAlumnos,struct Curso *cursos,
        int numCursos){ 
    ofstream archReporte("ReporteResultadosAlumnos.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ReporteResultadosAlumnos.txt"<<endl;
        exit(1);
    }
    int contAlumnos=0;
    double creditosTotales,creditosAprobCiclo,creditosDesaprobCiclo;
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(50)<<' '<<"INSTITUCION EDUCATIVA LIMA"<<endl;
    archReporte<<setw(45)<<' '<<"RESULTADOS DE ALUMNOS MATRICULADOS"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numAlumnos;i++){
        if(alumnos[i].cantCursosMatric>0){
            contAlumnos++;
            archReporte<<setw(8)<<contAlumnos<<".  Alumno: "<<alumnos[i].codigo
                    <<" - "<<left<<setw(45)<<alumnos[i].nombre<<right;
            if(alumnos[i].credFaltantes<=0)archReporte <<"PASA A FACULTAD"<<endl;
            else if(alumnos[i].credFaltantes>0)archReporte<<"NO PASA A FACULTAD"
                    <<endl;
            archReporte<<setw(11)<<' '<<"NOTAS EN EL CICLO"<<endl;
            archReporte<<setw(14)<<' '<<"CURSO"<<setw(43)<<' '<<"CREDITOS"
                        <<setw(4)<<' '<<"NOTA"<<endl; 
            creditosTotales=creditosAprobCiclo=creditosDesaprobCiclo=0;
            imprimeCursosMatriculados(alumnos[i],creditosAprobCiclo,
                    creditosDesaprobCiclo,creditosTotales,archReporte);
            imprimeResultadosFinal(alumnos[i],creditosAprobCiclo,creditosDesaprobCiclo,
                    creditosTotales,archReporte);
        }
    }
}

void imprimeCursosMatriculados(struct Alumno &alumno,double &creditosAprobCiclo,
        double &creditosDesaprobCiclo,double &creditosTotales,ofstream &archReporte){
    for(int k=0;k<alumno.cantCursosMatric;k++){
        archReporte<<setw(14)<<' '<<alumno.cursosMatriculados[k].
                codigo<<" - "<<left<<setw(40)<<alumno.
                cursosMatriculados[k].nombre<<right<<setw(5)
                <<alumno.cursosMatriculados[k].creditos<<setw(10)
                <<alumno.cursosMatriculados[k].nota<<endl;
        if(alumno.cursosMatriculados[k].nota>10)creditosAprobCiclo+=
                alumno.cursosMatriculados[k].creditos;
        else if(alumno.cursosMatriculados[k].nota<11)creditosDesaprobCiclo+=
                alumno.cursosMatriculados[k].creditos; 
        creditosTotales+=alumno.cursosMatriculados[k].creditos;
    }
}

void imprimeResultadosFinal(struct Alumno &alumno,double creditosAprobCiclo,
        double creditosDesaprobCiclo,double creditosTotales,ofstream &archReporte){
    imprimeLinea('-',MAX_LINE,archReporte);
    archReporte<<"RESULTADOS AL FINAL DEL CICLO"<<endl;
    archReporte<<"Creditos aprobados en el ciclo: "<<setw(11)<<creditosAprobCiclo;
    archReporte<<setw(12)<<' '<<"Promedio ponderado cursos aprobados: "
            <<setw(8)<<alumno.promedioPonderadoAprobados/creditosAprobCiclo<<endl;
    archReporte<<"Creditos desaprobados en el ciclo: "<<setw(8)<<creditosDesaprobCiclo;
    archReporte<<setw(12)<<' '<<"Promedio ponderado cursos desaprobados: "
            <<setw(5)<<alumno.promedioPonderadoDesaprobados/creditosDesaprobCiclo<<endl;
    archReporte<<"Promedio ponderado en el ciclo: "<<setw(20)
            <<alumno.promedioPonderado/creditosTotales<<endl;
    archReporte<<"Creditos aprobados acumulados: "<<setw(21)
            <<alumno.credTotalAprob<<endl;
    archReporte<<"Creditos desaprobados acumulados: "<<setw(18)
            <<alumno.credTotalDesaprob<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
}

int buscarAlumno(struct Alumno *alumnos, int codigo, int numAlumnos){
    for(int i=0;i<numAlumnos;i++)
        if(alumnos[i].codigo==codigo)return i;
    return NO_ENCONTRADO;
}

int buscarCurso(struct Curso *cursos,char *codCurso,int numCursos){
    
    for(int i=0;i<numCursos;i++)
        if(strcmp(cursos[i].codigo,codCurso)==0)return i;
    
    return NO_ENCONTRADO;
}


void imprimeLinea(char caracter, int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}
char *leerCadenaExacta(ifstream &arch){
    
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    longitud = strlen(buffer);
    cadena = new char [longitud+1];
    
    strcpy(cadena,buffer);
    
    return cadena;
}
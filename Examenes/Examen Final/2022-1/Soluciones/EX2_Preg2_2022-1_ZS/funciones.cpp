

/* 
 * File:   funciones.cpp
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 27 de junio de 2023, 03:03 PM
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <ios>
#include <cstring>
#include <streambuf>

using namespace std;
#define NO_ENCONTRADO -1
#define MAX_LINE 150
#include "CursoMatric.h"
#include "Alumnos.h"
#include "Cursos.h"
#include "funciones.h"

void crearCursosBin(const char *nombArchCsv,const char *nombArchBin){
    
    ifstream archCursos(nombArchCsv,ios::in);
    if(not archCursos.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    
    ofstream archCursosBin(nombArchBin,ios::out | ios::binary);
    if(not archCursosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }   
    struct Curso curso;
    char codigo[7],nombreCurso[50];
    double creditos;
    while(true){
        archCursos.getline(codigo,7,',');
        if(archCursos.eof())break;
        archCursos.getline(nombreCurso,50,',');
        archCursos>>creditos;
        archCursos.get();
        
        strcpy(curso.codigo,codigo);
        strcpy(curso.nombre,nombreCurso);
        curso.creditos = creditos;
        
        archCursosBin.write(reinterpret_cast<const char*>(&curso),
                sizeof(struct Curso));
    }
}

void mostrarCursosBin(const char *nombArchBin,const char *nombArchTxt){
    
    ifstream archBin(nombArchBin,ios::in | ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    
    struct Curso curso;
    while(true){
        archBin.read(reinterpret_cast<char *>(&curso),sizeof(struct Curso));
        if(archBin.eof())break;
        archReporte<<curso.codigo<<setw(10)<<' '<<curso.nombre<<setw(10)
                <<' '<<curso.creditos<<endl;
        
    }
}

void crearAlumnosBin(const char *nombArchCsv,const char *nombArchBin){   
    ifstream archAlumnos(nombArchCsv,ios::in);
    if(not archAlumnos.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
        exit(1);
    }
    ofstream archAlumnosBin(nombArchBin,ios::out | ios::binary);
    if(not archAlumnos.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchCsv<<endl;
    }   
    int codigo;
    char nombre[60],c;
    double credAprob,credDesap,credFalta;
    struct Alumno alumno;
    while(true){
        archAlumnos>>codigo;
        if(archAlumnos.eof())break;
        archAlumnos.get();
        archAlumnos.getline(nombre,60,',');
        archAlumnos>>credAprob>>c>>credDesap>>c>>credFalta;       
        alumno.codigo = codigo;
        strcpy(alumno.nombre,nombre);
        alumno.cantCredAprob = credAprob;
        alumno.cantCredDesap = credDesap;
        alumno.credPasarFac = credFalta;
        alumno.cantCursosMat=0; 
        archAlumnosBin.write(reinterpret_cast<const char*>(&alumno),
                sizeof(struct Alumno));
    }
}

void actualizarAlumnosBin(const char *nombAlumnosBin,const char *nomCursosBin,
        const char *nombArchTxt){
    fstream archAlumnosBin(nombAlumnosBin,ios::in | ios::out | ios::binary);
    if(not archAlumnosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombAlumnosBin<<endl;
        exit(1);
    }
    ifstream archCursosBin(nomCursosBin,ios::in | ios::binary);
    if(not archCursosBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nomCursosBin<<endl;
        exit(1);
    }
    ifstream archNotas(nombArchTxt,ios::in);
    if(not archNotas.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    struct Curso curso;
    int tamArchAlumno,numRegAlumno,tamArchCurso,numRegCurso;
    int tamRegAlumno = sizeof(struct Alumno);
    int tamRegCurso = sizeof(struct Curso);
    datosArchivoAlumnos(archAlumnosBin,tamArchAlumno,tamRegAlumno,numRegAlumno);
    datosArchivoCursos(archCursosBin,tamArchCurso,tamRegCurso,numRegCurso);
    int posCurso;
    char codCurso[7];
    while(true){
        archNotas>>codCurso;
        if(archNotas.eof())break;
        posCurso = buscarCurso(archCursosBin,codCurso,numRegCurso);
        if(posCurso!=NO_ENCONTRADO){
            archCursosBin.seekg(posCurso*tamRegCurso,ios::beg);
            archCursosBin.read(reinterpret_cast<char *>(&curso),tamRegCurso);
            registrarValores(curso,archAlumnosBin,tamRegAlumno,numRegAlumno,archNotas);
        }else while(archNotas.get()!='\n');
    }
}

void registrarValores(struct Curso &curso,fstream &archAlumnosBin,
        int tamRegAlumno,int numRegAlumno,ifstream &archNotas){
    struct Alumno alumno;
    int codigoAlumno,nota,posAlumno;
    while(true){
        archNotas>>codigoAlumno;
        archNotas>>nota;
        posAlumno = buscarAlumno(archAlumnosBin,codigoAlumno,numRegAlumno);
        if(posAlumno!=NO_ENCONTRADO){
            archAlumnosBin.seekg(posAlumno*tamRegAlumno,ios::beg);
            archAlumnosBin.read(reinterpret_cast<char *>(&alumno),tamRegAlumno);
            if(nota>=11){
                alumno.cantCredAprob+=curso.creditos;
                alumno.credPasarFac-=curso.creditos;
                strcpy(alumno.cursosMatriculados[alumno.cantCursosMat].codigo,curso.codigo);
                strcpy(alumno.cursosMatriculados[alumno.cantCursosMat].nombre,curso.nombre);
                alumno.cursosMatriculados[alumno.cantCursosMat].creditos = curso.creditos;
                alumno.cursosMatriculados[alumno.cantCursosMat].nota = nota;
                alumno.cantCursosMat++;
            }else if(nota<11){
                alumno.cantCredDesap+=curso.creditos;
                strcpy(alumno.cursosMatriculados[alumno.cantCursosMat].codigo,curso.codigo);
                strcpy(alumno.cursosMatriculados[alumno.cantCursosMat].nombre,curso.nombre);
                alumno.cursosMatriculados[alumno.cantCursosMat].creditos = curso.creditos;
                alumno.cursosMatriculados[alumno.cantCursosMat].nota = nota;
                alumno.cantCursosMat++;
            }
            archAlumnosBin.seekg(posAlumno*tamRegAlumno,ios::beg);
            archAlumnosBin.write(reinterpret_cast<const char*>(&alumno),tamRegAlumno);
            archAlumnosBin.flush();
        }
        if(archNotas.get()=='\n')break;
    }
}

void ordearAlumnosBin(const char *nombArchBin){
    fstream archAlumnoBin(nombArchBin,ios::in | ios::out | ios::binary);
    if(not archAlumnoBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    int tamReg = sizeof(struct Alumno);
    int tamArch,numReg;
    struct Alumno alumnoI, alumnoK;
    datosArchivoAlumnos(archAlumnoBin,tamArch,tamReg,numReg);
    for(int i=0;i<numReg-1;i++)
        for(int k=i+1;k<numReg;k++){
            archAlumnoBin.seekg(i*tamReg,ios::beg);
            archAlumnoBin.read(reinterpret_cast<char *>(&alumnoI),tamReg);
            archAlumnoBin.seekg(k*tamReg,ios::beg);
            archAlumnoBin.read(reinterpret_cast<char *>(&alumnoK),tamReg);
            if(alumnoI.cantCursosMat<alumnoK.cantCursosMat or 
                    alumnoI.cantCursosMat==alumnoK.cantCursosMat and 
                    strcmp(alumnoI.nombre,alumnoK.nombre)>0){
                archAlumnoBin.seekg(i*tamReg,ios::beg);
                archAlumnoBin.write(reinterpret_cast<const char*>(&alumnoK),tamReg);
                archAlumnoBin.seekg(k*tamReg,ios::beg);
                archAlumnoBin.write(reinterpret_cast<const char*>(&alumnoI),tamReg);
                archAlumnoBin.flush();
            }
        }
    
}

void emiteReporte(const char *nombArchBin,const char *nombArchTxt){
    ifstream archBin(nombArchBin,ios::in | ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchBin<<endl;
        exit(1);
    }
    ofstream archReporte(nombArchTxt,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de "<<nombArchTxt<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<setw(50)<<' '<<"INSTITUCION EDUCATIVA LIMA"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    struct Alumno alumno;
    int contAlumnos=0;
    double promedio=0,creditosTotales=0;
    while(true){
        archBin.read(reinterpret_cast<char *>(&alumno),sizeof(struct Alumno));
        if(archBin.eof())break;
        if(alumno.cantCursosMat>0){
            imprimeAlumnosYresumen(contAlumnos,promedio,creditosTotales,
                    alumno,archReporte);
        }
    }
}

void imprimeAlumnosYresumen(int &contAlumnos,double &promedio,
        double &creditosTotales,struct Alumno &alumno,ofstream &archReporte){
    contAlumnos++;
    archReporte<<setw(5)<<contAlumnos<<") "<<"Alumno: "<<alumno.codigo
            <<" - "<<alumno.nombre<<endl;
    archReporte<<setw(8)<<' '<<"Notas en el ciclo"<<endl;
    archReporte<<setw(12)<<' '<<"CURSO"<<setw(50)<<' '<<"CREDITOS"
            <<setw(10)<<' '<<"NOTA"<<endl;
    for(int i=0;i<alumno.cantCursosMat;i++){
        archReporte<<setw(12)<<' '<<alumno.cursosMatriculados[i].codigo
                <<" - "<<left<<setw(40)<<alumno.cursosMatriculados[i].nombre
                <<right<<setw(12)<<alumno.cursosMatriculados[i].creditos
                <<setw(15)<<alumno.cursosMatriculados[i].nota<<endl;
        promedio+=alumno.cursosMatriculados[i].creditos*
                alumno.cursosMatriculados[i].nota;
        creditosTotales+=alumno.cursosMatriculados[i].creditos;
    }
    promedio/=creditosTotales;
    imprimeLinea('-',MAX_LINE,archReporte);
    imprimeYanalizaResumen(alumno,promedio,archReporte);
}

void imprimeYanalizaResumen(struct Alumno &alumno,double promedio,ofstream &archReporte){
    archReporte<<"RESULTADOS AL FINAL DEL CICLO"<<endl;
    archReporte<<"Promedio ponderado en el ciclo: "<<setw(14)<<promedio<<endl;
    archReporte<<"Creditos aprobados acumulados: "<<setw(15)
            <<alumno.cantCredAprob<<endl;
    archReporte<<"Creditos desaprobados acumulados: "<<setw(12)
            <<alumno.cantCredDesap<<endl;
    if(alumno.credPasarFac>0){
        archReporte<<"El alumno no pasa a Facultad, le faltan: "<<
                setw(12)<<alumno.credPasarFac<<endl;
    }else archReporte<<"El alumno pasa a Facultad"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    
}

int buscarAlumno(fstream &arch,int codigo,int numReg){
    struct Alumno alumno;
    arch.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        arch.read(reinterpret_cast<char *>(&alumno),sizeof(struct Alumno));
        if(arch.eof())break;
        if(alumno.codigo == codigo)return i;
    }
    return NO_ENCONTRADO;
}

int buscarCurso(ifstream &arch, char *codigo,int numReg){
    struct Curso curso;
    arch.seekg(0,ios::beg);
    for(int i=0;i<numReg;i++){
        arch.read(reinterpret_cast<char *>(&curso),sizeof(struct Curso));
        if(arch.eof())break;
        if(strcmp(curso.codigo,codigo)==0)return i;
    }
    return NO_ENCONTRADO;
}

void datosArchivoAlumnos(fstream &arch,int &tamArch,int tamReg,int &numReg){   
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    arch.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

void datosArchivoCursos(ifstream &arch,int &tamArch,int tamReg,int &numReg){
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    arch.seekg(0,ios::beg);
    numReg = tamArch/tamReg;
}

void imprimeLinea(char caracter,int cantidad, ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}
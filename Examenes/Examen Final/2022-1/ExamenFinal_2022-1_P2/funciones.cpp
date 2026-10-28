#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Curso.h"
#include "CursoMatriculado.h"
#include "Alumno.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define ALING 5
#define MAX_CAR_LIN 170
#define MAX_CAR_COD 10
#define MAX_CAR_NOMBRE 60
#define MAX_CAR_CRED 20  
#define MAX_CAR_PROMEDIO 20
#define MAX_CAR_CANT 20
#define MAX_CAR_CONT 5

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
int cantidadElementosIf(ifstream& archivo, int tam){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch /tam;
    
}
int cantidadElementosF(fstream& archivo, int tam){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    return tamArch /tam;
    
}

void leeCursos(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Curso curso;
    
    while(true){
        // CIV123,Instalaciones de Edificaciones,3.75
        archivoCsv.getline(curso.codigo, MAX_CURSO_CODIGO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv.getline(curso.nombre, MAX_CURSO_NOMBRE, ',');        
        archivoCsv>>curso.creditos;
        archivoCsv.get();
        
        archivoBin.write(reinterpret_cast<const char*>(&curso), 
                sizeof(struct Curso));
    }
}
void confirmaCursos(const char* nombreArchivoReporte, const char* nombreArchivoBin){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    
    int tamElemento, cantidadCursos;
    tamElemento = sizeof(struct Curso);
    cantidadCursos = cantidadElementosIf(archivoBin, tamElemento);
    struct Curso curso;
    
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE CARGA DE CURSOS"
            <<endl;
    imprimeLinea('=', archivoReporte);
    for (int i = 0; i < cantidadCursos; i++) {        
        archivoBin.read(reinterpret_cast<char*>(&curso), tamElemento);
        
        archivoReporte<<left
                <<setw(MAX_CAR_COD)<<curso.codigo
                <<setw(MAX_CAR_NOMBRE)<<curso.nombre
                <<setw(MAX_CAR_CRED)<<curso.creditos
                <<endl;
    }

}

void leeAlumnos(const char* nombreArchivoCsv, const char* nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Alumno alumno;  
    
    while(true){
        // 20211011,Portugal Raffo Aleexander,12.5,0,55.5
        archivoCsv>>alumno.codigo;
        if(archivoCsv.eof()) break;
        archivoCsv.get();
        archivoCsv.getline(alumno.nombre, MAX_ALUMNO_NOMBRE, ',');
        archivoCsv>>alumno.cantidadCreditosAprobados;
        archivoCsv.get();
        archivoCsv>>alumno.cantidadCreditosDesaprobados;
        archivoCsv.get();
        archivoCsv>>alumno.cantidadCreditosPaseFacultad;
        
        alumno.cantidadCursosMatriculados=0;
        
        alumno.cantidadCreditosDesaprobados=0;
        alumno.cantidadCreditosAprobados=0;        
        
        archivoBin.write(reinterpret_cast<const char*>(&alumno), 
                sizeof(struct Alumno));
    }
}
void confirmaAlumnos(const char* nombreArchivoReporte, const char* nombreArchivoBin){
        ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);
    }
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoBin;
        exit(1);
    }
    
    
    int tamElemento, cantidadAlumnos;
    tamElemento = sizeof(struct Alumno);
    cantidadAlumnos = cantidadElementosIf(archivoBin, tamElemento);
    struct Alumno alumno;
    
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"CONFIRMACION DE CARGA DE CURSOS"
            <<endl;
    archivoReporte<<setw(2)<<"CONFIRMACION DE CARGADO DE ALUMNOS"<<endl;
    imprimeLinea('=', archivoReporte);
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_CRED)<<"CRED PARA FACU"
            <<setw(MAX_CAR_CRED)<<"CRED APROBADOS"
            <<setw(MAX_CAR_CRED)<<"CRED DESAPROBADOS"
            <<endl;
    imprimeLinea('=', archivoReporte);
    for (int i = 0; i < cantidadAlumnos; i++) {        
        archivoBin.read(reinterpret_cast<char*>(&alumno), tamElemento);
        
        archivoReporte<<left
                <<setw(MAX_CAR_COD)<<alumno.codigo
                <<setw(MAX_CAR_NOMBRE)<<alumno.nombre
                <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosPaseFacultad
                <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosAprobados
                <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosDesaprobados
                <<endl;
    }       
}

void leeNotas(const char* nombreArchivoNotas, 
        const char* nombreArchivoAlumnos, 
        const char* nombreArchivoCursos){
    
    ifstream archivoNotas(nombreArchivoNotas, ios::in);
    if(not archivoNotas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoNotas;
        exit(1);
    }
    fstream archivoAlumnos(nombreArchivoAlumnos, ios::in|ios::out|ios::binary);
    if(not archivoAlumnos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoAlumnos;
        exit(1);
    }
    fstream archivoCursos(nombreArchivoCursos, ios::in|ios::out|ios::binary);
    if(not archivoCursos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCursos;
        exit(1);
    }
    
    int tamAlumno, cantidadAlumnos;
    tamAlumno = sizeof(struct Alumno);
    cantidadAlumnos = cantidadElementosF(archivoAlumnos, tamAlumno);
    struct Alumno alumno;
    
    int tamCurso, cantidadCursos;
    tamCurso = sizeof(struct Curso);
    cantidadCursos = cantidadElementosF(archivoCursos, tamCurso);
    struct Curso curso;
    
    
    while(true){
        // CIV123   20198025  11 20211731   11 20200875  14  20207732   13  20193794   11 20184087  18  20211011   15  20212521  12
        char codigoCurso[MAX_CURSO_CODIGO]{};
        int codigoAlumno, nota;
        
        archivoNotas.getline(codigoCurso, MAX_CURSO_CODIGO, ' ');
        if(archivoNotas.eof()) break;

        while(archivoNotas.get()!='\n');
        
        while(true){
            if(archivoNotas.get()=='\n') break;
            archivoNotas>>codigoAlumno>>nota;
            
//            int posAlumno, posCurso;
//            posAlumno = buscaAlumno(codigoAlumno, alumnos, cantidadAlumnos);
//            posCurso = buscaCurso(codigoCurso, cursos, cantidadCursos);
//            
//            if(posAlumno!= NO_ENCONTRADO and posCurso != NO_ENCONTRADO);
//                procesaAlumno(alumnos[posAlumno], cursos[posCurso], nota);
        }
    }
}
//int buscaAlumno(int codigo, struct Alumno*alumnos, int cantidad){
//    for (int i = 0; i < cantidad; i++) {        
//        if(codigo == alumnos[i].codigo) return i;
//    }
//    return NO_ENCONTRADO;
//}
//int buscaCurso(char* codigo, struct Curso*cursos, int cantidad){
//    for (int i = 0; i < cantidad; i++) {        
//        if(strcmp(codigo, cursos[i].codigo)==0) return i;
//    }
//    return NO_ENCONTRADO;
//}
//void procesaAlumno(struct Alumno& alumno, struct Curso& curso, int nota){
//  
//    int posCurso = alumno.cantidadCursosMatriculados;
//    alumno.cursosMatriculados[posCurso].codigo = new char[strlen(curso.codigo)+1];
//    strcpy(alumno.cursosMatriculados[posCurso].codigo, curso.codigo);
//    alumno.cursosMatriculados[posCurso].creditos = curso.creditos;
//    alumno.cursosMatriculados[posCurso].nombre = new char[strlen(curso.nombre)+1];
//    strcpy(alumno.cursosMatriculados[posCurso].nombre, curso.nombre);
//    alumno.cursosMatriculados[posCurso].nota = nota;
//            
//    procesaNotas(alumno.cantidadCursosMatriculados, 
//            alumno.promedioCursosMatriculados, alumno.sumaPonderadaCursos,
//            alumno.cantidadCreditosMatriculados,
//            curso.creditos, nota);
//    
//    if(nota>=11)
//        procesaNotas(alumno.cantidadCursosAprobados, 
//                alumno.promedioCursosAprobados, alumno.sumaPonderadaAprobado,
//                alumno.cantidadCreditosAprobados, 
//                curso.creditos, nota);
//    else{
//        
//        procesaNotas(alumno.cantidadCursosDesaprobados, 
//                alumno.promedioCursosDesaprobados, alumno.sumaPonderadaDesaprobado, 
//                alumno.cantidadCreditosDesaprobados,
//                curso.creditos, nota);
//    }
//    
//    if(alumno.cantidadCreditosPaseFacultad>0)
//        alumno.cantidadCreditosPaseFacultad-=curso.creditos;
//    if(alumno.cantidadCreditosPaseFacultad<=0)
//        alumno.cantidadCreditosPaseFacultad=0;
//    
//}
//void procesaNotas(int& cantidad, double& promedio, int& sumaNotas, double& sumaCreditos, 
//        double credito, int nota){
//    cantidad++;
//    sumaCreditos+=credito;
//    sumaNotas += nota*credito;
//    
//    if(sumaCreditos> 0)
//        promedio = sumaNotas/sumaCreditos;
//    else promedio = 0;
//    
//    
//}
//int buscaCursoMatricula(char* codigo, struct CursoMatriculado* cursos, int cantidad){
//    for (int i = 0; i < cantidad; i++) {        
//        if(strcmp(codigo, cursos[i].codigo) == 0 ) return i;
//    }
//    return NO_ENCONTRADO;
//}
//
//void ordenaAlumnos(struct Alumno*alumnos, int cantidad){
//    for (int i = 0; i < cantidad-1; i++) {        
//        for (int j = i+1; j < cantidad; j++) {            
//            if(alumnos[i].cantidadCreditosAprobados<alumnos[j].cantidadCreditosAprobados){
//                cambiarAlumnos(alumnos[i], alumnos[j]);
//            }
//        }
//
//    }
//    
//    for (int i = 0; i < cantidad; i++){
//        ordenaCursos(alumnos[i].cursosMatriculados,
//                alumnos[i].cantidadCursosMatriculados);
//    }
//
//}
//void cambiarAlumnos(struct Alumno& alumno1, struct Alumno& alumno2){
//    struct Alumno aux;
//    aux = alumno1;
//    alumno1 = alumno2;
//    alumno2 = aux;
//}
//void ordenaCursos(struct CursoMatriculado* cursos, int cantidad){
//    for (int i = 0; i < cantidad-1; i++) {                
//        for (int j = i+1; j < cantidad; j++) {            
//            if(cursos[i].nota<cursos[j].nota 
//                    and
//                    strcmp(cursos[i].nombre, cursos[j].nombre))
//                cambiaCursos(cursos[i], cursos[j]);
//        }
//
//    }
//
//}
//void cambiaCursos(struct CursoMatriculado& curso1,struct CursoMatriculado& curso2){
//    struct CursoMatriculado aux;
//    aux = curso1;
//    curso1 = curso2;
//    curso2 = aux;
//}
//
//void emiteReporte(const char* nombreArchivo, struct Alumno* alumnos, int cantidad){
//    ofstream archivo(nombreArchivo, ios::out);
//    if(not archivo.is_open()){
//        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
//        exit(1);
//    }
//    
//    archivo<<setw(MAX_CAR_LIN/2)<<"INSTITUCIONEDUCATIVA VENUS SA"<<endl
//            <<setw(MAX_CAR_LIN/2)<<"RESULTADO DE ALUMNOS MATRICULADOS"<<endl;
//    imprimeLinea('=', archivo);
//  
//    for (int i = 0; i < cantidad; i++) {
//        
//        if(alumnos[i].cantidadCursosMatriculados>0)
//        imprimeAlumno(archivo, alumnos[i], i);                
//
//    }  
//}
//void imprimeAlumno(ofstream& archivo, const struct Alumno& alumno, int cont){
//        imprimeLinea('=', archivo);
//        archivo<<left<<fixed<<setprecision(2)
//            <<setw(ALING)<<" "
//            <<right<<setfill('0')<<setw(2)<<cont+1
//            <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "
//            <<"ALUMNO: "
//            <<setw(MAX_CAR_COD)<<alumno.codigo<<" - "
//            <<setw(MAX_CAR_NOMBRE)<<alumno.nombre;
//      if(alumno.cantidadCreditosPaseFacultad==0)
//          archivo<<"PASA A FACULTAD"<<endl;
//      else 
//          archivo<<"NO PASA A FACULTAD"<<endl;
//      
//      archivo<<left<<fixed<<setprecision(2)
//            <<setw(ALING)<<" "
//            <<"NOTAS DEL CICLO"<<endl;
//    for (int i = 0; i < alumno.cantidadCursosMatriculados; i++) {        
//        imprimeCurso(archivo, alumno.cursosMatriculados[i], i);
//    }                
//    imprimeLinea('-', archivo);
//    
//    imprimeResultados(archivo, alumno);
//   
//            
//    
//}
//void imprimeCurso(ofstream& archivo, const struct CursoMatriculado& curso, int cont){
//    if(cont == 0){
//     archivo<<left<<fixed<<setprecision(2)
//            <<setw(2*ALING)<<" "                                    
//            <<setw(MAX_CAR_COD+MAX_CAR_NOMBRE+3)<<"CURSO"            
//            <<setw(MAX_CAR_CRED)<<"CREDITOS"
//            <<setw(MAX_CAR_PROMEDIO)<<"NOTA"
//            <<endl;
//        
//    }
//     archivo<<left<<fixed<<setprecision(2)
//            <<setw(2*ALING)<<" "                                    
//            <<setw(MAX_CAR_COD)<<curso.codigo<<" - "
//            <<setw(MAX_CAR_NOMBRE)<<curso.nombre
//            <<setw(MAX_CAR_CRED)<<curso.creditos
//            <<setw(MAX_CAR_PROMEDIO)<<curso.nota<<endl; 
//}
//void imprimeResultados(ofstream& archivo, const struct Alumno& alumno){
//     archivo<<"RESULTADOS FINALES DEL CICLO"<<endl
//            <<"CREDITOS APROBADOS DEL CICLO: "
//            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosAprobados
//            <<"PROMEDIO PONDERADO CURSOS APROBADOS: "
//            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosAprobados<<endl
//            <<"CREDITOS DESAPROBADOS DEL CICLO: "
//            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosDesaprobados
//            <<"PROMEDIO PONDERADO CURSOS DESAPROBADOS: "
//            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosDesaprobados<<endl
//            <<"PROMEDIO PONDERADO DEL CICLO: "
//            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosMatriculados<<endl
//            <<"CREDITOS APROBADOS ACUMULADOS: "
//            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosAprobados<<endl
//            <<"CREDITOS DESAPROBADOS ACUMULADOS: "
//            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosDesaprobados<<endl;
//}
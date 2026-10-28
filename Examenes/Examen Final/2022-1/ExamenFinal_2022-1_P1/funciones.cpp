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
#define MAX_CAR_COD 6
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
char* leeCadena(ifstream& archivo, char del){
    char buff[100], *aux;
    archivo.getline(buff, 100, del);
    if(archivo.eof()) return nullptr;
    aux = new char [strlen(buff)+1];
    strcpy(aux, buff);
    return aux;
}

void leeCursos(const char* nombreArchivo, struct Curso* cursos, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // CIV123,Instalaciones de Edificaciones,3.75
        cursos[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        cursos[cantidad].nombre = leeCadena(archivo, ',');
        archivo>>cursos[cantidad].creditos;
        archivo.get();
        
        cantidad++;
    }
}

void leeAlumnos(const char* nombreArchivo, struct Alumno* alumnos, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    /*
    int codigo;
    char* nombre;
  
    struct CursoMatriculado* cursosMatriculados;
    int cantidadCursosMatriculados;
    double cantidadCreditosMatriculados;
    double cantidadCreditosAprobados;
    double cantidadCreditosDesaprobados;
    double cantidadCreditosPaseFacultad;
    double promedioCursosMatriculados;
    double promedioCursosAprobados;
    double promedioCursosDesaprobados;
    int sumaPonderadaAprobado;
    int sumaPonderadaDesaprobado;
    int sumaPonderadaCursos;
     */
    
    while(true){
        // 20211011,Portugal Raffo Aleexander,12.5,0,55.5
        archivo>>alumnos[cantidad].codigo;
        if(archivo.eof()) break;
        archivo.get();
        alumnos[cantidad].nombre = leeCadena(archivo, ',');
        archivo>>alumnos[cantidad].cantidadCreditosAprobados;
        archivo.get();
        archivo>>alumnos[cantidad].cantidadCreditosDesaprobados;
        archivo.get();
        archivo>>alumnos[cantidad].cantidadCreditosPaseFacultad;
        
        alumnos[cantidad].cantidadCursosMatriculados=0;
        alumnos[cantidad].cursosMatriculados
                = new struct CursoMatriculado[MAX_CURSOS_MATRICULADOS]{};
        
        alumnos[cantidad].cantidadCreditosMatriculados=0;
        alumnos[cantidad].cantidadCreditosDesaprobados=0;
        alumnos[cantidad].cantidadCreditosAprobados=0;        
        
        alumnos[cantidad].cantidadCursosAprobados=0;
        alumnos[cantidad].cantidadCursosDesaprobados=0;
        alumnos[cantidad].promedioCursosMatriculados=0;
        alumnos[cantidad].promedioCursosAprobados=0;
        alumnos[cantidad].promedioCursosDesaprobados=0;
        alumnos[cantidad].promedioCursosMatriculados=0;
        alumnos[cantidad].sumaPonderadaAprobado=0;
        alumnos[cantidad].sumaPonderadaDesaprobado=0;
        alumnos[cantidad].sumaPonderadaCursos=0;       
        
        cantidad++;
    }
}
void confirmaAlumnos(const char* nombreArchivo, struct Alumno* alumnos, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(2)<<"CONFIRMACION DE CARGADO DE ALUMNOS"<<endl;
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_CRED)<<"CRED APROBADOS"
            <<setw(MAX_CAR_CRED)<<"CRED DESAPROBADOS"
            <<setw(MAX_CAR_CRED)<<"CRED PARA FACU"
            <<setw(MAX_CAR_PROMEDIO)<<"PROMEDIO APROBADOS"
            <<setw(MAX_CAR_PROMEDIO)<<"PROMEDIO DESAPROBADOS"
            <<setw(MAX_CAR_PROMEDIO)<<"PROMEDIO TOTAL"
            <<endl;
    imprimeLinea('=', archivo);
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left<<fixed<<setprecision(2)
                <<setw(MAX_CAR_COD)<<alumnos[i].codigo
                <<setw(MAX_CAR_NOMBRE)<<alumnos[i].nombre
                <<setw(MAX_CAR_CRED)<<alumnos[i].cantidadCreditosAprobados
                <<setw(MAX_CAR_CRED)<<alumnos[i].cantidadCreditosDesaprobados
                <<setw(MAX_CAR_CRED)<<alumnos[i].cantidadCreditosPaseFacultad
                <<setw(MAX_CAR_PROMEDIO)<<alumnos[i].promedioCursosAprobados
                <<setw(MAX_CAR_PROMEDIO)<<alumnos[i].promedioCursosDesaprobados
                <<setw(MAX_CAR_PROMEDIO)<<alumnos[i].promedioCursosMatriculados
                <<setw(MAX_CAR_CANT)<<alumnos[i].cantidadCursosMatriculados
                <<endl;        

    }  
}

void leeNotas(const char* nombreArchivo, 
        struct Alumno* alumnos, int cantidadAlumnos, 
        struct Curso* cursos, int cantidadCursos){
    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // CIV123   20198025  11 20211731   11 20200875  14  20207732   13  20193794   11 20184087  18  20211011   15  20212521  12
        char* codigoCurso;
        int codigoAlumno, nota;
        
        codigoCurso = leeCadena(archivo, ' ');
        if(archivo.eof()) break;
        
        while(true){
            if(archivo.get()=='\n') break;
            archivo>>codigoAlumno>>nota;
            
            int posAlumno, posCurso;
            posAlumno = buscaAlumno(codigoAlumno, alumnos, cantidadAlumnos);
            posCurso = buscaCurso(codigoCurso, cursos, cantidadCursos);
            
            if(posAlumno!= NO_ENCONTRADO and posCurso != NO_ENCONTRADO);
                procesaAlumno(alumnos[posAlumno], cursos[posCurso], nota);
        }
    }
}
int buscaAlumno(int codigo, struct Alumno*alumnos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(codigo == alumnos[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}
int buscaCurso(char* codigo, struct Curso*cursos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, cursos[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
void procesaAlumno(struct Alumno& alumno, struct Curso& curso, int nota){
  
    int posCurso = alumno.cantidadCursosMatriculados;
    alumno.cursosMatriculados[posCurso].codigo = new char[strlen(curso.codigo)+1];
    strcpy(alumno.cursosMatriculados[posCurso].codigo, curso.codigo);
    alumno.cursosMatriculados[posCurso].creditos = curso.creditos;
    alumno.cursosMatriculados[posCurso].nombre = new char[strlen(curso.nombre)+1];
    strcpy(alumno.cursosMatriculados[posCurso].nombre, curso.nombre);
    alumno.cursosMatriculados[posCurso].nota = nota;
            
    procesaNotas(alumno.cantidadCursosMatriculados, 
            alumno.promedioCursosMatriculados, alumno.sumaPonderadaCursos,
            alumno.cantidadCreditosMatriculados,
            curso.creditos, nota);
    
    if(nota>=11)
        procesaNotas(alumno.cantidadCursosAprobados, 
                alumno.promedioCursosAprobados, alumno.sumaPonderadaAprobado,
                alumno.cantidadCreditosAprobados, 
                curso.creditos, nota);
    else{
        
        procesaNotas(alumno.cantidadCursosDesaprobados, 
                alumno.promedioCursosDesaprobados, alumno.sumaPonderadaDesaprobado, 
                alumno.cantidadCreditosDesaprobados,
                curso.creditos, nota);
    }
    
    if(alumno.cantidadCreditosPaseFacultad>0)
        alumno.cantidadCreditosPaseFacultad-=curso.creditos;
    if(alumno.cantidadCreditosPaseFacultad<=0)
        alumno.cantidadCreditosPaseFacultad=0;
    
}
void procesaNotas(int& cantidad, double& promedio, int& sumaNotas, double& sumaCreditos, 
        double credito, int nota){
    cantidad++;
    sumaCreditos+=credito;
    sumaNotas += nota*credito;
    
    if(sumaCreditos> 0)
        promedio = sumaNotas/sumaCreditos;
    else promedio = 0;
    
    
}
int buscaCursoMatricula(char* codigo, struct CursoMatriculado* cursos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, cursos[i].codigo) == 0 ) return i;
    }
    return NO_ENCONTRADO;
}

void ordenaAlumnos(struct Alumno*alumnos, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {            
            if(alumnos[i].cantidadCreditosAprobados<alumnos[j].cantidadCreditosAprobados){
                cambiarAlumnos(alumnos[i], alumnos[j]);
            }
        }

    }
    
    for (int i = 0; i < cantidad; i++){
        ordenaCursos(alumnos[i].cursosMatriculados,
                alumnos[i].cantidadCursosMatriculados);
    }

}
void cambiarAlumnos(struct Alumno& alumno1, struct Alumno& alumno2){
    struct Alumno aux;
    aux = alumno1;
    alumno1 = alumno2;
    alumno2 = aux;
}
void ordenaCursos(struct CursoMatriculado* cursos, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {                
        for (int j = i+1; j < cantidad; j++) {            
            if(cursos[i].nota<cursos[j].nota 
                    and
                    strcmp(cursos[i].nombre, cursos[j].nombre))
                cambiaCursos(cursos[i], cursos[j]);
        }

    }

}
void cambiaCursos(struct CursoMatriculado& curso1,struct CursoMatriculado& curso2){
    struct CursoMatriculado aux;
    aux = curso1;
    curso1 = curso2;
    curso2 = aux;
}

void emiteReporte(const char* nombreArchivo, struct Alumno* alumnos, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"INSTITUCIONEDUCATIVA VENUS SA"<<endl
            <<setw(MAX_CAR_LIN/2)<<"RESULTADO DE ALUMNOS MATRICULADOS"<<endl;
    imprimeLinea('=', archivo);
  
    for (int i = 0; i < cantidad; i++) {
        
        if(alumnos[i].cantidadCursosMatriculados>0)
        imprimeAlumno(archivo, alumnos[i], i);                

    }  
}
void imprimeAlumno(ofstream& archivo, const struct Alumno& alumno, int cont){
        imprimeLinea('=', archivo);
        archivo<<left<<fixed<<setprecision(2)
            <<setw(ALING)<<" "
            <<right<<setfill('0')<<setw(2)<<cont+1
            <<left<<setfill(' ')<<setw(MAX_CAR_CONT-2)<<" "
            <<"ALUMNO: "
            <<setw(MAX_CAR_COD)<<alumno.codigo<<" - "
            <<setw(MAX_CAR_NOMBRE)<<alumno.nombre;
      if(alumno.cantidadCreditosPaseFacultad==0)
          archivo<<"PASA A FACULTAD"<<endl;
      else 
          archivo<<"NO PASA A FACULTAD"<<endl;
      
      archivo<<left<<fixed<<setprecision(2)
            <<setw(ALING)<<" "
            <<"NOTAS DEL CICLO"<<endl;
    for (int i = 0; i < alumno.cantidadCursosMatriculados; i++) {        
        imprimeCurso(archivo, alumno.cursosMatriculados[i], i);
    }                
    imprimeLinea('-', archivo);
    
    imprimeResultados(archivo, alumno);
   
            
    
}
void imprimeCurso(ofstream& archivo, const struct CursoMatriculado& curso, int cont){
    if(cont == 0){
     archivo<<left<<fixed<<setprecision(2)
            <<setw(2*ALING)<<" "                                    
            <<setw(MAX_CAR_COD+MAX_CAR_NOMBRE+3)<<"CURSO"            
            <<setw(MAX_CAR_CRED)<<"CREDITOS"
            <<setw(MAX_CAR_PROMEDIO)<<"NOTA"
            <<endl;
        
    }
     archivo<<left<<fixed<<setprecision(2)
            <<setw(2*ALING)<<" "                                    
            <<setw(MAX_CAR_COD)<<curso.codigo<<" - "
            <<setw(MAX_CAR_NOMBRE)<<curso.nombre
            <<setw(MAX_CAR_CRED)<<curso.creditos
            <<setw(MAX_CAR_PROMEDIO)<<curso.nota<<endl; 
}
void imprimeResultados(ofstream& archivo, const struct Alumno& alumno){
     archivo<<"RESULTADOS FINALES DEL CICLO"<<endl
            <<"CREDITOS APROBADOS DEL CICLO: "
            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosAprobados
            <<"PROMEDIO PONDERADO CURSOS APROBADOS: "
            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosAprobados<<endl
            <<"CREDITOS DESAPROBADOS DEL CICLO: "
            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosDesaprobados
            <<"PROMEDIO PONDERADO CURSOS DESAPROBADOS: "
            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosDesaprobados<<endl
            <<"PROMEDIO PONDERADO DEL CICLO: "
            <<setw(MAX_CAR_PROMEDIO)<<alumno.promedioCursosMatriculados<<endl
            <<"CREDITOS APROBADOS ACUMULADOS: "
            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosAprobados<<endl
            <<"CREDITOS DESAPROBADOS ACUMULADOS: "
            <<setw(MAX_CAR_CRED)<<alumno.cantidadCreditosDesaprobados<<endl;
}
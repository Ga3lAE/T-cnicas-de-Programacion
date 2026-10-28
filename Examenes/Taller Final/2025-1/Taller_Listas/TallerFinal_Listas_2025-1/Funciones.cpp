/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 5 de julio de 2025, 04:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "NodoCurso.h"
#include "NodoEscala.h"
#include "NodoAlumno.h"

#define MAX_TAM_LIN 150
#define MAX_TAM_COD 10
#define MAX_TAM_NOM 40
#define MAX_TAM_ESC 10
#define MAX_TAM_CRED 15
#define MAX_TAM_CONT 5
#define MAX_TAM_DIN 10
#define MAX_TAM_CUR 55
//#define MAX_TAM_


//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[100], *cad;
    archivo.getline(aux, 100, del);
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    return cad;
}
char *copiaCadena(const char *cad){
    char *aux;
    aux = new char [strlen(cad)+1]{};
    strcpy(aux, cad);
    return aux;
}
void leeCursos(const char *nombreArchivo, struct NodoCurso *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Curso curso{};
    while(true){
        //231289,Turbomaquinas Y Maquinas De Desplazamiento Positivo,3.00
        archivo>>curso.codigo;
        if(archivo.eof()) break;
        archivo.get();
        curso.nombre = leeCadenaExacta(archivo, ',');
        archivo>>curso.creditos;
        //no necesitamos un get para '\n' por luego leer con >>
        
        insertaCurso(curso, lista);
    }
    
}
void leeEscalas(const char *nombreArchivo, struct NodoEscala *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Escala escala{};
    char descC;
    while(true){
        //2023-1,B,326.13
        archivo>>escala.anio;
        if(archivo.eof()) break;
        archivo>>descC>>escala.ciclo
                >>descC>>escala.escala
                >>descC>>escala.valorCredito;                
        
        insertaEscala(escala, lista);
    }    
}
void leeAlumnos(const char *nombreArchivo, struct NodoAlumno *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
        
    while(true){
        //20238549,Justino Forzani Ericka Victoria,A
		
        archivo>>alumno.codigo;
        if(archivo.eof()) break;
        archivo.get();
        alumno.nombre = leeCadenaExacta(archivo, ',');
        archivo>>alumno.escala.escala;
        alumno.cursos = new struct Curso [MAX_CANT_ALUMNO_CURSOS]{};
        
        insertaAlumno(alumno, lista);
    }    
}
void pideCiclo(bool& inicial, int& anioAnalisis, int& cicloAnalisis){
    char descC;
    cout<<"Ingrese el anio y el ciclo que desa analizar (20xx-x): "<<endl;
    cin>>anioAnalisis>>descC>>cicloAnalisis;
    inicial = false;                    
}
void leeMatricula(const char *nombreArchivo, 
        struct NodoEscala *listaEscala, 
        struct NodoAlumno *listaAlumnos, 
        struct NodoCurso *listaCursos, 
        int anioProcesa, int cicloProcesa){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    
    int anioMatr, cicloMatr, codigoAlumnoMatr, codigoCursoMatr;
    struct NodoEscala *nodoEscalaActual;
    struct Escala escalaActual;
    struct NodoCurso *nodoCursoActual;
    struct Curso cursoActgual;
    struct NodoAlumno *nodoAlumnoActual;
    while(true){
        //2023-1    20208175    109238    109246    231292    231269
        archivo>>anioMatr;
        if(archivo.eof()) break;
        archivo.get();
        archivo>>cicloMatr;
        
        if(anioMatr != anioProcesa or cicloMatr!=cicloProcesa)
            while(archivo.get()!='\n');
        else{
            archivo>>codigoAlumnoMatr;

            nodoAlumnoActual = buscaAlumno(listaAlumnos, codigoAlumnoMatr);
            if(nodoAlumnoActual == NULL) // no está el alumno
                while(archivo.get()!='\n');
            else{
                struct Alumno &alumnoActual = nodoAlumnoActual->alumno;
                nodoEscalaActual = buscaEscala(listaEscala, anioMatr, cicloMatr, alumnoActual.escala.escala);
                if(nodoEscalaActual == NULL) //no hay escala para este alumno
                    while(archivo.get()!='\n');
                else{
                    escalaActual = nodoEscalaActual->escala;                    
                    
                    while(true){
                        if(archivo.get()=='\n') break;
                        archivo>>codigoCursoMatr;
                        
                        nodoCursoActual = buscaCurso(listaCursos, codigoCursoMatr);
                        cursoActgual = nodoCursoActual->curso;

                        //ya tenemos todos los natos necesarios para procesarlos
                        int &posCurso = alumnoActual.cantidadCursos;
                        alumnoActual.cursos[posCurso].codigo = cursoActgual.codigo;
                        alumnoActual.cursos[posCurso].creditos = cursoActgual.creditos;                        
                        alumnoActual.cursos[posCurso].nombre = copiaCadena(cursoActgual.nombre);
                        posCurso++;
                        
                        alumnoActual.escala = escalaActual;
                        alumnoActual.totalCreditos+=cursoActgual.creditos;
                        alumnoActual.totalPago+=cursoActgual.creditos*escalaActual.valorCredito;                        
                    }

                }            
            }                        
        }
    
    }
}

//INSERCION
void insertaCurso(struct Curso curso, struct NodoCurso *&lista){
    struct NodoCurso *nuevo = new NodoCurso;
    nuevo->curso=curso;
    
    nuevo->siguiente = lista;
    lista = nuevo;
}
void insertaEscala(struct Escala escala, struct NodoEscala *&lista){
    struct NodoEscala *nuevo = new NodoEscala;
    nuevo->escala=escala;
    
    nuevo->siguiente = lista;
    lista = nuevo;
}
void insertaAlumno(struct Alumno alumno, struct NodoAlumno *&lista){
    struct NodoAlumno *nuevo = new NodoAlumno, *ptr=lista, *ant=NULL;
    nuevo->alumno = alumno;
    while(ptr){
        if(ptr->alumno.escala.escala>alumno.escala.escala 
                or 
            (strcmp(ptr->alumno.nombre, alumno.nombre)>0 
                and
            ptr->alumno.escala.escala==alumno.escala.escala)) break;
        ant = ptr;
        ptr = ptr->siguiente;
    }
    nuevo->siguiente = ptr;
    if(ant) ant->siguiente = nuevo;
    else lista = nuevo;        
}

//BUSQUEDA
struct NodoEscala *buscaEscala(struct NodoEscala *lista, 
        int anio, int ciclo, char escala){
    struct NodoEscala *ptr = lista;
    while(ptr){
        if(ptr->escala.anio == anio and ptr->escala.ciclo==ciclo and ptr->escala.escala == escala) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}
struct NodoAlumno *buscaAlumno(struct NodoAlumno *lista, int codigo){
    struct NodoAlumno *ptr = lista;
    while(ptr){
        if(ptr->alumno.codigo==codigo) return ptr;
        ptr = ptr->siguiente;
    }
    return NULL;
}
struct NodoCurso *buscaCurso(struct NodoCurso *lista, int codigo){
    struct NodoCurso *ptr = lista;
    while(ptr){
        if(ptr->curso.codigo==codigo) return ptr;        
        ptr = ptr->siguiente;
    }
    return NULL;
}

//ELIMINA
void eliminaNoMatriculados(struct NodoAlumno *&lista){
    struct NodoAlumno *ptr=lista, *ant = NULL;
    
    while(ptr){
        if(ptr->alumno.cantidadCursos==0){
            struct NodoAlumno *aux = ptr;
            if(ant){
                ant->siguiente =ptr->siguiente;
                ptr =ptr->siguiente;
            }
            else{
                lista=ptr->siguiente;
                ptr = ptr->siguiente;
            }
            delete aux;
        }
        else{
            ant = ptr;
            ptr = ptr->siguiente;
        }
        
        
        
        
    }
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void imprimeReporte(const char *nombreArchivo, struct NodoAlumno *lista, 
        bool inicial, int anio, int ciclo){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se puede abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<right<<setw(MAX_TAM_LIN/2)<<"INSTITUCION EDUCATIVA VENUS"<<endl
            <<setw(MAX_TAM_LIN/2)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    if(not inicial)
        archivo<<setw(MAX_TAM_LIN/2)<<anio<<'-'<<ciclo<<endl;
    
    struct NodoAlumno *ptr=lista;
    struct Alumno alumno;
    while(ptr){
        imprimeLinea(archivo, '=');
        alumno =ptr->alumno;
        archivo<<left
                <<"ALUMNO: "
                <<setw(MAX_TAM_COD)<<alumno.codigo<<" - "
                <<setw(MAX_TAM_NOM)<<alumno.nombre
                <<"ESCALA: "
                <<setw(MAX_TAM_ESC)<<alumno.escala.escala
                <<"VALOR DEL CREDITO: "
                <<setw(MAX_TAM_CRED)<<alumno.escala.valorCredito
                <<endl;        
        imprimeCursos(archivo, alumno);
        
        
        ptr = ptr->siguiente;
    }
}
void imprimeCursos(ofstream &archivo, struct Alumno alumno){
    imprimeLinea(archivo, '-');
    archivo<<setw(MAX_TAM_CONT)<<' '
            <<setw(MAX_TAM_COD+MAX_TAM_CUR)<<"CURSO MATRICULADO"            
            <<setw(MAX_TAM_CRED)<<"CREDITOS"
            <<setw(MAX_TAM_DIN)<<"TOTAL PAGADO"
            <<endl;
    for (int i = 0; i < alumno.cantidadCursos; i++) {        
    archivo<<setw(MAX_TAM_CONT)<<i+1
            <<setw(MAX_TAM_COD)<<alumno.cursos[i].codigo
            <<setw(MAX_TAM_CUR)<<alumno.cursos[i].nombre
            <<setw(MAX_TAM_CRED)<<alumno.cursos[i].creditos
            <<setw(MAX_TAM_DIN)<<alumno.cursos[i].creditos*alumno.escala.valorCredito
            <<endl;
    }
    imprimeLinea(archivo, '=');
    archivo<<"TOTAL DE CREDITOS: "
            <<setw(MAX_TAM_CRED)<<alumno.totalCreditos
            <<"TOTAL MONTO PAGADO: "
            <<setw(MAX_TAM_CRED)<<alumno.totalPago
            <<endl;    
}
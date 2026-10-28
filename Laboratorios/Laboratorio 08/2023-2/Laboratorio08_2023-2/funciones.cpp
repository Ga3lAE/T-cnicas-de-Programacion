#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funciones.h"
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_CAR_CONT 4
#define MAX_CAR_CURSO 70
#define MAX_CAR_CREDITOS 15
#define MAX_CAR_ALUMNOS 25
#define MAX_CAR_MONTO 10
#define ALING_TOTAL (MAX_CAR_CONT + MAX_CAR_CURSO + MAX_CAR_CREDITOS + MAX_CAR_ALUMNOS)

void imprimeLinea(char c, ofstream& archivo){
    for (int i = 0; i < MAX_CAR_LIN; i++) {
        archivo<<c;
    }
    archivo<<endl;
}

void solicitaCiclo(int& ciclo){
    int anio, periodo;
    cout<<"Ingrese un ciclo a analizar (entre 2021-1 y 2023-2) en el formato 20xx-x"<<endl;
    cin>>anio;
    cin.get();
    cin>>periodo;
    ciclo = anio*10 + periodo;
}

void leeAlumnos(const char* nombreArchivo, struct Alumno* alumnos, int& cantidadAlumnos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    while(true){
        // 20227341,Landa Piscoya Christian,D
        struct Alumno aux;
        int codigoAlumno;
        char nombreAlumno[TAM_ALUMNO_NOMBRE], codigoEscalaAlumno;
        
        archivo>>aux.codigo;
        if(archivo.eof()) break;
        archivo.get();
        archivo.getline(aux.nombre, TAM_ALUMNO_NOMBRE, ',');
        archivo>>aux.codigoEscala;
        
        int posicion;
        posicion = buscaAlumno(aux, alumnos, cantidadAlumnos);
        if(posicion == NO_ENCONTRADO)
            agregaAlumno(aux, alumnos, cantidadAlumnos);    
    }
}
int buscaAlumno(const struct Alumno &aux, struct Alumno* alumnos, int cantidad){
    int limiteInferior=0, limiteSuperior = cantidad-1, poscicionMedio;
    while(true){
        if(limiteInferior > limiteSuperior) return NO_ENCONTRADO;
        
        poscicionMedio =(limiteInferior+limiteSuperior)/2;        
        if(aux.codigo == alumnos[poscicionMedio].codigo) return poscicionMedio;
        else if(aux.codigo > alumnos[poscicionMedio].codigo) limiteInferior = poscicionMedio+1;
        else if(aux.codigo < alumnos[poscicionMedio].codigo) limiteSuperior = poscicionMedio-1;
        
    }
}
void agregaAlumno(const struct Alumno &aux, struct Alumno* alumnos, int& cantidad){
    int i= cantidad-1;
    while(true){
        if(i<0 or aux.codigo>alumnos[i].codigo) break;
        alumnos[i+1] = alumnos[i];        
        i--;
    }

    alumnos[i+1] = aux;
    
    cantidad++;
}


void leeCursos(const char* nombreArchivo, struct Curso* cursos, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    while(true){
        // 109263,Algoritmia,4.25        
        
        struct Curso aux;
        
        archivo>>aux.codigo;
        if(archivo.eof()) break;
        archivo.get();
        archivo.getline(aux.nombre, TAM_CURSO_NOMBRE, ',');
        modificaNombre(aux.nombre);
        archivo>>aux.creditos;
        
        int posicion;
        posicion = buscaCurso(aux, cursos, cantidad);
        if(posicion == NO_ENCONTRADO){
            agregaCurso(aux, cursos, cantidad);            
        }
        
        
        
    }
}
int buscaCurso(const struct Curso& aux, struct Curso* cursos, int cantidad){
    int limiteInferior=0, limiteSuperior = cantidad-1, poscicionMedio;
    while(true){
        if(limiteInferior > limiteSuperior) return NO_ENCONTRADO;
        
        poscicionMedio =(limiteInferior+limiteSuperior)/2;        
        if(aux.codigo == cursos[poscicionMedio].codigo) return poscicionMedio;
        else if(aux.codigo > cursos[poscicionMedio].codigo) limiteInferior = poscicionMedio+1;
        else if(aux.codigo < cursos[poscicionMedio].codigo) limiteSuperior = poscicionMedio-1;
        
    }
}
void agregaCurso(const struct Curso& aux, struct Curso* curso, int& cantidad){
    int i= cantidad-1;
    while(true){
        if(i<0 or aux.codigo>curso[i].codigo) break;
        curso[i+1].codigo = curso[i].codigo; 
        strcpy(curso[i+1].nombre, curso[i].nombre); 
        curso[i+1].creditos = curso[i].creditos;
        
        i--;
    }

    curso[i+1].codigo = aux.codigo;
    strcpy(curso[i+1].nombre, aux.nombre); 
    curso[i+1].creditos = aux.creditos;
    
    cantidad++;
}
void modificaNombre(char* nombre){
    for (int i = 0; nombre[i]; i++) {
        if(nombre[i] >= 'a' and nombre[i]<='z') nombre[i] += 'A'-'a';
    }

}

void leeEscalas(const char* nombreArchivo, struct Escala* escalas, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    while(true){
        // 2021-2,C,288.65
//        int anio, periodo, ciclo;
//        char codigo, descC;
//        double precio;
        
        int anio, periodo;
        char descC;
        struct Escala escalaAux;
        
        archivo>>anio;
        if(archivo.eof()) break;
        archivo>>descC>>periodo>>descC>>escalaAux.codigo>>descC>>escalaAux.precio;
        escalaAux.ciclo = anio*10 + periodo;
        
        int posicion;
        posicion = buscaEscala(escalaAux, escalas, cantidad);
        if(posicion == NO_ENCONTRADO)
            agregaEscala(escalaAux, escalas, cantidad);          
        
    }
}
int buscaEscala(const struct Escala& aux, struct Escala* escalas, int cantidad){
    int limiteInferior=0, limiteSuperior = cantidad-1, poscicionMedio;
    while(true){
        if(limiteInferior > limiteSuperior) return NO_ENCONTRADO;
        
        poscicionMedio =(limiteInferior+limiteSuperior)/2;        
        if(aux.ciclo == escalas[poscicionMedio].ciclo){
            if(aux.codigo == escalas[poscicionMedio].codigo)return poscicionMedio;
            else if(aux.codigo > escalas[poscicionMedio].codigo) limiteInferior = poscicionMedio+1; 
            else if(aux.codigo < escalas[poscicionMedio].codigo) limiteSuperior = poscicionMedio-1;
        }
        else if(aux.ciclo > escalas[poscicionMedio].ciclo) limiteInferior = poscicionMedio+1;
        else if(aux.ciclo < escalas[poscicionMedio].ciclo) limiteSuperior = poscicionMedio-1;
        
    }
}
void agregaEscala(const struct Escala& aux, struct Escala* escalas, int& cantidad){
    int i= cantidad-1;
    while(true){
        if(i<0 
            or 
                (aux.ciclo > escalas[i].ciclo) 
                or 
                (aux.ciclo == escalas[i].ciclo and aux.codigo > escalas[i].codigo)) break;        
        escalas[i+1].ciclo = escalas[i].ciclo; 
        escalas[i+1].codigo =  escalas[i].codigo; 
        escalas[i+1].precio = escalas[i].precio;
        
        i--;
    }

    escalas[i+1].ciclo = aux.ciclo;
    escalas[i+1].codigo = aux.codigo; 
    escalas[i+1].precio = aux.precio;
    
    cantidad++;
}

void leeMatricula(const char* nombreArchivo, int cicloValido, 
        struct Curso* cursos, int cantidadCursos, 
        struct Alumno* alumnos, int cantidadAlumos, 
        struct Escala* escalas, int cantidadEscalas){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    while(true){
        //2023-2,20231938,481203,375219,231286,231292
        int anio, periodo, ciclo;
        struct Alumno auxAlumno;
        char descC;
        archivo>>anio;
        if(archivo.eof()) break;
        archivo>>descC>>periodo>>descC>>auxAlumno.codigo;
        ciclo = anio*10 + periodo;
        
        int posicionAlumno, posicionEscala;
        posicionAlumno = buscaAlumno(auxAlumno, alumnos, cantidadAlumos);
        
        if(posicionAlumno != NO_ENCONTRADO){
            struct Escala auxEscala;
            auxEscala.ciclo = ciclo;
            auxEscala.codigo = alumnos[posicionAlumno].codigoEscala;
            posicionEscala = buscaEscala(auxEscala, escalas, cantidadEscalas);
      
            if(ciclo == cicloValido and posicionEscala != NO_ENCONTRADO){
                while(true){
                    if(archivo.get()=='\n') break;
                    int codigoCurso;
                    archivo>>codigoCurso;

                    int posicionCurso;
                    struct Curso auxCurso;
                    auxCurso.codigo = codigoCurso;
                    posicionCurso = buscaCurso(auxCurso, cursos, cantidadCursos);

                    if(posicionCurso != NO_ENCONTRADO){
                        cursos[posicionCurso].cantidadMatriculados++;
                        cursos[posicionCurso].pagoMatriculados += cursos[posicionCurso].creditos*escalas[posicionEscala].precio;
                    }
                }
            }
            else while(archivo.get()!='\n');
            
        }
        
        else while(archivo.get()!='\n');
        

    }
}
void ordenaCursos(struct Curso* cursos, int cantidad){
    for (int i = 0; i < cantidad-1; i++) {        
        for (int j = i+1; j < cantidad; j++) {
            if(cursos[i].cantidadMatriculados > cursos[j].cantidadMatriculados 
                    or
                cursos[i].cantidadMatriculados == cursos[j].cantidadMatriculados and strcmp(cursos[i].nombre, cursos[j].nombre)<0){
                
                cambiaCurso(cursos[i], cursos[j]);
            }
        }

    }

}
void cambiaCurso(struct Curso &c1, struct Curso &c2){
    struct Curso aux;
    aux = c1;
    c1=c2;
    c2=aux;
}  

void imprimeReporte(const char* nombreArchivo, int cicloValido, 
        struct Curso* cursos, int cantidadCursos){
    
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        exit(1);
    }
    
    imprimeEncabezado(archivo, cicloValido);    
    
    double total=0;
    for (int i = 0; i < cantidadCursos; i++) {    
        archivo<<left<<fixed<<setprecision(2)
            <<right<<setw(MAX_CAR_CONT-2)<<setfill('0')<<i+1<<setfill(' ')<<setw(2)<<left<<')'
            <<setw(MAX_CAR_CURSO)<<cursos[i].nombre
            <<setw(MAX_CAR_CREDITOS)<<cursos[i].creditos
            <<setw(MAX_CAR_ALUMNOS)<<cursos[i].cantidadMatriculados
            <<setw(MAX_CAR_MONTO)<<cursos[i].pagoMatriculados
//            <<setw(20)<<cursos[i].codigo 
            <<endl;    
        
        total+=cursos[i].pagoMatriculados;
    }
    
    imprimeLinea('-', archivo);
    archivo<<"MONTO TOTAL PAGADO: "<<setw(ALING_TOTAL-20)<<""<<total<<endl;
    imprimeLinea('=', archivo);

}
void imprimeEncabezado(ofstream& archivo, int ciclo){
    archivo<<right
            <<setw(MAX_CAR_LIN/2-3)<<"INSTITUCION EDUCATIVA VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"DETALLES DE PAGO REALIZADO POR CICLO"<<endl
            <<setw(MAX_CAR_LIN/2-20)<<"CICLO: "<<ciclo/10<<"-"<<ciclo%10<<endl;
    imprimeLinea('=', archivo);
    
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_CONT)<<"No."
            <<setw(MAX_CAR_CURSO)<<"CURSO"
            <<setw(MAX_CAR_CREDITOS)<<"CREDITOS"
            <<setw(MAX_CAR_ALUMNOS)<<"ALUMNOS MATRICULADOS"
            <<setw(MAX_CAR_MONTO)<<"MONTO PAGADO"
            <<endl;
    
    imprimeLinea('=', archivo);
}            
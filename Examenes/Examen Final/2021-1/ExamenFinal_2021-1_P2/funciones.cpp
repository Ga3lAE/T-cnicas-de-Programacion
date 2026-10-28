#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

#include "Libro.h"
#include "RegistroPrestamo.h"
#include "LibroPrestado.h"
#include "funciones.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 170
#define MAX_CAR_COD 10
#define MAX_CAR_TITULO 50
#define MAX_CAR_AUTOR 50
#define MAX_CAR_FECHA 12
#define MAX_CAR_CANT 10
#define MAX_CAR_NOMBRE 60
#define MAX_CAR_OBS 60

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
    aux = new char [strlen(buff)+1]{};
    strcpy(aux, buff);
    return aux;
}

void leeLibros(const char* nombreArchivo, struct Libro* libros, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //QV96140,El Duque en su territorio,Fiorella Florencio Polo,2003,5,0
        libros[cantidad].codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        libros[cantidad].titulo = leeCadena(archivo, ',');
        libros[cantidad].autor = leeCadena(archivo, ',');
        archivo>>libros[cantidad].aPublicacion;
        archivo.get();
        archivo>>libros[cantidad].cantidad;
        archivo.get();
        archivo>>libros[cantidad].prestamos;
        archivo.get();        
        
        cantidad++;
    }
}
void confirmaLibros(const char* nombreArchivo, struct Libro* libros, 
        int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_TITULO)<<"TITULO"
            <<setw(MAX_CAR_AUTOR)<<"AUTOR"
            <<setw(MAX_CAR_FECHA)<<"FECHA PUBLI"
            <<setw(MAX_CAR_CANT)<<"DISPONIBLE"
            <<setw(MAX_CAR_CANT)<<"PRESTADA"
            <<endl;
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_CAR_COD)<<libros[i].codigo
                <<setw(MAX_CAR_TITULO)<<libros[i].titulo
                <<setw(MAX_CAR_AUTOR)<<libros[i].autor
                <<setw(MAX_CAR_FECHA)<<libros[i].aPublicacion
                <<setw(MAX_CAR_CANT)<<libros[i].cantidad
                <<setw(MAX_CAR_CANT)<<libros[i].prestamos
                <<endl;
    }
    
}

void leePrestamos(const char* nombreArchivo, struct RegistroPrestamo* prestamos, 
        int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //35030611,Inga Flores Cesar Adolfo,XW06135,26/06/2021,LM05731,3/07/2021
        archivo>>prestamos[cantidad].codigo;
        if(archivo.eof()) break;
        archivo.get();
        prestamos[cantidad].nombre = leeCadena(archivo, ',');
        prestamos[cantidad].libros = 
                new struct LibroPrestado[MAX_LIBROS_PRESTADOS]{};
        prestamos[cantidad].cantidadLibros = 0;
        
        while(true){
            int posPrestamo=prestamos[cantidad].cantidadLibros, 
                    dd,mm,aa;
            char descC;
            prestamos[cantidad].libros[posPrestamo].codigo = 
                    leeCadena(archivo, ',');
            archivo>>dd>>descC>>mm>>descC>>aa;            
            prestamos[cantidad].libros[posPrestamo].fecha = dd+mm*100+aa*10000;
            prestamos[cantidad].cantidadLibros++; 
            if(archivo.get() == '\n') break;                                   
        }
        
        cantidad++;
    }
}
void confirmaPrestamos(const char* nombreArchivo, 
        struct RegistroPrestamo* prestamos, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_TITULO)<<"NOMBRE"<<endl;    
                        
    for (int i = 0; i < cantidad; i++) {        
        archivo<<left
                <<setw(MAX_CAR_COD)<<prestamos[i].codigo
                <<setw(MAX_CAR_NOMBRE)<<prestamos[i].nombre<<endl
                <<"PRESTAMOS:"<<endl;                
        for (int j = 0; j < prestamos[i].cantidadLibros; j++) {            
            archivo<<setw(MAX_CAR_COD)<<prestamos[i].libros[j].codigo
                    <<setw(MAX_CAR_FECHA)<<prestamos[i].libros[j].fecha
                    <<endl;
        }

    }
    
}

void leeSolicitudes(const char* nombreArchivo, const char* nombreArchivoReporte,
        struct RegistroPrestamo* prestamos, int& cantidadPrestamos, 
        struct Libro* libros, int cantidadLibros){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoReporte;
        exit(1);        
    }
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"BIBLIOTECA VENUS"<<endl;
    archivoReporte<<left
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_COD)<<"LIBRO"
            <<setw(MAX_CAR_TITULO)<<"TITULO"
            <<setw(MAX_CAR_OBS)<<"OBSERVACIO"
            <<endl;
    
    int fechaPedido, fechaDevolucion, dd,mm,aa;
    char descC;
    archivo>>dd>>descC>>mm>>descC>>aa;
    fechaPedido = dd+mm*100+aa*10000;
    archivo>>dd>>descC>>mm>>descC>>aa;
    fechaDevolucion = dd+mm*100+aa*10000;
    
    while(true){
        // 81082011,Arroyo Gordillo Maria Heli,BB35881
        int codigoUsuario;
        char* nombreUsuario, *codigoLibro;
        
        archivo>>codigoUsuario;
        if(archivo.eof()) break;
        archivo.get();
        nombreUsuario = leeCadena(archivo, ',');
        codigoLibro = leeCadena(archivo, '\n');
        
        int posUsuario, posLibro;
        posUsuario = buscaUsuario(codigoUsuario, prestamos, cantidadPrestamos);
        posLibro = buscaLibro(codigoLibro, libros, cantidadLibros);
                
        int tipo =0;
        if(posLibro!= NO_ENCONTRADO){
            if(posUsuario == NO_ENCONTRADO){
                prestamos[cantidadPrestamos].codigo = codigoUsuario;
                prestamos[cantidadPrestamos].nombre = 
                        new char[strlen(nombreUsuario)+1];
                strcpy(prestamos[cantidadPrestamos].nombre, nombreUsuario);
                prestamos[cantidadPrestamos].cantidadLibros = 0;
                
                int posPrestamo = prestamos[cantidadPrestamos].cantidadLibros;                                
                prestamos[cantidadPrestamos].libros[posPrestamo].codigo =
                        new char[strlen(codigoLibro)+1];
                strcpy(prestamos[cantidadPrestamos].libros[posPrestamo].codigo,
                        codigoLibro);z
                prestamos[cantidadPrestamos].libros[posPrestamo].fecha = fechaPedido;
                
                cantidadPrestamos++;
            }            
            posUsuario = buscaUsuario(codigoUsuario, prestamos, cantidadPrestamos);            
            imprimeEnReporte(archivoReporte, codigoUsuario, 
                prestamos[posUsuario], libros[posLibro], tipo);
        }
        else{
            struct Libro libroNoEncontrado;
            libroNoEncontrado.codigo = new char[4];
            strcpy(libroNoEncontrado.codigo, "---");
            libroNoEncontrado.titulo=  new char[4];
            strcpy(libroNoEncontrado.titulo, "---");
            tipo = 4;
            imprimeEnReporte(archivoReporte, codigoUsuario, 
                prestamos[posUsuario], libroNoEncontrado, tipo);
        }

    }
    
}

int buscaUsuario (int codigo, struct RegistroPrestamo* prestamos, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(codigo == prestamos[i].codigo) return i;
    }
    return NO_ENCONTRADO;
}
int buscaLibro (char* codigo, struct Libro* libros, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, libros[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}

void imprimeEnReporte(ofstream& archivo, 
        int dni, const struct RegistroPrestamo& prestamo,
        const struct Libro& libro,
        int tipo){
    
    archivo<<left
            <<setw(MAX_CAR_COD)<<dni
            <<setw(MAX_CAR_NOMBRE)<<prestamo.nombre
            <<setw(MAX_CAR_COD)<<libro.codigo
            <<setw(MAX_CAR_TITULO)<<libro.titulo;            
    if(tipo == 0)
        archivo<<"SE LE ENTREGÓ EL LIBRO"<<endl;
    else if(tipo == 1)
        archivo<<"NO HAY LIBRO DISPONIBLE"<<endl;
    else if(tipo == 2)
        archivo<<"SUPERO LA FECHA LIMITE"<<endl;
    else if(tipo == 3)
        archivo<<"SUPERO EL LIMTE DE PRESTAMOS"<<endl;
    else if(tipo == 4)
        archivo<<"NO EXISTE EL LIBRO"<<endl;
    
}
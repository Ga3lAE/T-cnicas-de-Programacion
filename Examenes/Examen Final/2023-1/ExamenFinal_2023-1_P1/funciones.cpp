#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

#include "Libro.h"
#include "UsuariosConElLibro.h"
#include "Usuario.h"
#include "LibroEnSuPoder.h"
#include "funciones.h"

#define NO_ECNONTRADO -1

#define MAX_LIBROS_PODER 6

#define ALING 5
#define MAX_CAR_LIN 200
#define MAX_CAR_COD 10
#define MAX_CAR_TITULO 60
#define MAX_CAR_NOMBRE 50
#define MAX_CAR_CANT 15
#define MAX_CAR_DINERO 15 

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
    aux = new char[strlen(buff)+1];
    strcpy(aux, buff);
    return aux;
}

void leeLibros(const char* nombreArchivo, struct Libro* libros, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //QV96140,El Duque en su territorio,Fiorella Florencio Polo,12,37.47,
        //17750908,3/07/2023,
        //14500753,6/07/2023,

        char *codigo;   
        codigo = leeCadena(archivo, ',');
        if(archivo.eof()) break;
        libros[cantidad].codigo = new char[strlen(codigo)+1];
        strcpy(libros[cantidad].codigo, codigo);
        libros[cantidad].titulo = leeCadena(archivo, ',');
        libros[cantidad].autor = leeCadena(archivo, ',');
        archivo>>libros[cantidad].cantidad;
        archivo.get();
        archivo>>libros[cantidad].precio;        
        
        libros[cantidad].usuarios = new struct UsuariosConElLibro[50]{};
        libros[cantidad].cantUsuarios = 0;
        int dni,dd,mm,aa;
        char descC;
        while(true){
            int posUsuario = libros[cantidad].cantUsuarios;
            if(archivo.get()=='\n') break;
            archivo>>dni>>descC>>dd>>descC>>mm>>descC>>aa;
            libros[cantidad].usuarios[posUsuario].dni = dni;
            libros[cantidad].usuarios[posUsuario].fechaDeDevolucion = 
                    dd+ mm*100+ aa*10000 ;
            libros[cantidad].cantUsuarios++;                        
        }
        
        cantidad++;
    }
}

void verificaLibros(const char* nombreArchivo, struct Libro* libros, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"LIBROS DE LA BIBLIOTECA"<<endl;
    
    for (int i = 0; i < cantidad; i++) {        
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_TITULO)<<"TITULO"
            <<setw(MAX_CAR_NOMBRE)<<"AUTOR"
            <<setw(MAX_CAR_CANT)<<"VOLUMENES"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"            
            <<endl;
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<libros[i].codigo
            <<setw(MAX_CAR_TITULO)<<libros[i].titulo
            <<setw(MAX_CAR_NOMBRE)<<libros[i].autor
            <<setw(MAX_CAR_CANT)<<libros[i].cantidad
            <<setw(MAX_CAR_DINERO)<<libros[i].precio    
            <<endl;
    imprimeLinea('-', archivo);
    archivo<<setw(ALING)<<" "<<"PRESTAMOS"<<endl;
    imprimeLinea('-', archivo);
    archivo<<setw(ALING)<<" "<<setw(MAX_CAR_COD)<<"DNI"<<setw(MAX_CAR_COD)<<"FECHA"<<endl;
    for (int j = 0; j < libros[i].cantUsuarios; j++) {
        int fecha = libros[i].usuarios[j].fechaDeDevolucion;
        int dd,mm,aa;
        aa=fecha/10000;
        fecha%=10000;
        mm=fecha/100;
        fecha%=100;
        dd=fecha;
        archivo<<setw(ALING)<<" "
                <<setw(MAX_CAR_COD)<<libros[i].usuarios[j].dni
                <<right<<setfill('0')
                <<setw(2)<<dd<<"/"
                <<setw(2)<<mm<<"/"
                <<setw(4)<<aa
                <<setw(MAX_CAR_COD-10)<<""
                <<left<<setfill(' ')                
                <<endl;
        }           
    }

}

void leeUsuarios(const char* nombreArchivo, struct Usuario* usuarios, int& cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        // 54393647,Reyes Tang Edward,V,13.00,XW06135 VA35843 QO90975
        int dni;
        archivo>>dni;
        if(archivo.eof()) break;
        usuarios[cantidad].dni = dni;
        archivo.get();
        usuarios[cantidad].nombre = leeCadena(archivo, ',') ;
        archivo>>usuarios[cantidad].categoria;
        archivo.get();
        archivo>>usuarios[cantidad].calificacion;
        archivo.get();
        usuarios[cantidad].cantLibros=0;
        usuarios[cantidad].libros = new struct LibroEnSuPoder[MAX_LIBROS_PODER]{};
        
        int posLibro;
        char codigoLibro[MAX_CAR_COD];
        while(true){
            if(archivo.peek()=='\n') break;
            posLibro = usuarios[cantidad].cantLibros;
            archivo>>codigoLibro;
            usuarios[cantidad].libros[posLibro].codLibro = new char[strlen(codigoLibro)+1]{};
            strcpy(usuarios[cantidad].libros[posLibro].codLibro, codigoLibro);
            usuarios[cantidad].cantLibros++;
        }
        cantidad++;

    }
}

void verificaUsuarios(const char* nombreArchivo, struct Usuario* usuarios, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    archivo<<setw(MAX_CAR_LIN/2)<<"USUARIOS DE LA BIBLIOTECA"<<endl;
    
    for (int i = 0; i < cantidad; i++) {        
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_COD)<<"CATEGORIA"
            <<setw(MAX_CAR_DINERO)<<"CALIFICACION"            
            <<endl;
    imprimeLinea('=', archivo);
    archivo<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<usuarios[i].dni
            <<setw(MAX_CAR_NOMBRE)<<usuarios[i].nombre
            <<setw(MAX_CAR_COD)<<usuarios[i].categoria
            <<setw(MAX_CAR_DINERO)<<usuarios[i].calificacion
            <<endl;
    imprimeLinea('-', archivo);
    archivo<<setw(ALING)<<" "<<"LIBROS EN POSESION"<<endl;
    for (int j = 0; j < usuarios[i].cantLibros; j++) {            
        archivo<<setw(ALING)<<" "
                <<setw(MAX_CAR_COD)<<usuarios[i].libros[j].codLibro                
                <<endl;
        }           
    }

}

void leeDevoluciones(const char* nombreArchivo, 
        struct Usuario* usuarios, int cantidadUsuarios, 
        struct Libro* libros, int cantidadLibros){    
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivo;
        exit(1);
    }
    
    // 3/7/2023
    int dd,mm,aa, fecha, nDNI;
    char descC, codigo[MAX_CAR_COD]{};
    archivo>>dd>>descC>>mm>>descC>>aa;
    fecha = dd+ mm*100+ aa*10000;
    while(true){
        // 79743481   QO90975
        if(archivo.eof()) break;
        archivo>>nDNI>>codigo;
        int posLibro, posUsuario;
        posLibro = buscaLibro(codigo, libros, cantidadLibros);
        posUsuario = buscaUsuario(nDNI, usuarios, cantidadUsuarios);
        
        if(posLibro != NO_ECNONTRADO and posUsuario != NO_ECNONTRADO){            
            /*
             * Usuario
                int dni;
                char* nombre;
                char categoria;
                double calificacion;
                struct LibroEnSuPoder *libros;
                int cantLibros;
             
             * Libro
                char* codigo;
                char* titulo;
                char* autor;
                int cantidad;
                double precio;
                struct UsuariosConElLibro* usuarios;
                int cantUsuarios;
                *UsuariosConLibro
                    int dni;
                    int fechaDeDevolucion;       
             */
                        
            eliminaLibroEnPoder(usuarios[posUsuario].libros, codigo, 
                    usuarios[posUsuario].cantLibros);
            
            procesaDevolucion(libros[posLibro],
                    fecha, usuarios[posUsuario]);
            
        }
        
    }
}
int buscaLibro(char* codigo, struct Libro* libros, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, libros[i].codigo)==0) return i;
    }
    return NO_ECNONTRADO;
}
int buscaUsuario(int nDNI, struct Usuario* usuarios, int cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(nDNI == usuarios[i].dni) return i;
    }
    return NO_ECNONTRADO;
}
void eliminaLibroEnPoder(struct LibroEnSuPoder *libros, char* codigo, int& cantidad){
    for (int i = 0; i < cantidad; i++) {        
        if(strcmp(codigo, libros[i].codLibro)==0){
            libros[i] = libros[cantidad-1];
            cantidad--;
        }
    }
}
void procesaDevolucion(struct Libro& libro, int fecha, struct Usuario& usuario){
    for (int i = 0; i < libro.cantUsuarios; i++) {        
        if(usuario.dni == libro.usuarios[i].dni){
            libro.usuarios[i] = libro.usuarios[libro.cantUsuarios-1];
            libro.cantUsuarios--;
            
            if(fecha>libro.usuarios[i].fechaDeDevolucion){
                if(usuario.categoria == 'A')
                    usuario.calificacion*=0.9;
                else if(usuario.categoria == 'D')
                    usuario.calificacion*=0.8;                    
                else if(usuario.categoria == 'V')
                    usuario.calificacion*=0.85;                                        
            }
        }
    }

}
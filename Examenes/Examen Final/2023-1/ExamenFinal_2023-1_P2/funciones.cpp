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

#define ALING 5
#define MAX_CAR_LIN 150
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
void datosArchivoIn(int tamElemento, int& cantidad, ifstream& archivoDatos){
    int tamArchivo;
    archivoDatos.seekg(0, ios::end);
    tamArchivo = archivoDatos.tellg();
    cantidad = tamArchivo / tamElemento;
    archivoDatos.seekg(0, ios::beg);
}
void datosArchivoF(int tamElemento, int& cantidad, fstream& archivoDatos){
    int tamArchivo;
    archivoDatos.seekg(0, ios::end);
    tamArchivo = archivoDatos.tellg();
    cantidad = tamArchivo / tamElemento;
    archivoDatos.seekg(0, ios::beg);
}

void leeLibros(const char* nombreArchivoLec, const char* nombreArchivoBin){
    ifstream archivoLec(nombreArchivoLec, ios::in);
    if(not archivoLec.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoLec;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Libro libro;
    while(true){
        //QV96140,El Duque en su territorio,Fiorella Florencio Polo,12,37.47,
        //17750908,3/07/2023,
        //14500753,6/07/2023,

        char codigo[TAM_LIBRO_COD]{};
        archivoLec.getline(codigo, TAM_LIBRO_COD, ',');
        if(archivoLec.eof()) break;
        strcpy(libro.codigo, codigo);
        archivoLec.getline(libro.titulo, TAM_LIBRO_TITULO, ',');
        archivoLec.getline(libro.autor, TAM_LIBRO_AUTOR, ',');
        archivoLec>>libro.cantidad;
        archivoLec.get();
        archivoLec>>libro.precio;
        
        int dni,dd,mm,aa;
        char descC;
        libro.cantUsuarios=0;        
        while(true){
            int posUsuario = libro.cantUsuarios;
            if(archivoLec.get()=='\n') break;
            archivoLec>>dni>>descC>>dd>>descC>>mm>>descC>>aa;
            libro.usuarios[posUsuario].dni = dni;
            libro.usuarios[posUsuario].fechaDeDevolucion = 
                    dd+ mm*100+ aa*10000 ;
            libro.cantUsuarios++;                        
        }
        
        archivoBin.write(reinterpret_cast<const char*>(&libro), sizeof(struct Libro));
    }
}
void verificaLibros(const char* nombreArchivoReporte, const char* nombreArchivoDatos){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    
    ifstream archivoDatos(nombreArchivoDatos, ios::in|ios::binary);
    if(not archivoDatos.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    
    int tamElemento, cantidadElementos;
    tamElemento=sizeof(struct Libro);
    datosArchivoIn(tamElemento, cantidadElementos, archivoDatos);
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"LIBROS DE LA BIBLIOTECA"<<endl;
    
    struct Libro libro;
    for (int i = 0; i < cantidadElementos; i++) {
        archivoDatos.read(reinterpret_cast<char*>(&libro), tamElemento);
    imprimeLinea('=', archivoReporte);
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"CODIGO"
            <<setw(MAX_CAR_TITULO)<<"TITULO"
            <<setw(MAX_CAR_NOMBRE)<<"AUTOR"
            <<setw(MAX_CAR_CANT)<<"VOLUMENES"
            <<setw(MAX_CAR_DINERO)<<"PRECIO"            
            <<endl;
    imprimeLinea('=', archivoReporte);
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<libro.codigo
            <<setw(MAX_CAR_TITULO)<<libro.titulo
            <<setw(MAX_CAR_NOMBRE)<<libro.autor
            <<setw(MAX_CAR_CANT)<<libro.cantidad
            <<setw(MAX_CAR_DINERO)<<libro.precio    
            <<endl;
    imprimeLinea('-', archivoReporte);
    archivoReporte<<setw(ALING)<<" "<<"PRESTAMOS"<<endl;
    imprimeLinea('-', archivoReporte);
    archivoReporte<<setw(ALING)<<" "<<setw(MAX_CAR_COD)<<"DNI"<<setw(MAX_CAR_COD)<<"FECHA"<<endl;
    for (int j = 0; j < libro.cantUsuarios; j++) {
        int fecha = libro.usuarios[j].fechaDeDevolucion;
        int dd,mm,aa;
        aa=fecha/10000;
        fecha%=10000;
        mm=fecha/100;
        fecha%=100;
        dd=fecha;
        archivoReporte<<setw(ALING)<<" "
                <<setw(MAX_CAR_COD)<<libro.usuarios[j].dni
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

void leeUsuarios(const char* nombreArchivoLec, const char* nombreArchivoBin){
    ifstream archivoLec(nombreArchivoLec, ios::in);
    if(not archivoLec.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoLec;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Usuario usuario;
    while(true){
        // 54393647,Reyes Tang Edward,V,13.00,XW06135 VA35843 QO90975
        int dni;
        archivoLec>>dni;
        if(archivoLec.eof()) break;
        usuario.dni = dni;
        archivoLec.get();
        archivoLec.getline(usuario.nombre, TAM_USUARIO_NOMBRE, ',');
        archivoLec>>usuario.categoria;
        archivoLec.get();
        archivoLec>>usuario.calificacion;
        archivoLec.get();
        usuario.cantLibros=0;
        archivoLec.get();
        
        int posLibro;        
        while(true){
            if(archivoLec.peek()=='\n') break;
            posLibro = usuario.cantLibros;
            archivoLec>>usuario.libros[posLibro].codLibro;
            usuario.cantLibros++;
        }
        archivoBin.write(reinterpret_cast<const char*>(&usuario), sizeof(struct Usuario));        
    }
}
void verificaUsuarios(const char* nombreArchivoReporte, const char* nombreArchivoDatos){
    ofstream archivoReporte(nombreArchivoReporte, ios::out);
    if(not archivoReporte.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoReporte;
        exit(1);
    }
    
    ifstream archivoDatos(nombreArchivoDatos, ios::in|ios::binary);
    if(not archivoDatos.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoDatos;
        exit(1);
    }
    
    int tamElemento, cantidadElementos;
    tamElemento=sizeof(struct Usuario);
    datosArchivoIn(tamElemento, cantidadElementos, archivoDatos);        
    struct Usuario usuario;
    
    archivoReporte<<setw(MAX_CAR_LIN/2)<<"USUARIOS DE LA BIBLIOTECA"<<endl;
    
    for (int i = 0; i < cantidadElementos; i++) {
        archivoDatos.read(reinterpret_cast<char*>(&usuario), tamElemento);
    imprimeLinea('=', archivoReporte);
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<"DNI"
            <<setw(MAX_CAR_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_COD)<<"CATEGORIA"
            <<setw(MAX_CAR_DINERO)<<"CALIFICACION"            
            <<endl;
    imprimeLinea('=', archivoReporte);
    archivoReporte<<left<<fixed<<setprecision(2)
            <<setw(MAX_CAR_COD)<<usuario.dni
            <<setw(MAX_CAR_NOMBRE)<<usuario.nombre
            <<setw(MAX_CAR_COD)<<usuario.categoria
            <<setw(MAX_CAR_DINERO)<<usuario.calificacion
            <<endl;
    imprimeLinea('-', archivoReporte);
    archivoReporte<<setw(ALING)<<" "<<"LIBROS EN POSESION"<<endl;
    for (int j = 0; j < usuario.cantLibros; j++) {            
        archivoReporte<<setw(ALING)<<" "
                <<setw(MAX_CAR_COD)<<usuario.libros[j].codLibro                
                <<endl;
        }           
    }

}

void leeDevoluciones(const char* nombreArchivoDevoluciones, 
        const char* nombreArchivoLibros, const char* nombreArchivoUsuarios){
    fstream archivoLibros(nombreArchivoLibros, ios::in|ios::out|ios::binary);
    if(not archivoLibros.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoLibros;
        exit(1);
    }
    fstream archivoUsuarios(nombreArchivoUsuarios, ios::in|ios::out|ios::binary);
    if(not archivoUsuarios.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoUsuarios;
        exit(1);
    }
    ifstream archivoDevoluciones(nombreArchivoDevoluciones, ios::in);
    if(not archivoDevoluciones.is_open()){
        cout<<"ERROR:  No se pudo abrir el archivo "<<nombreArchivoDevoluciones;
        exit(1);
    }
    
    // 3/7/2023
    int dd,mm,aa,fecha;
    char descC;
    archivoDevoluciones>>dd>>descC>>mm>>descC>>aa;
    fecha = dd+ mm*100+ aa*10000;
    
    int tamLibro, cantidadLibros;
    tamLibro = sizeof(struct Libro);
    datosArchivoF(tamLibro, cantidadLibros, archivoLibros);
    
    int tamUsuario, cantidadUsuarios;
    tamUsuario = sizeof(struct Usuario);
    datosArchivoF(tamUsuario, cantidadUsuarios, archivoUsuarios);    
    while(true){
        // 79743481   QO90975
        int dni;
        char codigo[TAM_LIBRO_COD]{};
        archivoDevoluciones>>dni;
        if(archivoDevoluciones.eof()) break;
        archivoDevoluciones>>codigo;
                
        int posUsuario, posLibro;
        posUsuario = buscaUsuario(dni, archivoUsuarios, cantidadUsuarios);
        posLibro = buscaLibro(codigo, archivoLibros, cantidadLibros);  
        
        if(posLibro!=NO_ECNONTRADO and posUsuario!=NO_ECNONTRADO){
            
             /*
//             * Usuario
//                int dni;
//                char* nombre;
//                char categoria;
//                double calificacion;
//                struct LibroEnSuPoder *libros;
//                int cantLibros;
//             
//             * Libro
//                char* codigo;
//                char* titulo;
//                char* autor;
//                int cantidad;
//                double precio;
//                struct UsuariosConElLibro* usuarios;
//                int cantUsuarios;
//                *UsuariosConLibro
//                    int dni;
//                    int fechaDeDevolucion;       
//             */
//                        
            eliminaLibroEnPoder(archivoUsuarios, posUsuario, codigo);
            
            procesaDevolucion(archivoLibros, archivoUsuarios, posLibro, fecha, dni);
            
        }
    }    
}

int buscaLibro(char* codigo, fstream& archivo, int cantidad){
    archivo.seekg(0, ios::beg);
    struct Libro libro;
    for (int i = 0; i < cantidad; i++) {
        archivo.read(reinterpret_cast<char*>(&libro), sizeof(struct Libro));
        if(strcmp(codigo, libro.codigo)==0) return i;
    }
    return NO_ECNONTRADO;
}
int buscaUsuario(int nDNI, fstream& archivo, int cantidad){
    archivo.seekg(0, ios::beg);
    struct Usuario usuario;
    for (int i = 0; i < cantidad; i++) {   
        archivo.read(reinterpret_cast<char*>(&usuario), sizeof(struct Usuario));
        if(nDNI == usuario.dni) return i;
    }
    return NO_ECNONTRADO;
}

void eliminaLibroEnPoder(fstream& archivo, int posUsuario, char* codigo){
    int tamUsuario, cantidadUsuarios;
    tamUsuario = sizeof(struct Usuario);
    datosArchivoF(tamUsuario, cantidadUsuarios, archivo);
    archivo.seekg(posUsuario*tamUsuario, ios::beg);
    
    struct Usuario usuario;
    archivo.read(reinterpret_cast<char*>(&usuario), tamUsuario);
        
    for (int i = 0; i < usuario.cantLibros; i++) {        
        if(strcmp(codigo, usuario.libros[i].codLibro)==0){
            usuario.libros[i] = usuario.libros[usuario.cantLibros-1];
            usuario.cantLibros--;
        }
    }
    archivo.seekg(posUsuario*tamUsuario, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&usuario), tamUsuario);
    archivo.flush();
}
void procesaDevolucion(fstream& archivo, fstream& archivoUsuarios, 
        int posLibro, int fecha, int dni){
    
    int tamLibro, cantidadLibros;
    tamLibro = sizeof(struct Libro);
    datosArchivoF(tamLibro, cantidadLibros, archivo);
    archivo.seekg(posLibro*tamLibro, ios::beg);
    
    struct Libro libro;
    archivo.read(reinterpret_cast<char*>(&libro), tamLibro);

    int tamUsuario, cantidadUsuarios;
    tamUsuario = sizeof(struct Usuario);
    datosArchivoF(tamUsuario, cantidadUsuarios, archivo);
    int posUsuario;
    posUsuario = buscaUsuario(dni, archivoUsuarios, cantidadUsuarios);
    archivo.seekg(posUsuario*tamUsuario, ios::beg);
    
    struct Usuario usuario;
    archivo.read(reinterpret_cast<char*>(&usuario), tamUsuario);
    
    for (int i = 0; i < libro.cantUsuarios; i++) {        
        if(dni == libro.usuarios[i].dni){
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
    
    archivo.seekg(posUsuario*tamUsuario, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&usuario), tamUsuario);
    archivo.flush();
    
    archivo.seekg(posLibro*tamLibro, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&libro), tamLibro);
    archivoUsuarios.flush();
    

}
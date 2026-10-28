/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */


/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 *
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX_LINE 150
#define NO_ENCONTRADO -1
#include "UsuarioConElLibro.h"
#include "Libro.h"
#include "funciones.h"
#include "Usuario.h"

/*almacenar los datos del archivo csv a los arreglos*/
void cargarDatosLibros(struct Libro *libros,int &numLibros){   
    ifstream archLibros("Libros.csv",ios::in);
    if(not archLibros.is_open()){
        cout<<"ERROR al abrir el archivo de Libros"<<endl;
        exit(1);
    }
    char *ptr_codLibro,*ptr_titulo,*ptr_autor,c;
    int cantidadVolumenes;
    double precio;
    numLibros=0;
    /*Lectura de datos*/
    while(true){
        ptr_codLibro = leerCadenaExacta(archLibros);
        if(archLibros.eof())break;
        ptr_titulo = leerCadenaExacta(archLibros);
        ptr_autor = leerCadenaExacta(archLibros);
        archLibros>>cantidadVolumenes>>c>>precio>>c;
        libros[numLibros].codigo = ptr_codLibro;
        libros[numLibros].titulo = ptr_titulo;
        libros[numLibros].autor = ptr_autor;
        libros[numLibros].cantidad = cantidadVolumenes;
        libros[numLibros].precio = precio;
        libros[numLibros].cantUsuarios=0;
        libros[numLibros].usuarios = new struct UsuarioConElLibro[cantidadVolumenes];
        leerPrestamos(libros[numLibros],archLibros);
        numLibros++;
    }  
}
/*Modulo encargado de leer los prestamos de cada usuario*/
void leerPrestamos(struct Libro &libro,ifstream &archLibros){
    int dni,dia,mes,anio;
    char c;
    while(true){
        archLibros>>dni;
        archLibros>>c>>dia>>c>>mes>>c>>anio;
        libro.usuarios[libro.cantUsuarios].dni=dni;
        libro.usuarios[libro.cantUsuarios].fechaDeDevolucion =
                anio*10000+mes*100+dia;
        
        libro.cantUsuarios++;   
        if(archLibros.get()=='\n')break;
    }
}
/*Impresion de los datos de libros*/
void verificarDatosLibros(struct Libro *libros,int numLibros){ 
    ofstream archReporte("ArregloInicialLibros.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ArregloInicialLibros"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<setw(50)<<' '<<"Datos Iniciales de Libros"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"CODIGO LIBRO"<<setw(10)<<' '<<"TITULO"<<setw(34)<<' '
            <<"AUTOR"<<setw(35)<<' '<<"CANTIDAD VOLUMENES"<<setw(11)<<' '
            <<"PRECIO"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numLibros;i++){
        archReporte<<libros[i].codigo<<setw(15)<<' '<<left
                <<setw(40)<<libros[i].titulo<<setw(30)<<libros[i].autor<<right
                <<setw(20)<<libros[i].cantidad<<setw(25)<<libros[i].precio<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Usuarios con ejemplares: "<<libros[i].cantUsuarios<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"DNI Usuario"<<setw(10)<<' '<<"Fecha Maxima"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<libros[i].cantUsuarios;k++){
            archReporte<<libros[i].usuarios[k].dni<<setw(17)<<' '
                    <<libros[i].usuarios[k].fechaDeDevolucion<<endl;
        }
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void cargarDatosUsuarios(struct Usuario *usuarios,int &numUsuarios){   
    ifstream archUsuarios("Usuarios.csv",ios::in);
    if(not archUsuarios.is_open()){
        cout<<"ERROR al abrir el archivo de Usuarios"<<endl;
        exit(1);
    }
    int dni;
    char categoria,*ptr_nombreUsuario;
    double calificacion;
    numUsuarios=0;
    /*Lectura de datos */
    while(true){
        archUsuarios>>dni;
        if(archUsuarios.eof())break;
        archUsuarios.get();
        ptr_nombreUsuario = leerCadenaExacta(archUsuarios);
        archUsuarios>>categoria;
        archUsuarios.get();
        archUsuarios>>calificacion;
        archUsuarios.get();
        usuarios[numUsuarios].dni = dni;
        usuarios[numUsuarios].nombre = ptr_nombreUsuario;
        usuarios[numUsuarios].categoria = categoria;
        usuarios[numUsuarios].calificacion = calificacion;
        
        leerLibrosDeUsuarios(usuarios[numUsuarios],archUsuarios);
        numUsuarios++;
    }
}
/*Modulo encargado de leer los libros prestados a los usuarios*/
void leerLibrosDeUsuarios(struct Usuario &usuario,
        ifstream &archUsuarios){
    char codLibro[8],*ptr_codLibro;
    
    usuario.cantLibros =0;
    usuario.libros = new struct LibroEnSuPoder[6];
    while(true){
        archUsuarios>>codLibro;
        ptr_codLibro = new char [strlen(codLibro)+1];
        strcpy(ptr_codLibro,codLibro);
        
        usuario.libros[usuario.cantLibros].codLibro = ptr_codLibro;
        
        usuario.cantLibros++;
        if(archUsuarios.get()=='\n')break;
    }
}
/*Impresion de datos de los usuarios*/
void verificarDatosUsuarios(struct Usuario *usuarios,int numUsuarios){
    
    ofstream archReporte("ArregloInicialUsuarios.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ArregloInicialUsuarios"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<setw(50)<<' '<<"Datos Iniciales de Usuarios"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"DNI"<<setw(15)<<' '<<"Nombre"<<setw(40)<<' '<<"Categoria"
            <<setw(5)<<' '<<"Calificacion de Usuario"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numUsuarios;i++){
        archReporte<<usuarios[i].dni<<setw(10)<<' '<<left<<setw(50)
                <<usuarios[i].nombre<<usuarios[i].categoria<<right<<setw(25)
                <<usuarios[i].calificacion<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Libros que han prestado: "<<usuarios[i].cantLibros<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"Codigo de Libro"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<usuarios[i].cantLibros;k++){
            archReporte<<usuarios[i].libros[k].codLibro<<endl;
        }
        imprimeLinea('=',MAX_LINE,archReporte);
    }
    
}

void modificarArreglos(struct Libro *libros,int numLibros,
        struct Usuario *usuarios,int numUsuarios){  
    ifstream archDevoluciones("DevolucionDeLibros.txt",ios::in);
    if(not archDevoluciones.is_open()){
        cout<<"ERROR al abrir el archivo de DevolucionDeLibros"<<endl;
        exit(1);
    }
    int dni,dia,mes,anio,posLibro,posUsuario,posUsuarioEliminar,posLibroEliminar;
    char c,codLibro[8];
    int fecha;
    archDevoluciones>>dia>>c>>mes>>c>>anio;
    fecha = anio*10000+mes*100+dia;
    while(true){
        archDevoluciones>>dni;
        if(archDevoluciones.eof())break;
        archDevoluciones>>codLibro;
        /*Buscar el libro devuelto y verificarlo*/
        posLibro = buscarLibro(codLibro,libros,numLibros);
        posUsuario = buscarUsuario(dni,usuarios,numUsuarios);
        if(posLibro!=NO_ENCONTRADO and posUsuario!=NO_ENCONTRADO){
            posUsuarioEliminar = buscarUsuarioaEliminar(dni,codLibro,libros,numLibros);
            posLibroEliminar = buscarLibroEliminar(dni,codLibro,usuarios,numUsuarios);
            if(posUsuarioEliminar!=NO_ENCONTRADO and posLibroEliminar!=NO_ENCONTRADO){
                /*Verificamos si la fecha en la que se devolvio esta en el rango
                                de la fecha maxima que se le presto al usuario*/
                if(libros[posLibro].usuarios[posUsuarioEliminar].fechaDeDevolucion
                        <fecha){
                    if(usuarios[posUsuario].categoria=='D')
                        usuarios[posUsuario].calificacion-=
                                0.2*usuarios[posUsuario].calificacion;
                    else if(usuarios[posUsuario].categoria=='V')
                        usuarios[posUsuario].calificacion-=
                                0.15*usuarios[posUsuario].calificacion;
                    else if(usuarios[posUsuario].categoria=='A')
                        usuarios[posUsuario].calificacion-=
                                0.1*usuarios[posUsuario].calificacion;
                }
                libros[posLibro].usuarios[posUsuarioEliminar].dni=libros[posLibro].
                        usuarios[libros[posLibro].cantUsuarios-1].dni;
                libros[posLibro].cantUsuarios--;
                usuarios[posUsuario].libros[posLibroEliminar].codLibro=
                        usuarios[posUsuario].
                        libros[usuarios[posUsuario].cantLibros-1].codLibro;
                usuarios[posUsuario].cantLibros--;
            }
        }
    }
}

int buscarLibroEliminar(int dni,char *codLibro,struct Usuario *usuarios,
        int numUsuarios){
    for(int i=0;i<numUsuarios;i++){
        if(usuarios[i].dni == dni){
            for(int j=0;j<usuarios[i].cantLibros;j++)
                if(strcmp(usuarios[i].libros[j].codLibro,codLibro)==0)return j;
        }
    }
    return NO_ENCONTRADO;
}

int buscarUsuarioaEliminar(int dni, char *codLibro,struct Libro *libros,
        int numLibros){
    for(int i=0;i<numLibros;i++){
        if(strcmp(libros[i].codigo,codLibro)==0){
            for(int j=0;j<libros[i].cantUsuarios;j++)
                if(libros[i].usuarios[j].dni==dni)return j;
        }
    }
    return NO_ENCONTRADO;
}

int buscarUsuario(int dni,struct Usuario *usuarios,int numUsuarios){
    for(int i=0;i<numUsuarios;i++){
        if(usuarios[i].dni == dni)return i;
    }
    return NO_ENCONTRADO;
}

int buscarLibro(char *codLibro,struct Libro *libros,int numLibros){
    
    for(int i=0;i<numLibros;i++){
        if(strcmp(libros[i].codigo,codLibro)==0)return i;
    }
    return NO_ENCONTRADO;
}

void mostrarDatosFinalesLibros(struct Libro *libros,int numLibros){
    ofstream archReporte("ArregloFinalLibros.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ArregloFinalLibros"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<setw(50)<<' '<<"Datos Finales de Libros"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"CODIGO LIBRO"<<setw(10)<<' '<<"TITULO"<<setw(34)<<' '
            <<"AUTOR"<<setw(35)<<' '<<"CANTIDAD VOLUMENES"<<setw(11)<<' '
            <<"PRECIO"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numLibros;i++){
        archReporte<<libros[i].codigo<<setw(15)<<' '<<left
                <<setw(40)<<libros[i].titulo<<setw(30)<<libros[i].autor<<right
                <<setw(20)<<libros[i].cantidad<<setw(25)<<libros[i].precio<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Usuarios con ejemplares: "<<libros[i].cantUsuarios<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"DNI Usuario"<<setw(10)<<' '<<"Fecha Maxima"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<libros[i].cantUsuarios;k++){
            archReporte<<libros[i].usuarios[k].dni<<setw(17)<<' '
                    <<libros[i].usuarios[k].fechaDeDevolucion<<endl;
        }
        imprimeLinea('=',MAX_LINE,archReporte);
    }
}

void mostrarDatosFinalesUsuarios(struct Usuario *usuarios,int numUsuarios){
    ofstream archReporte("ArregloFinalUsuarios.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR al abrir el archivo de ArregloFinalUsuarios"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2);
    archReporte<<fixed;
    archReporte<<setw(50)<<' '<<"Datos Finales de Usuarios"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    archReporte<<"DNI"<<setw(15)<<' '<<"Nombre"<<setw(40)<<' '<<"Categoria"
            <<setw(5)<<' '<<"Calificacion de Usuario"<<endl;
    imprimeLinea('=',MAX_LINE,archReporte);
    for(int i=0;i<numUsuarios;i++){
        archReporte<<usuarios[i].dni<<setw(10)<<' '<<left<<setw(50)
                <<usuarios[i].nombre<<usuarios[i].categoria<<right<<setw(25)
                <<usuarios[i].calificacion<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        archReporte<<"Libros que han prestado: "<<usuarios[i].cantLibros<<endl;
        imprimeLinea('=',MAX_LINE,archReporte);
        archReporte<<"Codigo de Libro"<<endl;
        imprimeLinea('-',MAX_LINE,archReporte);
        for(int k=0;k<usuarios[i].cantLibros;k++){
            archReporte<<usuarios[i].libros[k].codLibro<<endl;
        }
        imprimeLinea('=',MAX_LINE,archReporte);
    }  
}

void imprimeLinea(char caracter, int cantidad ,ofstream &archRep){
    for(int i=0;i<cantidad;i++)archRep<<caracter;
    archRep<<endl;
}
/*Funcion leercadena que devuelve una puntero/cadena de caracteres*/
char* leerCadenaExacta(ifstream &arch){
    
    char buffer[500],*cadena;
    int longitud;
    
    arch.getline(buffer,500,',');
    if(arch.eof())return nullptr;
    
    longitud = strlen(buffer);
    
    cadena = new char [longitud+1];
    
    strcpy(cadena,buffer);
    return cadena;
}

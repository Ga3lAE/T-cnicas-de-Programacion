/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Nombre: Derik Camacho Pastor
 * Codigo: 20191163
 * Created on 3 de julio de 2023, 06:34 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void cargarDatosLibros(struct Libro *libros,int &numLibros);
void leerPrestamos(struct Libro &libro,ifstream &archLibros);
void verificarDatosLibros(struct Libro* libros, int numLibros);
void cargarDatosUsuarios(struct Usuario *usuarios,int &numUsuarios);
void leerLibrosDeUsuarios(struct Usuario &usuario,ifstream &archUsuarios);
void verificarDatosUsuarios(struct Usuario *usuarios,int numUsuarios);
void modificarArreglos(struct Libro *libros,int numLibros,
        struct Usuario *usuarios,int numUsuarios);
int buscarLibroEliminar(int dni,char *codLibro,struct Usuario *usuarios,
        int numUsuarios);
int buscarUsuarioaEliminar(int dni, char *codLibro,struct Libro *libros,
        int numLibros);
int buscarUsuario(int dni,struct Usuario *usuarios,int numUsuarios);
int buscarLibro(char *codLibro,struct Libro *libros,int numLibros);
void mostrarDatosFinalesLibros(struct Libro *libros,int numLibros);
void mostrarDatosFinalesUsuarios(struct Usuario *usuarios,int numUsuarios);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);
char* leerCadenaExacta(ifstream& arch);
#endif /* FUNCIONES_H */


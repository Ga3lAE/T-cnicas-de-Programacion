

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 14 de junio de 2023, 11:56 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerLibros(struct Libro *libros,int &numLibros);
void imprimeLibros(struct Libro *libros, int numLibros);
void leerRegistrosPrestamos(struct RegPrestamo *regPrestamos,int &numRegistros);
void asignarLibros(struct RegPrestamo &regPrestamos,ifstream &archRegistros);
void imprimeRegistrosPrestamos(struct RegPrestamo *regPrestamos,int &numRegistros);
void emiteReporteAtencionPrestamos(struct Libro *libros,int numLibros,
        struct RegPrestamo *regPrestamos,int numRegistros);
void analizaSolicitudes(int codigo,char *ptr_usuario,char *ptr_libro,int fechaLimite,int fechaProceso,
        struct Libro *libros,int numLibros,struct RegPrestamo *regPrestamos,
        int numRegistros,ofstream &archReporte);
int contarLibros(int fechaLimite, struct RegPrestamo &regPrestamos);
int buscarLibro(struct Libro *libros,char *ptr_libro,int numLibros);
int buscarUsuario(struct RegPrestamo *regPrestamos,int codigo,int numRegistros);
char *leerCadenaExacta(ifstream& archivo);

#endif /* FUNCIONES_H */


/* 
 * File:   NodoLibro.h
 * Author: arias
 *
 * Created on 13 de junio de 2025, 11:15 AM
 */

#ifndef NODOLIBRO_H
#define NODOLIBRO_H

struct NodoLibro{
    struct Libro libro;
    struct NodoLibro *siguiente;
};


#endif /* NODOLIBRO_H */


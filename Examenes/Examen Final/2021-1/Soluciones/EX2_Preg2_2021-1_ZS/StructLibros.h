

/* 
 * File:   StructLibros.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 14 de junio de 2023, 12:02 PM
 */

#ifndef STRUCTLIBROS_H
#define STRUCTLIBROS_H

struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    int aPublicacion;
    int cantidad;
    int prestamos;
};

#endif /* STRUCTLIBROS_H */


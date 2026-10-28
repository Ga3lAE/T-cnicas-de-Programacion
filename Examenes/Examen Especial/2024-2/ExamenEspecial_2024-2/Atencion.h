/* 
 * File:   Atencion.h
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:23 PM
 */

#ifndef ATENCION_H
#define ATENCION_H

#include "Plato.h"
#include "Comentario.h"

#define MAX_CANT_ATENCION_PLATOS 20
#define MAX_CANT_ATENCION_COMENTARIOS 20

struct Atencion{
    int codigo;
    struct Plato platosAtendidos[MAX_CANT_ATENCION_PLATOS];
    int cantidadPlatos;
    double totalVenta;
    int hora;
    struct Comentario comentarios[MAX_CANT_ATENCION_COMENTARIOS];
    int cantidadComentarios;
};

#endif /* ATENCION_H */


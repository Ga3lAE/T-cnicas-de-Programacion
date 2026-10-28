/* 
 * File:   Atencion.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 03:52 PM
 */

#ifndef ATENCION_H
#define ATENCION_H

#include "Plato.h"
#include "Comentario.h"

#define MAX_CANT_ATENCION_PLATOS 20
#define MAX_CANT_ATENCION_COMENTARIOS 20

struct Atencion{
    int codigo;
    struct Plato *platos_atendidos;
    int cantidad_platos;
    double total_venta;
    int hora;
    struct Comentario *comentarios;
    int cantidad_comentarios;
};

#endif /* ATENCION_H */


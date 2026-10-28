/* 
 * File:   Atencion.h
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 09:51 PM
 */

#ifndef ATENCION_H
#define ATENCION_H

#include "Comentario.h"

#define MAX_CANT_ATENCION_COMENTARIOS 20

struct Atencion{
    int codigo;
    double total_venta;
    int hora;
    struct Comentario comentarios[MAX_CANT_ATENCION_COMENTARIOS];
    int cantidad_comentarios;
    
};

#endif /* ATENCION_H */


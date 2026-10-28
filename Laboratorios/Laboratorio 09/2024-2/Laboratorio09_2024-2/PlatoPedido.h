/* 
 * File:   PlatoPedido.h
 * Author: arias
 *
 * Created on 15 de junio de 2025, 02:23 PM
 */

#ifndef PLATOPEDIDO_H
#define PLATOPEDIDO_H

struct PlatoPedido{
    int codigoPedido;
    char *codigoPlato;
    char *descripcion;
    int cantidad;
    double precio;
    double subtotal;
};

#endif /* PLATOPEDIDO_H */


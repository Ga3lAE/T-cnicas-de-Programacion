

/* 
 * File:   ProductosPedidos.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 25 de junio de 2023, 09:05 PM
 */

#ifndef PRODUCTOSPEDIDOS_H
#define PRODUCTOSPEDIDOS_H

struct ProductoSolicitado{
    char codigo[7];
    char descrpcion[60];
    int cantidad;
    double precioUnitario;
    double subTotal;
};

#endif /* PRODUCTOSPEDIDOS_H */


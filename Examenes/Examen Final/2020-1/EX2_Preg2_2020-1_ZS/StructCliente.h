

/* 
 * File:   StructCliente.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 26 de junio de 2023, 12:46 AM
 */

#ifndef STRUCTCLIENTE_H
#define STRUCTCLIENTE_H

struct Cliente{
    int numeroDeCuenta;
    char nombre[60];
    double montoInicial;
    double haber;
    double debe;
    char estado[13];
};

#endif /* STRUCTCLIENTE_H */


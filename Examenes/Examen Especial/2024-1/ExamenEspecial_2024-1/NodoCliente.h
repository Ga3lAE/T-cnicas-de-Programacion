/* 
 * File:   NodoCliente.h
 * Author: arias
 *
 * Created on 13 de junio de 2025, 10:51 AM
 */

#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H

struct NodoCliente{
    struct Cliente cliente;
    struct NodoCliente *siguiente;
};


#endif /* NODOCLIENTE_H */


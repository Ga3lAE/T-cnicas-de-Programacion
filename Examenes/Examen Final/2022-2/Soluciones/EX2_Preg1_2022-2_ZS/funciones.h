

/* 
 * File:   funciones.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 30 de junio de 2023, 09:07 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerDirecciones(struct Direccion *direcciones,int &numDirecciones);
void leerPedidos(struct Pedido* pedidos, int& numPedidos);
void registrarNuevoPedido(struct Pedido& pedido, ifstream& archPedidos);
void acumulaPedidoEncontrado(struct Pedido& pedido, ifstream& archPedidos);
void completarPedidos(struct Direccion* direcciones, int numDirecciones,
        struct Pedido* pedidos, int numPedidos);
void emiteReporte(struct Direccion *direcciones,int numDirecciones,
        struct Pedido *pedidos,int numPedidos);
void imprimeProductos(struct Pedido &pedido,ofstream &archReporte);
void imprimeLinea(char caracter, int cantidad, ofstream& archRep);
int buscarDireccion(struct Direccion *direecciones, char *ptr_codUsuario,
        int numDirecciones);
int buscarPedido(struct Pedido* pedidos, int codigo_pedido, int numPedidos);
char *leerCadenaExacta(ifstream& arch);

#endif /* FUNCIONES_H */


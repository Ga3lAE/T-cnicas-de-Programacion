

/* 
 * File:   StockProduco.h
 * Author: Derik Camacho Pastor 20191163
 *
 * Created on 23 de junio de 2023, 01:20 AM
 */

#ifndef STOCKPRODUCO_H
#define STOCKPRODUCO_H

struct StockProd{
    char codigo[7];
    char descrpcion[60];
    int stock;
    double precio;
};

#endif /* STOCKPRODUCO_H */


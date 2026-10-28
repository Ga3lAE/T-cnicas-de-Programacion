/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 12 de abril de 2025, 07:53 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesAuxliares.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int codigoDocenteMayorDeuda, codigoEstudianteMayorDeuda;
    double montoDocenteMayorDeuda, montoEstudianteMayorDeuda;
    
    leeImprimeDatos(codigoDocenteMayorDeuda, montoDocenteMayorDeuda,
            codigoEstudianteMayorDeuda, montoEstudianteMayorDeuda);
    
    imprimeResumen(codigoDocenteMayorDeuda, montoDocenteMayorDeuda,
            codigoEstudianteMayorDeuda, montoEstudianteMayorDeuda);
    
    return 0;
}


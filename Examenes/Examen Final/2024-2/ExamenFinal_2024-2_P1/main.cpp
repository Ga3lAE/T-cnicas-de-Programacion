/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 03:46 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Atencion.h"
#include "Comentario.h"
#include "Palabra.h"
#include "Plato.h"

#include "Funciones.h"

#define MAX_CANT_LEXICON 100
#define MAX_CANT_PLATOS 200
#define MAX_CANT_ATENCIONES 100

/*
 * 
 */

int main(int argc, char** argv) {
    
    struct Palabra lexicon[MAX_CANT_LEXICON]{};
    int cantidadLexicon=0;
    leeLexicon("Lexicon.csv", lexicon, cantidadLexicon);
    
    struct Plato *platos;
    int cantidadPlatos=0;
    platos = leePlatos("Platos.csv", MAX_CANT_PLATOS, cantidadPlatos);           
    
    int cantidadAtenciones=0;
    struct Atencion atenciones[MAX_CANT_ATENCIONES]{};
    leeAtenciones("Atenciones.txt", atenciones, cantidadAtenciones, 
            platos, cantidadPlatos);       
    
    leeComentarios("Comentarios.csv", 
            atenciones, cantidadAtenciones, 
            lexicon, cantidadLexicon);
    
    emitirReporte("ReporteAnalisisSentimiento.txt", 
            atenciones, cantidadAtenciones);
    
    
   
    
    return 0;
}


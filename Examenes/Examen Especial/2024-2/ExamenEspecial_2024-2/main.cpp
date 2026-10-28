/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 24 de junio de 2025, 10:18 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Atencion.h"
#include "NodoAtencion.h"
#include "Comentario.h"
#include "Funciones.h"
#include "Plato.h"
#include "NodoPlato.h"
#include "Palabra.h"
#include "NodoPalabra.h"

/*
 * 
 */

int main(int argc, char** argv) {
    
    struct NodoPalabra *listaLexicon = NULL;
    leeLexicon("Lexicon.csv", listaLexicon);
    verificaLexicon("PruebaLexicon.txt", listaLexicon);
    
    struct NodoPlato *listaPlatos = NULL;
    leePlatos("Platos.csv", listaPlatos);
    verificaPlatos("PruebaPlatos.txt", listaPlatos);
    
    struct NodoAtencion *listaAtencion = NULL;    
    leeAtenciones("Atenciones.txt", listaAtencion, listaPlatos);  
    leeComentarios("Comentarios.csv", listaAtencion, listaLexicon);

    ordenaAtenciones(listaAtencion);

    emiteReporte("ReporteAtencionesAnalisisSentimientos.txt", listaAtencion);        
    
    return 0;
}


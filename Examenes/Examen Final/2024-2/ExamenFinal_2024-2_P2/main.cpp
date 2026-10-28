/* 
 * File:   main.cpp
 * Author: arias
 *
 * Created on 25 de mayo de 2025, 09:46 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

/*
 * 
 */

int main(int argc, char** argv) {
    
    leeLexicon("Lexicon.csv", "Lexicon.bin");
    verificaLexicon("VerificacionLexicon.txt", "Lexicon.bin");
    
    leePlatos("Platos.csv", "Platos.bin");
    verificaPlatos("VerificacionPlatos.txt", "Platos.bin");
    
    leeAtenciones("Atenciones.txt", "Atenciones.bin", "Platos.bin");
    
    imprimeAtencion("ReporteInicialAtencion.txt", "Atenciones.bin");
    
    leeComentarios("Comentarios.csv", "Atenciones.bin", "Lexicon.bin");
    
    
    
    imprimeAtencion("ReporteFinalAtencion.txt", "Atenciones.bin");

    return 0;
}

